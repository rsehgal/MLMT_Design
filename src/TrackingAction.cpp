#include "TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

TrackingAction::TrackingAction() {}

TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track *track)
{

#define KILL_SECONDARIES
#ifdef KILL_SECONDARIES
  if (track->GetTrackID() > 1) {
    G4Track *nonconstTrack = (G4Track *)track;
    nonconstTrack->SetTrackStatus(fStopAndKill);
  }
#endif

  //if (track->GetTrackID() == 1) std::cout << "GlobalTime : " << track->GetGlobalTime() << std::endl;
  // std::cout <<"RAMAN : Tracking Action begin....." << std::endl;
}

void TrackingAction::PostUserTrackingAction(const G4Track *track)
{
  // if(track->GetTrackID()==1)
  // std::cout <<"SEHGAL : Tracking Action ends....." << std::endl;
}
