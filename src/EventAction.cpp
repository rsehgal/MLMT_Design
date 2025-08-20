/*
**	Filename : EventAction.cpp
**	2025-03-05
**	username : rsehgal
*/
#include "EventAction.h"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "Global.h"
#include "Helpers.h"
#include "HitCollections.h"
#include "Muon_Hit.h"
#include "colors.h"
#include <cmath>
#include <iostream>
#include <G4RandomTools.hh>
EventAction::EventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *event) {
  // unsigned long long tme = G4RunManager::GetRunManager()->GetTrackingManager()->GetTrack()->GetGlobalTime();
  // std::cout << RED <<"Global Time at Begin of Event : " << tme << RESET << std::endl;
  InitializeHitPointVec();
  fRng.SetSeed(0.);
}

//--------
G4ThreeVector EventAction::GetGroundTruthPoCA(PoCAHitCollection *pocaHitcollection) {

  G4ThreeVector groundTruthPoCA(-50000, -50000, -50000.);
  if (pocaHitcollection) {
    G4ThreeVector stepDir = (*pocaHitcollection)[0]->fStepDirection;
    G4ThreeVector nextStepDir(0., 0., 0.);
    double thetaSqSum = 0.;
    double thetaSq = 0;
    for (unsigned int s = 1; s < pocaHitcollection->entries(); s++) {
      thetaSq = 0.;
      //(*pocaHitcollection)[i]->Print();
      nextStepDir = (*pocaHitcollection)[s]->fStepDirection;
      double theta = nextStepDir.angle(stepDir);
      thetaSq = theta * theta;
      thetaSqSum += thetaSq;
      groundTruthPoCA += thetaSq * (*pocaHitcollection)[s]->fStepPosition;
    }

    groundTruthPoCA /= thetaSqSum;
  }
  return groundTruthPoCA;
}

G4ThreeVector EventAction::GetGroundTruthPoCA_V2(PoCAHitCollection *pocaHitcollection) {
  G4ThreeVector groundTruthPoCA(-50000, -50000, -50000.);
bool firstHit = true;
      if (pocaHitcollection->entries() > 1) {
        // angleDev = fIncomingTrackRandomize.Angle(fOutgoingTrackRandomize);
        G4ThreeVector stepDir = (*pocaHitcollection)[0]->fStepDirection;
        G4ThreeVector nextStepDir(0., 0., 0.);
        double thetaSqSum = 0.;
        double thetaSq = 0;
    double ystart = ((*pocaHitcollection)[0]->fStepPosition).y();
    double yend = ((*pocaHitcollection)[pocaHitcollection->entries()-1]->fStepPosition).y();
    double randY = ystart + (yend - ystart) * G4UniformRand();
    

        for (unsigned int s = 1; s < pocaHitcollection->entries(); s++) {
          thetaSq = 0.;
          //(*pocaHitcollection)[i]->Print();
          nextStepDir = (*pocaHitcollection)[s]->fStepDirection;
          double theta = nextStepDir.angle(stepDir);
          thetaSq = theta * theta;
          thetaSqSum += thetaSq;
          if (firstHit) {
            groundTruthPoCA = thetaSq * (*pocaHitcollection)[s]->fStepPosition;
            firstHit = false;
          } else
            groundTruthPoCA += thetaSq * (*pocaHitcollection)[s]->fStepPosition;
          stepDir = nextStepDir;
        }
        /* if(groundTruthPoCA.y() > -45000.)
                std::cout << groundTruthPoCA << std::endl;
        */
        groundTruthPoCA /= thetaSqSum;
    groundTruthPoCA.setY(randY);
//std::cout << groundTruthPoCA << std::endl;
      }
  return groundTruthPoCA;
}
//-------

void EventAction::EndOfEventAction(const G4Event *event) {
  G4AnalysisManager *analMan = G4AnalysisManager::Instance();

  G4HCofThisEvent *hce = event->GetHCofThisEvent();
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID("ScintillatorCrystal_MuonHits");
  MuonHitCollection *muonHitCollectionStrip = static_cast<MuonHitCollection *>(hce->GetHC(hcID));
  G4int muonHitCollStripSize = muonHitCollectionStrip->entries();

  G4int maskHCID = G4SDManager::GetSDMpointer()->GetCollectionID("MaskingScintillatorCrystal_MuonHits");
  MuonHitCollection *muonHitcollectionMask = static_cast<MuonHitCollection *>(hce->GetHC(maskHCID));

  G4int pocaHCID = G4SDManager::GetSDMpointer()->GetCollectionID("PoCAHitCollection");
  PoCAHitCollection *pocaHitcollection = static_cast<PoCAHitCollection *>(hce->GetHC(pocaHCID));

  // Printing PoCA Hit Collection
  /*
  for (unsigned int i = 0; i < pocaHitcollection->entries(); i++) {
    (*pocaHitcollection)[i]->Print();
  }
  */

  // std::cout << "======================================" << std::endl;
  // std::cout << "Strip Hit collection size : " << muonHitCollStripSize << std::endl;
  for (unsigned int i = 0; i < muonHitCollectionStrip->entries(); i++) {
    Muon_Hit *hitStrip = (*muonHitCollectionStrip)[i];
    // Uncomment the below line to see the hit points
    // hitStrip->Print();
    analMan->FillNtupleDColumn(1, 0, hitStrip->fLayerNum);
    analMan->FillNtupleDColumn(1, 1, hitStrip->fPlaneNum);
    analMan->FillNtupleDColumn(1, 2, hitStrip->fStripNum);
    analMan->FillNtupleDColumn(1, 3, hitStrip->fMaskNum);
    analMan->FillNtupleDColumn(1, 4, hitStrip->GetChannelNum());
    analMan->FillNtupleDColumn(1, 6, yPosVec[hitStrip->fLayerNum]);
    if (hitStrip->fMaskNum >= 0 && hitStrip->fStripNum >= 0) {
      if (hitStrip->fPlaneNum == 0) {
        analMan->FillNtupleDColumn(1, 5, hitStrip->GetStripCenter());
        double stripCenter = hitStrip->GetStripCenter();
        double randomHit = fRng.Uniform(stripCenter - scintHalfx, stripCenter + scintHalfx);
        hitPointVec[hitStrip->fLayerNum].setX(stripCenter);
        exactHitPointVec[hitStrip->fLayerNum].setX(hitStrip->fExactHit.x());
        randomizeHitPointVec[hitStrip->fLayerNum].setX(randomHit);
        stripNumVec[hitStrip->fLayerNum].setX(hitStrip->fMaskNum * numOfGroups + hitStrip->fStripNum);
      } else {
        analMan->FillNtupleDColumn(1, 7, hitStrip->GetStripCenter());
        double stripCenter = hitStrip->GetStripCenter();
        double randomHit = fRng.Uniform(stripCenter - scintHalfx, stripCenter + scintHalfx);
        hitPointVec[hitStrip->fLayerNum].setZ(stripCenter);
        exactHitPointVec[hitStrip->fLayerNum].setZ(hitStrip->fExactHit.z());
        randomizeHitPointVec[hitStrip->fLayerNum].setZ(randomHit);
        stripNumVec[hitStrip->fLayerNum].setZ(hitStrip->fMaskNum * numOfGroups + hitStrip->fStripNum);
      }
      momentumVec[hitStrip->fLayerNum] = hitStrip->fMomentum;
      analMan->FillNtupleDColumn(1, 8, event->GetEventID());
      analMan->AddNtupleRow(1);
    }
  }

  // std::cout << "HitPointVec Size : " << hitPointVec.size() << std::endl;

  /*
  for(int i = hitPointVec.size()-1; i >= 0 ; i--){
  std::cout << "RAMAN : " << hitPointVec[i] << std::endl;
  }
  */

  bool hitInAllLayers = true;

  for (int i = hitPointVec.size() - 1; i >= 0; i--) {
    hitInAllLayers &= hitPointVec[i].x() > -50000.;
    hitInAllLayers &= hitPointVec[i].y() > -50000.;
    hitInAllLayers &= hitPointVec[i].z() > -50000.;
  }

  if (hitInAllLayers) {
    // Resetting previously set tracks
    fIncomingTrack.Reset();
    fIncomingTrackRandomize.Reset();
    fIncomingTrackExact.Reset();
    fOutgoingTrack.Reset();
    fOutgoingTrackRandomize.Reset();
    fOutgoingTrackExact.Reset();
    fMomentumTrack.Reset();
    fMomentumTrackRandomize.Reset();
    fMomentumTrackExact.Reset();

    for (int i = hitPointVec.size() - 1; i >= 0; i--) {
      analMan->FillNtupleDColumn(2, 0, i);
      analMan->FillNtupleDColumn(2, 1, hitPointVec[i].x());
      analMan->FillNtupleDColumn(2, 2, hitPointVec[i].y());
      analMan->FillNtupleDColumn(2, 3, hitPointVec[i].z());
      analMan->FillNtupleDColumn(2, 4, stripNumVec[i].x());
      analMan->FillNtupleDColumn(2, 5, stripNumVec[i].z());
      analMan->FillNtupleDColumn(2, 6,
                                 event->GetEventID(

                                     ));
      // analMan->AddNtupleRow(2);
    }

    // Hardcoded for incoming and outgoing track of size 2
    fIncomingTrack.SetP1(hitPointVec[5]);
    fIncomingTrack.SetP2(hitPointVec[4]);
    fOutgoingTrack.SetP1(hitPointVec[3]);
    fOutgoingTrack.SetP2(hitPointVec[2]);
    fMomentumTrack.SetP1(hitPointVec[1]);
    fMomentumTrack.SetP2(hitPointVec[0]);

    fIncomingTrackRandomize.SetP1(randomizeHitPointVec[5]);
    fIncomingTrackRandomize.SetP2(randomizeHitPointVec[4]);
    fOutgoingTrackRandomize.SetP1(randomizeHitPointVec[3]);
    fOutgoingTrackRandomize.SetP2(randomizeHitPointVec[2]);
    fMomentumTrackRandomize.SetP1(randomizeHitPointVec[1]);
    fMomentumTrackRandomize.SetP2(randomizeHitPointVec[0]);

    fIncomingTrackExact.SetP1(exactHitPointVec[5]);
    fIncomingTrackExact.SetP2(exactHitPointVec[4]);
    fOutgoingTrackExact.SetP1(exactHitPointVec[3]);
    fOutgoingTrackExact.SetP2(exactHitPointVec[2]);
    fMomentumTrackExact.SetP1(exactHitPointVec[1]);
    fMomentumTrackExact.SetP2(exactHitPointVec[0]);

#ifdef ML_TREE
    // TODO : Logic to detect ground truth PoCA from PoCA Hit Collection
    G4ThreeVector groundTruthPoCA(-50000., -50000., -50000.);
    G4ThreeVector calcPoCA(-50000., -50000., -50000.);
    double angleDev = -50000;
    double maxAngle = 0.;

    angleDev = fIncomingTrackRandomize.Angle(fOutgoingTrackRandomize);
    G4ThreeVector pIn = fIncomingTrackRandomize.GetP1();
    G4ThreeVector dIn = fIncomingTrackRandomize.GetDirCosine();
    G4ThreeVector pOut = fOutgoingTrackRandomize.GetP1();
    G4ThreeVector dOut = fOutgoingTrackRandomize.GetDirCosine();

    if (pocaHitcollection) {
      /*TRandom3 randGen(0); // 0 seeds with current time
      int stop = pocaHitcollection->entries();
      angleDev = fIncomingTrackRandomize.Angle(fOutgoingTrackRandomize);
      if (stop > 0) {
        int ranStepIndex = (int)randGen.Uniform(0, stop); // Include stop
        // std::cout << "ranStepIndex : " << ranStepIndex << std::endl;
        G4ThreeVector stepPos = (*pocaHitcollection)[ranStepIndex]->fStepPosition;
        if (stepPos.y() < 99.95 && stepPos.y() > -99.95) groundTruthPoCA = stepPos;
        // POCA(fIncomingTrackExact, fOutgoingTrackExact); // (*pocaHitcollection)[ranStepIndex]->fStepPosition;
      }

        groundTruthPoCA = GetGroundTruthPoCA(pocaHitcollection);*/
      // std::cout << "Size of PocaHitCollection : " << pocaHitcollection->entries() << std::endl;



      /*bool firstHit = true;

      //Logic taken to GroundTruthPoCA_V2

      if (pocaHitcollection->entries() > 1) {
        // angleDev = fIncomingTrackRandomize.Angle(fOutgoingTrackRandomize);
        G4ThreeVector stepDir = (*pocaHitcollection)[0]->fStepDirection;
        G4ThreeVector nextStepDir(0., 0., 0.);
        double thetaSqSum = 0.;
        double thetaSq = 0;
        for (unsigned int s = 1; s < pocaHitcollection->entries(); s++) {
          thetaSq = 0.;
          //(*pocaHitcollection)[i]->Print();
          nextStepDir = (*pocaHitcollection)[s]->fStepDirection;
          double theta = nextStepDir.angle(stepDir);
          thetaSq = theta * theta;
          thetaSqSum += thetaSq;
          if (firstHit) {
            groundTruthPoCA = thetaSq * (*pocaHitcollection)[s]->fStepPosition;
            firstHit = false;
          } else
            groundTruthPoCA += thetaSq * (*pocaHitcollection)[s]->fStepPosition;
          stepDir = nextStepDir;
        }
        groundTruthPoCA /= thetaSqSum;
      }
*/

        groundTruthPoCA = GetGroundTruthPoCA_V2(pocaHitcollection);
      /*for (unsigned int s = 0; s < pocaHitcollection->entries(); s++) {
        //(*pocaHitcollection)[i]->Print();
        G4ThreeVector stepDir = (*pocaHitcollection)[s]->fStepDirection;

        double angle = stepDir.angle(fIncomingTrack.GetDirCosine());
        if (angle > maxAngle) {
          maxAngle = angle;
          groundTruthPoCA = (*pocaHitcollection)[s]->fStepPosition;
        }
      }*/
      calcPoCA = POCA(fIncomingTrackRandomize, fOutgoingTrackRandomize);
    }
    // std::cout << "Ground Truth PoCA : " << groundTruthPoCA << std::endl;
    analMan->FillNtupleDColumn(5, 0, pIn.x());
    analMan->FillNtupleDColumn(5, 1, pIn.y());
    analMan->FillNtupleDColumn(5, 2, pIn.z());
    analMan->FillNtupleDColumn(5, 3, dIn.x());
    analMan->FillNtupleDColumn(5, 4, dIn.y());
    analMan->FillNtupleDColumn(5, 5, dIn.z());

    analMan->FillNtupleDColumn(5, 6, pOut.x());
    analMan->FillNtupleDColumn(5, 7, pOut.y());
    analMan->FillNtupleDColumn(5, 8, pOut.z());
    analMan->FillNtupleDColumn(5, 9, dOut.x());
    analMan->FillNtupleDColumn(5, 10, dOut.y());
    analMan->FillNtupleDColumn(5, 11, dOut.z());

    analMan->FillNtupleDColumn(5, 12, groundTruthPoCA.x());
    analMan->FillNtupleDColumn(5, 13, groundTruthPoCA.y());
    analMan->FillNtupleDColumn(5, 14, groundTruthPoCA.z());

    analMan->FillNtupleDColumn(5, 15, angleDev);
    analMan->FillNtupleDColumn(5, 16, calcPoCA.x());
    analMan->FillNtupleDColumn(5, 17, calcPoCA.y());
    analMan->FillNtupleDColumn(5, 18, calcPoCA.z());

    analMan->AddNtupleRow(5);
#endif
    //-----------------------------------------------------------------

    /*std::cout << "--------------------------------------" << std::endl;
    fIncomingTrack.Print();
    fOutgoingTrack.Print();*/

    /*
     double dev         = fIncomingTrack.Angle(fOutgoingTrack);
     double devMomentum = fOutgoingTrack.Angle(fMomentumTrack);
     double devRandomize = fOutgoingTrackRandomize.Angle(fMomentumTrackRandomize);
     double devExact = fOutgoingTrackExact.Angle(fMomentumTrackExact);

     // Momentum calculation using Scattering method
     double momentum       = 92.7 / devMomentum;
     double g4CalcMomentum = momentumVec[0].mag();*/

    double g4CalcMomentum = momentumVec[0].mag();
    double devTarget = 0;
    double devMomentum = 0;
    double pathLength = 0;
    double myMomentum = 0;
    G4ThreeVector poca(-50000., -50000., -50000.);

    // if (fIncomingTrack.Angle(fOutgoingTrack) > 0.01)
    {

      // if (!std::isnan(poca.x()) && !std::isnan(poca.y()) && !std::isnan(poca.z()))
      {
        double dev = fIncomingTrack.Angle(fOutgoingTrack);
        G4ThreeVector poca = POCA(fIncomingTrack, fOutgoingTrack);
        double L_1 = (fOutgoingTrack.GetP2() - fMomentumTrack.GetP1()).mag() / 10.;
        double L_2 = ComputePathLength(20, fOutgoingTrack.GetZenithAngle(), fMomentumTrack.GetZenithAngle());
        double devMomentum = fOutgoingTrack.Angle(fMomentumTrack);
        double momentum = 92.7 / devMomentum;

        // Estimate momentum
        // double momentum_pl = EstimateMomentum(devMomentum, L_1)*1000.;
        double momentum_pl = EstimateMomentum(devMomentum); //, L_1)*1000.;

        analMan->FillNtupleDColumn(3, 0, poca.x());
        analMan->FillNtupleDColumn(3, 1, poca.y());
        analMan->FillNtupleDColumn(3, 2, poca.z());
        analMan->FillNtupleDColumn(3, 3, dev);
        analMan->FillNtupleDColumn(3, 4, fOutgoingTrack.GetZenithAngle());
        analMan->FillNtupleDColumn(3, 5, fMomentumTrack.GetZenithAngle());
        analMan->FillNtupleDColumn(3, 6, L_1);
        analMan->FillNtupleDColumn(3, 7, L_2);
        analMan->FillNtupleDColumn(3, 8, devMomentum);
        analMan->FillNtupleDColumn(3, 9, momentum);
        analMan->FillNtupleDColumn(3, 10, momentum_pl);
        analMan->FillNtupleDColumn(3, 11, g4CalcMomentum);
        analMan->FillNtupleDColumn(3, 12, event->GetEventID());
        analMan->AddNtupleRow(3);
      }

#ifdef ML_TREE

      {
        devTarget = fIncomingTrack.Angle(fOutgoingTrack);
        devMomentum = fOutgoingTrack.Angle(fMomentumTrack);
        pathLength = ComputePathLength(20, fOutgoingTrack.GetZenithAngle(), fMomentumTrack.GetZenithAngle());
        double momentum = 92.7 / devMomentum;
        poca = POCA(fIncomingTrack, fOutgoingTrack);

        analMan->FillNtupleDColumn(4, 0, fIncomingTrack.GetP1().x());
        analMan->FillNtupleDColumn(4, 1, fIncomingTrack.GetP1().y());
        analMan->FillNtupleDColumn(4, 2, fIncomingTrack.GetP1().z());
        analMan->FillNtupleDColumn(4, 3, fIncomingTrack.GetP2().x());
        analMan->FillNtupleDColumn(4, 4, fIncomingTrack.GetP2().y());
        analMan->FillNtupleDColumn(4, 5, fIncomingTrack.GetP2().z());
        analMan->FillNtupleDColumn(4, 6, fOutgoingTrack.GetP1().x());
        analMan->FillNtupleDColumn(4, 7, fOutgoingTrack.GetP1().y());
        analMan->FillNtupleDColumn(4, 8, fOutgoingTrack.GetP1().z());
        analMan->FillNtupleDColumn(4, 9, fOutgoingTrack.GetP2().x());
        analMan->FillNtupleDColumn(4, 10, fOutgoingTrack.GetP2().y());
        analMan->FillNtupleDColumn(4, 11, fOutgoingTrack.GetP2().z());
        analMan->FillNtupleDColumn(4, 12, fMomentumTrack.GetP1().x());
        analMan->FillNtupleDColumn(4, 13, fMomentumTrack.GetP1().y());
        analMan->FillNtupleDColumn(4, 14, fMomentumTrack.GetP1().z());
        analMan->FillNtupleDColumn(4, 15, fMomentumTrack.GetP2().x());
        analMan->FillNtupleDColumn(4, 16, fMomentumTrack.GetP2().y());
        analMan->FillNtupleDColumn(4, 17, fMomentumTrack.GetP2().z());
        analMan->FillNtupleDColumn(4, 18, devTarget);
        analMan->FillNtupleDColumn(4, 19, devMomentum);
        analMan->FillNtupleDColumn(4, 20, pathLength);
        analMan->FillNtupleDColumn(4, 21, momentum);
        analMan->FillNtupleDColumn(4, 22, poca.x());
        analMan->FillNtupleDColumn(4, 23, poca.y());
        analMan->FillNtupleDColumn(4, 24, poca.z());
      }

      {
        devTarget = fIncomingTrackRandomize.Angle(fOutgoingTrackRandomize);
        devMomentum = fOutgoingTrackRandomize.Angle(fMomentumTrackRandomize);
        pathLength =
            ComputePathLength(20, fOutgoingTrackRandomize.GetZenithAngle(), fMomentumTrackRandomize.GetZenithAngle());
        double momentum = 92.7 / devMomentum;
        poca = POCA(fIncomingTrackRandomize, fOutgoingTrackRandomize);
        analMan->FillNtupleDColumn(4, 25, fIncomingTrackRandomize.GetP1().x());
        analMan->FillNtupleDColumn(4, 26, fIncomingTrackRandomize.GetP1().y());
        analMan->FillNtupleDColumn(4, 27, fIncomingTrackRandomize.GetP1().z());
        analMan->FillNtupleDColumn(4, 28, fIncomingTrackRandomize.GetP2().x());
        analMan->FillNtupleDColumn(4, 29, fIncomingTrackRandomize.GetP2().y());
        analMan->FillNtupleDColumn(4, 30, fIncomingTrackRandomize.GetP2().z());
        analMan->FillNtupleDColumn(4, 31, fOutgoingTrackRandomize.GetP1().x());
        analMan->FillNtupleDColumn(4, 32, fOutgoingTrackRandomize.GetP1().y());
        analMan->FillNtupleDColumn(4, 33, fOutgoingTrackRandomize.GetP1().z());
        analMan->FillNtupleDColumn(4, 34, fOutgoingTrackRandomize.GetP2().x());
        analMan->FillNtupleDColumn(4, 35, fOutgoingTrackRandomize.GetP2().y());
        analMan->FillNtupleDColumn(4, 36, fOutgoingTrackRandomize.GetP2().z());
        analMan->FillNtupleDColumn(4, 37, fMomentumTrackRandomize.GetP1().x());
        analMan->FillNtupleDColumn(4, 38, fMomentumTrackRandomize.GetP1().y());
        analMan->FillNtupleDColumn(4, 39, fMomentumTrackRandomize.GetP1().z());
        analMan->FillNtupleDColumn(4, 40, fMomentumTrackRandomize.GetP2().x());
        analMan->FillNtupleDColumn(4, 41, fMomentumTrackRandomize.GetP2().y());
        analMan->FillNtupleDColumn(4, 42, fMomentumTrackRandomize.GetP2().z());
        analMan->FillNtupleDColumn(4, 43, devTarget);
        analMan->FillNtupleDColumn(4, 44, devMomentum);
        analMan->FillNtupleDColumn(4, 45, pathLength);
        analMan->FillNtupleDColumn(4, 46, momentum);
        analMan->FillNtupleDColumn(4, 47, poca.x());
        analMan->FillNtupleDColumn(4, 48, poca.y());
        analMan->FillNtupleDColumn(4, 49, poca.z());
      }

      {
        devTarget = fIncomingTrackExact.Angle(fOutgoingTrackExact);
        devMomentum = fOutgoingTrackExact.Angle(fMomentumTrackExact);
        pathLength = ComputePathLength(20, fOutgoingTrackExact.GetZenithAngle(), fMomentumTrackExact.GetZenithAngle());
        double momentum = 92.7 / devMomentum;
        poca = POCA(fIncomingTrackExact, fOutgoingTrackExact);
        analMan->FillNtupleDColumn(4, 50, fIncomingTrackExact.GetP1().x());
        analMan->FillNtupleDColumn(4, 51, fIncomingTrackExact.GetP1().y());
        analMan->FillNtupleDColumn(4, 52, fIncomingTrackExact.GetP1().z());
        analMan->FillNtupleDColumn(4, 53, fIncomingTrackExact.GetP2().x());
        analMan->FillNtupleDColumn(4, 54, fIncomingTrackExact.GetP2().y());
        analMan->FillNtupleDColumn(4, 55, fIncomingTrackExact.GetP2().z());
        analMan->FillNtupleDColumn(4, 56, fOutgoingTrackExact.GetP1().x());
        analMan->FillNtupleDColumn(4, 57, fOutgoingTrackExact.GetP1().y());
        analMan->FillNtupleDColumn(4, 58, fOutgoingTrackExact.GetP1().z());
        analMan->FillNtupleDColumn(4, 59, fOutgoingTrackExact.GetP2().x());
        analMan->FillNtupleDColumn(4, 60, fOutgoingTrackExact.GetP2().y());
        analMan->FillNtupleDColumn(4, 61, fOutgoingTrackExact.GetP2().z());
        analMan->FillNtupleDColumn(4, 62, fMomentumTrackExact.GetP1().x());
        analMan->FillNtupleDColumn(4, 63, fMomentumTrackExact.GetP1().y());
        analMan->FillNtupleDColumn(4, 64, fMomentumTrackExact.GetP1().z());
        analMan->FillNtupleDColumn(4, 65, fMomentumTrackExact.GetP2().x());
        analMan->FillNtupleDColumn(4, 66, fMomentumTrackExact.GetP2().y());
        analMan->FillNtupleDColumn(4, 67, fMomentumTrackExact.GetP2().z());
        analMan->FillNtupleDColumn(4, 68, devTarget);
        analMan->FillNtupleDColumn(4, 69, devMomentum);
        analMan->FillNtupleDColumn(4, 70, pathLength);
        analMan->FillNtupleDColumn(4, 71, momentum);
        analMan->FillNtupleDColumn(4, 72, poca.x());
        analMan->FillNtupleDColumn(4, 73, poca.y());
        analMan->FillNtupleDColumn(4, 74, poca.z());
      }
      analMan->FillNtupleDColumn(4, 75, g4CalcMomentum);
      analMan->FillNtupleDColumn(4, 76, event->GetEventID());
      // analMan->AddNtupleRow(4);
#endif
    }
  }
  /* std::cout << "++++++++++++++++++++++++++++++++++++++" << std::endl;
   std::cout << "Masking Hit collection size : " << muonHitcollectionMask->entries() << std::endl;
   for (unsigned int i = 0; i < muonHitcollectionMask->entries(); i++) {
     Muon_Hit *hitMask = (*muonHitcollectionMask)[i];
     hitMask->Print();
   }*/
}
