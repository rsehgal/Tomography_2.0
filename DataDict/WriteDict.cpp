/*
**	Filename : WriteDict.cpp
**	2022-01-23
**	username : rsehgal
*/
#include<iostream>
#include <TTree.h>
#include "Data.h"
#include <TFile.h>
int main(int argc, char *argv[]){
TFile *fp = new TFile("test.root","RECREATE");
Data d;
TTree *tr = new TTree("testTree","testTree");
tr->Branch("DataObject","Data",&d);
d.SetEnergy(10);
tr->Fill();
d.SetEnergy(10);
tr->Fill();
d.SetEnergy(10);
tr->Fill();
fp->Write();

}
