/*
**	Filename : SingleTelescope.cpp
**	2025-01-12
**	username : rsehgal
*/
#include "G4PVPlacement.hh"
#include "Geometry.h"
#include "Global.h"
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
  G4LogicalVolume *logicalTomoLayer = (new TomoLayer("TomoLayer", 100, 10))->GetLogicalVolume();

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

  G4LogicalVolume *logicalScatterer = (new Box("Scatterer", 10 * cm, 10 * cm, 10 * cm, "G4_Pb"))->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0, 0., 0), logicalScatterer, "PhysicalScatterer", fLogicalVolume, false, 0,
                    checkOverlaps);

  G4LogicalVolume *logicalMomentumScatterer =
      (new Box("MomentumDetectionScattererSlab", 50 * cm, 10 * cm, 50 * cm, "G4_Pb"))->GetLogicalVolume();
  new G4PVPlacement(0, G4ThreeVector(0, -95. * cm, 0), logicalMomentumScatterer, "PhysicalMomentumScatterer",
                    fLogicalVolume, false, 0, checkOverlaps);
}
