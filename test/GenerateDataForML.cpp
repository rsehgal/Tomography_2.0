/*
**	Filename : GenerateDataForML.cpp
**	2022-02-03
**	username : rsehgal
*/
#include "Analysis.h"
#include "Data.h"
#include "EveVisualizer.h"
#include "MuonTrack.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "Track.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include "colors.h"
#include <fstream>
#include <iostream>
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
  std::ofstream outfile("mldata.txt");
  TApplication *fApp = new TApplication("Test", NULL, NULL);
  /*Tomography::VisualizationHelper *v = new Tomography::VisualizationHelper; //::instance();
  // Vec_t pt(3.,4.,5.,10.);
  v->InitializeVisualizer();
  // v->Register(pt);
  v->Register("geom.gdml");*/
  TFile *fp = new TFile(argv[1], "r");
  TTree *tr = (TTree *)fp->Get(argv[2]);
  std::vector<Data *> *VectorOfDataObject = NULL;
  Vector3D *poca = NULL;
  Vector3D *meanHitPt = NULL;
  double angDev;
  tr->SetBranchAddress("VectorOfDataObject", &VectorOfDataObject);
  tr->SetBranchAddress("POCA", &poca);
  tr->SetBranchAddress("MeanHitPt", &meanHitPt);
  tr->SetBranchAddress("AngularDeviation", &angDev);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;

  Vec_t tempPt;

  unsigned int counter = 0;

  Analysis an;
  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    /*if (angDev > 0.00006) {
      counter++;
      //tempPt.Set(poca->GetX(), poca->GetY(), poca->GetZ());
      tempPt.Set(meanHitPt->GetX(), meanHitPt->GetY(), meanHitPt->GetZ());
      //v->Register(tempPt);
    }*/

    tr->GetEntry(j);
    // Analysis an(*VectorOfDataObject);
    // an.Print();
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::vector<Data *> vecOfData;

    /*for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {

      Data *temp = (*VectorOfDataObject)[i];
      vecOfData.push_back(temp);
    }*/

    // an.SetVecOfData(vecOfData);
    if (angDev > 0.00006) {
      an.SetVecOfData(*VectorOfDataObject);
      std::cout << RED << "--------------------------------------" << RESET << std::endl;
      Tracking::Vector3D<double> incomingVec3D = an.GetIncomingTrack()->GetProcessorTrack()->GetDirectionRatio();
      Tracking::Vector3D<double> outgoingVec3D = an.GetOutgoingTrack()->GetProcessorTrack()->GetDirectionRatio();
      incomingVec3D.Print();
      outgoingVec3D.Print();
      outfile << incomingVec3D.x() << "," << incomingVec3D.y() << "," << incomingVec3D.z() << "," << outgoingVec3D.x()
              << "," << outgoingVec3D.y() << "," << outgoingVec3D.z() << "," << meanHitPt->GetX() << ","
              << meanHitPt->GetY() << "," << meanHitPt->GetZ() << std::endl;
    }
    // std::cout << "--------------------------------------" << std::endl;
    // an.GetOutgoingTrack()->Print();
    // an.Print();
  }

  std::cout << "No. of points plotted : " << counter << std::endl;
  outfile.close();
  return 0;
}
