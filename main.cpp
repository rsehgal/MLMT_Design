/*
**	Filename : main.cpp
**	2023-12-29
**	username : rsehgal
*/
#include "ActionInitialization.h"
#include "DetectorConstruction.h"

//#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "Randomize.hh"

#include "G4OpticalPhysics.hh"
#include "QGSP_BERT_HP.hh"
#include <Shielding.hh>

#include <TFile.h>

//#include "Analysis.h"
//#include "Physics.h"
#include <unistd.h> //To get process id

#ifdef ICNSE_USE_RANECU_RANDOM
#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/RanecuEngine.h"
#endif

//#include "TrackingAction.h"

int main(int argc, char **argv) {
  G4UIExecutive *ui = 0;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

#ifdef ICNSE_USE_RANECU_RANDOM
  CLHEP::RanecuEngine *ranecuEngine = new CLHEP::RanecuEngine;
  CLHEP::HepRandom::setTheEngine(ranecuEngine);
  // CLHEP::HepRandom::setTheSeed(time(0));
  CLHEP::HepRandom::setTheSeed(static_cast<int>(getpid()));
#endif
  // Analysis *anal = Analysis::Create("icnse.root");
  // TFile *fp = new TFile("icnse_data.root","RECREATE");
  // G4String outFileName = argv[2];
  // TFile *fp = new TFile(outFileName,"RECREATE");

  G4RunManager *runManager = new G4RunManager;
  runManager->SetUserInitialization(new DetectorConstruction());

  G4VModularPhysicsList *physicsList = new  QGSP_BERT_HP;//QBBC;
  runManager->SetUserInitialization(physicsList);

#ifdef ICNSE_ENABLE_OPTICAL_PHYSICS
  G4OpticalPhysics *opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
#endif

  runManager->SetUserInitialization(new ActionInitialization());

  //runManager->SetUserAction(new TrackingAction);

  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  TFile *fp;
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    G4String outFileName = fileName + ".root";
    fp = new TFile(outFileName.c_str(), "RECREATE");
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  // Output::instance()->Close();
  // anal->Close();
  // delete anal;
  fp->Close();
  delete visManager;
  delete runManager;
  // fp->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
