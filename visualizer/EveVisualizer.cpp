/*
**	Filename : EveVisualizer.cpp
**	2025-03-10
**	username : rsehgal
*/
#include <iostream>
#include "EveVisualizer.h"
#include "TStyle.h"
EveVisualizer *EveVisualizer::fInstance = nullptr;

EveVisualizer::EveVisualizer()
{

  gStyle->SetPalette(kRainbow);
  int numColors = gStyle->GetNumberOfColors();
  numOfBins     = numColors; // 50;
  binWidth      = 0.7 / numOfBins;
  TEveManager::Create();
  for (unsigned int i = 0; i < numOfBins; i++) {
    // for (unsigned int i = 0; i < numColors; i++) {
    TEvePointSet *pointSet = new TEvePointSet;
    pointSet->SetMarkerStyle(20);
    pointSet->SetMarkerSize(0.1);
    pointSet->SetMarkerColor(i);
    fVecOfPointSet.push_back(pointSet);
  }
  // fPoints->SetMarkerColor(kRed);
}

EveVisualizer *EveVisualizer::Instance()
{
  if (!fInstance) fInstance = new EveVisualizer();

  return fInstance;
}

void EveVisualizer::Register(double x, double y, double z, double dev)
{
  // int index = fPoints->GetN();
  // fPoints->SetNextPoint(x,y,z);
  int binNum = dev / binWidth;
  fVecOfPointSet[binNum]->SetNextPoint(x, y, z);
  // fPoints->SetPointColor(index,color);
}

void EveVisualizer::Show()
{
  for (unsigned int i = 0; i < numOfBins; i++)
    gEve->AddElement(fVecOfPointSet[i]);
}
