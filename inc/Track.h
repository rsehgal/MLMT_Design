/*
**	Filename : Track.h
**	2025-03-06
**	username : rsehgal
*/
#ifndef Track_h
#define Track_h

#include "G4ThreeVector.hh"
class Track {

  G4ThreeVector fP1;
  G4ThreeVector fP2;
  G4ThreeVector fDirection;
  G4ThreeVector fDirCosine;
  G4ThreeVector fDirRatio;

public:
  Track();
  Track(G4ThreeVector p1, G4ThreeVector p2);
  void CalculateDirCosine();
  G4ThreeVector GetP1() const;
  G4ThreeVector GetP2() const;
  void SetP1(G4ThreeVector p);
  void SetP2(G4ThreeVector p);
  double GetZenithAngle();
  double Angle(Track tr);
  G4ThreeVector GetDirCosine() const;

  void Print();
  void Reset();
  ~Track();
};
#endif
