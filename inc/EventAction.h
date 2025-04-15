/*
**	Filename : EventAction.h
**	2025-03-05
**	username : rsehgal
*/
#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "Track.h"
#include "TRandom3.h"

class EventAction : public G4UserEventAction {
  Track fIncomingTrack;
  Track fOutgoingTrack;
  Track fMomentumTrack;
  Track fOutgoingTrackRandomize;
  Track fMomentumTrackRandomize;
  Track fOutgoingTrackExact;
  Track fMomentumTrackExact;
  TRandom3 fRng;

public:
  EventAction();
  ~EventAction();
  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);
};

#endif
