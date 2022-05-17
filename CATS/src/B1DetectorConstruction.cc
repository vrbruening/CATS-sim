/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "B1TrackerSD.hh"
#include "B1TrackerHit.hh" //I think you need more include statements in other files ?

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

B1DetectorConstruction::~B1DetectorConstruction()
{ }

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;
     
  // World
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       3*m, 3*m, 3*m);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
 
  G4Material* sodiumiodide = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 150*cm);//Use this to change location of CATS
      
G4double z = 31.75*cm;//31.75
 //CATS Core
  G4Tubs* Core =
    new G4Tubs("Core", 1*cm, 13.335*cm, z, 0.*deg, 360.*deg); 
 
  G4LogicalVolume* logicCore =
    new G4LogicalVolume(Core,
		    	sodiumiodide,
			"Core");
  
  new G4PVPlacement(0,
		    pos1,
		    logicCore,
		    "Core",
		    logicWorld,
		    false,
		    1,
		    checkOverlaps);
  
  //Segmented Annulus
  G4Tubs* AnnulusPiece1 =
    new G4Tubs("AnnulusPiece1", 13.335*cm, 24.13*cm, z, 0.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece1 =
    new G4LogicalVolume(AnnulusPiece1, sodiumiodide, "AnnulusPiece1");
   new G4PVPlacement(0, pos1, logicAnnulusPiece1, "AnnulusPiece1", logicWorld, false, 2, checkOverlaps);
 
   G4Tubs* AnnulusPiece2 =
     new G4Tubs("AnnulusPiece2", 13.335*cm, 24.13*cm, z, 60.*deg, 60*deg);
   G4LogicalVolume *logicAnnulusPiece2 =
    new G4LogicalVolume(AnnulusPiece2, sodiumiodide, "AnnulusPiece2");
   new G4PVPlacement(0, pos1, logicAnnulusPiece2, "AnnulusPiece2", logicWorld, false, 3, checkOverlaps);
     
   G4Tubs* AnnulusPiece3 =
    new G4Tubs("AnnulusPiece3", 13.335*cm, 24.13*cm, z, 120.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece3 =
    new G4LogicalVolume(AnnulusPiece3, sodiumiodide, "AnnulusPiece3");
   new G4PVPlacement(0, pos1, logicAnnulusPiece3, "AnnulusPiece3", logicWorld, false, 4, checkOverlaps);

  G4Tubs* AnnulusPiece4 =
    new G4Tubs("AnnulusPiece4", 13.335*cm, 24.13*cm, z, 180.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece4 =
    new G4LogicalVolume(AnnulusPiece4, sodiumiodide, "AnnulusPiece4");
   new G4PVPlacement(0, pos1, logicAnnulusPiece4, "AnnulusPiece4", logicWorld, false, 5, checkOverlaps);
     
   G4Tubs* AnnulusPiece5 =
    new G4Tubs("AnnulusPiece5", 13.335*cm, 24.13*cm, z, 240.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece5 =
    new G4LogicalVolume(AnnulusPiece5, sodiumiodide, "AnnulusPiece5");
   new G4PVPlacement(0, pos1, logicAnnulusPiece5, "AnnulusPiece5", logicWorld, false, 6, checkOverlaps);

   G4Tubs* AnnulusPiece6 =
    new G4Tubs("AnnulusPiece6", 13.335*cm, 24.13*cm, z, 300.*deg, 60*deg);
  G4LogicalVolume *logicAnnulusPiece6 =
    new G4LogicalVolume(AnnulusPiece6, sodiumiodide, "AnnulusPiece6");
   new G4PVPlacement(0, pos1, logicAnnulusPiece6, "AnnulusPiece6", logicWorld, false, 0, checkOverlaps);         
  
   //Lithium Carbonate layer for insulation
   
  G4Material* lithiumcarbonate = nist->FindOrBuildMaterial("G4_LITHIUM_CARBONATE");
   G4Tubs* Ring =
    new G4Tubs("Ring", 24.13*cm, 25.13*cm, z, 0*deg, 360*deg);
  G4LogicalVolume *logicRing =
    new G4LogicalVolume(Ring, lithiumcarbonate, "Ring");
   new G4PVPlacement(0, pos1, logicRing, "Ring", logicWorld, false, 0, checkOverlaps);

 //scintillators to veto cosmic rays  
G4Material* plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 
G4Tubs* Scint1 =
    new G4Tubs("Scint1", 25.13*cm, 35.13*cm, z, 0*deg, 72*deg);
  G4LogicalVolume *logicScint1 =
    new G4LogicalVolume(Scint1, plastic, "Scint1");
   new G4PVPlacement(0, pos1, logicScint1, "Scint1", logicWorld, false, 0, checkOverlaps);

G4Tubs* Scint2 =
    new G4Tubs("Scint2", 25.13*cm, 35.13*cm, z, 72*deg, 72*deg);
  G4LogicalVolume *logicScint2 =
    new G4LogicalVolume(Scint2, plastic, "Scint2");
   new G4PVPlacement(0, pos1, logicScint2, "Scint2", logicWorld, false, 0, checkOverlaps);

G4Tubs* Scint3 =
    new G4Tubs("Scint3", 25.13*cm, 35.13*cm, z, 144*deg, 72*deg);
  G4LogicalVolume *logicScint3 =
    new G4LogicalVolume(Scint3, plastic, "Scint3");
   new G4PVPlacement(0, pos1, logicScint3, "Scint3", logicWorld, false, 0, checkOverlaps);

G4Tubs* Scint4 =
    new G4Tubs("Scint4", 25.13*cm, 35.13*cm, z, 216*deg, 72*deg);
  G4LogicalVolume *logicScint4 =
    new G4LogicalVolume(Scint4, plastic, "Scint4");
   new G4PVPlacement(0, pos1, logicScint4, "Scint4", logicWorld, false, 0, checkOverlaps);

G4Tubs* Scint5 =
    new G4Tubs("Scint5", 25.13*cm, 35.13*cm, z, 288*deg, 72*deg);
  G4LogicalVolume *logicScint5 =
    new G4LogicalVolume(Scint5, plastic, "Scint5");
   new G4PVPlacement(0, pos1, logicScint5, "Scint5", logicWorld, false, 0, checkOverlaps);

//This one goes on the back
    G4ThreeVector pos2 = G4ThreeVector(0, 0, 186.45*cm);//186.45
G4Tubs* Scint6 =
    new G4Tubs("Scint6", 0*cm, 35.13*cm, 4.7*cm, 0*deg, 360*deg);
  G4LogicalVolume *logicScint6 =
    new G4LogicalVolume(Scint6, plastic, "Scint6");
   new G4PVPlacement(0, pos2, logicScint6, "Scint6", logicWorld, false, 0, checkOverlaps);

  //always return to physical world
  return physWorld;
}
//trying to make detector sensitive, I think it needs to be done outside of the main function  
   void B1DetectorConstruction::ConstructSD()
{
  B1SD* CATSSD = new B1SD("CATSSD", "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(CATSSD);

  SetSensitiveDetector("Core", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece1", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece2", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece3", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece4", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece5", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece6", CATSSD, true);
}
/*void B2aDetectorConstruction::ConstructSD()

   {
  B1SD* CATSSD = new B1SD("CATSSD", "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(CATSSD);

  SetSensitiveDetector("Core", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece1", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece2", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece3", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece4", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece5", CATSSD, true);
  SetSensitiveDetector("AnnulusPiece6", CATSSD, true);
}
*/

   /*
//trying to make detector sensitive
   void B2aDetectorConstruction::ConstructSD()
{
  // Sensitive detectors
  G4String trackerChamberSDname = "B2/TrackerChamberSD";
  B2TrackerSD* aTrackerSD = new B2TrackerSD(trackerChamberSDname,
                                            "TrackerHitsCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name
  // of "Chamber_LV".
  SetSensitiveDetector("Chamber_LV", aTrackerSD, true);
}
*/


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
