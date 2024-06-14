/*
**	Filename : Test_Point3D_Tree.cpp
**	2024-06-13
**	username : rsehgal
*/
#include <iostream>
#include "Point3D.h"
#include <TFile.h>
#include <TTree.h>
int main(int argc, char *argv[])
{

  TFile *fp = new TFile("test.root", "RECREATE");
  Point3D vect(0., 0., 0.);
  TTree *tr = new TTree("testTree", "testTree");
  tr->Branch("Point3D", &vect);
  vect.Set(1., 2., 3.);
  tr->Fill();
  vect.Set(9., 10., 11);
  tr->Fill();
  vect.Set(9., 10., 11);
  tr->Fill();
  fp->Write();
}
