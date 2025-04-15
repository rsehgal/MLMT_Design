/*
**	Filename : SD.cpp
**	2024-12-21
**	username : rsehgal
*/

#include "SD.h"
#include <G4Track.hh>
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "colors.h"
#include <G4AnalysisManager.hh>
#include "Muon_Hit.h"
#include "Scint_Hit.h"
#include "HitCollections.h"
#include "Global.h"
SD::SD(const G4String detName) : G4VSensitiveDetector(detName) {}

SD::SD(const G4String detName, G4String collName) : G4VSensitiveDetector(detName)
{
  collectionName.insert(collName);
}

SD::~SD() {}

void SD::Initialize(G4HCofThisEvent *hitCollection)
{
  G4int hcID         = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  fMuonHitCollection = new MuonHitCollection(SensitiveDetectorName, collectionName[0]);
  hitCollection->AddHitsCollection(hcID, fMuonHitCollection);
}

G4bool SD::ProcessHits(G4Step *step, G4TouchableHistory *history)
{

  // Scint_Hit *hit = new Scint_Hit;
  // Hitt *ht = new Hitt;
  const G4StepPoint *preStepPoint = step->GetPreStepPoint();
  const G4ThreeVector exactHit = preStepPoint->GetPosition();

  G4Track *track        = step->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();

  // std::cout << "Particle Name : " << particleName << " : Strip Num : " << track->GetVolume()->GetCopyNo() <<
  // std::endl;

  if (particleName == "mu-" || particleName == "mu+") {
    // std::cout << "--------------------------------------" << std::endl;

    std::string volName = track->GetTouchable()->GetVolume()->GetName();

    int layerNum          = -1000;
    int subLayerNum       = -1000;
    int channelNum        = -1000;
    int maskNum           = -1000;
    int stripNum          = -1000;
    unsigned long long  tme         = 0;
    std::string layerType = "";
    if (volName.find("Masking") != std::string::npos) {
      layerNum    = track->GetTouchable()->GetVolume(3)->GetCopyNo();
      subLayerNum = track->GetTouchable()->GetVolume(2)->GetCopyNo();
      layerType   = "Masking";;;
    } else {
      layerNum    = track->GetTouchable()->GetVolume(4)->GetCopyNo();
      subLayerNum = track->GetTouchable()->GetVolume(3)->GetCopyNo();
    }

    G4AnalysisManager *analMan = G4AnalysisManager::Instance();

    unsigned short n = numOfGroups;//10;

    // unsigned int
    stripNum = track->GetTouchable()->GetVolume()->GetCopyNo();
    tme = track->GetGlobalTime();
    if (preStepPoint->GetStepStatus() == fGeomBoundary) {
      if (layerType == "Masking") {
        // return true;
        // unsigned int
        channelNum = layerNum * 4 * n + subLayerNum * 2 * n + n + stripNum;
        /*std::cout << RED << "Particle Name : " << particleName
       << " : Layer Number : " << layerNum // track->GetTouchable()->GetVolume(2)->GetCopyNo()
       << " : SubLayer Number : " << subLayerNum

                  << " : Bunch Num : " << stripNum << " :: Name : " << track->GetTouchable()->GetVolume()->GetName()
                  << " :: ChannelNum : " << channelNum << RESET << std::endl;
*/
        // Filling the Ntuples
        analMan->FillNtupleDColumn(0, 0, channelNum);
        analMan->FillNtupleDColumn(0, 1, track->GetGlobalTime());
        analMan->AddNtupleRow(0);

      } else {
        // unsigned int
        channelNum = layerNum * 4 * n + subLayerNum * 2 * n + stripNum;
        // unsigned int
        maskNum = track->GetTouchable()->GetVolume(1)->GetCopyNo();

        // unsigned actualChannelNum = layerNum * n * n + maskNum * n + stripNum;
        unsigned actualChannelNum = layerNum * 2 * n * n + subLayerNum * n * n + maskNum * n + stripNum;

        //Below line is good for visual comparision
	//std::cout << track->GetPosition() << std::endl;


        /*std::cout << "Particle Name : " << particleName << " : Layer Number : "
                  << layerNum // track->GetTouchable()->GetVolume(2)->GetCopyNo()
                  //<< " : Bunch Num : " << maskNum     // track->GetTouchable()->GetVolume(1)->GetCopyNo()
                  << " :: strip no :" << stripNum << " :: Name : " << track->GetTouchable()->GetVolume()->GetName()
                  << " :: EncodedChannelNum : " << channelNum << " :: ActualChannelNum : " << actualChannelNum << RESET
                  << std::endl;
*/
        // Filling the Ntuples
        analMan->FillNtupleDColumn(0, 0, channelNum);
        analMan->FillNtupleDColumn(0, 1, track->GetGlobalTime());
        analMan->AddNtupleRow(0);
      }
      // Muon_Hit *hit = new Muon_Hit(layerNum, subLayerNum, stripNum, maskNum);
      // fMuonHitCollection->insert(hit);
      fMuonHitCollection->insert(new Muon_Hit(layerNum, subLayerNum, stripNum, track->GetMomentum(),exactHit,maskNum,tme ));
      /*hit->Print();
      delete hit;*/
    }
  }
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *hitCollection) {}
