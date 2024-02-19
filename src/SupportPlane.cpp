/*
**	Filename : SupportPlane.cpp
**	2024-02-13
**	username : rsehgal
*/
#include <iostream>
#include <Geometry.h>
#include <G4SubtractionSolid.hh>
#include <G4LogicalVolume.hh>
#include <G4Box.hh>
#include <G4SystemOfUnits.hh>
#include <G4AssemblyVolume.hh>
#include "G4PVPlacement.hh"
#include "SD.h"
#include <G4SDManager.hh>
SupportPlane::SupportPlane() {}

SupportPlane::~SupportPlane() {}

// using Assembly
SupportPlane::SupportPlane(unsigned int numOfScintillators, double separation, ScintillatorDetector *envelope)
    : fNumOfScintillators(numOfScintillators), fSeparation(separation)
{

  bool checkOverlaps    = true;
  fScintillatorEnvelope = envelope;

  G4Box *envelopSolid = static_cast<G4Box *>(fScintillatorEnvelope->GetLogicalVolume()->GetSolid());

  double outerBoxHalfX =
      (fSeparation * (fNumOfScintillators + 1) + (fNumOfScintillators * 2 * envelopSolid->GetXHalfLength())) / 2.;
  double outerBoxHalfY = envelopSolid->GetYHalfLength() + fSeparation; // / 2.;;
  double outerBoxHalfZ = envelopSolid->GetZHalfLength();

  double basePlateHalfX = outerBoxHalfX;
  double basePlateHalfY = fSeparation / 2.;
  double basePlateHalfZ = outerBoxHalfZ;

  double separatorHalfX = fSeparation / 2.;
  double separatorHalfY = envelopSolid->GetYHalfLength();
  ;
  double separatorHalfZ = outerBoxHalfZ;

  fLogicalVolume = (new Box("SupportPaneEnvelope", outerBoxHalfX, outerBoxHalfY, outerBoxHalfZ))->GetLogicalVolume();
  G4LogicalVolume *basePlate =
      (new Box("BasePlate", basePlateHalfX, basePlateHalfY, basePlateHalfZ))->GetLogicalVolume();
  G4LogicalVolume *separator =
      (new Box("Separtor", separatorHalfX, separatorHalfY, separatorHalfZ))->GetLogicalVolume();

#ifdef USE_ASSEMBLIES
  // Let create the assembly
  fAssembly = new G4AssemblyVolume();
  G4ThreeVector basePlateTrans(0., 0., 0.);
  fAssembly->AddPlacedVolume(basePlate, basePlateTrans, 0);
  for (unsigned int i = 0; i < fNumOfScintillators; i++) {
    double shift  = (2 * i + 1) * (fSeparation / 2.) + (i * 2 * envelopSolid->GetXHalfLength());
    double transX = -1. * outerBoxHalfX + shift;
    double transY = (fSeparation / 2.) + separatorHalfY;
    G4ThreeVector transVec(transX, transY, 0.);
    G4ThreeVector transVecScint(transX + fSeparation / 2. + envelopSolid->GetXHalfLength(), transY, 0.);

    fAssembly->AddPlacedVolume(separator, transVec, 0);
    fAssembly->AddPlacedVolume(envelope->GetLogicalVolume(), transVecScint, 0);
  }
#else
  // Place the Base Plate
  new G4PVPlacement(0,                                                             // no rotation
                    G4ThreeVector(0., -1. * outerBoxHalfY + fSeparation / 2., 0.), // at (0,0,0)
                    basePlate,                                                     // its logical volume
                    "PhysicalBasePlate",                                           // its name
                    fLogicalVolume,                                                // its mother  volume
                    false,                                                         // no boolean operation
                    0,                                                             // copy number
                    checkOverlaps);                                                // overlaps checking

  for (unsigned int i = 0; i < fNumOfScintillators; i++) {

    // Place the separator and scintillator envelope

    double shift  = (2 * i + 1) * (fSeparation / 2.) + (i * 2 * envelopSolid->GetXHalfLength());
    double transX = -1. * outerBoxHalfX + shift;
    double transY = -1. * outerBoxHalfY + fSeparation + separatorHalfY;
    G4ThreeVector transVec(transX, transY, 0.);

    new G4PVPlacement(0,                   // no rotation
                      transVec,            //
                      separator,           // its logical volume
                      "PhysicalSeparator", // its name
                      fLogicalVolume,      // its mother  volume
                      false,               // no boolean operation
                      i,                   // copy number
                      checkOverlaps);      // overlaps checking

    G4ThreeVector transVecScint(transX + fSeparation / 2. + envelopSolid->GetXHalfLength(), transY, 0.);

    new G4PVPlacement(0,                              // no rotation
                      transVecScint,                  //
                      envelope->GetLogicalVolume(),   // its logical volume
                      "PhysicalScintillatorEnvelope", // its name
                      fLogicalVolume,                 // its mother  volume
                      false,                          // no boolean operation
                      i,                              // copy number
                      checkOverlaps);
  }

  G4SDManager *fSDMan = G4SDManager::GetSDMpointer();
  SD *supportPlaneSD         = new SD("SupportPlane");
  fSDMan->AddNewDetector(supportPlaneSD);
  fLogicalVolume->SetSensitiveDetector(supportPlaneSD);
#endif
}

// Tried with Subtraction solid, but generates lot a tetrahedron
#if (0)
SupportPlane::SupportPlane(unsigned int numOfScintillators, double separation, ScintillatorDetector *envelope)
    : fNumOfScintillators(numOfScintillators), fSeparation(separation)
{
  fScintillatorEnvelope = envelope;
  G4Box *envelopSolid   = static_cast<G4Box *>(fScintillatorEnvelope->GetLogicalVolume()->GetSolid());
  double outerBoxHalfX =
      (fSeparation * (fNumOfScintillators + 1) + (fNumOfScintillators * 2 * envelopSolid->GetXHalfLength())) / 2.;
  double outerBoxHalfY = envelopSolid->GetYHalfLength();
  double outerBoxHalfZ = envelopSolid->GetZHalfLength();

  fSolid = new G4Box("OuterBox", outerBoxHalfX, outerBoxHalfY, outerBoxHalfZ);

  fSolid = new G4SubtractionSolid("Raman", fSolid, envelopSolid, 0, G4ThreeVector(-10 * cm, fSeparation, 0.));
  fSolid = new G4SubtractionSolid("Raman", fSolid, envelopSolid, 0, G4ThreeVector(10 * cm, fSeparation, 0.));
  std::cout << "OUTER : " << outerBoxHalfX << std::endl;
  for (unsigned int i = 0; i < fNumOfScintillators; i++) {
    double xpos = -1. * outerBoxHalfX + (i + 1) * fSeparation + (2 * i + 1) * envelopSolid->GetXHalfLength();
    std::cout << "XPos : " << xpos << std::endl;
    fSolid = new G4SubtractionSolid("Raman", fSolid, envelopSolid, 0, G4ThreeVector(xpos, fSeparation, 0.));
  }
  SetProperties("G4_Galactic", fSolid);
}
#endif
