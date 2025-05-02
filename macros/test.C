#include <iostream>
#include <fstream>
{
std::ifstream infile("output.csv");
double x,y,z;
gStyle->SetPalette(kRainbow);
TH2F *histXZ = new TH2F("histXZ","histXZ", 500,-500,500,500,-500,500);
TH2F *histXY = new TH2F("histXY","histXY", 500,-500,500,500,-500,500);
TH2F *histZY = new TH2F("histZY","histZY", 500,-500,500,500,-500,500);
TCanvas *can = new TCanvas;
can->Divide(2,2);
while(!infile.eof()){
infile >> x >> y >> z;
histXZ->Fill(x,z);
histXY->Fill(x,y);
histZY->Fill(z,y);
}

can->cd(1);
histXZ->Draw("colz");
can->cd(2);
histXY->Draw("colz");
can->cd(3);
histZY->Draw("colz");


}
