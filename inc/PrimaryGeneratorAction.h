/*
**	Filename : PrimaryGeneratorAction.h
**	2024-02-13
**	username : rsehgal
*/
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  // method from the base class
  void GeneratePrimaries(G4Event *);

  // method to access particle gun
  const G4ParticleGun *GetParticleGun() const { return fParticleGun; }

private:
  G4ParticleGun *fParticleGun; // pointer a to G4 gun class
                               // G4Box* fEnvelopeBox;
};


#endif
