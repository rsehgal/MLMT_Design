#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "G4ThreeVector.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
void DrawPoint(const G4ThreeVector& position) {
    G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
    if (!visManager) return;

    // Create a large point marker (circle)
    G4Circle circle(position);
    circle.SetScreenSize(50.0);  // Large size
    circle.SetFillStyle(G4Circle::filled);

    // Set point color to RED
    G4VisAttributes attributes(G4Colour(1.0, 0.0, 0.0));  
    circle.SetVisAttributes(attributes);

    // Draw the point
    visManager->Draw(circle);
}

int main(int argc, char** argv) {
    // Initialize the Run Manager
    G4RunManager* runManager = new G4RunManager();

    // Initialize the Visualization Manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Create UI session (for interactive mode)
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    // Get the UI manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Open OpenGL Visualization Window
    UImanager->ApplyCommand("/vis/open OGL");  
    UImanager->ApplyCommand("/vis/viewer/set/viewpointThetaPhi 60 30");
    UImanager->ApplyCommand("/vis/viewer/set/style surface");  
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");

    // Adjust the camera to ensure the point is visible
    UImanager->ApplyCommand("/vis/viewer/zoom 5");  // Zoom in to see the point

    // Draw a 3D point at (10 cm, 20 cm, 30 cm)
    G4ThreeVector myPoint(10.0 * cm, 20.0 * cm, 30.0 * cm);
    DrawPoint(myPoint);

    // Force redraw
    UImanager->ApplyCommand("/vis/viewer/refresh");

    // Start interactive session
    ui->SessionStart();

    // Cleanup
    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}
