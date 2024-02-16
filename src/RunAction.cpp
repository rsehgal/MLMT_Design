
#include "RunAction.h"
#include "DetectorConstruction.h"
#include "PrimaryGeneratorAction.h"
#include "Run.h"

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <G4FastStep.hh>
#include <string.h>
//#include "B1EventAction.hh"
//#include "Helpers.h"
//#include "SD.h"
#include <G4VUserDetectorConstruction.hh>
#include <TFile.h>
using namespace std;

RunAction::RunAction() : G4UserRunAction() {}

RunAction::~RunAction() {}

G4Run *RunAction::GenerateRun()
{
  return new Run;
}

void RunAction::BeginOfRunAction(const G4Run *)
{
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  const DetectorConstruction *userDetectorConstruction =
      static_cast<const DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4LogicalVolume *logicalWorld = userDetectorConstruction->GetLogicalWorld();
  std::cout << "@@@@@@@@@@@@@ Weight of Complete Detector @@@@@@@@@@@@" << std::endl;
  // std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
}

void RunAction::EndOfRunAction(const G4Run *run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  /*PrintSummary("SensitiveHollowSpace",nofEvents);
  fOutFile->cd();
  Write();
  fOutFile->Close();
  */

  // WriteSD("BoratedPolyEthylene");
  // WriteSD("SensitiveHollowSpace");
  /*for (unsigned int i = 0; i < SD::fVecOfSD.size(); i++) {
    WriteSD(SD::fVecOfSD[i]);
  }*/
}
