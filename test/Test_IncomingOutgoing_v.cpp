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
static constexpr size_t kNruns = 1;//20;
static constexpr size_t kN = 1;//10000; //(1024 * 1024);

#ifdef VECCORE_TIMER_CYCLES
using time_unit = cycles;
static const char *time_unit_name = "cycles";
#else
using time_unit = nanoseconds;
static const char *time_unit_name = "ns";
#endif

using Tomography::VisualizationHelper;
using MyVec_t = Tracking::Vector3D<double>;

//--------------- Vectorized Stuff --------------------
#include <Vc/Vc>
#include <VecCore/VecCore>
#include <VecGeom/base/Vector3D.h>

#ifdef VECGEOM_FLOAT_PRECISION
using baseType = float;
#else
using baseType = double;
#endif

using Real_v = Vc::Vector<baseType>;
using vecgeomVec_t = vecgeom::Vector3D<Real_v>;

vecgeomVec_t POCA(vecgeomVec_t p, vecgeomVec_t u, vecgeomVec_t q, vecgeomVec_t v) {
  Real_v pDotv = p.Dot(v);
  Real_v qDotv = q.Dot(v);
  Real_v pDotu = p.Dot(u);
  Real_v qDotu = q.Dot(u);
  Real_v uDotv = u.Dot(v);
  Real_v vMag2 = v.Mag2();
  Real_v uMag2 = u.Mag2();

  Real_v s = 0., t = 0.;
  Real_v a = -(pDotv - qDotv) / uDotv;
  Real_v b1 = uDotv * (pDotu - qDotu);
  Real_v b2 = uMag2 * (pDotv - qDotv);
  Real_v b = b1 - b2;
  Real_v c = (-uDotv * uDotv + vMag2 * uMag2);
  Real_v d = (-vMag2 * b) / (uDotv * c);
  s = a + d;
  /*std::cout << "A : " << a << std::endl;
  std::cout << "D : " << d << std::endl;*/
  Real_v numer = (uDotv * (pDotu - qDotu) - uMag2 * (pDotv - qDotv));
  Real_v deno = (uDotv * uDotv - uMag2 * vMag2);
  t = numer / deno;
  vecgeomVec_t p1 = p + u * s;

  /*std::cout << "--------------------------------------" << std::endl;
  std::cout << "P : " << p << std::endl;
  std::cout << "U : " << u << std::endl;
  std::cout << "S : " << s << std::endl;
  std::cout << "--------------------------------------" << std::endl;*/

  vecgeomVec_t q1 = q + v * t;

  /*std::cout << "P1 : " << p1 << std::endl;
  std::cout << "Q1 : " << q1 << std::endl;*/
  return (p1 + q1) / 2.;
}
//------------------------------------------------------

int main(int argc, char *argv[]) {
  Timer<time_unit> timer;
  unsigned long long t[kNruns], mean = 0;

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

  MyVec_t tempPt;

  MuonTrack incomingTrack;
  MuonTrack outgoingTrack;

  std::vector<Vector3D> pocaVec;

  unsigned int counter = 0;

// For Incoming Track
#ifdef VECGEOM_FLOAT_PRECISION
  float *x = new float[tr->GetEntries()];
  float *y = new float[tr->GetEntries()];
  float *z = new float[tr->GetEntries()];
  float *dirx = new float[tr->GetEntries()];
  float *diry = new float[tr->GetEntries()];
  float *dirz = new float[tr->GetEntries()];

  // For Outgoing Track
  float *xO = new float[tr->GetEntries()];
  float *yO = new float[tr->GetEntries()];
  float *zO = new float[tr->GetEntries()];
  float *dirxO = new float[tr->GetEntries()];
  float *diryO = new float[tr->GetEntries()];
  float *dirzO = new float[tr->GetEntries()];
#else
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
#endif

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {
    // std::cout << RED << "Angle : " << angle << RESET << std::endl;
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

  for (size_t n = 0; n < kNruns; n++) {
    timer.Start();
    for (size_t i = 0; i < kN; i++) {

      for (unsigned int j = 0; j < counter; j++) {
        MyVec_t p(x[j], y[j], z[j]);
        MyVec_t u(dirx[j], diry[j], dirz[j]);
        MyVec_t q(xO[j], yO[j], zO[j]);
        MyVec_t v(dirxO[j], diryO[j], dirzO[j]);
        MyVec_t p1, q1;
        MyVec_t poca = img.POCA(p, u, q, v, p1, q1);
        /*std::cout << MAGENTA;
        poca.Print();
        std::cout << RESET;
        std::cout << BLUE;
        pocaVec[j].Print();
        std::cout << RESET;*/
      }
    }
    t[n] = timer.Elapsed();
    std::cout << BLUE << "Time elapsed in iteration number : " << n << " : " << t[n] << RESET << std::endl;
  }

  for (size_t n = 0; n < kNruns; n++)
    mean += t[n];

  mean = mean / (kN * kNruns);
  // std::cout << "Time elapsed in vector processing : " << timer.Elapsed() << std::endl;
  std::cout << "Average Time elapsed in Scalar processing : " << mean << std::endl;

  std::cout << RED << "Total Number of Muon Tracks : " << counter << std::endl;
  double color = 10;

  //---------- VEctorized Stuff -------
  {
    vecgeomVec_t Pi1(-2., 0., 0.), Pi2(0., 2., 0.);
    vecgeomVec_t dirI = (Pi2 - Pi1).Unit();
    vecgeomVec_t Po1(5., 0., 0.), Po2(0., 5., 0.);
    vecgeomVec_t dirO = (Po2 - Po1).Unit();
    // std::cout << "--------------------------------------" << std::endl;
    vecgeomVec_t poca = POCA(Pi1, dirI, Po1, dirO);
    // std::cout << "POCA Point : " << poca << std::endl;

    // std::cout << BLUE << "############### Going to do Vectorized PoCA #######################" << RESET << std::endl;
    unsigned int size = counter;
    unsigned int offset = size - size % vecCore::VectorSize<Real_v>();
    std::cout << "Offset : " << offset << std::endl;
    unsigned int vec_loop_counter = 0;
    for (size_t n = 0; n < kNruns; n++) {
      timer.Start();
      for (size_t i = 0; i < kN; i++) {
        for (unsigned int i = 0; i < offset; i += vecCore::VectorSize<Real_v>()) {
          // std::cout << RED << "Scalar : (" << x[i] <<","<<x[i+1]<<","<<x[i+2]<<","<<x[i+3] <<")" << RESET <<
          // std::endl ;
          vec_loop_counter++;
          vecgeom::Vector3D<Real_v> p(vecCore::FromPtr<Real_v>(x + i), vecCore::FromPtr<Real_v>(y + i),
                                      vecCore::FromPtr<Real_v>(z + i));
          // std::cout << p << std::endl;
          vecgeom::Vector3D<Real_v> u(vecCore::FromPtr<Real_v>(dirx + i), vecCore::FromPtr<Real_v>(diry + i),
                                      vecCore::FromPtr<Real_v>(dirz + i));

          vecgeom::Vector3D<Real_v> q(vecCore::FromPtr<Real_v>(xO + i), vecCore::FromPtr<Real_v>(yO + i),
                                      vecCore::FromPtr<Real_v>(zO + i));
          vecgeom::Vector3D<Real_v> v(vecCore::FromPtr<Real_v>(dirxO + i), vecCore::FromPtr<Real_v>(diryO + i),
                                      vecCore::FromPtr<Real_v>(dirzO + i));
          poca = POCA(p, u, q, v);
           std::cout << BLUE << "POCA : " << poca << RESET << std::endl;
        }
      }
      t[n] = timer.Elapsed();
      std::cout << BLUE << "Time elapsed in iteration number : " << n << " : " << t[n] << RESET << std::endl;
    }

    for (size_t n = 0; n < kNruns; n++)
      mean += t[n];

    mean = mean / (kN * kNruns);
    // std::cout << "Time elapsed in vector processing : " << timer.Elapsed() << std::endl;
    std::cout << "Average Time elapsed in vector processing : " << mean << std::endl;
    std::cout << MAGENTA << "Size : " << size << " : Vectorized Loop Counter : " << vec_loop_counter << RESET
              << std::endl;
  }

  //----------------------------------
  // fApp->Run();

  return 0;
}
