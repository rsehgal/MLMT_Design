/*
**	Filename : ScintillatorDetector.cpp
**	2024-02-13
**	username : rsehgal
*/
#include <iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "SD.h"
#include "G4SDManager.hh"

ScintillatorDetector::ScintillatorDetector() {}

ScintillatorDetector::~ScintillatorDetector() {}

ScintillatorDetector::ScintillatorDetector(G4String name, double scintHalfX, double scintHalfY, double scintHalfZ,
                                           double pmtRmin, double pmtRmax, double pmtDz, G4String scintillatorMaterial,
                                           G4String pmtMaterial)
    : fScintHalfX(scintHalfX), fScintHalfY(scintHalfY), fScintHalfZ(scintHalfZ), fPmtRmin(pmtRmin), fPmtRmax(pmtRmax),
      fPmtDz(pmtDz)
{
  fScintillatorEnvelopeHalfX = fScintHalfX;
  fScintillatorEnvelopeHalfY = fScintHalfY;
  fScintillatorEnvelopeHalfZ = fScintHalfZ + (2 * fPmtDz);

  fLogicalVolume = (new Box("ScintillatorEnvelope", fScintillatorEnvelopeHalfX, fScintillatorEnvelopeHalfY,
                            fScintillatorEnvelopeHalfZ))
                       ->GetLogicalVolume();

  G4LogicalVolume *logicalScintillator =
      (new Scintillator("Scintillator", fScintHalfX, fScintHalfY, fScintHalfZ, "ICNSE_PS"))->GetLogicalVolume();

  G4LogicalVolume *logicalPMT = (new PMT("PMT", fPmtRmin, fPmtRmax, fPmtDz))->GetLogicalVolume();

  bool checkOverlaps = true;
  new G4PVPlacement(0,                      // no rotation
                    G4ThreeVector(),        // at (0,0,0)
                    logicalScintillator,    // its logical volume
                    "PhysicalScintillator", // its name
                    fLogicalVolume,         // its mother  volume
                    false,                  // no boolean operation
                    0,                      // copy number
                    checkOverlaps);
  new G4PVPlacement(0,                                           // no rotation
                    G4ThreeVector(0., 0., fScintHalfZ + fPmtDz), //
                    logicalPMT,                                  // its logical volume
                    "PhysicalPMT",                               // its name
                    fLogicalVolume,                              // its mother  volume
                    false,                                       // no boolean operation
                    0,                                           // copy number
                    checkOverlaps);
  new G4PVPlacement(0,                                                   // no rotation
                    G4ThreeVector(0., 0., -1. * (fScintHalfZ + fPmtDz)), //
                    logicalPMT,                                          // its logical volume
                    "PhysicalPMT",                                       // its name
                    fLogicalVolume,                                      // its mother  volume
                    false,                                               // no boolean operation
                    1,                                                   // copy number
                    checkOverlaps);

  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  SD *scintSD         = new SD("ScintillatorDetector",this);
  fSDMan->AddNewDetector(scintSD);
  fLogicalVolume->SetSensitiveDetector(scintSD);
}
