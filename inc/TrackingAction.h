#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class TrackingAction : public G4UserTrackingAction {
public:
    TrackingAction();
    virtual ~TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
