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

void SD::Initialize(G4HCofThisEvent *hce)
{
  fPhotonCounter_LPMT = 0;
  fPhotonCounter_RPMT = 0;
}

G4bool SD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{

  G4Track *track        = aStep->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();
  /*
  ** The condition of stepLength != 0 represent reflected particle,
  ** more precisely reflected optical photon from the boundary
  ** so it volume next to the reflecting surface will not be
  ** registered.
  */
  if (track->GetTouchable()->GetVolume()->GetName() == "PhysicalSupportPlane" && aStep->GetStepLength() != 0) {
    std::cout << "TrackID : " << track->GetTrackID() << " : ParticleName : " << particleName
              << " : VolumeName : " << track->GetTouchable()->GetVolume()->GetName()
              << " : Material : " << track->GetTouchable()->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName()
              << " : CopyNum : " << track->GetTouchable()->GetCopyNumber() << std::endl;
  }
  if (track->GetTouchable()->GetVolume()->GetName() == "PhysicalPMT" && aStep->GetStepLength() == 0) {
    if(track->GetTouchable()->GetCopyNumber()==0)
    fPhotonCounter_LPMT++;

    if(track->GetTouchable()->GetCopyNumber()==1)
    fPhotonCounter_RPMT++;

    track->SetTrackStatus(fStopAndKill);
  }
  return true;
}

void SD::EndOfEvent(G4HCofThisEvent *)
{
  std::cout << "No of Photon reaching Left PMT : " << fPhotonCounter_LPMT << std::endl;
  std::cout << "No of Photon reaching Right PMT : " << fPhotonCounter_RPMT << std::endl;
}
