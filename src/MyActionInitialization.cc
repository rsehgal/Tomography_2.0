#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
//#include "B1RunAction.hh"
//#include "B1EventAction.hh"
//#include "B1SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyActionInitialization::~MyActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyActionInitialization::BuildForMaster() const
{
  //B1RunAction* runAction = new B1RunAction;
  //SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyActionInitialization::Build() const
{
  SetUserAction(new MyPrimaryGeneratorAction);

  //B1RunAction* runAction = new B1RunAction;
  //SetUserAction(runAction);
  
  //B1EventAction* eventAction = new B1EventAction(runAction);
  //SetUserAction(eventAction);
  
  //SetUserAction(new B1SteppingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
