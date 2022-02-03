/*
 * B.h
 *
 *  Created on: 11-Nov-2020
 *      Author: rsehgal
 */

#ifndef INC_B_H_
#define INC_B_H_

#include <vector>
#pragma once
#include <TROOT.h>
namespace lite_interface {
class A;
class B {
	std::vector<A*> fVecOfA;
public:
	void push_back(A *aObj);
	void clear();
	std::vector<A*> GetVectorOfA()const;
	B();
	void Print();
	virtual ~B();
	ClassDef(B,1)
};

} /* namespace lite_interface */

#endif /* INC_B_H_ */
