/*
 *	Filename : BoxShell.cpp
 **	2024-01-02
 **	username : rsehgal
 */
#include "Geometry.h"
#include <G4Box.hh>
#include <G4SubtractionSolid.hh>

// BoxShell::BoxShell() {}
BoxShell::~BoxShell() {}

BoxShell::BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness, G4String material)
    : // G4CSGSolid(name),
      fHalfX(halfx), fHalfY(halfy), fHalfZ(halfz), fThickness(thickness) {
  G4Box *outerBox = new G4Box("OuterBox", fHalfX, fHalfY, fHalfZ);
  G4Box *innerBox = new G4Box("InnerBox", fHalfX - fThickness, fHalfY - fThickness, fHalfZ - fThickness);
  fSolid = new G4SubtractionSolid(name, outerBox, innerBox, 0, G4ThreeVector(0., 0., 0.));

  // Keeping it simple, with no rotation on inner box
  fSolid = new G4SubtractionSolid(name, outerBox, innerBox);
  SetProperties(material, fSolid);
}

BoxShell::BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness, G4Material *material)
    : // G4CSGSolid(name),
      fHalfX(halfx), fHalfY(halfy), fHalfZ(halfz), fThickness(thickness) {
  G4Box *outerBox = new G4Box("OuterBox", fHalfX, fHalfY, fHalfZ);
  G4Box *innerBox = new G4Box("InnerBox", fHalfX - fThickness, fHalfY - fThickness, fHalfZ - fThickness);
  // fSolid = new G4SubtractionSolid(name, outerBox, innerBox, 0, G4ThreeVector(0.,0.,0.));

  // Keeping it simple, with no rotation on inner box
  fSolid = new G4SubtractionSolid(name, outerBox, innerBox);
  SetProperties(material, fSolid);
}
void BoxShell::SetXHalfLength(double half) { fHalfX = half; }

void BoxShell::SetYHalfLength(double half) { fHalfY = half; }

void BoxShell::SetZHalfLength(double half) { fHalfZ = half; }

void BoxShell::SetThickness(double thickness) { fThickness = thickness; }
