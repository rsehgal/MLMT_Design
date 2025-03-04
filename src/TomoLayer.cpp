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
  double envelopHalfXZ = envelopHalfX > envelopHalfZ ? envelopHalfX : envelopHalfZ;

  std::cout << "AYUSH : XLength : " << (2*envelopHalfX) << std::endl; 
  std::cout << "AYUSH : ZLength : " << (2*envelopHalfZ) << std::endl; 

  G4RotationMatrix *rot = new G4RotationMatrix();
  rot->rotateY(90. * deg);
  rot->rotateZ(180. * deg);

  bool checkOverlaps = true;
  fLogicalVolume     = (new Box(name, envelopHalfXZ, envelopHalfY, envelopHalfXZ))->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0, -1.* envelopHalfY / 2. + 0.5, 0), logical, "PhysicalPlaneWithMask_X", fLogicalVolume, false,
                    0, checkOverlaps);
  new G4PVPlacement(rot, G4ThreeVector(0, envelopHalfY / 2. + 0.5, 0), logical, "PhysicalPlaneWithMask_Y", fLogicalVolume,
                    false, 1, checkOverlaps);
}
