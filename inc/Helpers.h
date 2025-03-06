/*
**	Filename : Helpers.h
**	2025-03-07
**	username : rsehgal
*/
#ifndef Helpers_h
#define Helpers_h

#include "G4ThreeVector.hh"
#include "Track.h"

using Vec_t = G4ThreeVector;

extern Vec_t POCA(Track incoming, Track outgoing);
extern Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1);

#endif
