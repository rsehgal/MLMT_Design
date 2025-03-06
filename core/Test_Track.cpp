/*
**	Filename : Test_Track.cpp
**	2025-03-07
**	username : rsehgal
*/
#include<iostream>
#include "G4ThreeVector.hh"
#include "Helpers.h"
#include "Track.h"

using Vec_t  = G4ThreeVector;

int main(int argc, char *argv[]){

Vec_t p1(5,8,0);
Vec_t q1(6,4,0);
Vec_t p2(6,4,0);
Vec_t q2(7,-2,0);

Track incoming(p1,q1);
Track outgoing(Vec_t(6,4,0),Vec_t(7,-2,0));

incoming.Print();
outgoing.Print();

//Testing POCA with known intersecting line in 2D. 
//This should give (6,4,0) as output
Vec_t poca = POCA(incoming,outgoing);
std::cout << "POCA : " << poca << std::endl;
return 0;
}
