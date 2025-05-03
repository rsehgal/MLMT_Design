void tree(char *filename)
{
  gStyle->SetPalette(kRainbow);
  gStyle->SetOptStat(0000);
  //TFile *f    = new TFile("/home/rsehgal/shared/image_xgboost_test3.root", "r");
  //TFile *f    = new TFile("prediction.root", "r");
  TFile *f    = new TFile(filename, "r");
  //TFile *outfile = new TFile("plot.root","RECREATE");
  TTree *tree = (TTree *)f->Get("tree");
  // Declaration of leaves types
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t angleDev;

  // Set branch addresses.
  tree->SetBranchAddress("x", &x);
  tree->SetBranchAddress("y", &y);
  tree->SetBranchAddress("z", &z);
  tree->SetBranchAddress("angleDev", &angleDev);

  //     This is the loop skeleton;;
  //       To read only selected branches, Insert statements like:
  // tree->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries    = tree->GetEntries();
  int nbins            = 100;
  int xstart           = -500;
  int xend             = 500;
  TH2F *hist_count_threshold     = new TH2F("hist_count_threshold", "hist_count_threshold", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_count     = new TH2F("hist_count", "hist_count", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_countY     = new TH2F("hist_countY", "hist_countY", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_angleDev  = new TH2F("hist_Dev", "hist_Dev", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_angleDev2 = new TH2F("hist_Dev2", "hist_Dev2", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_final_mean = new TH2F("hist_Final_Mean", "hist_Final_Mean", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_final_mean_th = new TH2F("hist_Final_Mean_Threshold", "hist_Final_Mean_Threshold", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_final_stddev = new TH2F("hist_Final_StdDev", "hist_Final_StdDev", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_final2 = new TH2F("hist_Final2", "hist_Final2", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_angleDevY  = new TH2F("hist_DevY", "hist_DevY", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_angleDev2Y = new TH2F("hist_Dev2Y", "hist_Dev2Y", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_finalY = new TH2F("hist_FinalY", "hist_FinalY", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_final2Y = new TH2F("hist_Final2Y", "hist_Final2Y", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *hist_std_th = new TH2F("hist_std_th", "hist_std_th", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *histXY_final_stddev = new TH2F("histXY_Final_StdDev", "histXY_Final_StdDev", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *histXY_std_th = new TH2F("histXY_std_th", "histXY_std_th", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *histXY_final_mean = new TH2F("histXY_Final_Mean", "histXY_Final_Mean", nbins, xstart, xend, nbins, xstart, xend);
  TH2F *histXY_mean_th = new TH2F("histXY_mean_th", "histXY_mean_th", nbins, xstart, xend, nbins, xstart, xend);
 
  Long64_t nbytes      = 0;
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += tree->GetEntry(i);
    if(angleDev > 0.03)
    hist_count_threshold->Fill(x,z);
    hist_count->Fill(x, z);
    hist_angleDev->Fill(x, z, angleDev);
    hist_angleDev2->Fill(x, z, angleDev * angleDev);

    hist_countY->Fill(x, y);
    hist_angleDevY->Fill(x, y, angleDev);
    hist_angleDev2Y->Fill(x, y, angleDev * angleDev);

  }


  TCanvas *can = new TCanvas;
  can->Divide(4,3);

  //Smoothing all the histograms
  hist_count->Smooth(1);
  hist_angleDev->Smooth(1);
  hist_angleDev2->Smooth(1);
  //hist_final->Smooth(1);

  hist_countY->Smooth(1);
  hist_angleDevY->Smooth(1);
  hist_angleDev2Y->Smooth(1);
  //hist_finalY->Smooth(1);

  can->cd(1);
  hist_count->Draw();
  can->cd(2);
  hist_angleDev->Draw("colz");
  can->cd(3);
  hist_angleDev2->Draw("colz");


  for (unsigned int i = 1; i < nbins-1; i++) {
    for (unsigned int j = 1; j < nbins-1; j++) {

	//std::cout << i << " , " << j << std::endl; 
      int n = hist_count->GetBinContent(i, j);
      if (n > 1) 
	{
        double sumAngle   = hist_angleDev->GetBinContent(i, j);
        double sumAngle2  = hist_angleDev2->GetBinContent(i, j);
        double meanSquare = sumAngle2 / n;
        double mean       = sumAngle / n;
        double stddev     = std::sqrt(meanSquare - mean * mean);
	//std::cout << "SD : " << stddev << std::endl;
	//hist_final->SetBinContent(i,j,stddev);
	hist_final_mean->SetBinContent(i,j,mean);
	if(stddev > 0.02)
	hist_final_mean_th->SetBinContent(i,j,mean);

	hist_final_stddev->SetBinContent(i,j,stddev);
	if(stddev > 0.02)
	hist_std_th->SetBinContent(i,j,stddev);
	
	}
	//hist_final2->SetBinContent(i,j,stddev);
	if(n>1)
	{
        double sumAngle   = hist_angleDevY->GetBinContent(i, j);
        double sumAngle2  = hist_angleDev2Y->GetBinContent(i, j);
        double meanSquare = sumAngle2 / n;
        double mean       = sumAngle / n;
        double stddev     = std::sqrt(meanSquare - mean * mean);
	//std::cout << "SD : " << stddev << std::endl;
	histXY_final_stddev->SetBinContent(i,j,stddev);//*stddev);
	if(stddev > 0.02)
	histXY_std_th->SetBinContent(i,j,stddev);//*stddev);

       histXY_final_mean->SetBinContent(i,j,mean);//*stddev);
	if(mean > 0.02)
	histXY_mean_th->SetBinContent(i,j,mean);//*stddev);

      }
    }
   }
  
can->cd(4);
hist_final_stddev->Draw("colz");
can->cd(5);
hist_std_th->Draw("colz");
can->cd(6);
hist_final_mean->Draw("colz");
can->cd(7);
hist_final_mean_th->Draw("colz");

TH2F *mean_clone = (TH2F*)hist_final_mean->Clone("mean_clone");
mean_clone->Scale(1./mean_clone->Integral());
mean_clone->SetName("Normalized_mean");
mean_clone->SetTitle("Normalized_mean");
can->cd(8);
mean_clone->Draw("colz");
can->cd(9);
histXY_final_stddev->Draw("colz");
can->cd(10);
histXY_std_th->Draw("colz");
can->cd(11);
histXY_final_mean->Draw("colz");
can->cd(12);
histXY_mean_th->Draw("colz");


/*  TCanvas *canO = new TCanvas("Output","Output");
  canO->Divide(2,2);
  canO->cd(1);
  hist_final_mean->Draw("colz");
  canO->cd(2);
  hist_final_stddev->Draw("colz");

  canO->cd(3);
  hist_finalY->Draw("colz");
  canO->cd(4);
  hist_final2Y->Draw("colz");


new TCanvas("RawWithThreshold","RawWithThreshold");
hist_count_threshold->Draw("colz");*/


/*new TCanvas;
hist_final->Draw("colz");*/
//hist_final_mean->Write();
//outfile->Close();
}
