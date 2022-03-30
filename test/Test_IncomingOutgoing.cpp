#include "Data.h"
#include "EveVisualizer.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include <iostream>
#include "colors.h"
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
  // TApplication *fApp = new TApplication("Test", NULL, NULL);
  TFile *fp = new TFile(argv[1], "r");
  TTree *tr = (TTree *)fp->Get(argv[2]);
  std::vector<Data *> *Outgoint_VectorOfDataObject = NULL;
  std::vector<Data *> *Incoming_VectorOfDataObject = NULL;
  tr->SetBranchAddress("Incoming_VectorOfDataObject", &Incoming_VectorOfDataObject);
  tr->SetBranchAddress("Outgoing_VectorOfDataObject", &Outgoint_VectorOfDataObject);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;

  Vec_t tempPt;

  unsigned int counter = 0;

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    tr->GetEntry(j);

    if(Incoming_VectorOfDataObject->size() != Outgoint_VectorOfDataObject->size())
	std::cout << RED << "Incoming track size DOES NOT matches with outgoing ... " << RESET << std::endl;
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    //std::cout << "--------------------------------------" << std::endl;
    /*for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {
      (*VectorOfDataObject)[i]->Print();
    }*/
  }

  double color = 10;

  // fApp->Run();

  return 0;
}
