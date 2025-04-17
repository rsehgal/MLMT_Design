#ifndef POCA_HIT_HH
#define POCA_HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
class PoCA_Hit : public G4VHit {
public:
   G4ThreeVector fStepDirection;
   G4ThreeVector fStepPosition;

public:
  PoCA_Hit();
  PoCA_Hit(G4ThreeVector vecDir, G4ThreeVector vecPos);
  virtual ~PoCA_Hit();
  void Fill(G4ThreeVector vecDir, G4ThreeVector vecPos);
  void Print();
};


#endif
