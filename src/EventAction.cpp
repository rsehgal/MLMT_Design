/*
**	Filename : EventAction.cpp
**	2025-03-05
**	username : rsehgal
*/
#include <iostream>
#include "EventAction.h"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "HitCollections.h"
#include "Muon_Hit.h"
#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "colors.h"
#include "G4AnalysisManager.hh"
#include "Global.h"
#include "Helpers.h"
#include <cmath>
EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *event)
{
  // unsigned long long tme = G4RunManager::GetRunManager()->GetTrackingManager()->GetTrack()->GetGlobalTime();
  // std::cout << RED <<"Global Time at Begin of Event : " << tme << RESET << std::endl;
  InitializeHitPointVec();
}

void EventAction::EndOfEventAction(const G4Event *event)
{
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  G4HCofThisEvent *hce = event->GetHCofThisEvent();
  G4int hcID           = G4SDManager::GetSDMpointer()->GetCollectionID("ScintillatorCrystal_MuonHits");
  MuonHitCollection *muonHitCollectionStrip = static_cast<MuonHitCollection *>(hce->GetHC(hcID));
  G4int muonHitCollStripSize                = muonHitCollectionStrip->entries();

  G4int maskHCID = G4SDManager::GetSDMpointer()->GetCollectionID("MaskingScintillatorCrystal_MuonHits");
  MuonHitCollection *muonHitcollectionMask = static_cast<MuonHitCollection *>(hce->GetHC(maskHCID));

  // std::cout << "======================================" << std::endl;
  // std::cout << "Strip Hit collection size : " << muonHitCollStripSize << std::endl;
  for (unsigned int i = 0; i < muonHitCollectionStrip->entries(); i++) {
    Muon_Hit *hitStrip = (*muonHitCollectionStrip)[i];
    // Uncomment the below line to see the hit points
    // hitStrip->Print();
    analMan->FillNtupleDColumn(1, 0, hitStrip->fLayerNum);
    analMan->FillNtupleDColumn(1, 1, hitStrip->fPlaneNum);
    analMan->FillNtupleDColumn(1, 2, hitStrip->fStripNum);
    analMan->FillNtupleDColumn(1, 3, hitStrip->fMaskNum);
    analMan->FillNtupleDColumn(1, 4, hitStrip->GetChannelNum());
    analMan->FillNtupleDColumn(1, 6, yPosVec[hitStrip->fLayerNum]);
    if (hitStrip->fPlaneNum == 0) {
      analMan->FillNtupleDColumn(1, 5, hitStrip->GetStripCenter());
      hitPointVec[hitStrip->fLayerNum].setX(hitStrip->GetStripCenter());
    } else {
      analMan->FillNtupleDColumn(1, 7, hitStrip->GetStripCenter());
      hitPointVec[hitStrip->fLayerNum].setZ(hitStrip->GetStripCenter());
    }
    momentumVec[hitStrip->fLayerNum] = hitStrip->fMomentum;
    analMan->FillNtupleDColumn(1, 8, event->GetEventID());
    analMan->AddNtupleRow(1);
  }

  // std::cout << "HitPointVec Size : " << hitPointVec.size() << std::endl;

  /*for(int i = hitPointVec.size()-1; i >= 0 ; i--){
  std::cout << "RAMAN : " << hitPointVec[i] << std::endl;
  }*/

  bool hitInAllLayers = true;

  for (int i = hitPointVec.size() - 1; i >= 0; i--) {
    hitInAllLayers &= hitPointVec[i].x() > -50000.;
    hitInAllLayers &= hitPointVec[i].y() > -50000.;
    hitInAllLayers &= hitPointVec[i].z() > -50000.;
  }

  if (hitInAllLayers) {
    // Resetting previously set tracks
    fIncomingTrack.Reset();
    fOutgoingTrack.Reset();
    fMomentumTrack.Reset();

    for (int i = hitPointVec.size() - 1; i >= 0; i--) {
      analMan->FillNtupleDColumn(2, 0, i);
      analMan->FillNtupleDColumn(2, 1, hitPointVec[i].x());
      analMan->FillNtupleDColumn(2, 2, hitPointVec[i].y());
      analMan->FillNtupleDColumn(2, 3, hitPointVec[i].z());
      analMan->FillNtupleDColumn(2, 4, event->GetEventID(

));
      analMan->AddNtupleRow(2);
    }

    // Hardcoded for incoming and outgoing track of size 2
    fIncomingTrack.SetP1(hitPointVec[5]);
    fIncomingTrack.SetP2(hitPointVec[4]);
    fOutgoingTrack.SetP1(hitPointVec[3]);
    fOutgoingTrack.SetP2(hitPointVec[2]);
    fMomentumTrack.SetP1(hitPointVec[1]);
    fMomentumTrack.SetP2(hitPointVec[0]);

    /*std::cout << "--------------------------------------" << std::endl;
    fIncomingTrack.Print();
    fOutgoingTrack.Print();*/
    double dev = fIncomingTrack.Angle(fOutgoingTrack);
    double devMomentum = fOutgoingTrack.Angle(fMomentumTrack);
   
    //Momentum calculation using Scattering method
    double momentum = 13313.6/devMomentum;
    double g4CalcMomentum = momentumVec[0].mag(); 

    //if (fIncomingTrack.Angle(fOutgoingTrack) > 0.01) 
     {
      G4ThreeVector poca = POCA(fIncomingTrack, fOutgoingTrack);
      // std::cout << "POCA : " << poca << std::endl;

      if (!std::isnan(poca.x()) && !std::isnan(poca.y()) && !std::isnan(poca.z())) {
        analMan->FillNtupleDColumn(3, 0, poca.x());
        analMan->FillNtupleDColumn(3, 1, poca.y());
        analMan->FillNtupleDColumn(3, 2, poca.z());
        analMan->FillNtupleDColumn(3, 3, dev);
        analMan->FillNtupleDColumn(3, 4, devMomentum);
        analMan->FillNtupleDColumn(3, 5, momentum);
        analMan->FillNtupleDColumn(3, 6, g4CalcMomentum);
        analMan->FillNtupleDColumn(3, 7, event->GetEventID());
        analMan->AddNtupleRow(3);
      }
    }
  }
  /* std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
   std::cout << "Masking Hit collection size : " << muonHitcollectionMask->entries() << std::endl;
   for (unsigned int i = 0; i < muonHitcollectionMask->entries(); i++) {
     Muon_Hit *hitMask = (*muonHitcollectionMask)[i];
     hitMask->Print();
   }*/
}
