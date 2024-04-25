/*
**	Filename : SDBlock.h
**	2024-02-15
**	username : rsehgal
*/
#ifndef SDBlock_h
#define SDBlock_h

#include "G4VSensitiveDetector.hh"
#include "vector"
#include <map>
#include <G4String.hh>
#include <map>
#include <memory>

class G4Step;
class G4HCofThisEvent;
class G4String;
class TH1F;
//class Data;
class TFile;
class GeometryProperties;
class DetectorData;
class DataBlock;

class SDBlock : public G4VSensitiveDetector {
private:
  // static
  unsigned int numOfEventsProcessed;
  G4String fDetName;
  DataBlock *fDataBlock;
  

public:
  // SDBlock();
  SDBlock(const G4String &name);
  
  virtual ~SDBlock();

  // methods from base class
  virtual void Initialize(G4HCofThisEvent *hitCollection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hitCollection);

  };

#endif
