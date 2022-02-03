/*
**	Filename : MySensitiveDetector.h
**	2022-01-14
**	username : rsehgal
*/
#ifndef MySensitiveDetector_h
#define MySensitiveDetector_h

#include <G4VSensitiveDetector.hh>
//#include "HitCollection.h"
#include "MyHit.h"
#include "Analysis.h"
#include "G4PVPlacement.hh"
#include <TH1F.h>
class MySensitiveDetector : public G4VSensitiveDetector {
static int evNo;
public:
  MySensitiveDetector(G4String name, G4String collectionName = "Tomography");
  virtual ~MySensitiveDetector();

  virtual void Initialize(G4HCofThisEvent *HCE);
  virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *touchableHist);
  virtual void EndOfEvent(G4HCofThisEvent *HCE);
  void InitializeTotalEnergyDeposit();
  void InitializeAnalyzer(std::string phyVolumeName);
  void InitializeAnalyzer(G4PVPlacement *phyVolume){}
  void InitializeAnalyzer(std::string phyVolumeName,unsigned short detId, unsigned short layerId);
private:
  SDHitCollection *hitsCollection;
  G4int collectionID;
  double energyDep;

  //For debugging
  std::vector<G4ThreeVector> hitPointVec;
  TH1F *debugAngHist;
  // For Analysis
private:
  Analysis *fAnal;

public:
  void InitializeRootObjects(std::string name);
};

#endif
