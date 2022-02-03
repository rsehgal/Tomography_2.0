/*
**	Filename : MuonTrack.cpp
**	2022-01-27
**	username : rsehgal
*/
#include "Data.h"
#include "MuonTrack.h"
#include <TVector3.h>
#include <iostream>
MuonTrack::MuonTrack() {}

MuonTrack::MuonTrack(std::vector<Data *> vecOfData) {
  fVecOfData.clear();

  for (unsigned int i = 0; i < vecOfData.size(); i++) {
    fVecOfData.push_back(vecOfData[i]);
  }
}

MuonTrack::MuonTrack(Data *start, Data *end) {
  fVecOfData.clear();
  fVecOfData.push_back(start);
  fVecOfData.push_back(end);
}

Tomography::Track *MuonTrack::GetProcessorTrack() {
  return new Tomography::Track(
      Tracking::Vector3D<double>((fVecOfData[0]->GetEntryHitPoint()).GetX(), (fVecOfData[0]->GetEntryHitPoint()).GetY(),
                                 (fVecOfData[0]->GetEntryHitPoint()).GetZ()),
      Tracking::Vector3D<double>((fVecOfData[fVecOfData.size() - 1]->GetEntryHitPoint()).GetX(),
                                 (fVecOfData[fVecOfData.size() - 1]->GetEntryHitPoint()).GetY(),
                                 (fVecOfData[fVecOfData.size() - 1]->GetEntryHitPoint()).GetZ()));
}

void MuonTrack::Reset() { fVecOfData.clear(); }

void MuonTrack::Reset(std::vector<Data *> vecOfData) {
  fVecOfData.clear();
  for (unsigned int i = 0; i < vecOfData.size(); i++) {
    // std::cout << "+++++++++++++ FROM RESEST +++++++++++++++++++++++++" << std::endl;
    // vecOfData[i]->Print();
    fVecOfData.push_back(vecOfData[i]);
  }
}

TVector3 MuonTrack::GetEntryHitPoint_TVector3() {
  Vector3D start = fVecOfData[0]->GetEntryHitPoint();
  Vector3D end = fVecOfData[fVecOfData.size() - 1]->GetEntryHitPoint();
  return TVector3(end.GetX() - start.GetX(), end.GetY() - start.GetY(), end.GetZ() - start.GetZ());
}

TVector3 MuonTrack::GetMeanHitPoint_TVector3() {
  Vector3D start = fVecOfData[0]->GetMeanHitPoint();
  Vector3D end = fVecOfData[fVecOfData.size() - 1]->GetMeanHitPoint();
  return TVector3(end.GetX() - start.GetX(), end.GetY() - start.GetY(), end.GetZ() - start.GetZ());
}

double MuonTrack::GetAngularDeviation(MuonTrack *muonTrack) {
  TVector3 incoming = GetEntryHitPoint_TVector3();
  TVector3 outgoing = muonTrack->GetEntryHitPoint_TVector3();
  TVector3 dir(0., 0., -1.);
  double angleIncoming = dir.Angle(incoming);
  double angleOutgoing = dir.Angle(outgoing);
  return angleOutgoing - angleIncoming;
  //  std::cout << "(" << incoming.X() <<"," << incoming.Y() <<","<<incoming.Z() <<") : "
  //<< "(" << outgoing.X() <<"," << outgoing.Y() <<","<<outgoing.Z() <<") : " << __FILE__ << " : " << __LINE__ <<
  //std::endl; return incoming.Angle(outgoing); return outgoing.Theta(); return
  // atan(sqrt(outgoing.X()*outgoing.X()+outgoing.Y()*outgoing.Y())/std::fabs(outgoing.Z()));
}

void MuonTrack::Print() {
  std::cout << "--------------------------------------" << std::endl;
  for (unsigned int i = 0; i < fVecOfData.size(); i++) {
    fVecOfData[i]->Print();
  }
}
