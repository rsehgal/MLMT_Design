/*
**	Filename : SD.h
**	2024-02-15
**	username : rsehgal
*/
#ifndef SD_h
#define SD_h

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

class SD : public G4VSensitiveDetector {
private:
  // static
  unsigned int numOfEventsProcessed;
  //unsigned int fPhotonCounter_LPMT;
  //unsigned int fPhotonCounter_RPMT;
  G4String fDetName;
  GeometryProperties *fGeom;

  std::map<unsigned int,std::shared_ptr<DetectorData>> fDataMap;  

public:
  // SD();
  SD(const G4String &name);
  SD(const G4String &name,GeometryProperties *geom);
  virtual ~SD();

  // methods from base class
  virtual void Initialize(G4HCofThisEvent *hitCollection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hitCollection);

  };

#endif
