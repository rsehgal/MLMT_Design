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
//#include "Helpers.h"
#include "Materials.h"
//#include "SD.h"
#include <G4LogicalSkinSurface.hh>
#include <G4OpticalSurface.hh>
#include <G4SDManager.hh>
#include <G4RotationMatrix.hh>
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

  // G4LogicalVolume *scintillatorCrystalLogical = (new
  // Scintillator("ScintillatorCrystal",0.5*cm,0.5*cm,15*cm))->GetLogicalVolume();

  /*
  //whole thing is take in new class name **PlaneWithMask**
  double scintHalfx = 0.5 * cm;
  double scintHalfy = 0.5 * cm;
  double scintHalfz = 15 * cm;

  Scintillator *scintillator = new Scintillator("ScintillatorCrystal", scintHalfx, scintHalfy, scintHalfz);

  ScintillatorBunch *scintillatorBunch = new ScintillatorBunch("ScintillatorBunch", scintillator, 5);

  ScintillatorPlane *scintillatorPlane = new ScintillatorPlane("ScintillatorPlane", scintillatorBunch, 5);
  G4LogicalVolume *logical             = scintillatorPlane->GetLogicalVolume();

  G4Box *scintBunch      = static_cast<G4Box *>(scintillatorBunch->GetLogicalVolume()->GetSolid());
  double scintBunchHalfx = scintBunch->GetXHalfLength();
  double scintBunchHalfy = scintBunch->GetYHalfLength();
  double scintBunchHalfz = scintBunch->GetZHalfLength();

  Scintillator *maskingScintillator =
      new Scintillator("MaskingScintillatorCrystal", scintBunchHalfx, scintBunchHalfy, scintBunchHalfz);
  ScintillatorPlane *maskingScintillatorPlane =
      new ScintillatorPlane("MaskingScintillatorPlane", maskingScintillator, 5);
  G4LogicalVolume *logicalMaskingPlane = maskingScintillatorPlane->GetLogicalVolume();

  //
  //G4LogicalVolume *logical = (new ScintillatorPlane("ScintillatorPlane",30))->GetLogicalVolume();
  //
  std::vector<double> yPosVec     = {-30. * cm, -10 * cm, 10 * cm, 30. * cm};
  std::vector<double> yMaskPosVec = {-30. * cm + 1.5 * cm, -10 * cm + 1.5 * cm, 10 * cm + 1.5 * cm,
                                     30. * cm + 1.5 * cm};

  for (unsigned int i = 0; i < yPosVec.size(); i++) {

    //  G4VPhysicalVolume *scintillatorCrystalPhysical =
    new G4PVPlacement(0, G4ThreeVector(0, yPosVec[i], 0), logical, "PhysicalScintLayer", logicalWorld, false, i,
                      checkOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0, yMaskPosVec[i], 0), logicalMaskingPlane, "PhysicalMaskingLayer", logicalWorld,
                      false, i, checkOverlaps);
  }
  */

/*
 //This block is for on Plane with Masking Layer 
 G4RotationMatrix *rotZ = new G4RotationMatrix();
  rotZ->rotateZ(180.*deg);
  std::vector<double> yPosVec           = {-30. * cm, -10 * cm, 10 * cm, 30. * cm};
  G4LogicalVolume *logicalPlaneWithMask = (new PlaneWithMask("ScintillatorPlaneWithMask", 100, 10))->GetLogicalVolume();
  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    new G4PVPlacement(0, G4ThreeVector(0, yPosVec[i], 0), logicalPlaneWithMask, "PhysicalScintLayer", logicalWorld, false, i,
                      checkOverlaps);
  }
*/
  std::vector<double> yPosVec           = {-30. * cm, -10 * cm, 10 * cm, 30. * cm};
  G4LogicalVolume *logicalTomoLayer = (new TomoLayer("TomoLayer", 100, 10))->GetLogicalVolume();
  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    new G4PVPlacement(0, G4ThreeVector(0, yPosVec[i], 0), logicalTomoLayer, "PhysicalTomoLayer", logicalWorld, false, i,
                      checkOverlaps);
  }


  /*
  SD *bpSD = new SD("BoratedPolyEthylene");
  fSDMan->AddNewDetector(bpSD);
  logicalInnerBPShell->SetSensitiveDetector(bpSD);
  */

  std::cout << "========== TOTAL WEIGHT of DETECTOR =============" << std::endl;
  // std::cout << GetLogicalVolumeWeight(logicalWorld) << std::endl;
  std::cout << "=================================================" << std::endl;
  return physWorld;
}
