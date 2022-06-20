#include "MyDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "MySensitiveDetector.h"
#include <G4GDMLParser.hh>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::MyDetectorConstruction() : G4VUserDetectorConstruction(), fScoringVolume(0) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorConstruction::~MyDetectorConstruction() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume  *MyDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager *nist = G4NistManager::Instance();

  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXYZ = 2000 * cm;
  G4Material *world_mat  = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box *solidWorld = new G4Box("World",                                                        // its name
                                0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ); // its size

  G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, // its solid
                                                    world_mat,  // its material
                                                    "World");   // its name

  G4VPhysicalVolume  *physWorld = new G4PVPlacement(0,               // no rotation
                                                   G4ThreeVector(), // at (0,0,0)
                                                   logicWorld,      // its logical volume
                                                   "World",         // its name
                                                   0,               // its mother  volume
                                                   false,           // no boolean operation
                                                   0,               // copy number
                                                   checkOverlaps);  // overlaps checking
  /*--------------------------------------------------------------------------*/
  /* Making the logical volume sensitive
  ** Commenting the below four line, disable the senstivity of the logical volume
  */
  /*--------------------------------------------------------------------------*/
  MySensitiveDetector *mySD = new MySensitiveDetector("SensitiveDetector", "HitColSensitiveDetector");
  G4SDManager *sdman        = G4SDManager::GetSDMpointer();
  sdman->AddNewDetector(mySD);

  G4Box *trackingDetector = new G4Box("TrackingDetector",               // its name
                         50. * cm, 50. * cm, 0.5 * cm); // its size

  // G4Material* box_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Material *detector_mat       = nist->FindOrBuildMaterial("G4_Galactic");
  G4LogicalVolume *logicalTrackingDetector = new G4LogicalVolume(trackingDetector,               // its solid
                                                  detector_mat,           // its material
                                                  "LogicalTrackingDetector"); // its name

  logicalTrackingDetector->SetSensitiveDetector(mySD);
  unsigned short numOfLayers = 8;
  unsigned short numOfDetInEachLayer  = 1;
  std::string physicalDetName      = "PhysicalTrackingDetector";
  double spaceBetweenDetLayers = 160*cm;
  double offset = 30.*cm;  
  short counter = -1;
  for(unsigned int i = 0 ; i < numOfLayers ; i++){
	  unsigned short layerId = i;
          if(layerId == numOfLayers/2)
		counter = -1;
	  double zval = offset+(numOfLayers/2 - 1)*spaceBetweenDetLayers;
  	  if(layerId < numOfLayers/2){
		zval *= -1.;
		zval -= 20*cm;
	  }else{
		zval = offset;
		zval += 20*cm;
	  }
	  counter++;
	  zval += (counter*spaceBetweenDetLayers);
	  for(unsigned int j = 0 ; j < numOfDetInEachLayer ; j++){
		unsigned short detId = (numOfDetInEachLayer*layerId)+j;
		std::cout << "ZVal : " << zval << std::endl;
		physicalDetName = ("PhysicalTrackingDetector_"+std::to_string(layerId)+"_"+std::to_string(detId));
		new G4PVPlacement(0,                              // no rotation
                                                  G4ThreeVector(0., 0., zval), // at (0,0,0)
                                                  logicalTrackingDetector,                       // its logical volume
                                                  physicalDetName,                     // its name
                                                  logicWorld,                     // its mother  volume
                                                  false,                          // no boolean operation
                                                  detId,                              // copy number
                                                  checkOverlaps);
		mySD->InitializeAnalyzer(physicalDetName, layerId, detId);     
 	  }
  } 


#if(1)
  G4Box *box = new G4Box("leadBox",               // its name
                         10. * cm, 10. * cm, 5 * cm); // its size

  // G4Material* box_mat = nist->FindOrBuildMaterial("G4_Pb");
  //G4Material *box_mat       = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  G4Material *box_mat       = nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *logicBox = new G4LogicalVolume(box,               // its solid
                                                  box_mat,           // its material
                                                  "LeadLogicalBox"); // its name
 
  logicBox->SetSensitiveDetector(mySD);

  G4Box *smallbox = new G4Box("smallleadBox",               // its name
                         5. * cm, 5. * cm, 5 * cm); // its size

  G4Material *smallbox_mat       = nist->FindOrBuildMaterial("G4_Pb");
  G4LogicalVolume *smalllogicBox = new G4LogicalVolume(smallbox,               // its solid
                                                  smallbox_mat,           // its material
                                                  "LeadLogicalSmallBox"); // its name
 
  smalllogicBox->SetSensitiveDetector(mySD);
  //Placing small box
  G4VPhysicalVolume *physSmallBox = new G4PVPlacement(0,                              // no rotation
                                                  G4ThreeVector(0.*cm, 15*cm, 0.), // at (0,0,0)
                                                  smalllogicBox,                       // its logical volume
                                                  "SmallLeadScatterer",                     // its name
                                                  logicWorld,                     // its mother  volume
                                                  false,                          // no boolean operation
                                                  0,                              // copy number
                                                  checkOverlaps);                 // overlaps checking

  /*--------------------------------------------------------------------------*/
  std::string phyVolName      = "";
  phyVolName= "PhysicalLeadBox_1";
  G4VPhysicalVolume *physBox2 = new G4PVPlacement(0,                              // no rotation
                                                  G4ThreeVector(15.*cm, 0., 0.), // at (0,0,0)
                                                  logicBox,                       // its logical volume
                                                  phyVolName,                     // its name
                                                  logicWorld,                     // its mother  volume
                                                  false,                          // no boolean operation
                                                  0,                              // copy number
                                                  checkOverlaps);                 // overlaps checking
  //mySD->InitializeAnalyzer(phyVolName, 0, 0);

  phyVolName = "Scatterer_PhysicalLeadBox_2";
  // G4VPhysicalVolume *
  G4PVPlacement *physBox = new G4PVPlacement(0,               // no rotation
                                             G4ThreeVector(-15.*cm,0.,0.), // at (0,0,0)
                                             logicBox,        // its logical volume
                                             phyVolName,      // its name
                                             logicWorld,      // its mother  volume
                                             false,           // no boolean operation
                                             1,               // copy number
                                             checkOverlaps);  // overlaps checking
  //mySD->InitializeAnalyzer(phyVolName, 10, 10);
#endif

  // mySD->InitializeAnalyzer(physBox);

  /*phyVolName                  = "PhysicalLeadBox_3";
  G4VPhysicalVolume *physBox3 = new G4PVPlacement(0,                               // no rotation
                                                  G4ThreeVector(0., 0., -15 * cm), // at (0,0,0)
                                                  logicBox,                        // its logical volume
                                                  phyVolName,                      // its name
                                                  logicWorld,                      // its mother  volume
                                                  false,                           // no boolean operation
                                                  2,                               // copy number
                                                  checkOverlaps);                  // overlaps checking
  mySD->InitializeAnalyzer(phyVolName, 2, 2);*/
  //
  // always return the physical World
  //
//  return physWorld;
G4GDMLParser parser;
  parser.Write("geom.gdml",physWorld);
        return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
