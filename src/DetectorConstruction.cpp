/*
**	Filename : DetectorConstruction.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "DetectorConstruction.h"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4UnitsTable.hh"
#include "G4VPhysicalVolume.hh"
#include "Geometry.h"
#include "G4AssemblyVolume.hh"
//#include "Helpers.h"
#include "Materials.h"
//#include "SD.h"
#include <G4LogicalSkinSurface.hh>
#include <G4OpticalSurface.hh>
#include <G4SDManager.hh>

DetectorConstruction::DetectorConstruction()
{
  fSDMan = G4SDManager::GetSDMpointer();
}

DetectorConstruction::~DetectorConstruction() {}

G4LogicalVolume *DetectorConstruction::GetLogicalWorld() const
{
  return logicalWorld;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

  // G4NistManager* nist = G4NistManager::Instance();
  //
  // World
  //
  G4bool checkOverlaps   = true;
  G4double world_sizeXYZ = 200 * cm;

  logicalWorld =
      (new Box("World", 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, "G4_AIR"))->GetLogicalVolume();

  G4VPhysicalVolume *physWorld = new G4PVPlacement(0,               // no rotation
                                                   G4ThreeVector(), // at (0,0,0)
                                                   logicalWorld,    // its logical volume
                                                   "PhysicalWorld", // its name
                                                   0,               // its mother  volume
                                                   false,           // no boolean operation
                                                   0,               // copy number
                                                   checkOverlaps);  // overlaps checking

  ScintillatorDetector *scintDet = (new ScintillatorDetector("CompleteScintillatorDetector", 1. * cm, 1. * cm, 50. * cm,
                                                             0. * cm, 0.5 * cm, 1. * cm, "ICNSE_PS", "G4_Galactic"));

#ifdef USE_ASSEMBLIES
  G4AssemblyVolume *supportPlane = (new SupportPlane(50, 0.1 * cm, scintDet))->GetAssemblyVolume();
  G4ThreeVector trans(0., 0., 0.);
  supportPlane->MakeImprint(logicalWorld, trans, 0);

  G4ThreeVector trans2(0.,-50.*cm,0.);
  supportPlane->MakeImprint(logicalWorld, trans2, 0);
#else
  G4LogicalVolume *supportPlane = (new SupportPlane(50, 0.1 * cm, scintDet))->GetLogicalVolume();
new G4PVPlacement(0,                                                     // no rotation
                      G4ThreeVector(), // at (0,0,0)
                      supportPlane,                                             // its logical volume
                      "PhysicalPlane",                                   // its name
                      logicalWorld,                                  // its mother  volume
                      false,                                                 // no boolean operation
                      0,                                                     // copy number
                      checkOverlaps);

#endif


  
 /* SD *scintSD = new SD("Scintillator");
  fSDMan->AddNewDetector(scintSD);
  logicalInnerBPShell->SetSensitiveDetector(bpSD);
  */

  std::cout << "========== TOTAL WEIGHT of DETECTOR =============" << std::endl;
  // std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "=================================================" << std::endl;
  return physWorld;
}
