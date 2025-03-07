/*
**	Filename : Helpers.cpp
**	2025-03-07
**	username : rsehgal
*/
#include<iostream>
#include "Helpers.h"
#include "G4VisManager.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

using Vec_t = G4ThreeVector;
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
	Precision a = -(pDotv - qDotv) / uDotv;
	Precision b1 = uDotv * (pDotu - qDotu);
	Precision b2 = uMag2 * (pDotv - qDotv);
	Precision b = b1 - b2;
	Precision c = (-uDotv * uDotv + vMag2 * uMag2);
	Precision d = (-vMag2 * b) / (uDotv * c);
	s = a + d;
	//std::cout<<"B1 : "<<b1<<" : B2 : "<<b2<<std::endl;
	//std::cout<<"A : "<<a<<" : B : "<<b<<" : C : "<<c<<" : D : "<<d<<std::endl;
	//std::cout<<"S : "<<s<<std::endl;

	double numer = (uDotv * (pDotu - qDotu) - uMag2 * (pDotv - qDotv));
	double deno = (uDotv * uDotv - uMag2 * vMag2);
	t = numer / deno;
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


void DrawPoint(const G4ThreeVector& position) {
    G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
    if (!visManager) return;

    // Create a marker (circle) at the given position
    G4Circle circle(position);
    circle.SetScreenSize(5.0);  // Adjust size of the point
    circle.SetFillStyle(G4Circle::filled);

    // Set color and attributes
    G4VisAttributes attributes(G4Colour(1.0, 0.0, 0.0));  // Red color
    circle.SetVisAttributes(attributes);

    // Draw in the visualization manager
    visManager->Draw(circle);
}

