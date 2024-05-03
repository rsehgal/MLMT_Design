#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TApplication.h>
#include <TF1.h>
int main()
{

  std::ofstream outfile("testdata.csv");
  std::ofstream outfile2("testcentroiddata.csv");
  //TFile *f     = new TFile("block.mac.test.p15p8.root");
  //TFile *f     = new TFile("block.mac.p5m7.root");
  TFile *f     = new TFile("block.mac.m20p20.root");
  
  
  TTree *Block = (TTree *)f->Get("Block");
  // Declaration of leaves types
  UInt_t QNorth;
  UInt_t QSouth;
  UInt_t QEast;
  UInt_t QWest;

  // Set branch addresses.
  Block->SetBranchAddress("QNorth", &QNorth);
  Block->SetBranchAddress("QSouth", &QSouth);
  Block->SetBranchAddress("QEast", &QEast);
  Block->SetBranchAddress("QWest", &QWest);

  Long64_t nentries = Block->GetEntries();

  std::vector<int> pmtX = {0, 50, 25, 25};
  std::vector<int> pmtY = {25, 25, 0, 50};

  Long64_t nbytes = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += Block->GetEntry(i);
    outfile << QNorth << "," << QSouth << "," << QEast << "," << QWest << std::endl;
    double cenValX = (QNorth * pmtX[0] + QSouth * pmtX[1] + QEast * pmtX[2] + QWest * pmtX[3]) /
                     (1. * (QNorth + QSouth + QEast + QWest));
    double cenValY = (QNorth * pmtY[0] + QSouth * pmtY[1] + QEast * pmtY[2] + QWest * pmtY[3]) /
                     (1. * (QNorth + QSouth + QEast + QWest));
    outfile2 << cenValX << "," << cenValY << std::endl;
  }

  f->Close();
  outfile.close();
  outfile2.close();
  return 0;
}
