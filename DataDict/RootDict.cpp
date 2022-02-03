#include <iostream>
using namespace std;

#include "A.h"
#include "B.h"
//#include "ScintillatorBar.h"
//#include "SingleMuonTrack.h"
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TRint.h>
#include <ctime>
#include <iostream>
using namespace lite_interface;

int main(int argc, char **argv) {
	A *a1 = new A(1,100,5);
	A *a2 = new A(2,100,10);
	A *a3 = new A(3,100,15);
	a1->Print();
	a2->Print();
	a3->Print();



	B *b = new B;
	b->push_back(a1);
	b->push_back(a2);
	b->push_back(a3);
	b->Print();
	std::string outputFileName = "test.root";

	gROOT->Reset();
	TFile *f = new TFile(outputFileName.c_str(), "RECREATE");
	TTree *tree = new TTree("testTree", "testTree");

	tree->Branch("TestBranch", "lite_interface::B", &b);

	tree->Fill();

	/*b->clear();
	A *a4 = new A(11,300);
	A *a5 = new A(22,400);
	A *a6 = new A(33,500);

	b->push_back(a4);
	b->push_back(a5);
	b->push_back(a6);

	tree->Fill();*/

	//---------------------------------

/*
	ScintillatorBar *scint1 = new ScintillatorBar(1, 589, 590, 1024, 512);
	ScintillatorBar *scint2 = new ScintillatorBar(2, 591, 592, 1024, 512);
	ScintillatorBar *scint3 = new ScintillatorBar(3, 593, 594, 1024, 512);
	scint1->Print();

	SingleMuonTrack *smt = new SingleMuonTrack;
	smt->push_back(scint1);
	smt->push_back(scint2);
	smt->push_back(scint3);
	std::cout << "======================" << std::endl;
	smt->Print();

	TTree *mutree = new TTree("MuonTree", "MuonTree");
	mutree->Branch("TestMuonBranch", "lite_interface::SingleMuonTrack", &smt);

	mutree->Fill();
*/


	f->Write();
	f->Close();

	return 0;

}
