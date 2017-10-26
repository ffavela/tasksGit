#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"

// Task 4d.2: Uncomment the following line
// #include "EnergyTimeHit.hh"

using namespace std;

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    // Task 4c.2: Get the hit collections
    G4HCofThisEvent* hcofEvent = nullptr;

    // If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;

    // The variable fAbsorberId is initialized to -1 (see EventAction.hh) so this block 
    // of code is executed only at the end of the first event. After the first execution 
    // fAbsorberId gets a non-negative value and this block is skipped for all subsequent 
    // events.
    if (fAbsorberId < 0)
    {
      // Task 4c.2: Retrieve fAbsorberId from sdm: the name of the hit collection to retrieve is
      //  "absorber/energy"
      // Task 4d.2: ...and comment the block out (if you don't want to see a long error list)
      // fAbsorberId = sdm->....
        G4cout << "EventAction: absorber energy scorer ID: " << fAbsorberId << G4endl;
    }
    // Task 4c.2: Similarly, retrieve fScintillatorId. How is the hit collection named?
    // As before, fScintillatorId is defined in EventAction.hh and initialized to -1

    // Task 4d.2: ...Retrieve fAbsorberETId. What's the name to be used?
    // Task 4d.2: ...Retrieve fScintillatorETId

    G4int histogramId = 1;     // Note: We know this but in principle, we should ask

    if (fAbsorberId >= 0)
    {
      /// Task 4c.2: Get and cast hit collection with energy in absorber
      G4THitsMap<G4double>* hitMapA = nullptr;
      if (hitMapA)
      {
          for (auto pair : *(hitMapA->GetMap()))
          {
              G4double energy = *(pair.second);
	      //The position of the center of the i-th absorber is given by
	      //  50 * cm + thickness / 2 + i*2 * thickness, 
              //with thickness=0.5*cm. See lines 87 and 93 of DetectorConstruction.cc
	      //In short:
              G4double x = 50.25 + (pair.first * 1.0);   // already in cm
              // Task 4c.3. Store the position to the histogram
          }
      }
    }

    if (fScintillatorId >= 0)
    {
      // Task 4c.2: Get and cast hit collection with energy in scintillator
      G4THitsMap<G4double>* hitMapS = nullptr;
      if (hitMapS)
      {
          for (auto pair : *(hitMapS->GetMap()))
          {
              G4double energy = *(pair.second);
	      //The position of the center of the i-th scintillator is given by
	      //  50 * cm + thickness / 2 + (i*2 +1) * thickness, 
              //with thickness=0.5*cm. See lines 87 and 94 of DetectorConstruction.cc
	      //In short:
              G4double x = 50.75 + (pair.first * 1.0);   // already in cm
              // Task 4c.3. Store the position to the histogram	      
          }
      }
    }

    // Hit collections IDs to be looped over ("Don't Repeat Yourself" principle)
    vector<G4int> hitCollectionIds = {
        fScintillatorETId, fAbsorberETId
    };
    for (G4int collectionId : hitCollectionIds)
    {
        if (collectionId == -1) continue;
        // Task 4d.2: Get and cast hit collection with EnergyTimeHits
        // EnergyTimeHitsCollection* hitCollection = ...;

        // Task 4d.3: Uncomment the following block
        /* if (hitCollection)
        {
            for (auto hit: *hitCollection->GetVector())
            {
                // Task 4d.3: Fill ntuple columns (one prepared for you already)
		// Do not forget units of measurements, if you want your numbers 
		// to be stored consistenty in the ntuple
                analysis->FillNtupleDColumn(0, hit->GetDeltaEnergy() / MeV);

                // Task 4d.3: Add the ntuple row
            }
        }*/
    }
}
