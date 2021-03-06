#include <stdlib.h>
#include <fstream.h>
#include <rw/rstream.h>
#include <scenario/src/calendar.h>
#include <scenario/src/difPWcmr.h>
#include <scenario/src/difCmrpF.h>
#include <scenario/src/difImpl.h>
// #include <difMapic/src/difMapic.h>
#include <scenario/src/scBdCMRP.h>
#include <scenario/src/scenCMRP.h>
#include <scenario/src/scenDrct.h>
#include <scenario/src/ipCMRP.h>
#include <scenario/src/schFCMRP.h>
#include <scenario/src/outInter.h>
#include <scenario/src/schdDeSt.h>
#include <scenario/src/multPSch.h>
#include <scenario/src/multDSch.h>
#include <scenario/src/timeVecs.h>
#include <scenario/src/sOfPaFS.h>
#include <scenario/src/tvElemPC.h>
#include <scenario/src/zeroTvFS.h>
#include <scenario/src/boolFS.h>
#include <scenario/src/scCMRPP.h>
#include <scenario/src/demdSchP.h>
#include <scenario/src/partSchP.h>




// Initialize calendar and create a scenario
void
createScenario (RWBoolean useFileData, 
		char * * argv, 
		LgFrCalendar calendar,
		LgFrScenarioForCMRPSmartPointer & scenarioPtr)
{
  if (useFileData) {
    RWCString baseFileName = *(argv+1);
    RWCString msg
      = "INFO: Using the set of CMRP input files named\n"
      + baseFileName + ".{raw,dem,bom,...}";
    cout << msg << endl;
    cerr << msg << endl;
    calendar =
      LgFrDataInterfaceImplementationFromCmrpFiles::calendar( baseFileName );
    LgFrDataInterfaceImplementationFromCmrpFiles difImp( baseFileName );
    registerCmrpFilesDifImpFunctions(&difImp);
    LgFrDataInterface dif(&difImp);

    // Create a scenario using the builder
    LgFrScenarioBuilderForCMRPwithPrioritiesFromDif builder;
    LgFrScenarioDirector director(&builder);
    director.construct(dif, calendar);

    scenarioPtr = builder.getScenario();
  }
  else {	// Use Perfect World Data
    calendar = LgFrCalendar(8, RWTime(RWDate("8/01/95")));
    LgFrDataInterfaceImplementation* difImpPtr
	= createPWcmrpDifImp();
    registerPWcmrpDifImpFunctions(difImpPtr);
    LgFrDataInterface dif(difImpPtr);
    delete difImpPtr;
    difImpPtr = NULL;

    // Create a scenario using the builder
    LgFrScenarioBuilderForCMRP builder;
    LgFrScenarioDirector director(&builder);
    director.construct(dif, calendar);

    scenarioPtr = builder.getScenario();
  }
}

//-----------------------------------------------------------------------
//
// CMRP Two-scenario sample program
//
// Command Line Format: cmrpTest 
//
// This program shows that you can have two scenarios at the same time
// and compare their results.  It instantiates two scenarios, increases
// the supply of two components in one, implodes both scenarios, and then
// prints the difference in two scenario's backlogs.
//-----------------------------------------------------------------------
int main(int argc, char * * argv)
{
  RWBoolean interactive;
  RWBoolean useFileData;
  RWBoolean verbosePrinting;
  RWBoolean procurementSumToFile;

  interactive = FALSE;
  useFileData = FALSE;
  verbosePrinting = FALSE;
  procurementSumToFile = FALSE;

  const LgFrSchedulePrintStyle printStyle(useFileData  ?  CSV  :  TEXT);

  LgFrCalendar calendar;
  LgFrScenarioForCMRPSmartPointer scenarioPtr;
  LgFrScenarioForCMRPSmartPointer scenarioPtr2;

  createScenario (useFileData, argv, calendar, scenarioPtr);
  createScenario (useFileData, argv, calendar, scenarioPtr2);

  // create the multiSchedules
  LgFrMultiPartScheduleFloat * plannerMSPptr
      =  new LgFrMultiPartScheduleFloat(scenarioPtr);
  LgFrMultiDemandScheduleFloat * demandMSDptr
      = new LgFrMultiDemandScheduleFloat(scenarioPtr);
  LgFrMultiDemandScheduleFloat * demandMSDptr2
      = new LgFrMultiDemandScheduleFloat(scenarioPtr2);

  LgFrMultiPartScheduleFloat & plannerMSP = *plannerMSPptr;
  LgFrMultiDemandScheduleFloat & demandMSD = *demandMSDptr;
  LgFrMultiDemandScheduleFloat & demandMSD2 = *demandMSDptr2;

  // -----------------------------------------------------------------
  cout << "Running a CMRP script:\n";
  cerr << "Running a CMRP script:\n";
  // -----------------------------------------------------------------

  // set-up the MultiSchedules
  plannerMSP.newSchedule(LGFRPlannerManagedSupplyVol);

  demandMSD.newSchedule(LGFRCMRPDemandVol);
  demandMSD.newSchedule(LGFRCMRPBacklogVol);

  demandMSD2.newSchedule(LGFRCMRPDemandVol);
  demandMSD2.newSchedule(LGFRCMRPBacklogVol);

  // ------------------------------------------------------------------
  cout << "Step 1:  Edit supply of a constrained part in one scenario\n";
  cerr << "Step 1:  Edit supply of a constrained part in one scenario\n";
  // ------------------------------------------------------------------
  {
     // first make sure that the supply attribute is muteable
     RWBoolean result = plannerMSP.isMutable(LGFRPlannerManagedSupplyVol);
     assert (result == TRUE);

      // define the part of interest -- Screen_S

     const LgFrPart * part1Ptr = scenarioPtr->constSetOfParts().findValue("Screen_S");
     if (part1Ptr != NULL) {
        cout << "\nIncreasing supply on part Screen_S, by 100.0\n";
        LgFrPart     part1(*part1Ptr);

        // get the original  timevec
        const LgFrTimeVecFloat  * originalTVptr =
                      plannerMSP.getTimeVecFloat(part1, LGFRPlannerManagedSupplyVol);

        // add 100.0
        LgFrTimeVecFloat newTV1 = *originalTVptr + 100.0;

        // update the supply and check it
        result = plannerMSP.changeTimeVecInSchedule(
                         part1, LGFRPlannerManagedSupplyVol, newTV1);
        assert(result == TRUE);

      }

      // define the part of interest -- MEM_Module

     const LgFrPart * part2Ptr = scenarioPtr->constSetOfParts().findValue("MEM_Module");
     if (part2Ptr != NULL) {
        cout << "\nChanging supply on part MEM_Module, to  9500.0 (all periods)\n";
        LgFrPart     part2(*part2Ptr);

        // now change the second part's supply
        LgFrTimeVecFloat newTV2(calendar.nPeriods(), 9500.0);

        // update the supply and check it
        result = plannerMSP.changeTimeVecInSchedule(
                         part2, LGFRPlannerManagedSupplyVol, newTV2);
        assert(result == TRUE);
      }
  }

  // ------------------------------------------------------------------
  cout << "IMPLODE and View Demands\n";
  cerr << "IMPLODE and View Demands\n";
  // ------------------------------------------------------------------

  // user hits the Implode button
  scenarioPtr->newImplosionSolution();
  scenarioPtr2->newImplosionSolution();

  demandMSD.printByItemAndAttribute(printStyle);
  demandMSD2.printByItemAndAttribute(printStyle);

  // ------------------------------------------------------------------
  cout << "SUBTRACT the two backlog schedules\n";
  cerr << "SUBTRACT the two backlog schedules\n";
  // ------------------------------------------------------------------
  LgFrSortingDemandScheduleFloatSmartPointer backlogPtr
    = scenarioPtr->scheduleFactory()->newDemandSchedule(LGFRCMRPBacklogVol, FALSE);
  LgFrSortingDemandScheduleFloatSmartPointer backlogPtr2
    = scenarioPtr2->scheduleFactory()->newDemandSchedule(LGFRCMRPBacklogVol, FALSE);
  LgFrSortingDemandScheduleFloat diff 
    = *backlogPtr2 - *backlogPtr;
  diff.print();
  
  // ------------------------------------------------------------------
  cout << "Script Completed -- Cleaning Up\n";
  cerr << "Script Completed -- Cleaning Up\n";
  // ------------------------------------------------------------------


  delete plannerMSPptr;
  delete demandMSDptr;
  delete demandMSDptr2;

  cerr << "All tests completed successfully\n";
  cout << "All tests completed successfully\n";
  return 0;
}
