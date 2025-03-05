/*
**	Filename : Global.cpp
**	2025-03-05
**	username : rsehgal
*/
#include "Global.h"
#include "G4SystemOfUnits.hh"
double gPlaneSizeX = 112.4 * cm;
double gPlaneSizeZ = 112.4 * cm;
double gPlaneSize = 112.4 * cm;
int gNumOfStrips = 100;
int gNumOfStripsX = 100;
int gNumOfStripsZ = 100;

int gNumOfMasks = 10;
std::vector<double> yPosVec = {-80. * cm, -20 * cm, 20 * cm, 80. * cm};
