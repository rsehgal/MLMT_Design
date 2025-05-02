{
  gStyle->SetPalette(kRainbow);
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

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // pocaTree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = pocaTree->GetEntries();

  Long64_t nbytes = 0;

  TCanvas *can = new TCanvas;
  can->Divide(2,2);

  TH2F *histxz = new TH2F("pocaXZ", "pocaXZ", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxy = new TH2F("pocaXY", "pocaXY", 1200, -600, 600, 1200, -600, 600);
  TH2F *histyz = new TH2F("pocaYZ", "pocaYZ", 1200, -600, 600, 1200, -600, 600);
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += pocaTree->GetEntry(i);
    if (dev > 0.09) {
      histxz->Fill(x, z);
      histxy->Fill(x, y);
      histyz->Fill(y, z);
    }
  }
  can->cd(1);;
  histxz->Draw("colz"); 

  can->cd(2);
  histxy->Draw("colz");

  can->cd(3);
  histyz->Draw("colz");


}
