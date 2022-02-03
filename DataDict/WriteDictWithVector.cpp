/*
**	Filename : WriteDict.cpp
**	2022-01-23
**	username : rsehgal
*/
#include "Data.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <vector>
int main(int argc, char *argv[]) {
  TFile *fp = new TFile("test.root", "RECREATE");
  TTree *tr = new TTree("testTree", "testTree");

  /*Data d;
  tr->Branch("DataObject","Data",&d);
  d.SetEnergy(10);
  tr->Fill();
  d.SetEnergy(10);
  tr->Fill();
  d.SetEnergy(10);
  tr->Fill();*/

  std::vector<Data *> vecOfDataPt;
  tr->Branch("VectorOfDataObject", "std::vector<Data*>", &vecOfDataPt);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  tr->Fill();
  // Clearing the vector to emulate next event, with six entries
  vecOfDataPt.clear();
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  vecOfDataPt.push_back(new Data);
  tr->Fill();

  tr->Write();
  fp->Close();
}
