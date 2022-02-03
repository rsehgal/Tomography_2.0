#include "physicslist.hh"
#include "G4EmStandardPhysics_option4.hh"

//define constructor
MYphysicslist::MYphysicslist()
{
    /*Combination of EM models for simulation with high accuracy includes multiple scattering with “UseSafety-
    Plus” type of step limitation by combined G4WentzelVIModel and G4eCoulombScatteringModel for
    all particle types, for of e+- below 100 MeV G4GoudsmitSaundersonMscModel is used, RangeFactor
    = 0.08, Scin = 3 (error free stepping near geometry boundaries), reduced finalRange parameter of stepping
    function optimized per particle type, enabled fluorescence, enabled nuclear stopping, enable accurate angular
    generator for ionisation models, G4LowEPComptonModel below 20 MeV and G4KleinNishinaModel
    above, G4BetheHeitler5DModel for gamma conversion, G4LivermoreIonisationModel for
    electrons and positrons below 100 keV, G4IonParameterisedLossModel for ion ionisation,
    G4Generator2BS angular generator for bremsstrahlung, G4ePairProduction for electron/positron, and
    20 bins per energy decade of physics tables, (class name G4EmStandardPhysics_option4)
    */
    RegisterPhysics(new G4EmStandardPhysics_option4());
}

//define destructor
MYphysicslist::~MYphysicslist()
{}