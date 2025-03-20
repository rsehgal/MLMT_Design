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
  can->Divide(3,2);

  TH2F *histxz = new TH2F("pocaXZ", "pocaXZ", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxy = new TH2F("pocaXY", "pocaXY", 1200, -600, 600, 1200, -600, 600);
  TH2F *histyz = new TH2F("pocaYZ", "pocaYZ", 1200, -600, 600, 1200, -600, 600);

/*  TH2F *histxyS1 = new TH2F("pocaXYS1", "XY Plane Slice 1", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS2 = new TH2F("pocaXYS2", "XY Plane Slice 2", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS3 = new TH2F("pocaXYS3", "XY Plane Slice 3", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS4 = new TH2F("pocaXYS4", "XY Plane Slice 4", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS5 = new TH2F("pocaXYS5", "XY Plane Slice 5", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS6 = new TH2F("pocaXYS6", "XY Plane Slice 6", 1200, -600, 600, 1200, -600, 600);
*/
  TH2F *histxyS1 = new TH2F("pocaXYS1", "Z ~ -200 mm", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS2 = new TH2F("pocaXYS2", "Z ~ -100 mm", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS3 = new TH2F("pocaXYS3", "Z ~ -40 mm", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS4 = new TH2F("pocaXYS4", "Z ~ 40 mm", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS5 = new TH2F("pocaXYS5", "Z ~ 100 mm", 1200, -600, 600, 1200, -600, 600);
  TH2F *histxyS6 = new TH2F("pocaXYS6", "Z ~ 200 mm", 1200, -600, 600, 1200, -600, 600);


  histxyS1->GetXaxis()->SetTitle("X position(mm)");
  histxyS1->GetXaxis()->CenterTitle(true);
  histxyS1->GetXaxis()->SetTitleFont(42);
  histxyS1->GetXaxis()->SetTitleSize(0.05);
  histxyS1->GetXaxis()->SetLabelSize(0.05);
  histxyS1->GetYaxis()->SetTitle("Y position(mm)");
  histxyS1->GetYaxis()->CenterTitle(true);
  histxyS1->GetYaxis()->SetTitleFont(42);
  histxyS1->GetYaxis()->SetTitleSize(0.05);
  histxyS1->GetYaxis()->SetLabelSize(0.05);
  histxyS1->GetYaxis()->SetTitleOffset(1.1);

  histxyS2->GetXaxis()->SetTitle("X position(mm)");
  histxyS2->GetXaxis()->CenterTitle(true);
  histxyS2->GetXaxis()->SetTitleFont(42);
  histxyS2->GetXaxis()->SetTitleSize(0.05);
  histxyS2->GetXaxis()->SetLabelSize(0.05);
  histxyS2->GetYaxis()->SetTitle("Y position(mm)");
  histxyS2->GetYaxis()->CenterTitle(true);
  histxyS2->GetYaxis()->SetTitleFont(42);
  histxyS2->GetYaxis()->SetTitleSize(0.05);
  histxyS2->GetYaxis()->SetLabelSize(0.05);
  histxyS2->GetYaxis()->SetTitleOffset(1.1);

  histxyS3->GetXaxis()->SetTitle("X position(mm)");
  histxyS3->GetXaxis()->CenterTitle(true);
  histxyS3->GetXaxis()->SetTitleFont(42);
  histxyS3->GetXaxis()->SetTitleSize(0.05);
  histxyS3->GetXaxis()->SetLabelSize(0.05);
  histxyS3->GetYaxis()->SetTitle("Y position(mm)");
  histxyS3->GetYaxis()->CenterTitle(true);
  histxyS3->GetYaxis()->SetTitleFont(42);
  histxyS3->GetYaxis()->SetTitleSize(0.05);
  histxyS3->GetYaxis()->SetLabelSize(0.05);
  histxyS3->GetYaxis()->SetTitleOffset(1.1);

  histxyS4->GetXaxis()->SetTitle("X position(mm)");
  histxyS4->GetXaxis()->CenterTitle(true);
  histxyS4->GetXaxis()->SetTitleFont(42);
  histxyS4->GetXaxis()->SetTitleSize(0.05);
  histxyS4->GetXaxis()->SetLabelSize(0.05);
  histxyS4->GetYaxis()->SetTitle("Y position(mm)");
  histxyS4->GetYaxis()->CenterTitle(true);
  histxyS4->GetYaxis()->SetTitleFont(42);
  histxyS4->GetYaxis()->SetTitleSize(0.05);
  histxyS4->GetYaxis()->SetLabelSize(0.05);
  histxyS4->GetYaxis()->SetTitleOffset(1.1);

  histxyS5->GetXaxis()->SetTitle("X position(mm)");
  histxyS5->GetXaxis()->CenterTitle(true);
  histxyS5->GetXaxis()->SetTitleFont(42);
  histxyS5->GetXaxis()->SetTitleSize(0.05);
  histxyS5->GetXaxis()->SetLabelSize(0.05);
  histxyS5->GetYaxis()->SetTitle("Y position(mm)");
  histxyS5->GetYaxis()->CenterTitle(true);
  histxyS5->GetYaxis()->SetTitleFont(42);
  histxyS5->GetYaxis()->SetTitleSize(0.05);
  histxyS5->GetYaxis()->SetLabelSize(0.05);
  histxyS5->GetYaxis()->SetTitleOffset(1.1);

  histxyS6->GetXaxis()->SetTitle("X position(mm)");
  histxyS6->GetXaxis()->CenterTitle(true);
  histxyS6->GetXaxis()->SetTitleFont(42);
  histxyS6->GetXaxis()->SetTitleSize(0.05);
  histxyS6->GetXaxis()->SetLabelSize(0.05);
  histxyS6->GetYaxis()->SetTitle("Y position(mm)");
  histxyS6->GetYaxis()->CenterTitle(true);
  histxyS6->GetYaxis()->SetTitleFont(42);
  histxyS6->GetYaxis()->SetTitleSize(0.05);
  histxyS6->GetYaxis()->SetLabelSize(0.05);
  histxyS6->GetYaxis()->SetTitleOffset(1.1);

 
  

  gStyle->SetOptStat(0000);
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += pocaTree->GetEntry(i);
    if (dev > 0.08) {
      /*histxz->Fill(x, z);
      if(z > -10 && z < 10)
      histxy->Fill(x, y);
      if(x > -10 && x < 10)
      histyz->Fill(z, y);*/

 if(z > -200 && z < -190)
      histxyS1->Fill(x, y);

 if(z > -100 && z < -90)
      histxyS2->Fill(x, y);
 if(z > -50 && z < -40)
      histxyS3->Fill(x, y);
 if(z > 40 && z < 50)
      histxyS4->Fill(x, y);

 if(z > 90 && z < 100)
      histxyS5->Fill(x, y);

if(z > 190 && z < 200)
      histxyS6->Fill(x, y);
    }
  }
  

    
  histxyS1->RebinX(4);
  histxyS1->RebinY(4);
  histxyS1->Smooth(1);
  histxyS1->Smooth(1);

  histxyS2->RebinX(4);
  histxyS2->RebinY(4);
  histxyS2->Smooth(1);
  histxyS2->Smooth(1);

  histxyS3->RebinX(4);
  histxyS3->RebinY(4);
  histxyS3->Smooth(1);
  histxyS3->Smooth(1);

  histxyS4->RebinX(4);
  histxyS4->RebinY(4);
  histxyS4->Smooth(1);
  histxyS4->Smooth(1);

  histxyS5->RebinX(4);
  histxyS5->RebinY(4);
  histxyS5->Smooth(1);
  histxyS5->Smooth(1);

  histxyS6->RebinX(4);
  histxyS6->RebinY(4);
  histxyS6->Smooth(1);
  histxyS6->Smooth(1);

  can->cd(1);
  histxyS1->Draw("colz");
  can->cd(2);
  histxyS2->Draw("colz");
  can->cd(3);
  histxyS3->Draw("colz");
  can->cd(4);;
  histxyS4->Draw("colz");
  can->cd(5);;
  histxyS5->Draw("colz");
 can->cd(6);;
  histxyS6->Draw("colz");

}
