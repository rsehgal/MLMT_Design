
#include "DetectorConstruction.h"
#include "PrimaryGeneratorAction.h"
#include "Run.h"
#include "RunAction.h"

#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include <G4FastStep.hh>
#include <string.h>
// #include "B1EventAction.hh"
// #include "Helpers.h"
// #include "SD.h"
#include <G4VUserDetectorConstruction.hh>
#include <TFile.h>

#include <G4AnalysisManager.hh>

using namespace std;

RunAction::RunAction() : G4UserRunAction() { fGlobalRunningTime = 0; }

RunAction::~RunAction() {}

G4Run *RunAction::GenerateRun() { return new Run; }

void RunAction::BeginOfRunAction(const G4Run *) {
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  const DetectorConstruction *userDetectorConstruction =
      static_cast<const DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4LogicalVolume *logicalWorld = userDetectorConstruction->GetLogicalWorld();
  std::cout << "@@@@@@@@@@@@@ Weight of Complete Detector @@@@@@@@@@@@" << std::endl;
  // std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

  // Opening a ROOT file and creating a ROOT TTree using Ntuple
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();
  analMan->OpenFile("out.root");

  // Tree ID 0
  analMan->CreateNtuple("ftree", "A simple TTree");
  analMan->CreateNtupleDColumn("channelNum");
  analMan->CreateNtupleDColumn("tstamp");
  analMan->FinishNtuple();

  // Tree ID 1
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

  // Tree ID 2
  analMan->CreateNtuple("ReconsMuonHits", "A Reconstructed MuonHit TTree");
  analMan->CreateNtupleDColumn("layerNum");
  analMan->CreateNtupleDColumn("x");
  analMan->CreateNtupleDColumn("y");
  analMan->CreateNtupleDColumn("z");
  analMan->CreateNtupleDColumn("stripNumX");
  analMan->CreateNtupleDColumn("stripNumZ");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->FinishNtuple();

  // Tree ID 3
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
  // Tree ID 4
  analMan->CreateNtuple("mlData", "A TTree with data for ML");
  analMan->CreateNtupleDColumn("x1Center");
  analMan->CreateNtupleDColumn("y1Center");
  analMan->CreateNtupleDColumn("z1Center");
  analMan->CreateNtupleDColumn("x2Center");
  analMan->CreateNtupleDColumn("y2Center");
  analMan->CreateNtupleDColumn("z2Center");
  analMan->CreateNtupleDColumn("x3Center");
  analMan->CreateNtupleDColumn("y3Center");
  analMan->CreateNtupleDColumn("z3Center");
  analMan->CreateNtupleDColumn("x4Center");
  analMan->CreateNtupleDColumn("y4Center");
  analMan->CreateNtupleDColumn("z4Center");
  analMan->CreateNtupleDColumn("x5Center");
  analMan->CreateNtupleDColumn("y5Center");
  analMan->CreateNtupleDColumn("z5Center");
  analMan->CreateNtupleDColumn("x6Center");
  analMan->CreateNtupleDColumn("y6Center");
  analMan->CreateNtupleDColumn("z6Center");
  // analMan->CreateNtupleDColumn("angleIncoming");
  // analMan->CreateNtupleDColumn("angleOutgoing");
  analMan->CreateNtupleDColumn("devTarget");
  analMan->CreateNtupleDColumn("devMomentum");
  analMan->CreateNtupleDColumn("pathLength");
  analMan->CreateNtupleDColumn("myMomentum");
  analMan->CreateNtupleDColumn("pocaXCenter");
  analMan->CreateNtupleDColumn("pocaYCenter");
  analMan->CreateNtupleDColumn("pocaZCenter");

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
  analMan->CreateNtupleDColumn("x5Randomize");
  analMan->CreateNtupleDColumn("y5Randomize");
  analMan->CreateNtupleDColumn("z5Randomize");
  analMan->CreateNtupleDColumn("x6Randomize");
  analMan->CreateNtupleDColumn("y6Randomize");
  analMan->CreateNtupleDColumn("z6Randomize");
  // analMan->CreateNtupleDColumn("angleIncomingRandomize");
  // analMan->CreateNtupleDColumn("angleOutgoingRandomize");
  analMan->CreateNtupleDColumn("devTargetRandomize");
  analMan->CreateNtupleDColumn("devMomentumRandomize");
  analMan->CreateNtupleDColumn("pathLengthRandomize");
  analMan->CreateNtupleDColumn("myMomentumRandomize");
  analMan->CreateNtupleDColumn("pocaXRandomize");
  analMan->CreateNtupleDColumn("pocaYRandomize");
  analMan->CreateNtupleDColumn("pocaZRandomize");

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
  analMan->CreateNtupleDColumn("x5Exact");
  analMan->CreateNtupleDColumn("y5Exact");
  analMan->CreateNtupleDColumn("z5Exact");
  analMan->CreateNtupleDColumn("x6Exact");
  analMan->CreateNtupleDColumn("y6Exact");
  analMan->CreateNtupleDColumn("z6Exact");
  // analMan->CreateNtupleDColumn("angleIncomingExact");
  // analMan->CreateNtupleDColumn("angleOutgoingExact");
  analMan->CreateNtupleDColumn("devTargetExact");
  analMan->CreateNtupleDColumn("devMomentumExact");
  analMan->CreateNtupleDColumn("pathLengthExact");
  analMan->CreateNtupleDColumn("myMomentumExact");
  analMan->CreateNtupleDColumn("pocaXExact");
  analMan->CreateNtupleDColumn("pocaYExact");
  analMan->CreateNtupleDColumn("pocaZExact");

  analMan->CreateNtupleDColumn("g4Momentum");
  analMan->CreateNtupleDColumn("eventNum");
  analMan->FinishNtuple();

  // Tree ID 5
  analMan->CreateNtuple("groundTruthPoCA", "Tree that contain true PoCA from step");
  analMan->CreateNtupleDColumn("inX");
  analMan->CreateNtupleDColumn("inY");
  analMan->CreateNtupleDColumn("inZ");
  analMan->CreateNtupleDColumn("dInX");
  analMan->CreateNtupleDColumn("dInY");
  analMan->CreateNtupleDColumn("dInZ");
  analMan->CreateNtupleDColumn("outX");
  analMan->CreateNtupleDColumn("outY");
  analMan->CreateNtupleDColumn("outZ");
  analMan->CreateNtupleDColumn("dOutX");
  analMan->CreateNtupleDColumn("dOutY");
  analMan->CreateNtupleDColumn("dOutZ");
  analMan->CreateNtupleDColumn("pocaX");
  analMan->CreateNtupleDColumn("pocaY");
  analMan->CreateNtupleDColumn("pocaZ");
  analMan->CreateNtupleDColumn("angleDev");
  analMan->CreateNtupleDColumn("pX");
  analMan->CreateNtupleDColumn("pY");
  analMan->CreateNtupleDColumn("pZ");

  analMan->FinishNtuple();
#endif

  std::cout << "RAMAN : Tree structure created..." << std::endl;
  // TTree structure created
}

void RunAction::EndOfRunAction(const G4Run *run) {
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0)
    return;
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  // Writing and closing the ROOT File
  analMan->Write();
  analMan->CloseFile();
  std::cout << "SEHGAL : Closing the ROOT file........." << std::endl;
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
