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
  std::vector<Data *> *Incoming_VectorOfDataObject = NULL;
  std::vector<Data *> *Outgoing_VectorOfDataObject = NULL;
  Vector3D *poca = NULL;
  tr->SetBranchAddress("Incoming_VectorOfDataObject", &Incoming_VectorOfDataObject);
  tr->SetBranchAddress("Outgoing_VectorOfDataObject", &Outgoing_VectorOfDataObject);
  tr->SetBranchAddress("POCA", &poca);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;

  Vec_t tempPt;

  unsigned int counter = 0;

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    counter++;
    tr->GetEntry(j);
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << RED << "######################################" << RESET << std::endl;
    for (unsigned int i = 0; i < Incoming_VectorOfDataObject->size(); i++) {
      std::cout << MAGENTA;
      (*Incoming_VectorOfDataObject)[i]->Print();
      std::cout << RESET;
    }
	for (unsigned int i = 0; i < Outgoing_VectorOfDataObject->size(); i++) {
      std::cout <<  BLUE;
      (*Outgoing_VectorOfDataObject)[i]->Print();
      std::cout << RESET;
    }

  }
std::cout << RED << "Total Number of Muon Tracks : " << counter << std::endl;
  double color = 10;

  // fApp->Run();

  return 0;
}
