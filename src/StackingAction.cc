#include "StackingAction.hh"
#include "RunAction.hh"

#include <G4SystemOfUnits.hh>

StackingAction::StackingAction(RunAction* aRunAction) :
  G4UserStackingAction(),fRunAction(aRunAction)
{;}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack (const G4Track*
 aTrack)
{
    // Task 4a.1: If the track has energy < 1 MeV, return fKill
    
  // Register only secondaries, i.e. tracks having ParentID > 0
  if (aTrack->GetParentID())
  {
    fRunAction->AddSecondary(aTrack->GetParticleDefinition(),
			     aTrack->GetKineticEnergy());
  }
  // Do not affect track classification. Just return what would have
  // been returned by the base class
  return G4UserStackingAction::ClassifyNewTrack(aTrack);
}
