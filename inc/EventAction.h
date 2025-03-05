/*
**	Filename : EventAction.h
**	2025-03-05
**	username : rsehgal
*/
#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class EventAction : public G4UserEventAction {

public:
  EventAction();
  ~EventAction();
  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);
};

#endif
