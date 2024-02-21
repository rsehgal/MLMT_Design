/*
**	Filename : Data.cpp
**	2024-02-21
**	username : rsehgal
*/
#include "Data.h"
#include <TH1F.h>
#include <TTree.h>
#include <iostream>

Data::Data()
{
  fTree = new TTree("MLMT","MLMT");
  fTree->Branch("EventNum", &fEvNo);
  fTree->Branch("DetectorNo", &fDetNo);
  fTree->Branch("TNear", &fTNear);
  fTree->Branch("TFar", &fTFar);
  fTree->Branch("QNear", &fQNear);
  fTree->Branch("QFar", &fQFar);
}

Data::~Data() {}

unsigned int Data::GetCount() const
{
  return fTree->GetEntries();
}

void Data::Fill(unsigned int evNo, unsigned int detNo, unsigned long int tnear, unsigned long int tfar,
                unsigned int qnear, unsigned int qfar)
{
  fEvNo      = evNo;
  fDetNo = detNo;
  fTNear     = tnear;
  fTFar      = tfar;
  fQNear     = qnear;
  fQFar      = qfar;

  Fill();
}

void Data::Fill()
{
  fTree->Fill();
}

void Data::Write()
{
  fTree->Write();
}
