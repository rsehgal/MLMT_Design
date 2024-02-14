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

SupportPlane::SupportPlane() {}

SupportPlane::~SupportPlane() {}

// using Assembly
SupportPlane::SupportPlane(unsigned int numOfScintillators, double separation, ScintillatorDetector *envelope)
    : fNumOfScintillators(numOfScintillators), fSeparation(separation)
{

  fScintillatorEnvelope = envelope;

  G4Box *envelopSolid = static_cast<G4Box *>(fScintillatorEnvelope->GetLogicalVolume()->GetSolid());

  double outerBoxHalfX =
      (fSeparation * (fNumOfScintillators + 1) + (fNumOfScintillators * 2 * envelopSolid->GetXHalfLength())) / 2.;
  double outerBoxHalfY = envelopSolid->GetYHalfLength();
  double outerBoxHalfZ = envelopSolid->GetZHalfLength();

  double basePlateHalfX = outerBoxHalfX;
  double basePlateHalfY = fSeparation / 2.;
  double basePlateHalfZ = outerBoxHalfZ;

  double separatorHalfX = fSeparation / 2.;
  double separatorHalfY = outerBoxHalfY;
  double separatorHalfZ = outerBoxHalfZ;

  G4LogicalVolume *basePlate =
      (new Box("BasePlate", basePlateHalfX, basePlateHalfY, basePlateHalfZ, "G4_Fe"))->GetLogicalVolume();
  G4LogicalVolume *separator =
      (new Box("Separtor", separatorHalfX, separatorHalfY, separatorHalfZ, "G4_Fe"))->GetLogicalVolume();

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
}

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
