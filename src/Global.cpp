/*
**	Filename : Global.cpp
**	2025-03-05
**	username : rsehgal
*/
#include "G4SystemOfUnits.hh"
#include "Global.h"
std::vector<double> yPosVec = {-140 * cm, -110 * cm, -80. * cm, -50 * cm, 50 * cm, 80. * cm};
//std::vector<double> yPosVec = {-140 * cm, -110 * cm, -80. * cm, -50 * cm};//, 50 * cm, 80. * cm};
//std::vector<double> yPosVec = {-100. * cm, -50 * cm, 50 * cm, 100. * cm};

//This must be defined to a value above topmost plane.
//double gunPos = 110*cm;
double gunPos = 90*cm;
//double gunPos = -40*cm;

//The lowermost value used to generated random direction, if not using CRY
//This value should be less than bottom-most plane
double ybottom = -160.*cm;

std::map<int, G4ThreeVector> hitPointVec;
std::map<int, G4ThreeVector> momentumVec;
std::map<int, G4ThreeVector> stripNumVec;

std::map<int, G4ThreeVector> exactHitPointVec;
std::map<int, G4ThreeVector> randomizeHitPointVec;

void InitializeHitPointVec() {
  for (unsigned int i = 0; i < yPosVec.size(); i++) {
    hitPointVec[i] = G4ThreeVector(-50000., yPosVec[i], -50000.);
    exactHitPointVec[i] = G4ThreeVector(-50000., yPosVec[i], -50000.);
    randomizeHitPointVec[i] = G4ThreeVector(-50000., yPosVec[i], -50000.);
    momentumVec[i] = G4ThreeVector(0.,0.,0.);
    stripNumVec[i] = G4ThreeVector(-50000., yPosVec[i], -50000.);
  }
}

std::vector<G4ThreeVector> vecOfPts;


double scintHalfy = 0.5*cm;

//double scintHalfx = 3.125*cm;//0.5*cm;
//double scintHalfz = 52*cm ;
//unsigned int numOfScintillators = 16;
//unsigned int numOfGroups = 4;

double scintHalfx = 0.5*cm;//0.5*cm;
double scintHalfz = 56.2*cm ;
unsigned int numOfScintillators = 100;
unsigned int numOfGroups = 10;

double gPlaneSizeZ = scintHalfz*2;//112.4 * cm;
double gPlaneSizeX = gPlaneSizeZ;//112.4 * cm;
double gPlaneSize = gPlaneSizeZ;//112.4 * cm;
int gNumOfStrips =  numOfScintillators;//100;
int gNumOfStripsX = numOfScintillators;//100;
int gNumOfStripsZ = numOfScintillators;//100;
int gNumOfMasks = numOfGroups;//10;


