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
  fParticleGun->GeneratePrimaryVertex(event);
}
