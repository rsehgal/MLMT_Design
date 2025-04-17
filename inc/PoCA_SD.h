#ifndef POCA_SD_HH
#define POCA_SD_HH

#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "HitCollections.h"

class PoCA_SD : public G4VSensitiveDetector {

   PoCAHitCollection *fPoCAHitCollection;
public:
    PoCA_SD(const G4String& name, const G4String &collName);
    virtual ~PoCA_SD();
    virtual void Initialize(G4HCofThisEvent *hce);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent *hce);
};

#endif
