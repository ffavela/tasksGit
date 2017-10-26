#include "SteppingAction.hh"
#include "RunAction.hh"

#include <G4Step.hh>
#include <G4Electron.hh>

SteppingAction::SteppingAction(RunAction* runAction)
    : fRunAction(runAction)
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  // Task 4a.2: Get the volume where the step starts (the length is inside).
  //G4VPhysicalVolume* volume= ...

  //   Take care, because this volume might not be available: be sure that the pointer  
  //   "volume" is non-NULL, otherwise any volume->Get... would cause a crash.
        
  // Task 4a.2: If the volume exists and has a proper name (absorber0), use the appropriate
  //   run action method to accumulate the track length. Apply this
  //   only for electrons.
}
