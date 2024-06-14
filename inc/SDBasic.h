/*
**	Filename : SDBasic.h
**	2024-06-14
**	username : rsehgal
*/
#ifndef SDBasic_h
#define SDBasic_h
#include "G4VSensitiveDetector.hh"
class SDBasic : public G4VSensitiveDetector {
private:
  G4String fDetName;

public:
  SDBasic(G4String name);
  virtual ~SDBasic();
  virtual void Initialize(G4HCofThisEvent *hitCollection);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);
  virtual void EndOfEvent(G4HCofThisEvent *hitCollection);
};
#endif
