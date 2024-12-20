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
         

SD::SD(const G4String detName) : G4VSensitiveDetector(detName) {}

SD::~SD() {}

void SD::Initialize(G4HCofThisEvent *hitCollection) {}

G4bool SD::ProcessHits(G4Step *step, G4TouchableHistory *history)
{
  G4Track *track        = step->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();

		std::cout << "--------------------------------------" << std::endl;
  std::cout << "Particle Name : " << particleName << " : Strip Num : " << track->GetVolume()->GetCopyNo() << std::endl;
  std::cout << "Particle Name : " << particleName << " : Envelop Num : " << track->GetTouchable()->GetVolume(1)->GetCopyNo() << " :: strip no :" << track->GetTouchable()->GetVolume()->GetCopyNo() << std::endl;
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *hitCollection) {}
