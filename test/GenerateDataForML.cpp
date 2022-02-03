/*
**	Filename : GenerateDataForML.cpp
**	2022-02-03
**	username : rsehgal
*/
#include "Data.h"
#include "EveVisualizer.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include <iostream>
#include "Analysis.h"
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
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

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    /*if (angDev > 0.00006) {
      counter++;
      //tempPt.Set(poca->GetX(), poca->GetY(), poca->GetZ());
      tempPt.Set(meanHitPt->GetX(), meanHitPt->GetY(), meanHitPt->GetZ());
      //v->Register(tempPt);
    }*/

    tr->GetEntry(j);
    //Analysis an(*VectorOfDataObject);
    //an.Print();
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::vector<Data*> vecOfData;
    for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {

	Data *temp =  (*VectorOfDataObject)[i];
	vecOfData.push_back(temp);
      /*std::cout << "--------------------------------------" << std::endl;
      std::cout << "POCA : ";
      poca->Print();
      (*VectorOfDataObject)[i]->Print();*/
      // tempPt.Set(poca->GetX()/10.,poca->GetY()/10.,poca->GetZ()/10.);
      /*if (angDev > 0.00006) {
        counter++;
        tempPt.Set(poca->GetX(), poca->GetY(), poca->GetZ());
        v->Register(tempPt);
      }*/
    }

    Analysis an(vecOfData);
    an.Print();
  }

  std::cout << "No. of points plotted : " << counter << std::endl;
  return 0;
}
