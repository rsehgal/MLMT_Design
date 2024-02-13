/*
**	Filename : ActionInitialization.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "ActionInitialization.h"
#include "PrimaryGeneratorAction.h"
#include "RunAction.h"
#include <iostream>
//#include "B1EventAction.hh"
//#include "B1SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  //  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const {
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new RunAction);

  //  B1EventAction* eventAction = new B1EventAction;
  //  SetUserAction(eventAction);

  //  SetUserAction(new B1SteppingAction(eventAction));
}
