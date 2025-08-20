/*
**	Filename : SingleTelescope.cpp
**	2025-01-12
**	username : rsehgal
*/
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "Geometry.h"
#include "Global.h"
#include "PoCA_SD.h"
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4RotationMatrix.hh>
#include <G4SystemOfUnits.hh>
#include <iostream>
SingleTelescope::SingleTelescope() {}

SingleTelescope::~SingleTelescope() {}

SingleTelescope::SingleTelescope(G4String name, unsigned int numOfScintillators, unsigned short numOfGroups) {

  // std::vector<double> yPosVec           = {-80. * cm, -50 * cm, 50 * cm, 80. * cm};
  // std::vector<double> yPosVec           = {-275. * cm, -175 * cm, 175 * cm, 275. * cm};
  // std::vector<double> yPosVec           = {0. * cm};
  G4LogicalVolume *logicalTomoLayer = (new TomoLayer("TomoLayer", numOfScintillators, numOfGroups))->GetLogicalVolume();

  G4NistManager *nist = G4NistManager::Instance();
  G4Material *pb = nist->FindOrBuildMaterial("G4_Pb");

  G4Box *solid = static_cast<G4Box *>(logicalTomoLayer->GetSolid());

  double envelopHalfX = solid->GetXHalfLength() + 1; // 0.5
  double yrange = std::fabs(yPosVec[0]) > std::fabs(yPosVec[yPosVec.size() - 1])
                      ? std::fabs(yPosVec[0])
                      : std::fabs(yPosVec[yPosVec.size() - 1]);
  // double envelopHalfY = yPosVec[yPosVec.size()-1]+ 2 * solid->GetYHalfLength() + 1;
  double envelopHalfY = yrange + 2 * solid->GetYHalfLength() + 1;
  double envelopHalfZ = solid->GetZHalfLength() + 1; // 0.5;
  double envelopHalfXZ = envelopHalfX > envelopHalfZ ? envelopHalfX : envelopHalfZ;

  bool checkOverlaps = true;
  fLogicalVolume = (new Box(name, envelopHalfXZ, envelopHalfY, envelopHalfXZ))->GetLogicalVolume();

  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    new G4PVPlacement(0, G4ThreeVector(0, yPosVec[i], 0), logicalTomoLayer, "PhysicalTomoLayer", fLogicalVolume, false,
                      i, checkOverlaps);
  }
#ifdef TRAINING_DATA
  // Scatterer under test
#ifdef BACKGROUND_DATA
  G4LogicalVolume *logicalScatterer =
      (new Box("Scatterer", 50 * cm, 0.005 * cm, 50 * cm, "G4_Galactic"))->GetLogicalVolume();
#else
  G4LogicalVolume *logicalScatterer = (new Box("Scatterer", 50 * cm, 10. * cm, 50 * cm, "G4_Pb"))->GetLogicalVolume();
#endif
  new G4PVPlacement(0, G4ThreeVector(0, 0., 0.), logicalScatterer, "PhysicalScatterer", fLogicalVolume, false, 0,
                    checkOverlaps);

  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  PoCA_SD *pocaSD = new PoCA_SD("PoCA_Sensitive_Detector", "PoCAHitCollection");
  fSDMan->AddNewDetector(pocaSD);
  logicalScatterer->SetSensitiveDetector(pocaSD);

#else

#ifdef TESTING_DATA

/*  G4LogicalVolume *logicalOuterBox = (new Box("OuterBox", 25 * cm, 25 * cm, 25 * cm, "G4_Fe"))->GetLogicalVolume();
      G4Orb *orb = new G4Orb("ORB", 15 * cm);
      G4LogicalVolume *logicalScatterer = new G4LogicalVolume(orb, pb, "LogicalOrb");
     new G4PVPlacement(0, G4ThreeVector(0*cm, 0., 0.*cm), logicalScatterer, "PhysicalScatterer",logicalOuterBox , false, 0,
                      checkOverlaps);
    new G4PVPlacement(0, G4ThreeVector(0, 0., 0.), logicalOuterBox, "PhysicalOuterBox", fLogicalVolume, false, 0,
                       checkOverlaps);
*/

/*
//Orb with tube setup
      G4Orb *orb = new G4Orb("ORB", 15 * cm);
      G4LogicalVolume *logicalScatterer = new G4LogicalVolume(orb, pb, "LogicalOrb");


  G4LogicalVolume *logicalTube =
        (new CylindricalShell("TubeScatterer", 3 * cm, 6 * cm, 10 * cm, 0., 2 * M_PI, "G4_Fe"))->GetLogicalVolume();

    new G4PVPlacement(0, G4ThreeVector(0, 0., 0.), logicalScatterer, "PhysicalScatterer", fLogicalVolume, false, 0,
                       checkOverlaps);
     new G4PVPlacement(0, G4ThreeVector(30*cm, 0., 30.*cm), logicalTube, "PhysicalScatterer", fLogicalVolume, false, 0,
                      checkOverlaps);
      new G4PVPlacement(0, G4ThreeVector(-30.*cm, 0., -30.*cm), logicalTube, "PhysicalScatterer", fLogicalVolume, false,
  0, checkOverlaps); G4RotationMatrix *rotation = new G4RotationMatrix(); rotation->rotateX(90.0 * deg); new
  G4PVPlacement(rotation, G4ThreeVector(30*cm, 0., -30.*cm), logicalTube, "PhysicalScatterer", fLogicalVolume, false, 0,
                      checkOverlaps);
      new G4PVPlacement(rotation, G4ThreeVector(-30.*cm, 0., 30.*cm), logicalTube, "PhysicalScatterer", fLogicalVolume,
  false, 0, checkOverlaps);
*/



/*    G4LogicalVolume *logicalScattererAl = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm,
  "G4_Al"))->GetLogicalVolume(); G4LogicalVolume *logicalScattererU = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm,
  "G4_U"))->GetLogicalVolume();

    G4LogicalVolume *logicalScattererFeEnv = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm,
  "G4_Fe"))->GetLogicalVolume(); G4LogicalVolume *logicalScattererHiddenU = (new Box("Scatterer", 8 * cm, 8 * cm, 8 *
  cm, "G4_U"))->GetLogicalVolume(); new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalScattererHiddenU,
  "PhysicalScattererHiddenU",logicalScattererFeEnv , false, 0, checkOverlaps);
 */ 
  G4LogicalVolume *logicalScatterer = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm, "G4_Fe"))->GetLogicalVolume();
  G4LogicalVolume *logicalScattererPb = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm, "G4_Pb"))->GetLogicalVolume();
 

  new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalScatterer, "PhysicalScatterer", fLogicalVolume, false, 0,
                    checkOverlaps);

  new G4PVPlacement(0, G4ThreeVector(20 * cm, 0., 20. * cm), logicalScattererPb, "PhysicalScatterer", fLogicalVolume,
                    false, 1, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(20 * cm, 0., -20. * cm), logicalScatterer, "PhysicalScatterer", fLogicalVolume,
                    false, 2, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-20 * cm, 0., 20. * cm), logicalScatterer, "PhysicalScatterer", fLogicalVolume,
                    false, 3, checkOverlaps);
  new G4PVPlacement(0, G4ThreeVector(-20 * cm, 0., -20. * cm), logicalScattererPb, "PhysicalScatterer", fLogicalVolume,
                    false, 4, checkOverlaps);

  /*  G4LogicalVolume *logicalTube =
        (new CylindricalShell("TubeScatterer", 3 * cm, 6 * cm, 10 * cm, 0., 2 * M_PI, "G4_Pb"))->GetLogicalVolume();
    new G4PVPlacement(rotation, G4ThreeVector(0, 0., 0), logicalTube, "PhysicalTubeScatterer", fLogicalVolume, false, 0,
                      checkOverlaps);
  */
  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  PoCA_SD *pocaSD = new PoCA_SD("PoCA_Sensitive_Detector", "PoCAHitCollection");
  fSDMan->AddNewDetector(pocaSD);
  logicalScatterer->SetSensitiveDetector(pocaSD);
  logicalScattererPb->SetSensitiveDetector(pocaSD);
   //logicalTube->SetSensitiveDetector(pocaSD);
   //logicalOuterBox->SetSensitiveDetector(pocaSD);

#endif
#endif
  // For momentum estimation
  G4LogicalVolume *logicalMomentumScatterer =
      (new Box("MomentumDetectionScattererSlab", 50 * cm, 10 * cm, 50 * cm, "G4_Pb"))->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0, -95. * cm, 0), logicalMomentumScatterer, "PhysicalMomentumScatterer",
                    fLogicalVolume, false, 0, checkOverlaps);
}
