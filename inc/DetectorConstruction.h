/*
**	Filename : DetectorConstruction.h
**	2023-12-29
**	username : rsehgal
*/
#ifndef DetectorConstruction_h
#define DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VUserDetectorConstruction;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4SDManager;
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction {
  // G4Material *fScintMaterial;
  G4LogicalVolume *logicalWorld;

public:
  DetectorConstruction();
  ~DetectorConstruction();
  G4VPhysicalVolume *Construct();
  G4LogicalVolume *GetLogicalWorld() const;

public:
  G4SDManager *fSDMan;
};
#endif
