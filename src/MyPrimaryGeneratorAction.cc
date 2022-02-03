#include "MyPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <TRandom.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  fParticleGun->SetParticleEnergy(6.*MeV);
  fRand = new TRandom;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,10.));
  G4ThreeVector startPt = G4ThreeVector(fRand->Uniform(-50*cm,50*cm),fRand->Uniform(-50*cm,50*cm),100*cm);
  G4ThreeVector endPt = G4ThreeVector(fRand->Uniform(-50*cm,50*cm),fRand->Uniform(-50*cm,50*cm),-100*cm);
  G4ThreeVector dir = (endPt-startPt).unit();
  
  fParticleGun->SetParticlePosition(startPt);
  fParticleGun->SetParticleMomentumDirection(dir);
  //fParticleGun->SetParticleEnergy(3.0*GeV);
  //fParticleGun->SetParticleMomentum(3*GeV);
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

