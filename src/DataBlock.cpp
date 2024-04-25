/*
**	Filename : DataBlock.cpp
**	2024-02-21
**	username : rsehgal
*/
#include "DataBlock.h"
#include <TH1F.h>
#include <TTree.h>
#include <iostream>

DataBlock::DataBlock()
{
  fTree = new TTree("Block","Block");
  //fTree->Branch("EventNum", &fEvNo);
  fTree->Branch("QNorth", &fQNorth);
  fTree->Branch("QSouth", &fQSouth);
  fTree->Branch("QEast", &fQEast);
  fTree->Branch("QWest", &fQWest);
  
}

void DataBlock::Reset(){
  fQNorth = 0;
  fQSouth = 0;
  fQEast = 0;
  fQWest = 0;
  fTNorth = 0;
  fTSouth=0;
  fTEast = 0;
  fTWest = 0;
}

DataBlock::~DataBlock() {}

unsigned int DataBlock::GetCount() const
{
  return fTree->GetEntries();
}

void DataBlock::Print(){
  std::cout <<"========== RAMAN ============" << std::endl;
  std::cout << "North " << fQNorth << std::endl
            << "South " << fQSouth << std::endl
            << "East " << fQEast << std::endl
            << "West " << fQWest << std::endl;
}

void DataBlock::Fill(unsigned int evNo,unsigned int qnorth, unsigned int qsouth,
                unsigned int qeast, unsigned int qwest)
{
  fEvNo      = evNo;
  fQNorth     = qnorth;
  fQSouth = qsouth;
  fQEast = qeast;
  fQWest = qwest;

  Fill();
}

void DataBlock::Fill()
{
  fTree->Fill();
  //std::cout <<"Treeeee Filledddddddddddddddd......." << std::endl;
}

void DataBlock::Write()
{
  fTree->CloneTree()->Write();
  //std::cout <<"Treeeeeee Writtteeennnn............." << std::endl;
}
