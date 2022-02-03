#include "MyDetectorConstruction.hh"
#include "MyActionInitialization.hh"

//#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "FTFP_BERT.hh"
#include <TFile.h>
#include "physicslist.hh"

/*Visualizer related includes*/
#include "EveVisualizer.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TFile *fp;
int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
   fp = new TFile("anal.root","RECREATE");
  fp->cd();
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);
  
  // Construct the default run manager
  //
//  auto* runManager =
G4RunManager *runManager = new G4RunManager;
    //G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new MyDetectorConstruction());

  // Physics list
  //G4VModularPhysicsList* physicsList = new FTFP_BERT;//QBBC;
  //physicsList->SetVerboseLevel(1);
  //runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new MYphysicslist());
    
  // User action initialization
  runManager->SetUserInitialization(new MyActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
  fp->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
