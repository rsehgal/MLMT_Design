/*
**	Filename : HitCollections.h
**	2025-01-20
**	username : rsehgal
*/
#ifndef HitCollections_h
#define HitCollections_h

#include "G4THitsCollection.hh"
#include "Scint_Hit.h"
#include "Muon_Hit.h"
using ScintHitCollection = G4THitsCollection<Scint_Hit>;
using MuonHitCollection = G4THitsCollection<Muon_Hit>;
#endif
