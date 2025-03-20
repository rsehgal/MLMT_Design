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
#include "Global.h"
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
  G4double world_sizeXYZ = 300 * cm;
  G4double world_sizeX = 450 * cm;
  G4double world_sizeY = 700 * cm;
  G4double world_sizeZ = 850 * cm;

  G4double cargo_sizeX = 260*cm;
  G4double cargo_sizeY = 260*cm;
  G4double cargo_sizeZ = 600*cm;
 
  logicalWorld =
      (new Box("World", 0.5 * world_sizeX, 0.5 * world_sizeY, 0.5 * world_sizeZ, "G4_AIR"))->GetLogicalVolume();
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

/*
//This is just to create one 1m x 1m setup, Now can be done by instantiating class of SingleTelescope
  std::vector<double> yPosVec           = {-30. * cm, -10 * cm, 10 * cm, 30. * cm};
  G4LogicalVolume *logicalTomoLayer = (new TomoLayer("TomoLayer", 100, 10))->GetLogicalVolume();
  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    new G4PVPlacement(0, G4ThreeVector(0, yPosVec[i], 0), logicalTomoLayer, "PhysicalTomoLayer", logicalWorld, false, i,
                      checkOverlaps);
  }
*/

G4LogicalVolume *logicalSingleTelescope = (new SingleTelescope("SingleTelescope", numOfScintillators, numOfGroups))->GetLogicalVolume();
//using tracker approach
/*G4LogicalVolume *logicalTracker = (new Tracker("SingleTelescope", 100, 10))->GetLogicalVolume();
G4Box *solid                 = static_cast<G4Box *>(logicalTracker->GetSolid());

  double envelopHalfX = solid->GetXHalfLength() + 0.5;
  double envelopHalfY = solid->GetYHalfLength() + 0.5;
  double envelopHalfZ = solid->GetZHalfLength() + 0.5;
  //double envelopHalfXZ = envelopHalfX > envelopHalfZ ? envelopHalfX : envelopHalfZ;
  std::vector<double> yPosVec           = { -175 * cm, 175 * cm};

unsigned short n = 3;
unsigned short m = 1;
int fullX = 2*envelopHalfX;
int fullZ = 2*envelopHalfZ;

//for(unsigned int yindex = 0 ; yindex < yPosVec.size() ; yindex++){


  
  for(unsigned int i = 0 ; i < n ; i++){


	  for(unsigned int j = 0 ; j < m ; j++){

		int zpos = (-1.*m*fullZ)/2.+(2*j+1)*envelopHalfZ+0.5;	
		int xpos = (-1.*n*fullX)/2.+(2*i+1)*envelopHalfX+0.5;
		new G4PVPlacement(0, G4ThreeVector(xpos, yPosVec[0]-envelopHalfY, zpos), logicalTracker, "PhysicalTracker", logicalWorld, false, 0,
                      checkOverlaps);	

		new G4PVPlacement(0, G4ThreeVector(xpos, yPosVec[1]+envelopHalfY, zpos), logicalTracker, "PhysicalTracker", logicalWorld, false, 0,
                      checkOverlaps);	


	}
}
*/
#ifdef USE_CARGO
//Creating Cargo
G4LogicalVolume *logicalCargo =
      (new Box("Cargo", 0.5 * cargo_sizeX, 0.5 * cargo_sizeY, 0.5 * cargo_sizeZ, "G4_Fe"))->GetLogicalVolume();


//Placing the cargo
new G4PVPlacement(0, G4ThreeVector(0, 0, 0*cm), logicalCargo, "PhysicalCargo", logicalWorld, false, 0,
                      checkOverlaps);
#endif

//}
new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicalSingleTelescope, "PhysicalSingleTelescope", logicalWorld, false, 0,
                      checkOverlaps);



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
