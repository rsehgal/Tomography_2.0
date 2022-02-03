/*
 * A.h
 *
 *  Created on: 11-Nov-2020
 *      Author: rsehgal
 */

#ifndef INC_A_H_
#define INC_A_H_
#pragma once
#include <TROOT.h>
namespace lite_interface {

class A {

	unsigned int fBarIndex;
	unsigned int fEnergy;
	int fDelT;

public:

	A();
	A(unsigned int barIndex,unsigned int energy);
	A(unsigned int barIndex,unsigned int energy,int delT);
	void Print();
	virtual ~A();
	ClassDef(A,1)
};

} /* namespace lite_interface */

#endif /* INC_A_H_ */
