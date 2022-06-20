#include "Data.h"
#include "EveVisualizer.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include <iostream>
#include <fstream>
#include "CommonFunc.h"
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
  TApplication *fApp = new TApplication("Test", NULL, NULL);
  Tomography::VisualizationHelper *v = new Tomography::VisualizationHelper; //::instance();
  // Vec_t pt(3.,4.,5.,10.);
  v->InitializeVisualizer();
  // v->Register(pt);
  v->Register("Hodoscope.gdml");
  unsigned int counter = 0;
  std::ifstream ft(argv[1]);
  double x=0.,y=0.,z=0;
    double color=0;
Vec_t pt;
double deno=10.;
while(!ft.eof()){



        ft >> x >> y >> z >> color;
        std::cout << x <<" , " << y <<" , "<< " , " << z << " , " << color << std::endl;
        pt.Set(x,y,z);
        double colorVal = CommonFunc::Functions::instance()->CreateColorVal(color*1000.);
        pt.SetColor(colorVal);
  	v->Register(pt);
}


/*  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    if (angDev > 0.00006) {
      counter++;
      //tempPt.Set(poca->GetX(), poca->GetY(), poca->GetZ());
      tempPt.Set(meanHitPt->GetX(), meanHitPt->GetY(), meanHitPt->GetZ());
      v->Register(tempPt);
    }

    tr->GetEntry(j);
    // std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {

      std::cout << "--------------------------------------" << std::endl;
      //std::cout << "POCA : ";
      //poca->Print();
      //(*VectorOfDataObject)[i]->Print();
      // tempPt.Set(poca->GetX()/10.,poca->GetY()/10.,poca->GetZ()/10.);
      if (angDev > 0.00006) {
        counter++;
        tempPt.Set(poca->GetX(), poca->GetY(), poca->GetZ());
        v->Register(tempPt);
      }
    }
  }
*/
  std::cout << "No. of points plotted : " << counter << std::endl;
  // Now tryig to register a voxel
  /*Vec_t voxDim(10.,10.,10.);
  Vec_t voxCenter(0.,0.,0.);
  v->Register(voxDim,voxCenter,5);*/

  v->Lock();
  // rev.CloseBins();

  v->Show();
  fApp->Run();

  return 0;
}
