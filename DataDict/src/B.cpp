/*
 * B.cpp
 *
 *  Created on: 11-Nov-2020
 *      Author: rsehgal
 */

#include "B.h"
#include "A.h"

ClassImp(lite_interface::B)

namespace lite_interface {

B::B() {
	// TODO Auto-generated constructor stub

}

B::~B() {
	// TODO Auto-generated destructor stub
}

void B::push_back(A *aObj){
	fVecOfA.push_back(aObj);
}

void B::clear(){
	fVecOfA.clear();
}

void B::Print(){
	for(unsigned int i = 0 ; i < fVecOfA.size() ; i++){
		fVecOfA[i]->Print();
	}
}

std::vector<A*> B::GetVectorOfA()const{
	return fVecOfA;
}

} /* namespace lite_interface */
