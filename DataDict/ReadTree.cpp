/*
 * ReadTracks.cpp
 *
 *  Created on: 10-Nov-2020
 *      Author: rsehgal
 */

#include "A.h"
#include "B.h"
//#include "ScintillatorBar.h"
//#include "SingleMuonTrack.h"
#include <iostream>
#include <TTree.h>
#include <TFile.h>

int main(int argc,char *argv[]){
	lite_interface::B *smt = 0;
	std::string inputFileName = "test.root";
	TFile *f = new TFile(inputFileName.c_str(),"READ");
	TTree *testTree = (TTree*)f->Get("testTree");
	//TTree *testTree = (TTree*)f->Get("MuonTree");

	testTree->SetBranchAddress("TestBranch",&smt);
	//testTree->SetBranchAddress("TestMuonBranch",&smt);


	Long64_t nentries = testTree->GetEntries();

	Long64_t nbytes = 0;
	if(nentries > 5)
		nentries = 5;
	for (Long64_t i=0; i<nentries;i++) {
		nbytes += testTree->GetEntry(i);
		std::cout << "============ Event Num : " << i << " ============" << std::endl;
		smt->Print();

	}


	/*//-----------
	lite_interface::SingleMuonTrack *tmt = 0;
	TTree *testMuTree = (TTree*)f->Get("MuonTree");
	testMuTree->SetBranchAddress("TestMuonBranch",&tmt);
	nentries = testMuTree->GetEntries();

	nbytes = 0;
	if (nentries > 5)
		nentries = 5;
	for (Long64_t i = 0; i < nentries; i++) {
		nbytes += testMuTree->GetEntry(i);
		std::cout << "============ Event Num : " << i << " ============"
				<< std::endl;
		tmt->Print();

	}
*/

	f->Close();

	return 0;
}



