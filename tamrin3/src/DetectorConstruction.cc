#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"


DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

DetectorConstruction::~DetectorConstruction()
{ }

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance(); //for use geant lib
G4Material* mat1vacuum = nist->FindOrBuildMaterial("G4_Galactic"); //Definition of the first mat vacum
G4Material* mat2water = nist->FindOrBuildMaterial("G4_WATER"); //Definition of the secund mat water

//The definition of geometry starts with the definition of the mother volume
G4Box* SBox = new G4Box("World", 1.*m, 1.*m, 1.*m);
G4LogicalVolume* LBox = new G4LogicalVolume(SBox, mat1vacuum, "World");
G4VPhysicalVolume* PBox = new G4PVPlacement(0, G4ThreeVector(), LBox, "World",0,false, 0);

//definition tube
G4Tubs* STube = new G4Tubs("Tube", 0 * cm, 1 * cm, 15 * cm, 0 * deg, 360 * deg);
G4LogicalVolume* LTube = new G4LogicalVolume(STube, mat2water, "Tube");
new G4PVPlacement(0, G4ThreeVector(), LTube, "Tube", LBox, false, 9); //center Tube

//rep tube whit for
 for (G4int i = 0; i < 8; i++)
 {
	 G4double x, y;
	 x = cos(i * 45 *deg) * 10;
	 y = sin(i * 45 * deg) * 10;

	 new G4PVPlacement(0, G4ThreeVector(x * cm, y * cm, 0)
			 , LTube, "Tuberep", LBox, false, i);//reptube

		 //Definition the color of the cone
		/* G4VisAttributes* vis = new G4VisAttributes();
		 vis->SetForceSolid(true);
		 vis->SetColor(250-(i*20), 50 + (i * 20), 0, 0.5);
		 LTube->SetVisAttributes(vis);
		 */
 }

return PBox;
}

