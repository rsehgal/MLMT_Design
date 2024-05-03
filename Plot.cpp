#include <TFile.h>
#include <TH1F.h>
#include <vector>
#include <fstream>
#include <TTree.h>
#include <TApplication.h>
#include <TF1.h>
#include <TCanvas.h>

int main(){
    TApplication *fApp = new TApplication("App",NULL,NULL);
    std::ifstream infile("output.csv");
    double xval=0.,yval=0.;
    TH1F *histX = new TH1F("outHistX","outHistX",100,-25,25);
    TH1F *histY = new TH1F("outHistY","outHistY",100,-25,25);
    while(!infile.eof()){
        infile >> xval >> yval;
        histX->Fill(xval);
        histY->Fill(yval);
    }

    new TCanvas("X","X");
    histX->Draw();

    new TCanvas("Y","Y");
    histY->Draw();

    fApp->Run();


}