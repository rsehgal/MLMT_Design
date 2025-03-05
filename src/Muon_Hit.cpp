/*
**	Filename : Muon_Hit.cpp
**	2025-03-04
**	username : rsehgal
*/
#include <iostream>
#include "Muon_Hit.h"
#include "colors.h"
#include "Global.h"

Muon_Hit::Muon_Hit() : fLayerNum(-1), fPlaneNum(-1), fStripNum(-1), fMaskNum(-1) {}

Muon_Hit::Muon_Hit(int layerNum, int planeNum, int stripNum, int maskNum, unsigned long long tme)
    : fLayerNum(layerNum), fPlaneNum(planeNum), fStripNum(stripNum), fMaskNum(maskNum), fTime(tme)
{
}

Muon_Hit::~Muon_Hit() {}

void Muon_Hit::Print()
{
  if (fMaskNum < 0)
    std::cout << MAGENTA;
  else
    std::cout << BLUE;
  std::cout << "LayerNum : " << fLayerNum << " : PlaneNum : " << fPlaneNum << " : StripNum : " << fStripNum << " : StripCenter : " << GetStripCenter()
            << " : ChannelNum : " << GetChannelNum() << " : MaskNum : " << fMaskNum << " : Timestamp : " << fTime << RESET << std::endl;
}

int Muon_Hit::GetChannelNum(int n)
{
  if (fMaskNum < 0.)
    return fLayerNum * 4 * n + fPlaneNum * 2 * n + n + fStripNum;
  else
    return fLayerNum * 4 * n + fPlaneNum * 2 * n + fStripNum;
}

double Muon_Hit::GetStripCenter()
{
  double stripWidth = gPlaneSize / gNumOfStrips;
  double maskWidth = gPlaneSize / gNumOfMasks;
  double center     = -1. * gPlaneSize / 2. + maskWidth*fMaskNum + stripWidth * fStripNum + stripWidth / 2.;
  return center;
}
