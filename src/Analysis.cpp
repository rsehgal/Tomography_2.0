/*
**	Filename : Analysis.cpp
**	2022-01-17
**	username : rsehgal
*/
#include "Analysis.h"
#include "Data.h"
#include "MuonTrack.h"
#include "base/Vector3D.h"
#include "colors.h"
#include <TFile.h>
#include <TH1F.h>
#include <iostream>
#include <string>
#include <vector>
Analysis::Analysis() {
  fp = new TFile("anal.root", "RECREATE");
  ftree = new TTree("ftree", "A tree with objects of Data");
  ftree->Branch("VectorOfDataObject", "std::vector<Data*>", &fVecOfData);
  ftree->Branch("POCA", "Vector3D", &fPOCA);
  ftree->Branch("MeanHitPt", "Vector3D", &fMeanHitPt);
  ftree->Branch("AngularDeviation", &fAngularDeviation, "fAngularDeviation/D");
  // ftree->Branch("VecOfMeanHitPt", "std::vector<Vector3D>", &fVecOfMeanHitPt);
  fIncomingMuonTrack = new MuonTrack;
  fOutgoingMuonTrack = new MuonTrack;
  fAngDevHist = new TH1F("AngularDeviation", "AngularDeviation", 200, -0.2, 0.2);

  fPocaTree = new TTree("fPocaTree", "A tree to evaluate vectorized PoCA");
  fPocaTree->Branch("Incoming_VectorOfDataObject", "std::vector<Data*>", &fIncomingVecOfData);
  fPocaTree->Branch("Outgoing_VectorOfDataObject", "std::vector<Data*>", &fOutgoingVecOfData);
  fPocaTree->Branch("POCA", "Vector3D", &fPOCA);
  fPocaTree->Branch("AngularDeviation", &fAngularDeviation, "fAngularDeviation/D");
}
Analysis::~Analysis() {
  // fEnergyDepHist->Write();
}

Analysis::Analysis(std::string phyVolumeName) {
  /*std::cout << "RAMAN : Initializing Analyzer for LogicalVolume : " << phyVolumeName << std::endl;
  fPhyVolumeName = phyVolumeName;
  ftree = new TTree("ftree", "A tree with objects of Data");
  ftree->Branch("VectorOfDataObject", "std::vector<Data*>", &fVecOfData);
  fIncomingMuonTrack = new MuonTrack;
  fOutgoingMuonTrack = new MuonTrack;*/
}

std::string Analysis::GetPhyVolumeName() const { return fPhyVolumeName; }

std::vector<Data *> Analysis::GetVectorOfData() { return fVecOfData; }

void Analysis::EnergyDepositInSteps(std::string name, double eDepStep) {
  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    if (fVecOfRootObjects[i]->GetObjectName() == name) {
      fVecOfRootObjects[i]->FillVecOfEnergyDepositInSteps(eDepStep);
    }
  }
}
void Analysis::PreStepPositionInSteps(std::string name, G4ThreeVector pt) {
  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    if (fVecOfRootObjects[i]->GetObjectName() == name) {
      fVecOfRootObjects[i]->FillVecOfPreStepPositionInSteps(pt);
    }
  }
}

void Analysis::SetHittedFor(std::string name) {
  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    if (fVecOfRootObjects[i]->GetObjectName() == name) {
      fVecOfRootObjects[i]->SetHitted();
    }
  }
}

void PreStepPositionInSteps(std::string name, G4ThreeVector pt);

void Analysis::InitializeTotalEnergyDeposit() {

  fVecOfData.clear();
  // fVecOfMeanHitPt.clear();
  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    fVecOfRootObjects[i]->InitializeTotalEnergyDeposit();
  }
}

void Analysis::InitializeRootObjects(std::string name) { fVecOfRootObjects.push_back(new RootObjects(name)); }

void Analysis::InitializeRootObjects(std::string name, unsigned short detId, unsigned short layerId) {
  fVecOfRootObjects.push_back(new RootObjects(name, detId, layerId));
}

/*void Analysis::FillEnergyDep(std::string name,double energyDep){

for(unsigned int i = 0 ; i < fVecOfRootObjects.size() ; i++){
  if(fVecOfRootObjects[i]->GetObjectName()==name){
    fVecOfRootObjects[i]->FillEnergyDep(energyDep);
}
}
}*/

void Analysis::FillEnergyDep() {

  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    if (fVecOfRootObjects[i]->GetHitted()) {
      fVecOfRootObjects[i]->FillEnergyDep();
      Data *temp = fVecOfRootObjects[i]->GetDataObject();
      // temp->Print();
      fVecOfData.push_back(temp);
      std::string detName = temp->GetDetName();
      std::size_t pos = detName.find("_");
      std::string preString = detName.substr(0, pos);
      if (preString == "Scatterer") {
        // std::cout << "Going to fill vecOf Mean Hit Pt .... : " << __FILE__ << " : "<< __LINE__ << std::endl;
        // fVecOfMeanHitPt.push_back(temp->GetMeanHitPoint());
        fMeanHitPt = temp->GetMeanHitPoint();
      }
    }
  }
  ftree->Fill();
}

void Analysis::Write() {
  fp->cd();
  for (unsigned int i = 0; i < fVecOfRootObjects.size(); i++) {
    fVecOfRootObjects[i]->Write();
  }
  ftree->Write();
  fPocaTree->Write();
  fAngDevHist->Write();
  fp->Close();
}
Data *Analysis::HitInLayer(unsigned short layerId, bool &yes) {
  yes = false;
  // std::cout << MAGENTA << "Size of Vector Data : " << fVecOfData.size() << RESET << std::endl;
  for (unsigned int i = 0; i < fVecOfData.size(); i++) {
    std::string detName = fVecOfData[i]->GetDetName();
    // std::cout << BLUE << "Detector Name : " << detName << RESET << std::endl;
    std::size_t pos = detName.find("_");
    std::string preString = detName.substr(0, pos);
    if (fVecOfData[i]->GetLayerId() == layerId && preString == "PhysicalTrackingDetector") {
      yes = true;
      return fVecOfData[i];
    }
  }
  return NULL;
}
std::vector<Data *> Analysis::HitInAllLayers(bool &yes) {
  std::vector<Data *> vecOfData;
  yes = true;
  short numOfLayers = 4;
  for (short i = numOfLayers - 1; i >= 0; i--) {
    // std::cout << RED <<  "I : " << i << RESET << std::endl;
    bool hitDone = false;
    Data *temp = HitInLayer(i, hitDone);
    yes &= hitDone;
    if (yes) {
      vecOfData.push_back(temp);
    }
  }
  if (!yes) {
    vecOfData.clear();
  }
  return vecOfData;
}
std::vector<Data *> Analysis::GetIncomingMuonTrack(bool &hitInAllLayers) {
  // bool hitInAllLayers = true;
  std::vector<Data *> incomingTrack;
  //std::cout << RED << "Size of DataVEc from IncomingTrack : " << fVecOfData.size() << RESET << std::endl;
  if (fVecOfData.size() == 4) {
    std::vector<Data *> completeTrack = HitInAllLayers(hitInAllLayers);
    if (hitInAllLayers) {
      for (unsigned int i = 0; i < completeTrack.size() / 2; i++) {
        incomingTrack.push_back(completeTrack[i]);
      }
    }
  } else
    hitInAllLayers = false;
  return incomingTrack;
}
std::vector<Data *> Analysis::GetOutgoingMuonTrack(bool &hitInAllLayers) {
  // bool hitInAllLayers = true;
  std::vector<Data *> outgoingTrack;
  //std::cout << RED << "Size of DataVEc from OutgoingTrack : " << fVecOfData.size() << RESET << std::endl;
  if (fVecOfData.size() == 4) {
    std::vector<Data *> completeTrack = HitInAllLayers(hitInAllLayers);
    if (hitInAllLayers) {

      for (unsigned int i = completeTrack.size() / 2; i < completeTrack.size(); i++) {
        outgoingTrack.push_back(completeTrack[i]);
      }
    }
  } else
    hitInAllLayers = false;
  return outgoingTrack;
}
double Analysis::GetAngularDeviation() {
  // std::vector<Data *> incomingTrackData = GetIncomingMuonTrack();
  // std::vector<Data *> outgoingTrackData = GetOutgoingMuonTrack();
  bool hitInAllLayers = true;
  fIncomingVecOfData = GetIncomingMuonTrack(hitInAllLayers);
  hitInAllLayers = true;
  fOutgoingVecOfData = GetOutgoingMuonTrack(hitInAllLayers);

  //  if (fVecOfData.size() > 4) {
  if (0) {
    std::cout << RED << "@@@@@@@@@@@@@@@@@@ ERROR ################## : " << RESET << BLUE << fVecOfData.size() << RESET
              << std::endl;

    for (unsigned int i = 0; i < fVecOfData.size(); i++) {

      std::cout << "**************************************" << std::endl;
      fVecOfData[i]->Print();
    }
  }
  // fIncomingMuonTrack->Reset(incomingTrackData);
  if (hitInAllLayers) {
  fIncomingMuonTrack->Reset(fIncomingVecOfData);

  // std::cout << RED << "--------------------------------" << RESET << std::endl;
  // fIncomingMuonTrack->Print();
  // std::cout << BLUE << "--------------------------------" << RESET << std::endl;
  // fIncomingMuonTrack->GetProcessorTrack()->Print();

  // fOutgoingMuonTrack->Reset(outgoingTrackData);
  fOutgoingMuonTrack->Reset(fOutgoingVecOfData);

  // fOutgoingMuonTrack->Print();
  // Print();
  fAngularDeviation = fIncomingMuonTrack->GetAngularDeviation(fOutgoingMuonTrack);
  // if (std::fabs(fAngularDeviation) > 0.000001)
  //std::cout << RED << "HitInAllLayers from GetAngularDeviation : " << hitInAllLayers << RESET << std::endl; 
  //if (hitInAllLayers) {
    fAngDevHist->Fill(fAngularDeviation);
    CalculatePOCA();
    fPocaTree->Fill();
    //Print();
  }
  return fAngularDeviation;
}

void Analysis::CalculatePOCA() {
  Tracking::Vector3D<double> pocaPt =
      fIm.POCA(*fIncomingMuonTrack->GetProcessorTrack(), *fOutgoingMuonTrack->GetProcessorTrack());
  fPOCA.Set(pocaPt.x(), pocaPt.y(), pocaPt.z());
  // fPocaPt.SetColor(fScatteringAngle);
   //std::cout << "POCA from Analyzer : ";
   //pocaPt.Print();
}

void Analysis::Print() {
  std::cout << RED << "----------------------------------------------------------" << RESET << std::endl;
  fIncomingMuonTrack->Print();
  fOutgoingMuonTrack->Print();
}
/*void Analysis::FillEnergy(double energyVal){
//fEnergyDepHist->Fill(energyVal/1000.);
}

void Analysis::Write(){
//fEnergyDepHist->Write();
//fp->Close();
}

void Analysis::Close(){
//fp->Close();
}*/
