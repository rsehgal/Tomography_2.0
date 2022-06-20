/*
**	Filename : Data.h
**	2022-01-22
**	username : rsehgal
*/
#ifndef Data_h
#define Data_h
#pragma once
#include <TROOT.h>
#include <iostream>
//struct 
class Vector3D {
private:
#define PRIV_DATA_MEM
#ifdef PRIV_DATA_MEM
  double x;
  double y;
  double z;
#endif

public:
  Vector3D();          //{}
  void Set(double xval, double yval, double zval);
  void Print() const;
  double GetX()const;
  double GetY()const;
  double GetZ()const;
  void SmearIt();
  void Initialize();
  virtual ~Vector3D(); //{}
  ClassDef(Vector3D, 1)
};

class Data {
  double fEnergy;
  Vector3D fEntryHitPoint;
  Vector3D fMeanHitPoint;
  std::string fDetName;
  unsigned short fDetId;
  unsigned short fLayerId;
public:
  Data();
  Data(std::string name, unsigned short detId, unsigned short layerId);
  Data(const Data &data);
  double GetEnergy() const;
  std::string GetDetName()const;
  void SetEnergy(double energy);
  unsigned short GetLayerId()const;
  unsigned short GetDetectorId()const;
  void SetEntryHitPoint(double px, double py, double pz);
  void SetMeanHitPoint(double px, double py, double pz);
  
  Vector3D GetMeanHitPoint() const;
  Vector3D GetEntryHitPoint() const;
  
  void SmearIt();
  Vector3D GetEntryHitPoint_Smeared();
  void Initialize();
  void Print();
  virtual ~Data();
  ClassDef(Data, 1)
};

#endif
