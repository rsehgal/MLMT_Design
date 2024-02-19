/*
**      Filename : Scintillator.cpp
**      2024-02-13
**      username : rsehgal
*/
#include <iostream>
#include "Geometry.h"
#include <G4LogicalVolume.hh>
#include <G4SurfaceProperty.hh>
#include <G4LogicalSkinSurface.hh>
#include "Materials.h"
#include <G4SDManager.hh>
#include "SD.h"
Scintillator::Scintillator() {}

Scintillator::~Scintillator() {}

Scintillator::Scintillator(G4String name, double halfx, double halfy, double halfz, G4String material)
{
  fLogicalVolume = (new Box(name, halfx, halfy, halfz, material))->GetLogicalVolume();
#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
  // std::cout << "Adding Reflective surfaces" << std::endl;
  G4SurfaceProperty *opticalMirror = Materials::Instance()->GetMirror("opticalMirror");
  const G4String skinName          = fLogicalVolume->GetName() + "_OpticalSkin";
  new G4LogicalSkinSurface(skinName, fLogicalVolume, opticalMirror);
#endif

  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  SD *scintSD         = new SD("Scintillator");
  fSDMan->AddNewDetector(scintSD);
  fLogicalVolume->SetSensitiveDetector(scintSD);

}
