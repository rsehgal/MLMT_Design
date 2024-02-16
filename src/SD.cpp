/*
 * SD.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "SD.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
//#include "Helpers.h"
#include <G4EventManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VProcess.hh>
#include <TFile.h>
#include <TH1F.h>
#include <algorithm>

SD::~SD()
{
  // TODO Auto-generated destructor stub
  // delete fp;
}

SD::SD(const G4String &name) : G4VSensitiveDetector(name) {}

void SD::Initialize(G4HCofThisEvent *hce) {}

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{

  G4Track *track        = aStep->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();
  std::cout << "VolumeName : " << track->GetTouchable()->GetVolume(1)->GetName()
            << " : CopyNum : " << track->GetTouchable()->GetCopyNumber(1) << std::endl;
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *) {}
