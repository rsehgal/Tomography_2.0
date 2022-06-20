#include "Data.h"
#include "EveVisualizer.h"
#include "MuonTrack.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include "colors.h"
#include "timer.h"
#include <Imaging.h>
#include <iostream>

int main(int argc, char *argv[]) {

  Tracking::ImageReconstruction img;
  // TApplication *fApp = new TApplication("Test", NULL, NULL);
  TFile *fp = new TFile(argv[1], "r");
  TTree *tr = (TTree *)fp->Get(argv[2]);
  std::vector<Data *> *Incoming_VectorOfDataObject = NULL;
  std::vector<Data *> *Outgoing_VectorOfDataObject = NULL;
  Vector3D *poca = NULL;
  double angle = 0;
  tr->SetBranchAddress("Incoming_VectorOfDataObject", &Incoming_VectorOfDataObject);
  tr->SetBranchAddress("Outgoing_VectorOfDataObject", &Outgoing_VectorOfDataObject);
  tr->SetBranchAddress("POCA", &poca);
  tr->SetBranchAddress("AngularDeviation", &angle);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;
  unsigned int counter = 0;
  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    // std::cout << RED << "Angle : " << angle << RESET << std::endl;
    tr->GetEntry(j);
    if (angle > 0.00006) {
      std::cout << "Angle : " << angle << std::endl;
      std::cout << RED << "++++++++++++++++++++++++++++++++++++++" << RESET << std::endl;
      for (unsigned int k = 0; k < (*Incoming_VectorOfDataObject).size(); k++) {
        (*Incoming_VectorOfDataObject)[k]->Print();
      }
      counter++;
    }
  }
  std::cout << RED << "Total Number of Muon Tracks : " << counter << std::endl;

  return 0;
}
