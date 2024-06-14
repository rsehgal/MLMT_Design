/*
**	Filename : DataBasic.cpp
**	2024-06-13
**	username : rsehgal
*/
#include <iostream>
#include "DataBasic.h"
#include "Point3D.h"
#include <TTree.h>

DataBasic::DataBasic()
{
  // Defining TTree structure
  fTree = new TTree("BasicDataTree", "BasicDataTree");
  fTree->Branch("Point3D", &fPoint);
  fTree->Branch("Time", &fTime);
}

DataBasic::DataBasic(Point3D *pt, double tm)
{
  fPoint.Set(pt->GetX(), pt->GetY(), pt->GetZ());
  fTime = tm;
}

DataBasic::DataBasic(double x, double y, double z, double tm)
{
  fPoint.Set(x, y, z);
  fTime = tm;
}

void DataBasic::Fill(Point3D *pt, double tm)
{
  fPoint.Set(pt->GetX(), pt->GetY(), pt->GetZ());
  fTime = tm;
  Fill();
}

void DataBasic::Fill(double x, double y, double z, double tm)
{
  fPoint.Set(x, y, z);
  fTime = tm;
  Fill();
}

void DataBasic::Fill()
{
  fTree->Fill();
}

void DataBasic::Write()
{
  fTree->Write();
}