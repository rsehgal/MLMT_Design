/*
**	Filename : RunAction.h
**	2024-02-13
**	username : rsehgal
*/
#ifndef RunAction_h
#define RunAction_h

#include "G4UserRunAction.hh"
#include "globals.hh"

//#include <fstream>
using namespace std;
class G4Run;
class G4LogicalVolume;
class TFile;

class RunAction : public G4UserRunAction {

  TFile *fOutFile;

public:
  RunAction();
  virtual ~RunAction();

  virtual G4Run *GenerateRun();
  virtual void BeginOfRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);
};

#endif
