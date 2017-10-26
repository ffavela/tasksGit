#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>

// Task 2b.1 Include the proper header file for GPS

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Task 2b.1: Comment out the particle gun creation and instatiate a GPS instead
    fGun = new G4ParticleGun();

    // Task 2a.1: Set the basic properties for the particles to be produced
    // Task 2b.1: Set the same properties for the GPS (removing previous lines)
    // Task 2b.2: You can remove or keep the previous lines in the later stages
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    // Task 2b.2: Delete the GPS instead of the gun
    delete fGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Task 2a.2: Include the position randomization
    // Task 2b.1: Comment out all previous commands in this method (there is no fGun!)
    // Task 2b.1: The method for vertex creation remains the same,.just change the object to your GPS
    fGun->GeneratePrimaryVertex(anEvent);
}