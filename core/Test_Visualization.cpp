/*
**	Filename : Test_Visualization.cpp
**	2025-03-07
**	username : rsehgal
*/
#include<iostream>
#include "Helpers.h"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
int main(int argc, char *argv[]){

G4ThreeVector myPoint(10.0 * cm, 20.0 * cm, 30.0 * cm);
DrawPoint(myPoint);

return 0;
}
