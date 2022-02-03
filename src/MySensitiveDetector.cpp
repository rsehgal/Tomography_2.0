/*
**	Filename : MySensitiveDetector.cpp
**	2022-01-14
**	username : rsehgal
*/
#include "Analysis.h"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include "MuonTrack.h"
#include "MyHit.h"
#include "MySensitiveDetector.h"
#include "colors.h"
#include <TVector3.h>
//#include "HitCollection.h"

int MySensitiveDetector::evNo = -1;

MySensitiveDetector::MySensitiveDetector(G4String name, G4String collName)
    : G4VSensitiveDetector(name), collectionID(-1) {
  //  collectionName.insert("Tomo");
  collectionName.insert(collName);
  fAnal = new Analysis; //(name);
  debugAngHist = new TH1F("DebugAngHist", "DebugAngHist", 1000,-1.*M_PI/2. , M_PI / 2.);
  energyDep = 0.;
}
void MySensitiveDetector::InitializeRootObjects(std::string name) { fAnal->InitializeRootObjects(name); }
MySensitiveDetector::~MySensitiveDetector() {
  fAnal->Write();
  debugAngHist->Write();
}

void MySensitiveDetector::InitializeAnalyzer(std::string phyVolumeName) { fAnal->InitializeRootObjects(phyVolumeName); }
void MySensitiveDetector::InitializeAnalyzer(std::string phyVolumeName, unsigned short detId, unsigned short layerId) {
  fAnal->InitializeRootObjects(phyVolumeName, detId, layerId);
}

void MySensitiveDetector::InitializeTotalEnergyDeposit() { fAnal->InitializeTotalEnergyDeposit(); }
void MySensitiveDetector::Initialize(G4HCofThisEvent *hce) {
  hitPointVec.clear();
  hitPointVec.resize(4);

  evNo++;
  if (!(evNo % 10000) && (evNo != 0))
    std::cout << BLUE << "Processed : " << evNo << " events..." << RESET << std::endl;
  InitializeTotalEnergyDeposit();
  // std::cout <<"@@@@@@ Initialize SD in the beginning of Event @@@@@@@" << std::endl;
  hitsCollection = new SDHitCollection(SensitiveDetectorName, collectionName[0]);
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, hitsCollection);
}

G4bool MySensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *touchableHist) {
  // energyDep += step->GetTotalEnergyDeposit();
  MyHit *newHit = new MyHit();
  G4Track *track = step->GetTrack();
  bool isPrimary = (track->GetParentID() == 0);
  /*For debugging*/
  G4TouchableHandle touch1 = step->GetPreStepPoint()->GetTouchableHandle();
  if (isPrimary && step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) {
    std::string geomName = std::string(touch1->GetVolume()->GetName());

    if (geomName == "PhysicalTrackingDetector_0_0")
      hitPointVec[0] = step->GetPostStepPoint()->GetPosition();
    if (geomName == "PhysicalTrackingDetector_1_1")
      hitPointVec[1] = step->GetPostStepPoint()->GetPosition();
    if (geomName == "PhysicalTrackingDetector_2_2")
      hitPointVec[2] = step->GetPostStepPoint()->GetPosition();
    if (geomName == "PhysicalTrackingDetector_3_3")
      hitPointVec[3] = step->GetPostStepPoint()->GetPosition();
  }

  if (isPrimary) {
    // newHit->SetPosition(step->GetPostStepPoint()->GetPosition());
    G4TouchableHandle touchable = step->GetPreStepPoint()->GetTouchableHandle();
    newHit->SetName(touchable->GetVolume(0)->GetName());
    //    std::cout << "EDEP :  "  << step->GetTotalEnergyDeposit() << std::endl;
    newHit->SetEnergyDep(step->GetTotalEnergyDeposit());
    newHit->SetPosition(step->GetPreStepPoint()->GetPosition());
    hitsCollection->insert(newHit);
  }
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *HCE) {
  unsigned int evId = 0;
  if (1) {
    // std::cout << RED << "Reached end of event from SD : " << evId << RESET <<  std::endl;
    unsigned int noOfHits = hitsCollection->entries();
    // std::cout << "No. Of hits in EvNo : " << evId <<" : " << noOfHits << std::endl;
    // fAnal->FillEnergy(energyDep);
    for (unsigned int i = 0; i < noOfHits; i++) {
      //(*hitsCollection)[i]->Print();
      fAnal->EnergyDepositInSteps((*hitsCollection)[i]->GetName(), (*hitsCollection)[i]->GetEnergyDep());
      fAnal->PreStepPositionInSteps((*hitsCollection)[i]->GetName(), (*hitsCollection)[i]->GetPosition());
    }
    // std::cout << __FILE__ << " : " <<  __LINE__ << std::endl;
    fAnal->FillEnergyDep();
    fAnal->GetAngularDeviation();
    //fAnal->CalculatePOCA();
    // MuonTrack *mt = new MuonTrack(fAnal->GetVectorOfData());

    /*std::cout << BLUE << "**************************************" << RESET << std::endl;
    std::cout << RED << "------------- INCOMING -------------------------" << RESET << std::endl; 
    MuonTrack *mt = new MuonTrack(fAnal->GetIncomingMuonTrack());
    mt->Print();

    std::cout << RED << "------------- OUTGOING -------------------------" << RESET << std::endl; 
    mt = new MuonTrack(fAnal->GetOutgoingMuonTrack());
    mt->Print();*/

    // std::cout<<"Angular Deviation : " << fAnal->GetAngularDeviation() << std::endl;
    // fAnal->Print();
  }
  // std::cout << __FILE__ << " : " <<  __LINE__ << std::endl;

  /*For debugging*/
  TVector3 incoming = TVector3(hitPointVec[1].x() - hitPointVec[0].x(), hitPointVec[1].y() - hitPointVec[0].y(),
                               hitPointVec[1].z() - hitPointVec[0].z());
  TVector3 outgoing = TVector3(hitPointVec[3].x() - hitPointVec[2].x(), hitPointVec[3].y() - hitPointVec[2].y(),
                               hitPointVec[3].z() - hitPointVec[2].z());
   debugAngHist->Fill(incoming.Angle(outgoing));

  // std::cout << outgoing.X() << " : " << outgoing.Z() << std::endl;
  //debugAngHist->Fill(atan2(outgoing.X(), std::fabs(outgoing.Z())));
  return;
}
