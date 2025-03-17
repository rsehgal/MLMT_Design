/*
**	Filename : Test_Cry.cpp
**	2025-03-18
**	username : rsehgal
*/
#include<iostream>
#include "CryInterface.h"
#include "Muon.h"

int main(int argc, char *argv[]){

CryInterface *cryInteface = new CryInterface();
Muon *muon = cryInteface->SampleMuon();
muon->Print();

muon = cryInteface->SampleMuon();
muon->Print();

muon = cryInteface->SampleMuon();
muon->Print();
return 0;
}
