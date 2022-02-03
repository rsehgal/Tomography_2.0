/*
**	Filename : Analysis.h
**	2022-01-17
**	username : rsehgal
*/
/*
** For adding ROOT related functionality
**
** Idea is to attach an object of this class to the
** sensitive detector volume.
**
** Its function will be just to fill the ROOT data structures
** and write them to the ROOT file
**
** NOTE : The ROOT file needs to be opened in the start of simulation
**
*/

#ifndef Analysis_h
#define Analysis_h

#include "RootObjects.h"
#include "TH1F.h"
#include <TFile.h>
#include <string>
#include <vector>
#include <TTree.h>
#include "Data.h"
#include "MuonTrack.h"
#include "Imaging.h"

class Analysis {
  std::string fPhyVolumeName;
  std::vector<RootObjects *> fVecOfRootObjects;
  
  /*Variable to be stored in TTree*/
  std::vector<Data *> fVecOfData;
  Vector3D fPOCA;
  double fScattering;
  //std::vector<Vector3D> fVecOfMeanHitPt;
  Vector3D fMeanHitPt; 

  TTree *ftree;

  MuonTrack *fIncomingMuonTrack;
  MuonTrack *fOutgoingMuonTrack;
  Tracking::ImageReconstruction fIm; 
  
  double fAngularDeviation;
  TH1F *fAngDevHist;

  /*Required ROOT plots*/
  // TH1F *fEnergyDepHist;
  // TFile *fp;

public:
  Analysis();
  ~Analysis();
  Analysis(std::string logicalVolumeName);
  void InitializeRootObjects(std::string name);
  void InitializeRootObjects(std::string name, unsigned short detId, unsigned short layerId);
  std::string GetPhyVolumeName() const;
  void Write();
  void InitializeTotalEnergyDeposit();
  void EnergyDepositInSteps(std::string name, double eDepStep);
  void PreStepPositionInSteps(std::string name, G4ThreeVector pt);
  void FillEnergyDep();

  /*Function to analyze the tracks */
  Data* HitInLayer(unsigned short layerId, bool &yes);
  std::vector<Data*> HitInAllLayers(bool &yes);
  std::vector<Data*> GetIncomingMuonTrack();
  std::vector<Data*> GetOutgoingMuonTrack();
  double GetAngularDeviation();
  std::vector<Data*> GetVectorOfData();
  void CalculatePOCA();

  void Print();
  
  /*void FillEnergy(double energyVal);
  void Write();
  void Close();*/
};
#endif
