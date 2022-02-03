/*
 * A.cpp
 *
 *  Created on: 11-Nov-2020
 *      Author: rsehgal
 */

#include "A.h"
#include <iostream>

ClassImp(lite_interface::A)

namespace lite_interface {

A::A() {
	// TODO Auto-generated constructor stub


}

A::~A() {
	// TODO Auto-generated destructor stub
}

A::A(unsigned int barIndex,unsigned int energy)
:fBarIndex(barIndex),fEnergy(energy){
}

A::A(unsigned int barIndex,unsigned int energy, int delT)
:fBarIndex(barIndex),fEnergy(energy),fDelT(delT){
}

void A::Print(){
	std::cout << "BarIndex : " << fBarIndex << " : Energy : " << fEnergy << " : DelT : " << fDelT <<  std::endl;
}

} /* namespace lite_interface */
