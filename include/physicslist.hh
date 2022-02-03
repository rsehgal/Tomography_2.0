#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class MYphysicslist : public G4VModularPhysicsList
{
private:
    /* data */
public:
    MYphysicslist(/* args */);
    ~MYphysicslist();
};

#endif