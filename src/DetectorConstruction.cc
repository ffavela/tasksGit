#include "DetectorConstruction.hh"

#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include <G4Box.hh>
#include <G4Orb.hh>
#include <G4SDManager.hh>

#include <sstream>

using namespace std;

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();
    G4double worldSizeX = 2 * m;
    G4double worldSizeY = 1 * m;
    G4double worldSizeZ = 1 * m;

    // We have created the world volume for you
    // As with all volumes, it requires three steps:

    // 1) Solid
    G4VSolid* worldBox = new G4Box("world", worldSizeX / 2, worldSizeY / 2, worldSizeZ / 2);

    // 2) Logical volume
    G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, nist->FindOrBuildMaterial("G4_AIR"), "world");
    G4VisAttributes* visAttr = new G4VisAttributes();
    visAttr->SetVisibility(false);
    worldLog->SetVisAttributes(visAttr);

    // 3) Physical volume
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(nullptr, {}, worldLog, "world", nullptr, false, 0);

    // The following creates a couple of volumes inside the world volume, see what happens :-)
    // Task 1b.1: Remove the "Catania" label. It is nice but not very practical.
    // ConstructDemo(worldLog);

    // Task 1a.1: Create three instances of G4Element to support BC400 material
    // (name, symbol, effectiveZ, effectiveA as mass/mole)
    G4Element* elH = new G4Element("Hydrogen", "H", 1., 1.0079 * g/mole);
    G4Element* elC = new G4Element("Carbon", "C", 6., 12.011 * g/mole);

    // Task 1a.1: Once you have the elements, create the material
    // (name, density, number of components)
    G4Material* bc400 = new G4Material("BC400", 1.032 * g/cm3, 2);
    bc400->AddElement(elH, 8.5*perCent);
    bc400->AddElement(elC, 91.5*perCent);

    // Task 1a.2: Get lead (Pb) from the NIST database
    G4Material* lead = nist->FindOrBuildMaterial("G4_Pb");

    // Task 1b.1: Create a solid for the absorber (box)
    // Task 1b.1: Create a solid for the scintillator (box)
    // We have already provided the layer thickness for you.
    G4double thickness = .5 * cm;
    G4double width = 10 * cm;     // Task 1b.2: Update this
    G4double height = 10 * cm;    // Task 1b.2: Update this

    G4VSolid* scintillatorBox = new G4Box("scintillator", thickness / 2, width / 2, height / 2);
    G4VSolid* absorberBox = new G4Box("absorber", thickness / 2, width / 2, height / 2);

    // Task 1b.2: Create a logical volume for the absorber
    G4LogicalVolume* absorberLog = new G4LogicalVolume(absorberBox, lead, "absorber");

    // Task 1b.2: Create a logical volume for the scintillator
    G4LogicalVolume* scintillatorLog = new G4LogicalVolume(scintillatorBox, bc400, 
							   "scintillator");

    // Task 1b.2: Colorize the absorber using proper vis. attributes
    G4VisAttributes* red = new G4VisAttributes(G4Colour::Red());
    red->SetVisibility(true);
    red->SetForceSolid(true);
    absorberLog->SetVisAttributes(red);

    // Task 1b.2: Colorize the scintillator using proper vis. attributes
    G4VisAttributes* yellow = new G4VisAttributes(G4Colour::Yellow());
    yellow->SetVisibility(true);
    yellow->SetForceSolid(true);
    scintillatorLog->SetVisAttributes(yellow);

    // We have already provided the positions, you finish the rest...
    G4int numberOfLayers = 10;
    G4double minX = 50 * cm + thickness / 2;

    vector<G4ThreeVector> absorberPositions;
    vector<G4ThreeVector> scintillatorPositions;
    for (int i = 0; i < numberOfLayers; i++)
    {
        absorberPositions.push_back({minX + i*2 * thickness, 0, 0});
        scintillatorPositions.push_back({minX + (i * 2 + 1) * thickness, 0, 0});
    }

    for (int i = 0; i < numberOfLayers; i++)
    {
        ostringstream aName; aName << "absorber" << i;
        ostringstream sName; sName << "scintillator" << i;
        // Task 1b.3  Create 10 layers for the absorber (use aName.str() for name)
        new G4PVPlacement(nullptr, absorberPositions[i],
			  absorberLog, aName.str(), worldLog, 0, i);
        // Task 1b.3: Create 10 layers for the scintillator (use sName.str() for name)
        new G4PVPlacement(nullptr, scintillatorPositions[i],
			  scintillatorLog, sName.str(), worldLog, 0, i);
    }

    // Task 1a.0: Show the material table
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    // The Construct() method has to return the final (physical) world volume:
    return worldPhys;
}

void DetectorConstruction::ConstructDemo(G4LogicalVolume* worldLog)
{
    vector<string> labelData = {
        "                                                  ",
        "                                                  ",
        "       ####    #    #   #      #   #  ####  #     ",
        "       #       #     # #       ## ##  #     #     ",
        "       ###     #      #        # # #  ###   #     ",
        "       #       #     # #       #   #  #           ",
        "       #       #    #   #      #   #  ###€  #     ",
        "                                                  ",
        "                                                  "
    };

    G4NistManager* nist = G4NistManager::Instance();

    G4double step = 10.0 * mm;
    G4double thickness = 10.0 * mm;

    G4VSolid* labelBox = new G4Box("label", thickness / 2, step / 2 * labelData.size(), step / 2 * labelData[0].size());
    G4LogicalVolume* labelLog = new G4LogicalVolume(labelBox, nist->FindOrBuildMaterial("G4_Galactic"), "label");
    new G4PVPlacement(nullptr, {15 * cm, 0, 0}, labelLog, "label", worldLog, false, 0);

    G4VSolid* smallBox = new G4Box("small", thickness / 2 , step / 2, step / 2);
    G4LogicalVolume* smallLog = new G4LogicalVolume(smallBox, nist->FindOrBuildMaterial("G4_Fe"), "small");

    // By default, all volumes are hidden. For the to be displayed in visualization,
    // you have to assign visual attributes to them:
    G4VisAttributes* blue = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0, 0.4));
    blue->SetVisibility(true);
    blue->SetForceSolid(true);
    smallLog->SetVisAttributes(blue);

    // And now just place the logical volume in many copies in a nested loop:
    int i = 0;
    for (auto line : labelData)
    {
        int j = 0;
        for (auto chr : line)
        {
            if (chr == ' ')
            {
                G4ThreeVector pos {0, ((labelData.size() - 1) / 2.0 - i) * step,
		    (j - (line.size() - 1) / 2.0) * step};
                new G4PVPlacement(nullptr, pos, smallLog, "small", labelLog, false, 0);
            }
            j++;
        }
        i++;
    }
}

// Task 1c.1: Include the proper header for the magnetic field messenger.
#include <G4GlobalMagFieldMessenger.hh>

// Task 4c.1: Include the proper header for the multi-functional detector

// Task 4c.1: Include the proper header for energy deposit primitive scorer

// Task 1c.1: Uncomment the following method definition and implement it
void DetectorConstruction::ConstructSDandField()
{
    // Task 1c.1: Create the magnetic field messenger
    /*
    G4ThreeVector fieldValue = G4ThreeVector(0.0, 0.2 * tesla, 0.0);
    G4GlobalMagFieldMessenger* fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);  // to set messenger verbosity
    */

    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    sdManager->SetVerboseLevel(2);  // Useful for 4c

    // Task 4c.1: Create 2 instances of G4MultiFunctionalDetector (for absorber and scintillator)
    // G4MultiFunctionalDetector* absorberDetector = ...

    // Task 4c.1: Create 2 primitive scorers for the dose and assign them to respective detectors
    // G4VPrimitiveScorer* absorberScorer = ...

    // Task 4c.1 Assign multi-functional detectors to the logical volumes and register them to 
    //   the SDmanager
    // SetSensitiveDetector("....");
    // sdManager->AddNewDetector(...);

    // Task 4d.2: Comment out the attachment of previous sensitive detectors
    // Task 4d.2: Create and assign the custom sensitive detector. Do not forget to register them 
    //  to the SDmanager
    // EnergyTimeSD* absorberET = ...
}
