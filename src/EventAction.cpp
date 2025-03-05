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

EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *event) {
//unsigned long long tme = G4RunManager::GetRunManager()->GetTrackingManager()->GetTrack()->GetGlobalTime();
//std::cout << RED <<"Global Time at Begin of Event : " << tme << RESET << std::endl;
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

  std::cout << "======================================" << std::endl;
  std::cout << "Strip Hit collection size : " << muonHitCollStripSize << std::endl;
  for (unsigned int i = 0; i < muonHitCollectionStrip->entries(); i++) {
    Muon_Hit *hitStrip = (*muonHitCollectionStrip)[i];
    hitStrip->Print();
    analMan->FillNtupleDColumn(1,0,hitStrip->fLayerNum); 
    analMan->FillNtupleDColumn(1,1,hitStrip->fPlaneNum); 
    analMan->FillNtupleDColumn(1,2,hitStrip->fStripNum); 
    analMan->FillNtupleDColumn(1,3,hitStrip->fMaskNum); 
    analMan->FillNtupleDColumn(1,4,hitStrip->GetChannelNum()); 
    analMan->FillNtupleDColumn(1,6,yPosVec[hitStrip->fLayerNum]); 
    if(hitStrip->fPlaneNum==0)
    analMan->FillNtupleDColumn(1,5,hitStrip->GetStripCenter()); 
    else
    analMan->FillNtupleDColumn(1,7,hitStrip->GetStripCenter()); 
    analMan->FillNtupleDColumn(1,8,event->GetEventID());
    analMan->AddNtupleRow(1); 
  }

  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "Masking Hit collection size : " << muonHitcollectionMask->entries() << std::endl;
  for (unsigned int i = 0; i < muonHitcollectionMask->entries(); i++) {
    Muon_Hit *hitMask = (*muonHitcollectionMask)[i];
    hitMask->Print();
  }
 
}
