/*
**	Filename : Hit.h
**	2022-01-14
**	username : rsehgal
*/
#ifndef Hit_h
#define Hit_h

#include <G4VHit.hh>
#include <G4ThreeVector.hh>
#include "G4THitsCollection.hh"
class MyHit:public G4VHit{
public:
MyHit();
virtual ~MyHit();
void Print();

public:
G4ThreeVector GetPosition() const ;
void SetPosition(G4ThreeVector pos);


G4String GetName() const ;
void SetName(G4String name);

void SetEnergyDep(double edep);
double GetEnergyDep()const;

inline void * operator new(size_t);
inline void operator delete(void *aHit);

private:
G4ThreeVector hitPos;
G4String touchableName;
double energyDep;
};


typedef G4THitsCollection<MyHit> SDHitCollection;
extern G4ThreadLocal G4Allocator<MyHit>* HitAllocator;

inline void* MyHit::operator new(size_t)
{
          if(!HitAllocator)
              HitAllocator = new G4Allocator<MyHit>;
          return (void *) HitAllocator->MallocSingle();
}

inline void MyHit::operator delete(void *aHit)
{
        HitAllocator->FreeSingle((MyHit*) aHit);
}

#endif
