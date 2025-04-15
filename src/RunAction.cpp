
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

#include <G4AnalysisManager.hh>

using namespace std;

RunAction::RunAction() : G4UserRunAction() {
fGlobalRunningTime = 0;
}

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

  //Opening a ROOT file and creating a ROOT TTree using Ntuple
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("out.root");

  //Tree ID 0
  analMan->CreateNtuple("ftree", "A simple TTree");
  analMan->CreateNtupleDColumn("channelNum");
  analMan->CreateNtupleDColumn("tstamp");
  analMan->FinishNtuple();

  //Tree ID 1 
  analMan->CreateNtuple("MuonHits", "A MuonHit TTree");
  analMan->CreateNtupleDColumn("layerNum");
  analMan->CreateNtupleDColumn("planeNum");
  analMan->CreateNtupleDColumn("stripNum");
  analMan->CreateNtupleDColumn("maskNum");
  analMan->CreateNtupleDColumn("channelNum");
  analMan->CreateNtupleDColumn("x");
  analMan->CreateNtupleDColumn("y");
  analMan->CreateNtupleDColumn("z");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->FinishNtuple();

  //Tree ID 2
  analMan->CreateNtuple("ReconsMuonHits", "A Reconstructed MuonHit TTree");
  analMan->CreateNtupleDColumn("layerNum");
  analMan->CreateNtupleDColumn("x");
  analMan->CreateNtupleDColumn("y");
  analMan->CreateNtupleDColumn("z");
  analMan->CreateNtupleDColumn("stripNumX");
  analMan->CreateNtupleDColumn("stripNumZ");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->FinishNtuple();

  //Tree ID 3
  analMan->CreateNtuple("pocaTree", "A reconstructed PoCA points TTree");
  analMan->CreateNtupleDColumn("x");
  analMan->CreateNtupleDColumn("y");
  analMan->CreateNtupleDColumn("z");
  analMan->CreateNtupleDColumn("dev");
  analMan->CreateNtupleDColumn("angleMomentumIncoming");
  analMan->CreateNtupleDColumn("angleMomentumOutgoing");
  analMan->CreateNtupleDColumn("pathLength_FromHitPoint");
  analMan->CreateNtupleDColumn("pathLength_FromScattering");
  analMan->CreateNtupleDColumn("devMomentum");
  analMan->CreateNtupleDColumn("momentum");
  analMan->CreateNtupleDColumn("momentum_pl");
  analMan->CreateNtupleDColumn("g4Momentum");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->FinishNtuple();

#ifdef ML_TREE
  analMan->CreateNtuple("mlData", "A TTree with data for ML");
  analMan->CreateNtupleDColumn("x1");
  analMan->CreateNtupleDColumn("y1");
  analMan->CreateNtupleDColumn("z1");
  analMan->CreateNtupleDColumn("x2");
  analMan->CreateNtupleDColumn("y2");
  analMan->CreateNtupleDColumn("z2");
  analMan->CreateNtupleDColumn("x3");
  analMan->CreateNtupleDColumn("y3");
  analMan->CreateNtupleDColumn("z3");
  analMan->CreateNtupleDColumn("x4");
  analMan->CreateNtupleDColumn("y4");
  analMan->CreateNtupleDColumn("z4");

  analMan->CreateNtupleDColumn("x1Randomize");
  analMan->CreateNtupleDColumn("y1Randomize");
  analMan->CreateNtupleDColumn("z1Randomize");
  analMan->CreateNtupleDColumn("x2Randomize");
  analMan->CreateNtupleDColumn("y2Randomize");
  analMan->CreateNtupleDColumn("z2Randomize");
  analMan->CreateNtupleDColumn("x3Randomize");
  analMan->CreateNtupleDColumn("y3Randomize");
  analMan->CreateNtupleDColumn("z3Randomize");
  analMan->CreateNtupleDColumn("x4Randomize");
  analMan->CreateNtupleDColumn("y4Randomize");
  analMan->CreateNtupleDColumn("z4Randomize");
  analMan->CreateNtupleDColumn("devRandomize");

  analMan->CreateNtupleDColumn("x1Exact");
  analMan->CreateNtupleDColumn("y1Exact");
  analMan->CreateNtupleDColumn("z1Exact");
  analMan->CreateNtupleDColumn("x2Exact");
  analMan->CreateNtupleDColumn("y2Exact");
  analMan->CreateNtupleDColumn("z2Exact");
  analMan->CreateNtupleDColumn("x3Exact");
  analMan->CreateNtupleDColumn("y3Exact");
  analMan->CreateNtupleDColumn("z3Exact");
  analMan->CreateNtupleDColumn("x4Exact");
  analMan->CreateNtupleDColumn("y4Exact");
  analMan->CreateNtupleDColumn("z4Exact");
  analMan->CreateNtupleDColumn("devExact");



  analMan->CreateNtupleDColumn("pathLength");
  analMan->CreateNtupleDColumn("angleIncoming");
  analMan->CreateNtupleDColumn("angleOutgoing");
  analMan->CreateNtupleDColumn("deviation");
  analMan->CreateNtupleDColumn("myMomentum");
  analMan->CreateNtupleDColumn("g4Momentum");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->CreateNtupleDColumn("reconsX");
  analMan->CreateNtupleDColumn("reconsY");
  analMan->CreateNtupleDColumn("reconsZ");
  analMan->FinishNtuple();
#endif

  std::cout <<"RAMAN : Tree structure created..." << std::endl;
  //TTree structure created
}

void RunAction::EndOfRunAction(const G4Run *run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  //Writing and closing the ROOT File
  analMan->Write();
  analMan->CloseFile();
  std::cout <<"SEHGAL : Closing the ROOT file........." << std::endl;
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
