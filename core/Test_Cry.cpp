/*
**	Filename : Test_Cry.cpp
**	2025-03-18
**	username : rsehgal
*/
#include<iostream>
#include "CryInterface.h"
#include "Muon.h"
#include "TH1F.h"
#include <TApplication.h>
#include <TVector3.h>
#include <TF1.h>

int main(int argc, char *argv[]){
TApplication *fApp = new TApplication("fApp",NULL,NULL);
CryInterface *cryInteface = new CryInterface();
Muon *muon = cryInteface->SampleMuon();
muon->Print();

muon = cryInteface->SampleMuon();
muon->Print();

muon = cryInteface->SampleMuon();
muon->Print();

TH1F *hist = new TH1F("Zenith","Zenith",50.,0,M_PI/2.);

unsigned int numOfMuons = 1000000;

for(unsigned int i = 0 ; i < numOfMuons ; i++){

muon = cryInteface->SampleMuon();
TVector3 ref(0.,-1.,0);
double angle = TVector3(muon->angleX,muon->angleY,muon->angleZ).Angle(ref);
hist->Fill(angle);
}

//TF1 *formula = new TF1("cos2theta","[0]*std::pow(std::cos(x),[1])",0,M_PI/2.);;
//hist->Fit(formula,"r");

TF1 *cosSqr = new TF1("cosSqr", "[0]*sin(x)*cos(x)*pow(cos(x),[1])", 0.,M_PI/2.);
hist->Fit(cosSqr);

hist->Draw("hist");
cosSqr->Draw("same");
fApp->Run();
return 0;
}
