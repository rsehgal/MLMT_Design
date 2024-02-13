/*
**	Filename : Box.cpp
**	2024-01-02
**	username : rsehgal
*/

#include "Geometry.h"
#include <G4Box.hh>
#include <G4GenericMessenger.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4RunManager.hh>
#include <G4String.hh>
#include <G4VSolid.hh>
#include <iostream>
#include <vector>

Box::Box() {}

Box::~Box() {}

Box::Box(G4String name, double halfx, double halfy, double halfz, G4String material) {
  fSolid = new G4Box(name, halfx, halfy, halfz);
  SetProperties(material, fSolid);
}

Box::Box(G4String name, double halfx, double halfy, double halfz, G4Material *material) {
  fSolid = new G4Box(name, halfx, halfy, halfz);
  SetProperties(material, fSolid);
}