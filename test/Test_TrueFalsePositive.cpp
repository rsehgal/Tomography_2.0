/*
**	Filename : Test_TrueFalsePositive.cpp
**	2022-04-22
**	username : rsehgal
*/
#include "Data.h"
#include "EveVisualizer.h"
#include "MuonTrack.h"
#include "MyDetectorConstruction.hh"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include "colors.h"
#include "timer.h"
#include <G4AffineTransform.hh>
#include <G4GDMLParser.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4ThreeVector.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSolid.hh>
#include <Imaging.h>
#include <iostream>
int main(int argc, char *argv[]) {
  /*
   ** Reading geometry using gdml parser
   */
  G4GDMLParser parser;
  parser.Read("geom.gdml");
  G4VPhysicalVolume *world = parser.GetWorldVolume("World");

  /*
   ** Trying to list the daughter volume of world
   */
  unsigned short numOfDaughters = world->GetLogicalVolume()->GetNoDaughters();

  G4ThreeVector ptToTest(-200, 0., 0.);
  for (unsigned int i = 0; i < numOfDaughters; i++) {
    G4VPhysicalVolume *daugPhysical = world->GetLogicalVolume()->GetDaughter(i);
    std::cout << "Physical Daughter Name : " << daugPhysical->GetName() << std::endl;
    std::string daughName = daugPhysical->GetName();
    // if (daughName.substr(0, 9) == "Scatterer") {
    if (daughName.substr(0, 16) != "PhysicalTracking") {

      std::cout << "--------------------------------------" << std::endl;
      std::cout << GREEN << "Physical Scatterer Name : " << daughName << RESET << std::endl;
      std::cout << "Translation : " << daugPhysical->GetTranslation() << std::endl;
      std::cout << "Rotation : " << daugPhysical->GetRotation() << std::endl;

      G4AffineTransform Tm(daugPhysical->GetRotation(), daugPhysical->GetTranslation());
      Tm = Tm.Invert();
      std::cout << RED << "Before : " << ptToTest << RESET << std::endl;
      G4ThreeVector tranformedPt = Tm.TransformPoint(ptToTest);
      std::cout << BLUE << "After : " << tranformedPt << RESET << std::endl;
      G4VSolid *solid = daugPhysical->GetLogicalVolume()->GetSolid();
      std::cout << RED << "Inside : " << solid->Inside(tranformedPt) << RESET << std::endl;
      if (solid->Inside(tranformedPt) == EInside::kInside)
        std::cout << RED << "Point is Inside " << RESET << std::endl;
      if (solid->Inside(tranformedPt) == EInside::kSurface)
        std::cout << RED << "Point is on the Surface " << RESET << std::endl;
      if (solid->Inside(tranformedPt) == EInside::kOutside)
        std::cout << RED << "Point is Outside " << RESET << std::endl;
    }
  }
}
