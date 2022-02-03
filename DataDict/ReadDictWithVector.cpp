/*
**	Filename : ReadDictWithVector.cpp
**	2022-01-24
**	username : rsehgal
*/
#include "Data.h"
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

  TFile *fp = new TFile(argv[1], "r");
  TTree *tr = (TTree *)fp->Get(argv[2]);
  std::vector<Data *> *VectorOfDataObject = NULL;
  Vector3D *poca = NULL;
  tr->SetBranchAddress("VectorOfDataObject", &VectorOfDataObject);
  tr->SetBranchAddress("POCA", &poca);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {

    tr->GetEntry(j);
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {

      std::cout << "--------------------------------------" << std::endl;
      std::cout << "POCA : ";
      poca->Print();
      (*VectorOfDataObject)[i]->Print();
    }
  }

  return 0;
}
