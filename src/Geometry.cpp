/*
**	Filename : Geometry.cpp
**	2024-01-01
**	username : rsehgal
*/
#include "Geometry.h"
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4String.hh>
#include <G4Tubs.hh>
#include <G4VSolid.hh>
#include <iostream>
//#include "GeometryMessenger.h"
#include "Materials.h"
#include <G4Color.hh>
#include <G4GenericMessenger.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4RunManager.hh>
#include <G4SubtractionSolid.hh>
#include <G4SurfaceProperty.hh>
#include <G4VisAttributes.hh>
#include <vector>
std::vector<G4LogicalVolume *> vecOfLogicalVolumes;

GeometryProperties::GeometryProperties() {}

GeometryProperties::GeometryProperties(G4Material *material, G4VSolid *solid) {
  fLogicalVolume = new G4LogicalVolume(solid, material, solid->GetName() + "_Logical");
}
GeometryProperties::GeometryProperties(G4String material, G4VSolid *solid) {

  G4NistManager *nist = G4NistManager::Instance();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  fLogicalVolume = new G4LogicalVolume(solid, solid_material, solid->GetName() + "_Logical");
  // fGeometryMessenger = new DetectorMessenger(this);
  DefineCommands();
}

void GeometryProperties::DefineCommands() {

  fGeometryMessenger = new G4GenericMessenger(this, "/ICNSE/", "Material Name");
  fGeometryMessenger->DeclareMethod("setMaterial", &GeometryProperties::SetMaterial,
                                    "Set the material of your geometry");
  fGeometryMessenger->DeclareMethod("setInnerRadius", &GeometryProperties::SetInnerRadius,
                                    "Set the Inner Radius of Cylindrical Shell");
  fGeometryMessenger->DeclareMethod("setOuterRadius", &GeometryProperties::SetOuterRadius,
                                    "Set the Outer Radius of Cylindrical Shell");
  fGeometryMessenger->DeclareMethod("setBoxXDim", &GeometryProperties::SetBoxXDim, "Set the X Dimension of the Box");
  fGeometryMessenger->DeclareMethod("setBoxYDim", &GeometryProperties::SetBoxYDim, "Set the Y Dimension of the Box");
  fGeometryMessenger->DeclareMethod("setBoxZDim", &GeometryProperties::SetBoxZDim, "Set the Z Dimension of the Box");
  // For Box Shell
  fGeometryMessenger->DeclareMethod("setBoxShellXDim", &GeometryProperties::SetBoxShellXDim,
                                    "Set the X Dimension of the Box");
  fGeometryMessenger->DeclareMethod("setBoxShellYDim", &GeometryProperties::SetBoxShellYDim,
                                    "Set the Y Dimension of the Box");
  fGeometryMessenger->DeclareMethod("setBoxShellZDim", &GeometryProperties::SetBoxShellZDim,
                                    "Set the Z Dimension of the BoxShell");
  fGeometryMessenger->DeclareMethod("setBoxShellThickness", &GeometryProperties::SetBoxShellThickness,
                                    "Set the Thickness of the BoxShell");
}

void GeometryProperties::SetBoxShellXDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      // BoxShell *boxShell = dynamic_cast<BoxShell *>(vecOfLogicalVolumes[i]->GetSolid());
      // //->SetInnerRadius(innerRad); boxShell->SetXHalfLength(half);
      G4SubtractionSolid *boxShell = dynamic_cast<G4SubtractionSolid *>(vecOfLogicalVolumes[i]->GetSolid());
      G4VSolid *boxOuter = boxShell->GetConstituentSolid(0);
      G4Box *box = dynamic_cast<G4Box *>(boxOuter);
      box->SetXHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxShellYDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      // BoxShell *boxShell = dynamic_cast<BoxShell *>(vecOfLogicalVolumes[i]->GetSolid());
      // //->SetInnerRadius(innerRad); boxShell->SetXHalfLength(half);
      G4SubtractionSolid *boxShell = dynamic_cast<G4SubtractionSolid *>(vecOfLogicalVolumes[i]->GetSolid());
      G4VSolid *boxOuter = boxShell->GetConstituentSolid(0);
      G4Box *box = dynamic_cast<G4Box *>(boxOuter);
      box->SetYHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxShellZDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      // BoxShell *boxShell = dynamic_cast<BoxShell *>(vecOfLogicalVolumes[i]->GetSolid());
      // //->SetInnerRadius(innerRad); boxShell->SetXHalfLength(half);
      G4SubtractionSolid *boxShell = dynamic_cast<G4SubtractionSolid *>(vecOfLogicalVolumes[i]->GetSolid());
      G4VSolid *boxOuter = boxShell->GetConstituentSolid(0);
      G4Box *box = dynamic_cast<G4Box *>(boxOuter);
      box->SetZHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxShellThickness(G4String logicalVolumeName, double thickness) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4SubtractionSolid *boxShell = static_cast<G4SubtractionSolid *>(vecOfLogicalVolumes[i]->GetSolid());
      G4VSolid *boxOuter = boxShell->GetConstituentSolid(0);
      G4VSolid *boxInner = boxShell->GetConstituentSolid(1);
      G4Box *boxOuterSolid = static_cast<G4Box *>(boxOuter);
      G4Box *boxInnerSolid = static_cast<G4Box *>(boxInner);

      double newInnerHalfX = boxOuterSolid->GetXHalfLength() - thickness;
      double newInnerHalfY = boxOuterSolid->GetYHalfLength() - thickness;
      double newInnerHalfZ = boxOuterSolid->GetZHalfLength() - thickness;

      std::cout << "Details of outer box  " << std::endl;
      std::cout << boxOuterSolid->GetXHalfLength() << std::endl;

      std::cout << "Details of inner box  " << std::endl;
      std::cout << boxInnerSolid->GetXHalfLength() << std::endl;

      boxInnerSolid->SetXHalfLength(newInnerHalfX);
      boxInnerSolid->SetYHalfLength(newInnerHalfY);
      boxInnerSolid->SetZHalfLength(newInnerHalfZ);

      std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetProperties(G4String material, G4VSolid *solid) {

  // G4NistManager *nist = G4NistManager::Instance();
  Materials *nist = Materials::Instance();
  std::map<G4String, G4VisAttributes *> colorMap = nist->GetColorMap();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  fLogicalVolume = new G4LogicalVolume(solid, solid_material, solid->GetName() + "_Logical");
  if (colorMap.count(material)) {
    colorMap[material]->SetForceSolid(true);
    fLogicalVolume->SetVisAttributes(colorMap[material]);
  }
  vecOfLogicalVolumes.push_back(fLogicalVolume);
  DefineCommands();
}

void GeometryProperties::SetProperties(G4Material *material, G4VSolid *solid) {

  fLogicalVolume = new G4LogicalVolume(solid, material, solid->GetName() + "_Logical");
  vecOfLogicalVolumes.push_back(fLogicalVolume);
  // DefineCommands();
}

GeometryProperties::~GeometryProperties() {}

void GeometryProperties::SetInnerRadius(G4String logicalVolumeName, double innerRad) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Tubs *tubs = dynamic_cast<G4Tubs *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      tubs->SetInnerRadius(innerRad);
      // std::cout << "After material change : " << vecOfLogicalVolumes[i]->GetMaterial()->GetName() << std::endl;
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetOuterRadius(G4String logicalVolumeName, double outerRad) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Tubs *tubs = dynamic_cast<G4Tubs *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      tubs->SetOuterRadius(outerRad);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxXDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Box *box = dynamic_cast<G4Box *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      box->SetXHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxYDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Box *box = dynamic_cast<G4Box *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      box->SetYHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxZDim(G4String logicalVolumeName, double half) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Box *box = dynamic_cast<G4Box *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      box->SetZHalfLength(half);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void GeometryProperties::SetBoxAllDim(G4String logicalVolumeName, double halfx, double halfy, double halfz) {
  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName) {
      G4Box *box = dynamic_cast<G4Box *>(vecOfLogicalVolumes[i]->GetSolid()); //->SetInnerRadius(innerRad);
      box->SetXHalfLength(halfx);
      box->SetYHalfLength(halfy);
      box->SetZHalfLength(halfz);
      // std::cout << "--------------------------------------" << std::endl;
    }
  }
}

void GeometryProperties::SetMaterial(G4String logicalVolumeName, G4String material) {
  // G4NistManager *nist = G4NistManager::Instance();
  Materials *nist = Materials::Instance();
  G4Material *solid_material = nist->FindOrBuildMaterial(material);
  std::map<G4String, G4VisAttributes *> colorMap = nist->GetColorMap();
  if (solid_material)
    fMaterial = solid_material;
  else
    std::cout << "Material Not found : " << std::endl;

  for (unsigned int i = 0; i < vecOfLogicalVolumes.size(); i++) {

    std::cout << "--------------------------------------" << std::endl;
    std::cout << vecOfLogicalVolumes[i]->GetName() << std::endl;
    // if (fLogicalVolume->GetName() == logicalVolumeName)
    if (vecOfLogicalVolumes[i]->GetName() == logicalVolumeName){
      vecOfLogicalVolumes[i]->SetMaterial(fMaterial);
      vecOfLogicalVolumes[i]->SetVisAttributes(colorMap[material]);
    }

#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
    // std::cout << "Adding Reflective surfaces" << std::endl;
    G4SurfaceProperty *opticalMirror = Materials::Instance()->GetMirror("opticalMirror");
    // G4LogicalSkinSurface *skin1 =
    const G4String skinName = logicalVolumeName + "_OpticalSkin";
    new G4LogicalSkinSurface(skinName, vecOfLogicalVolumes[i], opticalMirror);
#endif
    std::cout << "After material change : " << vecOfLogicalVolumes[i]->GetMaterial()->GetName() << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

G4Material *GeometryProperties::GetMaterial() const { return fMaterial; }

G4LogicalVolume *GeometryProperties::GetLogicalVolume() const { return fLogicalVolume; }

// Cylindrical Shell
CylindricalShell::CylindricalShell() {}

CylindricalShell::~CylindricalShell() {}

CylindricalShell::CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi,
                                   G4String material) {
  fSolid = new G4Tubs(name, rmin, rmax, dz, sphi, dphi);
  SetProperties(material, fSolid);
  // GeometryProperties("G4_Al", fSolid);
}

CylindricalShell::CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi,
                                   G4Material *material) {
  fSolid = new G4Tubs(name, rmin, rmax, dz, sphi, dphi);
  SetProperties(material, fSolid);
  // GeometryProperties("G4_Al", fSolid);
}
