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
#include "HitCollections.h"

class EventAction : public G4UserEventAction {
  Track fIncomingTrack;
  Track fIncomingTrackRandomize;
  Track fIncomingTrackExact;
  Track fOutgoingTrack;
  Track fOutgoingTrackRandomize;
  Track fOutgoingTrackExact;
  Track fMomentumTrack;
  Track fMomentumTrackRandomize;
  Track fMomentumTrackExact;
  TRandom3 fRng;

public:
  EventAction();
  ~EventAction();
  void BeginOfEventAction(const G4Event *event);
  void EndOfEventAction(const G4Event *event);
  G4ThreeVector GetGroundTruthPoCA(PoCAHitCollection *pocaHitcollection);
};

#endif
