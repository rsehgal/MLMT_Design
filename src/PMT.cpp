/*
**      Filename : PMT.cpp
**      2024-02-13
**      username : rsehgal
*/
#include<iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>

PMT::PMT(){}

PMT::~PMT(){}

PMT::PMT(G4String name, double rmin, double rmax, double dz, double sphi, double dphi, G4String material)
{
fLogicalVolume = (new CylindricalShell(name,rmin,rmax,dz,sphi,dphi,material))->GetLogicalVolume(); 
}
