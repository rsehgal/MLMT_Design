#include "SDBasic.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"
#include "AnalysisT.h"
#include "DataBasic.h"
#include "G4VPhysicalVolume.hh"

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
    G4VPhysicalVolume *volume = point1->GetPhysicalVolume();
    if(volume->GetName()=="PhysicalPlane"){
    //std::cout << point1->GetPosition() << std::endl;
    G4ThreeVector prepos = point1->GetPosition();
    G4ThreeVector postpos = point2->GetPosition();
    
    if(track->GetGlobalTime())
    std::cout << "PrePost : " << prepos << " : PostPos : " << postpos << " : GlobalTime : " << track->GetGlobalTime() << std::endl;
    AnalysisT<DataBasic>::Instance()->GetData()->Fill(prepos.x(),prepos.y(),prepos.z(),track->GetGlobalTime());
    }
  }
}

void SDBasic::EndOfEvent(G4HCofThisEvent *) {}