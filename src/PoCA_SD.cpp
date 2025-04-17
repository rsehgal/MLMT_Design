#include "PoCA_SD.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include <iostream>
#include "PoCA_Hit.h"
PoCA_SD::PoCA_SD(const G4String &name, const G4String &collName) : G4VSensitiveDetector(name)
{
  collectionName.insert(collName);
}

PoCA_SD::~PoCA_SD() {}

void PoCA_SD::Initialize(G4HCofThisEvent *hce)
{
  fPoCAHitCollection = new PoCAHitCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID         = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fPoCAHitCollection);
}

G4bool PoCA_SD::ProcessHits(G4Step *step, G4TouchableHistory *)
{
  /*G4Track *track  = step->GetTrack();
  G4double energy = track->GetKineticEnergy();
  G4cout << "Detected energy: " << energy / MeV << " MeV" << G4endl;*/

  G4StepPoint *preStepPoint = step->GetPreStepPoint();
  G4ThreeVector dir         = preStepPoint->GetMomentumDirection();
  G4ThreeVector pos         = preStepPoint->GetPosition();
  if (0) {
    G4ThreeVector ref(0., -1., 0.);
    std::cout << "Step Direction : " << dir << " : Angle : " << ref.angle(dir) << std::endl;
  }

  PoCA_Hit *newHit = new PoCA_Hit(dir, pos);
  fPoCAHitCollection->insert(newHit);

  return true;
}

void PoCA_SD::EndOfEvent(G4HCofThisEvent *hce)
{
/*
  //Working
  for (unsigned int i = 0; i < fPoCAHitCollection->entries(); i++) {
    // std::cout <<
    (*fPoCAHitCollection)[i]->Print();
  }
*/
}
