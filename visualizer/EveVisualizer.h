/*
**	Filename : EveVisualizer.h
**	2025-03-10
**	username : rsehgal
*/
#ifndef EveVisualizer_h
#define EveVisualizer_h

#include <TEveManager.h>
#include <TEvePointSet.h>
#include <TColor.h>
#include <vector>

class EveVisualizer{
EveVisualizer();
//TEvePointSet *fPoints;
std::vector<TEvePointSet*> fVecOfPointSet;
double binWidth;
unsigned int numOfBins;
public:
static EveVisualizer *fInstance;
static EveVisualizer* Instance();
void Register(double x, double y, double z, double color = kRed);
void Show();
};

#endif
