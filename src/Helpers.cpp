/*
**	Filename : Helpers.cpp
**	2025-03-07
**	username : rsehgal
*/
#include <iostream>
#include "Helpers.h"
#include "G4VisManager.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
using Vec_t     = G4ThreeVector;
using Precision = double;

Vec_t POCA(Vec_t p, Vec_t u, Vec_t q, Vec_t v, Vec_t &p1, Vec_t &q1)
{

  Precision pDotv = p.dot(v);
  Precision qDotv = q.dot(v);
  Precision pDotu = p.dot(u);
  Precision qDotu = q.dot(u);
  Precision uDotv = u.dot(v);
  Precision vMag2 = v.mag2();
  Precision uMag2 = u.mag2();

  Precision s = 0., t = 0.;
  Precision a  = -(pDotv - qDotv) / uDotv;
  Precision b1 = uDotv * (pDotu - qDotu);
  Precision b2 = uMag2 * (pDotv - qDotv);
  Precision b  = b1 - b2;
  Precision c  = (-uDotv * uDotv + vMag2 * uMag2);
  Precision d  = (-vMag2 * b) / (uDotv * c);
  s            = a + d;
  // std::cout<<"B1 : "<<b1<<" : B2 : "<<b2<<std::endl;
  // std::cout<<"A : "<<a<<" : B : "<<b<<" : C : "<<c<<" : D : "<<d<<std::endl;
  // std::cout<<"S : "<<s<<std::endl;

  double numer = (uDotv * (pDotu - qDotu) - uMag2 * (pDotv - qDotv));
  double deno  = (uDotv * uDotv - uMag2 * vMag2);
  t            = numer / deno;
  // std::cout<<"T : "<<t<<std::endl;

  // Vec_t
  p1 = p + u * s;
  // Vec_t
  q1 = q + v * t;

  // std::cout <<"S : " << s <<" : T : " << t << std::endl;
  return (p1 + q1) / 2.;
  // return s;
}

Vec_t POCA(Track incoming, Track outgoing)
{
  Vec_t p1(0., 0., 0.), q1(0., 0., 0.);
  // std::cout<<"INComing Track : "; incoming.Print();
  // std::cout<<"OUTGoing Track : "; outgoing.Print();
  return POCA(incoming.GetP1(), incoming.GetDirCosine(), outgoing.GetP1(), outgoing.GetDirCosine(), p1, q1);
  // return POCA_V3(incoming,outgoing);
}

void DrawPoint(const G4ThreeVector &position)
{
  G4VVisManager *visManager = G4VVisManager::GetConcreteInstance();
  if (!visManager) return;

  // Create a marker (circle) at the given position
  G4Circle circle(position);
  circle.SetScreenSize(5.0); // Adjust size of the point
  circle.SetFillStyle(G4Circle::filled);

  // Set color and attributes
  G4VisAttributes attributes(G4Colour(1.0, 0.0, 0.0)); // Red color
  circle.SetVisAttributes(attributes);

  // Draw in the visualization manager
  visManager->Draw(circle);
}

// const double X0 = 5.6; // Radiation length for lead in cm
// const double SCATTERING_CONST = 13.6e-3; // 13.6 MeV converted to GeV

// Function to compute path length in the material
double ComputePathLength(double d, double theta_in, double theta_out)
{
  double theta_eff = (theta_in + theta_out) / 2.0;
  return d / cos(theta_eff);
}

// Function to estimate muon momentum using Molière’s formula
double EstimateMomentum(double theta_scatt, double L)
{
  if (theta_scatt == 0 || L == 0) return std::numeric_limits<double>::infinity(); // Avoid division by zero

  double log_term = 1 + 0.038 * log(L / X0);
  double p        = (SCATTERING_CONST * sqrt(L / X0) * log_term) / theta_scatt;
  return p;
}

double EstimateMomentum(double theta_scatt, double L, double Z, double X0)
{
  const double highland_factor = 13.6 * MeV;
  if (theta_scatt == 0) return 0; // Avoid division by zero

  double sqrt_factor    = sqrt(L / X0);
  double log_correction = 1.0 + 0.038 * log(L / X0);

  return (highland_factor / theta_scatt) * sqrt_factor * log_correction;
}
