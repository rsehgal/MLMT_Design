#include "PrimaryGeneratorAction.h"

#include "G4Box.hh"
#include "G4Electron.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <G4IonTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
//#include "RadioactiveSource.h"
#include <G4Geantino.hh>
#include "CLHEP/Random/RandFlat.h"
#include "Global.h"

#ifdef USE_CRY
#include "CryInterface.h"
#endif
PrimaryGeneratorAction::PrimaryGeneratorAction() {
  // Default place holders
  fParticleGun = new G4ParticleGun(1);
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  G4ThreeVector pos(-90. * cm, 0., 0.);
  G4ThreeVector mom(1., 0., 0.);
  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(0. * GeV);
  fParticleGun->SetParticleDefinition(particle);

#ifdef USE_CRY
  cryInterface = new CryInterface();
#endif

}
PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event) {

  // std::cout << "INSIDE GENERATE PRIMARIESSS..........." << std::endl;
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  // If particle gun is NOT set from the macro then it will use the default
  // Cs137 as particle gun

  if (particle == G4Geantino::Geantino()) {
    std::cout << "@@@@ Changed particle from geantino to required ion @@@@" << std::endl;

    double charge = 0. * eplus;
    double energy = 0. * keV;
    // Creating Cs137 source
    // G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(55, 137, energy);
    // Creating Na22 source
    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(11, 22, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
  }

  double randX1 = CLHEP::RandFlat::shoot(-500.,500.);
  double randZ1 = CLHEP::RandFlat::shoot(-500.,500.);
  double randX2 = CLHEP::RandFlat::shoot(-500.,500.);
  double randZ2 = CLHEP::RandFlat::shoot(-500.,500.);

  //Used for unidirection muon beam
  //G4ThreeVector startPoint(0.,yPosVec[3]+100,0.);
  double ypos = gunPos;//150*cm;
  //G4ThreeVector startPoint(randX1,yPosVec[3]+100,randZ1);
  G4ThreeVector startPoint(randX1,ypos,randZ1);
  G4ThreeVector endPoint = startPoint; //(-50000,-50000,-50000);
  //endPoint.setY(yPosVec[0]-100);
  endPoint.setY(-1.*ypos);

  G4ThreeVector dir;

#ifdef USE_CRY
  Muon *muon                = cryInterface->SampleMuon();
  dir.set(muon->angleX,muon->angleY,muon->angleZ);
  fParticleGun->SetParticleEnergy(muon->energy);
#else

  fParticleGun->SetParticleEnergy(2*GeV);
#define RANDOM_DIRECTION
#ifdef RANDOM_DIRECTION
  //endPoint.set(randX2,yPosVec[0]-100,randZ2);
  endPoint.set(randX2,-1.*ypos,randZ2);
  dir = endPoint-startPoint;
#else
  dir = endPoint-startPoint;
#endif

//  fParticleGun->SetParticleEnergy(2*GeV);
#endif
  //G4ThreeVector endPoint(randX2,yPosVec[0]-100,randZ2);

  //G4ThreeVector dir = endPoint-startPoint;
  G4ThreeVector unitDir = dir.unit();

  fParticleGun->SetParticlePosition(startPoint);
  fParticleGun->SetParticleMomentumDirection(unitDir);

  fParticleGun->GeneratePrimaryVertex(event);
}
