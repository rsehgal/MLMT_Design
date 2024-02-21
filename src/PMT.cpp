/*
**      Filename : PMT.cpp
**      2024-02-13
**      username : rsehgal
*/
#include <iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include <G4SDManager.hh>
#include "SD.h"
PMT::PMT() {}

PMT::~PMT() {}

PMT::PMT(G4String name, double rmin, double rmax, double dz, double sphi, double dphi, G4String material)
{
  fCounter = 0;
  fLogicalVolume = (new CylindricalShell(name, rmin, rmax, dz, sphi, dphi, material))->GetLogicalVolume();
  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  SD *pmtSD       = new SD("PMT",this);
  fSDMan->AddNewDetector(pmtSD);
  fLogicalVolume->SetSensitiveDetector(pmtSD);
}

void PMT::Inc(){ fCounter++; }
void PMT::Reset(){fCounter=0;}
unsigned int PMT::GetCounter(){return fCounter;}
