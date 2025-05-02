{
  gStyle->SetPalette(kRainbow);
  TFile *fp       = new TFile("out.root", "r");
  TTree *pocaTree = (TTree *)fp->Get("ReconsMuonHits");
  // Declaration of leaves types
  Double_t layerNum;
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t stripNumX;
  Double_t stripNumZ;

  // Set branch addresses.
  pocaTree->SetBranchAddress("layerNum", &layerNum);
  pocaTree->SetBranchAddress("x", &x);
  pocaTree->SetBranchAddress("y", &y);
  pocaTree->SetBranchAddress("z", &z);
  pocaTree->SetBranchAddress("stripNumX", &stripNumX);
  pocaTree->SetBranchAddress("stripNumZ", &stripNumZ);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // pocaTree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = pocaTree->GetEntries();

  Long64_t nbytes = 0;

  TCanvas *can = new TCanvas;
  can->Divide(3,2);

  TH2F *pixelHist_3 = new TH2F("pixelHist_3", "pixelHist_3", 100, 0, 100, 100, 0, 100);
  TH2F *pixelHist_2 = new TH2F("pixelHist_2", "pixelHist_2", 100, 0, 100, 100, 0, 100);
  TH2F *pixelHist_1 = new TH2F("pixelHist_1", "pixelHist_1", 100, 0, 100, 100, 0, 100);
  TH2F *pixelHist_0 = new TH2F("pixelHist_0", "pixelHist_0", 100, 0, 100, 100, 0, 100);


  pixelHist_3->GetXaxis()->SetTitle("X Strip Number");
  pixelHist_3->GetXaxis()->CenterTitle(true);
  pixelHist_3->GetXaxis()->SetTitleFont(42);
  pixelHist_3->GetXaxis()->SetTitleSize(0.05);
  pixelHist_3->GetXaxis()->SetLabelSize(0.05);
  pixelHist_3->GetYaxis()->SetTitle("Z Strip Number");
  pixelHist_3->GetYaxis()->CenterTitle(true);
  pixelHist_3->GetYaxis()->SetTitleFont(42);
  pixelHist_3->GetYaxis()->SetTitleSize(0.05);
  pixelHist_3->GetYaxis()->SetLabelSize(0.05);
  pixelHist_3->GetYaxis()->SetTitleOffset(1.1);
 
  pixelHist_2->GetXaxis()->SetTitle("X Strip Number");
  pixelHist_2->GetXaxis()->CenterTitle(true);
  pixelHist_2->GetXaxis()->SetTitleFont(42);
  pixelHist_2->GetXaxis()->SetTitleSize(0.05);
  pixelHist_2->GetXaxis()->SetLabelSize(0.05);
  pixelHist_2->GetYaxis()->SetTitle("Z Strip Number");
  pixelHist_2->GetYaxis()->CenterTitle(true);
  pixelHist_2->GetYaxis()->SetTitleFont(42);
  pixelHist_2->GetYaxis()->SetTitleSize(0.05);
  pixelHist_2->GetYaxis()->SetLabelSize(0.05);
  pixelHist_2->GetYaxis()->SetTitleOffset(1.1);
 
  pixelHist_1->GetXaxis()->SetTitle("X Strip Number");
  pixelHist_1->GetXaxis()->CenterTitle(true);
  pixelHist_1->GetXaxis()->SetTitleFont(42);
  pixelHist_1->GetXaxis()->SetTitleSize(0.05);
  pixelHist_1->GetXaxis()->SetLabelSize(0.05);
  pixelHist_1->GetYaxis()->SetTitle("Z Strip Number");
  pixelHist_1->GetYaxis()->CenterTitle(true);
  pixelHist_1->GetYaxis()->SetTitleFont(42);
  pixelHist_1->GetYaxis()->SetTitleSize(0.05);
  pixelHist_1->GetYaxis()->SetLabelSize(0.05);
  pixelHist_1->GetYaxis()->SetTitleOffset(1.1);
  
  pixelHist_0->GetXaxis()->SetTitle("X Strip Number");
  pixelHist_0->GetXaxis()->CenterTitle(true);
  pixelHist_0->GetXaxis()->SetTitleFont(42);
  pixelHist_0->GetXaxis()->SetTitleSize(0.05);
  pixelHist_0->GetXaxis()->SetLabelSize(0.05);
  pixelHist_0->GetYaxis()->SetTitle("Z Strip Number");
  pixelHist_0->GetYaxis()->CenterTitle(true);
  pixelHist_0->GetYaxis()->SetTitleFont(42);
  pixelHist_0->GetYaxis()->SetTitleSize(0.05);
  pixelHist_0->GetYaxis()->SetLabelSize(0.05);
  pixelHist_0->GetYaxis()->SetTitleOffset(1.1);
  

  gStyle->SetOptStat(0000);
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += pocaTree->GetEntry(i);

    if(layerNum==3)
	pixelHist_3->Fill(stripNumX,stripNumZ);
    if(layerNum==2)
	pixelHist_2->Fill(stripNumX,stripNumZ);    
    if(layerNum==1)
	pixelHist_1->Fill(stripNumX,stripNumZ);    
    if(layerNum==0)
	pixelHist_0->Fill(stripNumX,stripNumZ);



  }
  
pixelHist_3->Smooth(1);
pixelHist_2->Smooth(1);
pixelHist_1->Smooth(1);
pixelHist_0->Smooth(1);
  

new TCanvas("Layer3","Layer3");
pixelHist_3->Draw("colz");
new TCanvas("Layer2","Layer2");
pixelHist_2->Draw("colz");
new TCanvas("Layer1","Layer1");
pixelHist_1->Draw("colz");
new TCanvas("Layer0","Layer0");
pixelHist_0->Draw("colz");



}
