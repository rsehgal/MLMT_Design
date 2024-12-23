/*
**	Filename : ScintillatorBunch.cpp
**	2024-12-20
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

ScintillatorBunch::ScintillatorBunch() {}

ScintillatorBunch::ScintillatorBunch(G4String name, double halfx, double halfy, double halfz,
                                     unsigned int numOfScintillators, G4String material)
{
}

ScintillatorBunch::ScintillatorBunch(G4String name, unsigned int numOfScintillators, G4String material)
{

  G4bool checkOverlaps = true;

  double scintHalfx = 0.5 * cm;
  double scintHalfy = 0.5 * cm;
  double scintHalfz = 15 * cm;

  double envFullX = numOfScintillators * (2 * scintHalfx + 1) + 1;
  double envFullY = 2 * (scintHalfy + 1); // numOfScintillators*(2*scintHalfy+1)+1;
  double envFullZ = 2 * (scintHalfz + 1);
  fLogicalVolume  = (new Box(name, envFullX / 2., envFullY / 2., envFullZ / 2., material))->GetLogicalVolume();

  G4LogicalVolume *singleScintillator =
      (new Scintillator("ScintillatorCrystal", scintHalfx, scintHalfy, scintHalfz))->GetLogicalVolume();

  for (unsigned int i = 0; i < numOfScintillators; i++) {

    double x = -1. * envFullX / 2. + ((2 * i + 1) * scintHalfx) + (i * 1);
    new G4PVPlacement(0, G4ThreeVector(x, 0, 0), singleScintillator, "PhysicalScintillator", fLogicalVolume, false, i,
                      checkOverlaps);
  }
}

ScintillatorBunch::ScintillatorBunch(G4String name, Scintillator *scintillator, unsigned int numOfScintillators)
{

  G4bool checkOverlaps = true;

  G4LogicalVolume *singleScintillatorLogical = scintillator->GetLogicalVolume();
  G4VSolid *solid                = singleScintillatorLogical->GetSolid();
  G4Box *box                     = static_cast<G4Box *>(solid);
  double scintHalfx              = box->GetXHalfLength(); // 0.5*cm;
  double scintHalfy              = box->GetYHalfLength(); // 0.5*cm;
  double scintHalfz              = box->GetZHalfLength(); // 15*cm;

  double envFullX = numOfScintillators * (2 * scintHalfx + 1) + 1;
  double envFullY = 2 * (scintHalfy + 1); // numOfScintillators*(2*scintHalfy+1)+1;
  double envFullZ = 2 * (scintHalfz + 1);
  fLogicalVolume  = (new Box(name, envFullX / 2., envFullY / 2., envFullZ / 2.))->GetLogicalVolume();


  for (unsigned int i = 0; i < numOfScintillators; i++) {

    double x = -1. * envFullX / 2. + ((2 * i + 1) * scintHalfx) + (i * 1);
    new G4PVPlacement(0, G4ThreeVector(x, 0, 0), singleScintillatorLogical, "PhysicalScintillator", fLogicalVolume, false, i,
                      checkOverlaps);
  }
}
