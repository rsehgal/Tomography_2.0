/*
**	Filename : Data.cpp
**	2022-01-22
**	username : rsehgal
*/

#include "Data.h"
#include <TRandom.h>
#include <TRandom3.h>
ClassImp(Data);
ClassImp(Vector3D);

Vector3D::Vector3D() {}
Vector3D::~Vector3D() {}

void Vector3D::Set(double xval, double yval, double zval) {
  x = xval;
  y = yval;
  z = zval;
}

void Vector3D::SmearIt() {
  x = gRandom->Gaus(x, 27.5);
  y = gRandom->Gaus(y, 27.5);
  //z = gRandom->Gaus(z, 2.);
}

void Vector3D::Initialize() {
  x = -1000000.;
  y = -1000000.;
  z = -1000000.;
}

void Vector3D::Print() const { std::cout << "(" << x << "," << y << "," << z << ")" << std::endl; }

double Vector3D::GetX() const { return x; }
double Vector3D::GetY() const { return y; }
double Vector3D::GetZ() const { return z; }

std::string Data::GetDetName() const { return fDetName; }

Data::Data() {}

Data::~Data() {}

Data::Data(const Data &data) {
  fEnergy = data.fEnergy;
  // fEntryHitPoint.Set(data.fEntryHitPoint.GetX(),data.fEntryHitPoint.GetY(),data.fEntryHitPoint.GetZ());
  fEntryHitPoint = data.fEntryHitPoint;
  fMeanHitPoint = data.fMeanHitPoint;
  fDetName = data.fDetName;
  fDetId = data.fDetId;
  fLayerId = data.fLayerId;
}

Data::Data(std::string name, unsigned short detId, unsigned short layerId)
    : fDetName(name), fDetId(detId), fLayerId(layerId) {}

double Data::GetEnergy() const { return fEnergy; }
unsigned short Data::GetLayerId() const { return fLayerId; }
unsigned short Data::GetDetectorId() const { return fDetId; }

void Data::SetEnergy(double energy) { fEnergy = energy; }

void Data::SetEntryHitPoint(double px, double py, double pz) { fEntryHitPoint.Set(px, py, pz); }

void Data::SetMeanHitPoint(double px, double py, double pz) { fMeanHitPoint.Set(px, py, pz); }

Vector3D Data::GetMeanHitPoint() const { return fMeanHitPoint; }

Vector3D Data::GetEntryHitPoint() const { return fEntryHitPoint; }

Vector3D Data::GetEntryHitPoint_Smeared() {
  Vector3D temp;
  temp.Set(fEntryHitPoint.GetX(), fEntryHitPoint.GetY(), fEntryHitPoint.GetZ());
  return temp;
}

void Data::SmearIt() { fEntryHitPoint.SmearIt(); }

void Data::Initialize() {
  fMeanHitPoint.Initialize();
  fEntryHitPoint.Initialize();
  fEnergy = -1000000.;
  /*fLayerId = 10000;
  fDetId = 10000;
  fDetName = "Initialized";*/
}

void Data::Print() {
  std::cout << "Detector Name : " << fDetName << std::endl;
  std::cout << "DetectorId : " << fDetId << " :: LayerId : " << fLayerId << std::endl;
  std::cout << "Energy : " << fEnergy << std::endl;
  fEntryHitPoint.Print();
  fMeanHitPoint.Print();
}
