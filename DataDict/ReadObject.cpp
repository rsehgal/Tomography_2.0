/*
**	Filename : ReadObject.cpp
**	2022-01-23
**	username : rsehgal
*/
#include<iostream>
#include "Data.h"
#include <TFile.h>
#include <TTree.h>

int main(int argc, char *argv[]){
Data *d=0;
TFile *fp = new TFile("test.root","r");
TTree *tr = (TTree*)fp->Get("testTree");
tr->SetBranchAddress("DataObject",&d);
tr->GetEntry(0);
d->Print();

fp->Close();
}
