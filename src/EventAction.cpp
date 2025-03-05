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
EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *event) {}

void EventAction::EndOfEventAction(const G4Event *event)
{
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
  }

  std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "Masking Hit collection size : " << muonHitcollectionMask->entries() << std::endl;
  for (unsigned int i = 0; i < muonHitcollectionMask->entries(); i++) {
    Muon_Hit *hitMask = (*muonHitcollectionMask)[i];
    hitMask->Print();
  }
}
