/*
**	Filename : SD.h
**	2024-12-21
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
#include "HitCollections.h"
class G4Step;
class G4HCofThisEvent;
class G4String;
class TH1F;
class TFile;

class SD : public G4VSensitiveDetector {

  MuonHitCollection *fMuonHitCollection;

public:
  SD(const G4String name);
  SD(const G4String name, G4String collName);
  ~SD();

  // methods from base class
  virtual void Initialize(G4HCofThisEvent *hitCollection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hitCollection);
};

#endif
