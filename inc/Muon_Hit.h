/*
**	Filename : Muon_Hit.h
**	2025-03-04
**	username : rsehgal
*/
#ifndef Muon_Hit_h
#define Muon_Hit_h

#include "G4VHit.hh"

class Muon_Hit : public G4VHit {
  int fLayerNum;
  int fPlaneNum; // x : 0, y : 1
  int fStripNum;
  int fMaskNum;

public:
  Muon_Hit();
  Muon_Hit(int layerNum, int planeNum, int stripNum, int maskNum = -1);
  virtual ~Muon_Hit();
  int GetChannelNum(int n=10);
  double GetStripCenter();
  void Print();
};
#endif
