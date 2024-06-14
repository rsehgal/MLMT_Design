#include "SDBasic.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"
#include "AnalysisT.h"
#include "DataBasic.h"

SDBasic::SDBasic(G4String name) : G4VSensitiveDetector(name), fDetName(name)
{
  //std::cout << "RAMAN : Constructor of SDBasic Called.... " << std::endl;
}

SDBasic::~SDBasic() {}

void SDBasic::Initialize(G4HCofThisEvent *hce)
{
  //std::cout << "RAMAN : Initialize of SDBasic Called.... " << std::endl;
}
G4bool SDBasic::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
  //std::cout << "RAMAN : Entered processed HITs for SD BASIC" << std::endl;
  G4StepPoint *point1   = aStep->GetPreStepPoint();
  G4StepPoint *point2   = aStep->GetPostStepPoint();
  G4Track *track        = aStep->GetTrack();
  G4String particleName = track->GetDefinition()->GetParticleName();
  bool isPrimary        = (track->GetParentID() == 0);
  if (isPrimary && point1->GetStepStatus() == fGeomBoundary) {
    //std::cout << point1->GetPosition() << std::endl;
    G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();
    std::cout << "Pos : " << pos << std::endl;
    AnalysisT<DataBasic>::Instance()->GetData()->Fill(pos.x(),pos.y(),pos.z(),track->GetGlobalTime());
  }
}

void SDBasic::EndOfEvent(G4HCofThisEvent *) {}