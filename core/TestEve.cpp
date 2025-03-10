#include <TEveManager.h>
#include <TEvePointSet.h>
#include <TApplication.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include "EveVisualizer.h"
int main(int argc, char **argv)
{
  // Create a ROOT application
  TApplication app("TEve Example", &argc, argv);

  EveVisualizer *vis = EveVisualizer::Instance();
  //---------------------
  TFile *fp       = new TFile("out.root", "r");
  TTree *pocaTree = (TTree *)fp->Get("pocaTree");
  // Declaration of leaves types
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t dev;
  Double_t eventNum;

  // Set branch addresses.
  pocaTree->SetBranchAddress("x", &x);
  pocaTree->SetBranchAddress("y", &y);
  pocaTree->SetBranchAddress("z", &z);
  pocaTree->SetBranchAddress("dev", &dev);
  pocaTree->SetBranchAddress("eventNum", &eventNum);

  Long64_t nentries = pocaTree->GetEntries();

  Long64_t nbytes = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += pocaTree->GetEntry(i);
    if(dev > 0.08)
       vis->Register(x,y,z,dev);
    //points->SetNextPoint(x, y, z);
  }
  //--------------------

  // Add some points
  /*    points->SetNextPoint(1.0, 2.0, 3.0);
      points->SetNextPoint(-1.0, -2.0, -3.0);
      points->SetNextPoint(2.0, -1.0, 1.5);
  */
  // Add to the TEve viewer
  //gEve->AddElement(points);
  vis->Show();

  std::cout << "ALLL Points added................" << std::endl;
  // Run the ROOT event loop
  app.Run();

  return 0;
}
