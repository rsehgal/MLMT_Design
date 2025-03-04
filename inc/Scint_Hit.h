/*
**	Filename : Scint_Hit.h
**	2025-01-20
**	username : rsehgal
*/
#ifndef Scint_Hit_h
#define Scint_Hit_h

#include "G4VHit.hh"
class Scint_Hit : public G4VHit {
private:
  uint32_t fChannelNum;
  uint64_t fTime;

public:
  Scint_Hit();
  ~Scint_Hit();
  void Fill(uint32_t channelNum, uint64_t tm);
};
#endif
