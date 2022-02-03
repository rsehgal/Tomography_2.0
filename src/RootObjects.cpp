/*
**	Filename : RootObjects.cpp
**	2022-01-17
**	username : rsehgal
*/
#include "RootObjects.h"
#include <TH1F.h>
#include <iostream>

RootObjects::RootObjects() {}

RootObjects::~RootObjects() {}

Data *RootObjects::GetDataObject() const { return fDataObject; }

std::string RootObjects::GetObjectName() const { return fObjectName; }

RootObjects::RootObjects(std::string name) {
  fObjectName = name;
  fDataObject = new Data();
  std::string histName = fObjectName + "_EnergyDep";
  fEnergyDepHist = new TH1F(histName.c_str(), histName.c_str(), 200, 0, 50.);
  fHitted = false;
}

RootObjects::RootObjects(std::string name, unsigned short detId, unsigned short layerId) {
  fObjectName = name;
  fDataObject = new Data(fObjectName, detId, layerId);
  std::string histName = fObjectName + "_EnergyDep";
  fEnergyDepHist = new TH1F(histName.c_str(), histName.c_str(), 200, 0, 50.);
  fHitted = false;
}

void RootObjects::FillEnergyDep(double energyDep) { fEnergyDepHist->Fill(energyDep); }

TH1F *RootObjects::GetEnergyDepHist() const { return fEnergyDepHist; }

/* This function actually resets the Root Object for next event,
** That's why it is called by Initialize function of the
** Sensitive detector
*/
void RootObjects::InitializeTotalEnergyDeposit() {
  fVecOfEnergyDepositInSteps.clear();
  fHitted = false;
  fDataObject->Initialize();
  fVecOfPreStepPoint.clear();
}

void RootObjects::FillVecOfEnergyDepositInSteps(double eDepStep) { fVecOfEnergyDepositInSteps.push_back(eDepStep); }

void RootObjects::FillVecOfPreStepPositionInSteps(G4ThreeVector pos) { fVecOfPreStepPoint.push_back(pos); }

void RootObjects::FillEnergyDep() {
  double eDep = 0;
  double xval = 0;
  double yval = 0;
  double zval = 0;
  for (unsigned int i = 0; i < fVecOfEnergyDepositInSteps.size(); i++) {
    eDep += fVecOfEnergyDepositInSteps[i];
    xval += fVecOfPreStepPoint[i].x();
    yval += fVecOfPreStepPoint[i].y();
    zval += fVecOfPreStepPoint[i].z();
  }

  // std::cout << "Ener depo vec size : " << fVecOfEnergyDepositInSteps.size() << " : " << fVecOfPreStepPoint.size() <<
  // std::endl;
  if (fVecOfPreStepPoint.size() > 0) {
    xval /= fVecOfPreStepPoint.size();
    yval /= fVecOfPreStepPoint.size();
    zval /= fVecOfPreStepPoint.size();
    // std::cout << "RAMAN : " << xval << " : " << yval <<" : " << zval << std::endl;
    // std::cout << "Volume Name  : " << fObjectName << std::endl;
    fEnergyDepHist->Fill(eDep);
    fDataObject->SetEnergy(eDep);

    fDataObject->SetEntryHitPoint(fVecOfPreStepPoint[0].x(), fVecOfPreStepPoint[0].y(), fVecOfPreStepPoint[0].z());
    fDataObject->SetMeanHitPoint(xval, yval, zval);
  }
  // std::cout <<" @@ EEENERGY from RootObjects::FillEnergyDep : " << eDep << std::endl;
}

void RootObjects::Write() { fEnergyDepHist->Write(); }
