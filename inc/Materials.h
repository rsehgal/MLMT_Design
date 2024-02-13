/*
**	Filename : Materials.h
**	2024-01-02
**	username : rsehgal
**
**	This class is introduced to add user defined materials
**	to the nist database, so that they be access as other
**	materials.
**
**	User Just needs to create an object somewhere,
**	May be in the main program itself.
*/

#ifndef Materials_h
#define Materials_h

class G4Material;
class G4String;
class G4OpticalSurface;
class G4SurfaceProperty;
class G4VisAttributes;

#include <G4String.hh>
#include <map>

class Materials {
private:
  G4Material *fBP;
  G4Material *fHDPE;
  std::map<G4String, G4Material *> fMaterialMap;
  std::map<G4String, G4VisAttributes *> fColor;

  // G4Material *fMirror;

  // To make the class Singleton
  static Materials *s_instance;
  Materials();
  void CreateBoratedPolyethylene();
  void CreateHighDensityPolyethylene();
  void CreateScintillatorMaterial();
  void AttachScintillatorOpticalProperties(G4Material *material);
  void AttachAirOpticalProperties(G4Material *material);

public:
  static Materials *Instance();
  G4SurfaceProperty *GetOpticalSurface(G4String surfaceName = G4String("Mirror"));
  G4SurfaceProperty *GetMirror(G4String mirrorName);
  ~Materials();
  G4Material *GetBP() const;
  G4Material *GetHDPE() const;
  std::map<G4String, G4VisAttributes *> GetColorMap() const;

  /*
  ** Special function as a wrapper to G4Nist
  */
  G4Material *FindOrBuildMaterial(G4String material);
};

#endif
