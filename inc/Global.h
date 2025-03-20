/*
**	Filename : Global.h
**	2025-03-05
**	username : rsehgal
*/
#ifndef Global_h
#define Global_h

#include <vector>
#include <map>
#include <G4ThreeVector.hh>

extern double gPlaneSizeX;
extern double gPlaneSizeZ;
extern double gPlaneSize;
extern int gNumOfStrips;
extern int gNumOfStripsX;
extern int gNumOfStripsZ;

extern int gNumOfMasks;
extern std::vector<double> yPosVec;
extern std::map<int,G4ThreeVector> hitPointVec;
extern std::map<int,G4ThreeVector> momentumVec;


extern void InitializeHitPointVec();

extern std::vector<G4ThreeVector> vecOfPts;

extern double scintHalfx ;
extern double scintHalfy ;
extern double scintHalfz ;
extern unsigned int numOfScintillators;
extern unsigned int numOfGroups;

#endif
