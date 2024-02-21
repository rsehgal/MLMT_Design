/*
**	Filename : Analysis.cpp
**	2024-02-21
**	username : rsehgal
*/
#include "Analysis.h"
#include <TFile.h>
#include <iostream>
#include "Data.h"

Analysis *Analysis::s_instance = 0;

Analysis *Analysis::Create(std::string filename) {
  if (!s_instance)
    s_instance = new Analysis(filename);
  return s_instance;
}

Analysis *Analysis::Instance() {
  if (!s_instance)
    std::cout << "Analysis object does not exist in memory, Please create it first..." << std::endl;
  else
    return s_instance;
}

Analysis::Analysis(std::string filename) {
  fp = new TFile(filename.c_str(), "RECREATE");
  fData = new Data();
}

Data* Analysis::GetData() const {
return fData;
}

void Analysis::Close() {
  fData->Write();
  fp->Close();
}


