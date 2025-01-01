/*
**	Filename : TomoLayer.cpp
**	2025-01-01
**	username : rsehgal
*/
#include <iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include <iostream>
#include <G4Box.hh>
#include <G4SystemOfUnits.hh>
#include "G4PVPlacement.hh"
#include <G4RotationMatrix.hh>
#include <G4SystemOfUnits.hh>

TomoLayer::TomoLayer() {}

TomoLayer::~TomoLayer() {}

TomoLayer::TomoLayer(G4String name, unsigned int numOfScintillators, unsigned short numOfGroups)
{

  PlaneWithMask *planeWithMask = new PlaneWithMask(name, numOfScintillators, numOfGroups);
  G4LogicalVolume *logical     = planeWithMask->GetLogicalVolume();
  G4Box *solid                 = static_cast<G4Box *>(logical->GetSolid());

  double envelopHalfX = solid->GetXHalfLength() + 0.5;
  double envelopHalfY = 2 * solid->GetYHalfLength() + 1;
  double envelopHalfZ = solid->GetZHalfLength() + 0.5;

  G4RotationMatrix *rotZ = new G4RotationMatrix();
  rotZ->rotateZ(180. * deg);

  bool checkOverlaps = true;
  fLogicalVolume     = (new Box(name, envelopHalfX, envelopHalfY, envelopHalfZ))->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0, envelopHalfY / 2. + 0.5, 0), logical, "PhysicalPlane1", fLogicalVolume, false,
                    0, checkOverlaps);
  new G4PVPlacement(rotZ, G4ThreeVector(0, -1. * envelopHalfY / 2. + 0.5, 0), logical, "PhysicalPlane2", fLogicalVolume,
                    false, 1, checkOverlaps);
}
