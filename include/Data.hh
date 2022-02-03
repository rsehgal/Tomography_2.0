/*
**	Filename : Data.h
**	2022-01-22
**	username : rsehgal
*/
#ifndef Data_h
#define Data_h
#pragma once
#include <TROOT.h>
/*struct Vector3D {
  double x;
  double y;
  double z;
};*/

class Data
{
public:
  double fEnergy;
 // Vector3D fEntryHitPoint;
 // Vector3D fMeanHitPoint;

  Data();
  double GetEnergy() const;
  virtual ~Data();
  ClassDef(Data,1)
 
};

#endif
