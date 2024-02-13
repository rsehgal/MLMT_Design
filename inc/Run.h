/*
**	Filename : Run.h
**	2024-02-13
**	username : rsehgal
*/
#ifndef Run_h
#define Run_h

#include "G4Run.hh"
#include "globals.hh"

class Run : public G4Run {
public:
  Run();
  virtual ~Run();

  // method from the base class
  virtual void Merge(const G4Run *);

};


#endif
