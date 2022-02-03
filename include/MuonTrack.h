/*
**	Filename : MuonTrack.h
**	2022-01-27
**	username : rsehgal
*/
#ifndef MuonTrack_h
#define MuonTrack_h

#include "Data.h"
#include <vector>
#include <TVector3.h>
#include "Track.h"
class MuonTrack {
  std::vector<Data *> fVecOfData;

public:
  MuonTrack();
  MuonTrack(std::vector<Data *> vecOfData);
  MuonTrack(Data *start, Data *end);
  void Reset();
  void Reset(std::vector<Data*> vecOfData);
  TVector3 GetEntryHitPoint_TVector3();
  TVector3 GetMeanHitPoint_TVector3();
  Tomography::Track* GetProcessorTrack();
  double GetAngularDeviation(MuonTrack *muonTrack);
  void Print();
};

#endif
