/*
**	Filename : ScintillatorPlane.cpp
**	2024-02-15
**	username : rsehgal
*/
#include <iostream>
#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <algorithm>
#include "Geometry.h"
#include <G4RotationMatrix.hh>
#include <G4SystemOfUnits.hh>
#include <G4AssemblyVolume.hh>
#include "G4PVPlacement.hh"
ScintillatorPlane::ScintillatorPlane()
{
  bool checkOverlaps             = true;
  ScintillatorDetector *scintDet = (new ScintillatorDetector("CompleteScintillatorDetector", 1.5 * cm, 1.5 * cm, 50. * cm,
                                                             0. * cm, 1.27 * cm, 1. * cm, "ICNSE_PS", "G4_Galactic"));
  G4LogicalVolume *supportPlane  = (new SupportPlane(33, 0.1 * cm, scintDet))->GetLogicalVolume();

  G4Box *supportBox = static_cast<G4Box *>(supportPlane->GetSolid());
  double planeHalfX = supportBox->GetXHalfLength();
  double planeHalfY = supportBox->GetYHalfLength();
  double planeHalfZ = supportBox->GetZHalfLength();

  double planeHalfXZ = std::max(planeHalfX, planeHalfZ);
  fLogicalVolume     = (new Box("ScintillatorPlane", planeHalfXZ, 2 * planeHalfY, planeHalfXZ))->GetLogicalVolume();

  G4RotationMatrix *rotation = new G4RotationMatrix();
  rotation->rotateY(90.0 * deg);
  new G4PVPlacement(0,                                       // no rotation
                    G4ThreeVector(0., -1. * planeHalfY, 0.), //
                    supportPlane,                            // its logical volume
                    "PhysicalSupportPlane",                  // its name
                    fLogicalVolume,                          // its mother  volume
                    false,                                   // no boolean operation
                    0,                                       // copy number
                    checkOverlaps);

  new G4PVPlacement(rotation,                          // rotation by 90 degree
                    G4ThreeVector(0., planeHalfY, 0.), //
                    supportPlane,                      // its logical volume
                    "PhysicalSupportPlane",            // its name
                    fLogicalVolume,                    // its mother  volume
                    false,                             // no boolean operation
                    1,                                 // copy number
                    checkOverlaps);
}

ScintillatorPlane::~ScintillatorPlane() {}
