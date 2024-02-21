/*
**	Filename : Geometry.h
**	2024-02-13
**	username : rsehgal
*/
#ifndef Geometry_h
#define Geometry_h

class G4Tubs;
class G4Box;
class G4LogicalVolume;
class G4Material;
class G4VSolid;
class G4Tubs;
class G4SubtractionSolid;
class G4AssemblyVolume;

#include <G4CSGSolid.hh>
#include <G4String.hh>
#include <vector>

class G4GenericMessenger;
class G4VSolid;
class GeometryProperties {
public:
  G4VSolid *fSolid;
  G4Material *fMaterial;
  G4LogicalVolume *fLogicalVolume;
  G4AssemblyVolume *fAssembly;
  // DetectorMessenger *fGeometryMessenger;
  G4GenericMessenger *fGeometryMessenger = nullptr;

public:
  GeometryProperties();
  GeometryProperties(G4Material *material, G4VSolid *solid);
  GeometryProperties(G4String material, G4VSolid *solid);
  void SetProperties(G4String material, G4VSolid *solid);
  void SetProperties(G4Material *material, G4VSolid *solid);
  ~GeometryProperties();
  // void SetMaterial(G4Material *material);
  void SetMaterial(G4String logicalVolumeName, G4String material);

  // Function to change the inner and outer radius of tube
  void SetInnerRadius(G4String logicalVolumeName, double innerRad);
  void SetOuterRadius(G4String logicalVolumeName, double outerRad);

  // Functions to change Box dimensions
  void SetBoxXDim(G4String logicalVolumeName, double half);
  void SetBoxYDim(G4String logicalVolumeName, double half);
  void SetBoxZDim(G4String logicalVolumeName, double half);
  void SetBoxAllDim(G4String logicalVolumeName, double halfx, double halfy, double halfz);

  // Functions to change BoxShell dimension
  void SetBoxShellXDim(G4String logicalVolumeName, double half);
  void SetBoxShellYDim(G4String logicalVolumeName, double half);
  void SetBoxShellZDim(G4String logicalVolumeName, double half);
  void SetBoxShellThickness(G4String logicalVolumeName, double thickness);
  // Function to create geometry from UI
  /*void CreateBox(G4String name, double halfx, double halfy, double halfz,
                 G4String material,G4Rotation *rot, G4ThreeVector trans,
                 G4LogicalVolume *)
   */

  // void SetInnerRadius(double innerRad);
  G4Material *GetMaterial() const;
  G4LogicalVolume *GetLogicalVolume() const;
  G4AssemblyVolume *GetAssemblyVolume() const;
  void DefineCommands();
};

class CylindricalShell : public GeometryProperties {

public:
  CylindricalShell();
  CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi,
                   G4String material = G4String("G4_Galactic"));
  CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi, G4Material *material);
  ~CylindricalShell();
};

class Box : public GeometryProperties {

public:
  Box();
  Box(G4String name, double halfx, double halfy, double halfz, G4String material = G4String("G4_Galactic"));
  Box(G4String name, double halfx, double halfy, double halfz, G4Material *material);

  ~Box();
};

class BoxShell : public GeometryProperties {

private:
  double fHalfX;
  double fHalfY;
  double fHalfZ;
  double fThickness;

public:
  void SetXHalfLength(double half);
  void SetYHalfLength(double half);
  void SetZHalfLength(double half);
  void SetThickness(double thickness);

public:
  // BoxShell();
  BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness,
           G4String material = G4String("G4_Galactic"));
  BoxShell(G4String name, double halfx, double halfy, double halfz, double thickness, G4Material *material);

  ~BoxShell();
};

/*
** A class to represent Bare Scintillator
*/
class Scintillator : public GeometryProperties{
private:
  unsigned int fCounter;

public:
  Scintillator();
  Scintillator(G4String name, double halfx, double halfy, double halfz, G4String material = G4String("G4_Galactic"));

  ~Scintillator();
};

/*
** A class to represent Bare PMT
*/
class PMT : public GeometryProperties{
private:
  unsigned int fCounter;
  std::vector<unsigned int> fTimeVector;

public:
  PMT();
  PMT(G4String name, double rmin, double rmax, double dz, double sphi = 0., double dphi = 2 * M_PI,
      G4String material = G4String("G4_Galactic"));
  void Inc();
  void Reset();
  unsigned int GetCounter();

  ~PMT();
};

/*
** Scintillator couple with PMT
*/
class ScintillatorDetector : public GeometryProperties{
private:
  double fScintillatorEnvelopeHalfX;
  double fScintillatorEnvelopeHalfY;
  double fScintillatorEnvelopeHalfZ;
  double fScintHalfX;
  double fScintHalfY;
  double fScintHalfZ;
  double fPmtRmin;
  double fPmtRmax;
  double fPmtDz;

  unsigned int fCounter;

public:
  ScintillatorDetector();
  ScintillatorDetector(G4String name, double scintHalfX, double scintHalfY, double scintHalfZ, double pmtRMin,
                       double pmtRMax, double pmtDz, G4String scintillatorMaterial=G4String("G4_Galactic"), G4String pmtMaterial = G4String("G4_Galactic"));
  /*ScintillatorDetector(G4String name, double scintHalfX, double scintHalfY, double scintHalfZ, double pmtRMin,
                       double pmtRMax, double pmtDz, G4Material *material);*/

  ~ScintillatorDetector();
  unsigned int GetHalfX() const;
  unsigned int GetHalfY() const;
  unsigned int GetHalfZ() const;
};

/*
** A skeleton or support structure to hold series of scintillator
** that form a complete scintillator plane
**
** Formed by subtracting sequence of scintillator size box from a
** from a solid box
*/
class SupportPlane : public GeometryProperties{
private:
  unsigned int fNumOfScintillators;
  double fSeparation;
  ScintillatorDetector *fScintillatorEnvelope;

  double fSupportingPlaneHalfX;
  double fSupportingPlaneHalfY;
  double fSupportingPlaneHalfZ;

public:
  SupportPlane();
  ~SupportPlane();
  SupportPlane(unsigned int numOfScintillators,double separation, ScintillatorDetector *envelope);
};

/*
** A full assembly of support structure with scintillator detector
** inserted in the slots
*/
class ScintillatorPlane : public GeometryProperties{

public:
ScintillatorPlane();
~ScintillatorPlane();

};
#endif
