/*
**	Filename : Global.cpp
**	2025-03-05
**	username : rsehgal
*/
#include "G4SystemOfUnits.hh"
#include "Global.h"
double gPlaneSizeX = 112.4 * cm;
double gPlaneSizeZ = 112.4 * cm;
double gPlaneSize = 112.4 * cm;
int gNumOfStrips = 100;
int gNumOfStripsX = 100;
int gNumOfStripsZ = 100;

int gNumOfMasks = 10;
//std::vector<double> yPosVec = {-140 * cm, -110 * cm, -80. * cm, -50 * cm, 50 * cm, 80. * cm};
std::vector<double> yPosVec = {-100. * cm, -50 * cm, 50 * cm, 100. * cm};

std::map<int, G4ThreeVector> hitPointVec;
std::map<int, G4ThreeVector> momentumVec;

void InitializeHitPointVec() {
  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    hitPointVec[i] = G4ThreeVector(-50000., yPosVec[i], -50000.);
    momentumVec[i] = G4ThreeVector(0.,0.,0.);
  }
}

std::vector<G4ThreeVector> vecOfPts;


double scintHalfx = 3.125*cm;//0.5*cm;
double scintHalfy = 3.125*cm;
double scintHalfz = 52*cm ;
unsigned int numOfScintillators = 16;
unsigned int numOfGroups = 4;
