/*
**	Filename : Hit.cpp
**	2022-01-14
**	username : rsehgal
*/
#include "MyHit.h"
G4ThreadLocal G4Allocator<MyHit>* HitAllocator=0;
#include <G4ThreeVector.hh>

MyHit::MyHit(){}

MyHit::~MyHit(){}

G4ThreeVector MyHit::GetPosition()const{
return hitPos;
}

void MyHit::SetPosition(G4ThreeVector pos){
hitPos = pos;
}

G4String MyHit::GetName()const{
return touchableName;
}

void MyHit::SetEnergyDep(double edep){
//std::cout << "From MYHIT  : " << edep << std::endl; 
energyDep = edep;
}

double MyHit::GetEnergyDep()const{
return energyDep;
}
void MyHit::SetName(G4String name){
touchableName = name;
}

void MyHit::Print(){

std::cout << "--------------------------------------" << std::endl;
std::cout << "Touchable Name : " << touchableName << " : Pos : " << hitPos << " : EnergyDeposited : " << energyDep << std::endl;
}
