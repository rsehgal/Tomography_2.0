#include "Data.h"
#include "EveVisualizer.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include <iostream>
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
  // TApplication *fApp = new TApplication("Test", NULL, NULL);
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
    tr->GetEntry(j);
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {
      (*VectorOfDataObject)[i]->Print();
    }
  }

  double color = 10;

  // fApp->Run();

  return 0;
}
