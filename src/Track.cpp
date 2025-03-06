/*
**	Filename : Track.cpp
**	2025-03-06
**	username : rsehgal
*/
#include <iostream>
#include "Track.h"
//#include "Point3D.h"

Track::Track()
{
  fP1 = G4ThreeVector();
  fP2 = G4ThreeVector();
}

Track::~Track() {}

Track::Track(G4ThreeVector p, G4ThreeVector q)
{
  fP1 = p;
  fP2 = q;
  CalculateDirCosine();
}

void Track::CalculateDirCosine()
{
  fDirCosine = (fP2 - fP1).unit();
  fDirection = (fP2 - fP1).unit();
  fDirRatio  = (fP2 - fP1);
}

G4ThreeVector Track::GetDirCosine() const
{
  return fDirCosine;
}

G4ThreeVector Track::GetP1() const
{
  return fP1;
}

G4ThreeVector Track::GetP2() const
{
  return fP2;
}

void Track::SetP1(G4ThreeVector p)
{
  fP1 = p;
  CalculateDirCosine();
}

void Track::SetP2(G4ThreeVector p)
{
  fP2 = p;
  CalculateDirCosine();
}

double Track::Angle(Track tr)
{
  G4ThreeVector incoming = fP2 - fP1;
  G4ThreeVector outgoing = tr.fP2 - tr.fP1;
  double cosTheta        = incoming.dot(outgoing) / (incoming.mag() * outgoing.mag());
  return std::acos(cosTheta);
}

double Track::GetZenithAngle()
{
  Track ref(G4ThreeVector(0., 0., 0.), G4ThreeVector(0., -1., 0));
  return this->Angle(ref);
}

void Track::Reset(){
 fP1.set(0.,0.,0);
 fP2.set(0.,0.,0);
}
void Track::Print()
{
  std::cout << fP1 << " : " << fP2 << std::endl;
}
