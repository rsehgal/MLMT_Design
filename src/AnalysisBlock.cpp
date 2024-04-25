/*
**	Filename : AnalysisBlock.cpp
**	2024-02-21
**	username : rsehgal
*/
#include "AnalysisBlock.h"
#include <TFile.h>
#include <iostream>
#include "DataBlock.h"

AnalysisBlock *AnalysisBlock::s_instance = 0;

AnalysisBlock *AnalysisBlock::Create(std::string filename) {
  if (!s_instance)
    s_instance = new AnalysisBlock(filename);
  return s_instance;
}

AnalysisBlock *AnalysisBlock::Instance() {
  if (!s_instance)
    std::cout << "AnalysisBlock object does not exist in memory, Please create it first..." << std::endl;
  else
    return s_instance;
}

AnalysisBlock::AnalysisBlock(std::string filename) {
  fp = new TFile(filename.c_str(), "RECREATE");
  fData = new DataBlock();
}

DataBlock* AnalysisBlock::GetData() const {
return fData;
}

void AnalysisBlock::Close() {
  fData->Write();
  fp->Close();
  //std::cout <<"Fillleeeee Closeeeeddd..........." << std::endl;
}


