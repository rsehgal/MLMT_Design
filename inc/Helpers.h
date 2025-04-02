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

const double X0 = 5.6; // Radiation length for lead in cm
const double SCATTERING_CONST = 13.6e-3; // 13.6 MeV converted to GeV

extern Vec_t POCA(Track incoming, Track outgoing);
extern Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1);
extern void DrawPoint(const G4ThreeVector& position);

extern double ComputePathLength(double d, double theta_in, double theta_out);
extern double EstimateMomentum(double theta_scatt, double L);
extern double EstimateMomentum(double theta_scatt, double L=20, double Z=82,  double X0=5.6);
#endif
