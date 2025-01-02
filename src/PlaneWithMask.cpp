/*
**	Filename : PlaneWithMask.cpp
**	2024-12-24
**	username : rsehgal
*/
#include <iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include<iostream>
#include <G4Box.hh>
#include <G4SystemOfUnits.hh>
#include "G4PVPlacement.hh"
PlaneWithMask::PlaneWithMask(){}

PlaneWithMask::~PlaneWithMask(){}

PlaneWithMask::PlaneWithMask(G4String name, unsigned int numOfScintillators, unsigned short numOfGroups){

  double scintHalfx = 0.5 * cm;
  double scintHalfy = 0.5 * cm;

  //This needs to be carefully calculated, as we have kept a gap of 1 mm between scintillator.
  //Hence, to make the X & Y plane completely overlapping the Z length of the scintillator 
  //must be equal to 100 cm (considering each scintillator is 1 cm wide) plus the addition
  //of all the gaps, which in this case comes out to be 112.4 cm.
  double scintHalfz = 56.2 * cm;

  Scintillator *scintillator = new Scintillator("ScintillatorCrystal", scintHalfx, scintHalfy, scintHalfz,"G4_Pb");

  ScintillatorBunch *scintillatorBunch = new ScintillatorBunch("ScintillatorBunch", scintillator, numOfGroups);

  ScintillatorPlane *scintillatorPlane = new ScintillatorPlane("BunchScintillatorPlane", scintillatorBunch, numOfGroups);
  G4LogicalVolume *logical             = scintillatorPlane->GetLogicalVolume();

  G4Box *scintBunch      = static_cast<G4Box *>(scintillatorBunch->GetLogicalVolume()->GetSolid());
  double scintBunchHalfx = scintBunch->GetXHalfLength();
  double scintBunchHalfy = scintBunch->GetYHalfLength();
  double scintBunchHalfz = scintBunch->GetZHalfLength();

  Scintillator *maskingScintillator =
      new Scintillator("MaskingScintillatorCrystal", scintBunchHalfx, scintBunchHalfy, scintBunchHalfz,"G4_Cu");
  ScintillatorPlane *maskingScintillatorPlane =
      new ScintillatorPlane("MaskingScintillatorPlane", maskingScintillator, numOfGroups);
  G4LogicalVolume *logicalMaskingPlane = maskingScintillatorPlane->GetLogicalVolume();


  G4Box *scintPlaneSolid = static_cast<G4Box*> (logical->GetSolid());  
  G4Box *maskPlaneSolid = static_cast<G4Box*> (logicalMaskingPlane->GetSolid());  

  double envelopHalfX = scintPlaneSolid->GetXHalfLength() + 1;
  double envelopHalfY = scintPlaneSolid->GetYHalfLength() + maskPlaneSolid->GetYHalfLength() + 1;
  double envelopHalfZ = scintPlaneSolid->GetZHalfLength() + 1;

  bool checkOverlaps = true;
  fLogicalVolume = (new Box(name,envelopHalfX,envelopHalfY,envelopHalfZ))->GetLogicalVolume();
  new G4PVPlacement(0,G4ThreeVector(0,-1.*scintPlaneSolid->GetYHalfLength()+0.5,0),logical,"PhysicalBunch",fLogicalVolume,false,0,checkOverlaps); 
  new G4PVPlacement(0,G4ThreeVector(0,maskPlaneSolid->GetYHalfLength()+0.5,0),logicalMaskingPlane,"PhysicalMask",fLogicalVolume,false,0,checkOverlaps); 
}

