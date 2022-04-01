#include "Data.h"
#include "EveVisualizer.h"
#include "MuonTrack.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include "colors.h"
#include <Imaging.h>
#include <iostream>
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
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

  Vec_t tempPt;

  MuonTrack incomingTrack;
  MuonTrack outgoingTrack;

  std::vector<Vector3D> pocaVec;

  unsigned int counter = 0;
  // For Incoming Track
  double *x = new double[tr->GetEntries()];
  double *y = new double[tr->GetEntries()];
  double *z = new double[tr->GetEntries()];
  double *dirx = new double[tr->GetEntries()];
  double *diry = new double[tr->GetEntries()];
  double *dirz = new double[tr->GetEntries()];

  // For Outgoing Track
  double *xO = new double[tr->GetEntries()];
  double *yO = new double[tr->GetEntries()];
  double *zO = new double[tr->GetEntries()];
  double *dirxO = new double[tr->GetEntries()];
  double *diryO = new double[tr->GetEntries()];
  double *dirzO = new double[tr->GetEntries()];

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    //std::cout << RED << "Angle : " << angle << RESET << std::endl;
    tr->GetEntry(j);
    if (angle > 0.00006) {
      pocaVec.push_back(*poca);
      incomingTrack.Reset(*Incoming_VectorOfDataObject);
      outgoingTrack.Reset(*Outgoing_VectorOfDataObject);

      Tomography::Track *incoming = incomingTrack.GetProcessorTrack();
      Tomography::Track *outgoing = outgoingTrack.GetProcessorTrack();

      x[counter] = incoming->GetP1().x();
      y[counter] = incoming->GetP1().y();
      z[counter] = incoming->GetP1().z();
      dirx[counter] = incoming->GetDirCosine().x();
      diry[counter] = incoming->GetDirCosine().y();
      dirz[counter] = incoming->GetDirCosine().z();

      xO[counter] = outgoing->GetP1().x();
      yO[counter] = outgoing->GetP1().y();
      zO[counter] = outgoing->GetP1().z();
      dirxO[counter] = outgoing->GetDirCosine().x();
      diryO[counter] = outgoing->GetDirCosine().y();
      dirzO[counter] = outgoing->GetDirCosine().z();

      counter++;
    }
  }

  std::cout << BLUE << "*************** Printing PoCA ***********************" << RESET << std::endl;
  // for (unsigned int j = 0; j < tr->GetEntries(); j++) {
  for (unsigned int j = 0; j < counter; j++) {
    Vec_t p(x[j], y[j], z[j]);
    Vec_t u(dirx[j], diry[j], dirz[j]);
    Vec_t q(xO[j], yO[j], zO[j]);
    Vec_t v(dirxO[j], diryO[j], dirzO[j]);
    Vec_t p1, q1;
    Vec_t poca = img.POCA(p, u, q, v, p1, q1);
    std::cout << MAGENTA;
    poca.Print();
    std::cout << RESET;
    std::cout << BLUE;
    pocaVec[j].Print();
    std::cout << RESET;
  }
  std::cout << RED << "Total Number of Muon Tracks : " << counter << std::endl;
  double color = 10;

  // fApp->Run();

  return 0;
}
