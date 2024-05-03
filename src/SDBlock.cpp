/*
 * SDBlock.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: rsehgal
 */

#include "SDBlock.h"
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
#include "Geometry.h"
#include "Data.h"
#include "DetectorData.h"
#include "AnalysisBlock.h"
#include "DataBlock.h"
SDBlock::~SDBlock()
{
  // TODO Auto-generated destructor stub
  // delete fp;
}

SDBlock::SDBlock(const G4String &name) : G4VSensitiveDetector(name), fDetName(name){
  fDataBlock = new DataBlock; //::Instance()->GetData();//new DataBlock;
}

void SDBlock::Initialize(G4HCofThisEvent *hce)
{
fDataBlock->Reset();
}

G4bool SDBlock::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  G4Track *track        = aStep->GetTrack();
  if (track->GetTouchable()->GetVolume()->GetName() == "PhysicalPMT" && aStep->GetStepLength() == 0) {
    // if (track->GetTouchable()->GetCopyNumber() == 0) fPhotonCounter_LPMT++;
    // if (track->GetTouchable()->GetCopyNumber() == 1) fPhotonCounter_RPMT++;

    if (track->GetTouchable()->GetVolume()->GetName() == "PhysicalPMT" && aStep->GetStepLength() == 0) {
      
        if (track->GetTouchable()->GetCopyNumber() == 0) 
          fDataBlock->fQNorth++;
          if (track->GetTouchable()->GetCopyNumber() == 1) 
          fDataBlock->fQSouth++;
          if (track->GetTouchable()->GetCopyNumber() == 2) 
          fDataBlock->fQEast++;
          if (track->GetTouchable()->GetCopyNumber() == 3) 
          fDataBlock->fQWest++;
        
          track->SetTrackStatus(fStopAndKill);
      
    }

  return true;
}
}

void SDBlock::EndOfEvent(G4HCofThisEvent *)
{
  //fDataBlock->Print();
  AnalysisBlock::Instance()->GetData()->Fill(0,fDataBlock->fQNorth,fDataBlock->fQSouth,fDataBlock->fQEast,fDataBlock->fQWest);
}
