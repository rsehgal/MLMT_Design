/*
**      Filename : Scintillator.cpp
**      2024-02-13
**      username : rsehgal
*/
#include<iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>

Scintillator::Scintillator(){}

Scintillator::~Scintillator(){}

Scintillator::Scintillator(G4String name, double halfx, double halfy, double halfz, G4String material)
{
fLogicalVolume = (new Box(name,halfx,halfy,halfz,material))->GetLogicalVolume(); 
}
