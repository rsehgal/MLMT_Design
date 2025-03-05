/*
**	Filename : ActionInitialization.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "ActionInitialization.h"
#include "PrimaryGeneratorAction.h"
#include "RunAction.h"
#include <iostream>
#include "EventAction.h"
#include "TrackingAction.h"
//#include "B1SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  //  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const {
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new RunAction);
  SetUserAction(new EventAction);
  SetUserAction(new TrackingAction);

  //  B1EventAction* eventAction = new B1EventAction;
  //  SetUserAction(eventAction);

  //  SetUserAction(new B1SteppingAction(eventAction));
}
