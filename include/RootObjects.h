/*
**	Filename : RootObjects.h
**	2022-01-17
**	username : rsehgal
*/

#include <TH1F.h>
#ifndef RootObjects_h
#define RootObjects_h
#include "Data.h"
#include <G4ThreeVector.hh>

class RootObjects {
  std::string fObjectName;
  TH1F *fEnergyDepHist;
  std::vector<double> fVecOfEnergyDepositInSteps;
  std::vector<G4ThreeVector> fVecOfPreStepPoint;
  Data *fDataObject;
  bool fHitted;

public:
  RootObjects();
  ~RootObjects();
  RootObjects(std::string name);
  RootObjects(std::string name,unsigned short detId, unsigned short layerId);
  TH1F *GetEnergyDepHist() const;
  std::string GetObjectName() const;
  Data *GetDataObject() const;
  void InitializeTotalEnergyDeposit();
  void FillEnergyDep(double energyDep);
  void FillEnergyDep();
  void FillVecOfEnergyDepositInSteps(double eDepStep);
  void FillVecOfPreStepPositionInSteps(G4ThreeVector pos);
  void Write();
};
#endif
