#include "PoCA_Hit.h"
#include <iostream>
PoCA_Hit::PoCA_Hit() {}

PoCA_Hit::PoCA_Hit(G4ThreeVector vecDir, G4ThreeVector vecPos) : fStepDirection(vecDir), fStepPosition(vecPos) {}

PoCA_Hit::~PoCA_Hit() {}

void PoCA_Hit::Fill(G4ThreeVector vecDir, G4ThreeVector vecPos)
{
  fStepDirection = vecDir;
  fStepPosition  = vecPos;
}

void PoCA_Hit::Print(){
std::cout << "Dir : " << fStepDirection <<" : Pos : " << fStepPosition << std::endl;
}
