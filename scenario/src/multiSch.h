#ifndef LGFR_MULTISCH_H
#define LGFR_MULTISCH_H

//NOTES from 8/10 meeting
/*

  1) multischedule must subscribe to ALL schedules

*/

// This is a base class for representing multiple schedules of items.
// Items are parts or demands.

// It provides an abstraction in which there are multiple attributes
// (LgFrTimeVecFloat's) for each item.  A major iterator iterates over
// the items; a minor iterator iterates over the LgFrTimeVecFloat's.

// Assumptions:
// (0) Schedules are refered to by their LgFrScheduleDescriptor's.  The
//     schedules themselves are owned and managed by *this.
// (1) A given item may or may not be in a given schedule.  If the client
//     asks for an LgFrTimeVecFloat that is not in a schedule, return an
//     indication that it is not there.
// (2) Since there are multiple schedules which may contain different
//     set of items, one of the schedules is labelled as Selection schedule.
//     Only the items in this schedule are returned by the multischedule
// (3) If a filter strategy is given to the multi-schedule, it is applied to
//     Selection schedule.  The multischedule only returns the items that are not
//     filtered out of the Selection schedule.
// (4) The multischedule can be sorted by specifying a pairCompare and a
//     schedule that is in the multischedule.  The schedule that is sorted
//     is refered to as the Order schedule.  The items in the multischedule
//     will be returned in the order they appear in the Order schedule.
//     Items in the Selection schedule that are not in the Order schedule
//     will be returned at the end.
// (5) Schedules can be given priorities.  The LgFrTimeVecFloat's for a given
//     item will be returned in the order of lowest to highest numerical
//     priority.
// (6) Two iterators are used for this class, major iterator is called
//     MSItemIterator, and minor iterator called MSAttributeIterator.
// (7) MSItemIterator will iterate through items in the Selection schedule.
// (8) MSAttributeIterator will iterate through the schedules in the order of
//     lowest to highest numerical priority.

#include <scenario/src/schdDeSt.h>
#include <scenario/src/descSchd.h>
#include <scenario/src/scenP.h>

#ifndef LgFrDescriptorSchedulePairFloatGSListDef
#define LgFrDescriptorSchedulePairFloatGSListDef
#include <rw/gslist.h>
declare(RWGSlist, LgFrDescriptorSchedulePairFloat)
typedef RWGSlist(LgFrDescriptorSchedulePairFloat)
                 LgFrDescriptorSchedulePairFloatGSList;
#endif
enum LgFrSchedulePosition {BEFORE, AFTER};
enum LgFrScheduleType {DEMAND, PART, OTHER};

const LgFrSortDescriptor LgFrNullRWCString = "";
const RWCString LgFrFilterNothing = ".*";

// Forward declarations
class ofstream;
class LgFrPairCompareFloat;
class LgFrAttributeSensitivePairCompareFloat;
class LgFrItem;
class LgFrScenario;
class LgFrFilterStrategy;

class LgFrMultiScheduleFloat : public LgFrSubscription {

friend class LgFrMultiScheduleItemIterator;
friend class LgFrMultiScheduleAttributeIterator;

public:

  // This is a pure virtual function and
  // derived classes of MS should have the right implementation.
  // Inside the derived class, add a schedule if it is not already in the multi-schedule
  // and return TRUE, Otherwise, just return TRUE.
  virtual
    RWBoolean
      newSchedule(const LgFrScheduleDescriptor&) = 0;

  // Remove a schedule from the multi-schedule.  If it was in the
  // multi-schedule return TRUE, otherwise return FALSE.
  virtual
    RWBoolean
      deleteSchedule(const LgFrScheduleDescriptor&);

  // Return the schedule type: DEMAND or PART
  virtual
     LgFrScheduleType
        schedType()
           const;

  // Return number of schedules.
  virtual
     size_t
        entries()
           const;

  //  Remove all items in the list and delete them
  virtual
    void
      clear();

  //  Returns TRUE if the list contains this schedule
  virtual
    RWBoolean
      contains(const LgFrScheduleDescriptor&)
       const;

  //  Returns TRUE if the list is empty
  virtual
    RWBoolean
      isEmpty() const;

  // Return a list of schedule descriptor abbreviations in MS
  LgFrVectorRWCString
    schedAbbrevVec () const;

  // Return a list of schedule descriptors  in MS
  LgFrVectorScheduleDescriptor
    schedDescVec () const;

  // Return the relative priority of a schedule.  The schedule with priority
  // 0 is processed first by the minor iterator, 1 is next, and so on.
  // When a schedule is inserted, it is given the highest numerical priority-value.
  virtual
    int
      priority (const LgFrScheduleDescriptor&) const;

  // Note: there is no method for setting a schedules priority absolutely because
  // (a) priorities are all relative, (b) it would have to check for invalid
  // priorities.

  // Shift priorities (e.g. moving one schedule before another)
  virtual
    RWBoolean
      priorityShift(const LgFrScheduleDescriptor& from,
		    const LgFrScheduleDescriptor& to,
		    const LgFrSchedulePosition = BEFORE);

  // Swap priorities.  Exchange the priority of a and b
  virtual
    RWBoolean
      prioritySwap(const LgFrScheduleDescriptor& a,
		   const LgFrScheduleDescriptor& b);

  // Return number of items
  size_t
    numberOfItems() const;

  // Get the Selection schedule.
  virtual
    const LgFrScheduleDescriptor&
      itemSelectionSchedule() const;

  // Set a Selection schedule.
  // If a LgFrFilterStrategy is specified, it is associated with the (new)
  // selection schedule.
  // This method removes the filter from the current selection schedule.
  virtual
    RWBoolean
      itemSelectionSchedule(const LgFrScheduleDescriptor&,
			    LgFrFilterStrategy* = NULL);

  // Set a Selection schedule using a FilterDescriptor and perform filtering.
  // This method removes the filter from the current selection schedule.
  // Implementation note: this call can be used to change the filter if sd is
  // the descriptor of the old selection-schedule
  // Return TRUE  :if sd is found and changes are made.
  //        FALSE :if sd is not found.
  virtual
    RWBoolean
      filterItemSelectionSchedule(
         const LgFrScheduleDescriptor& sd,
         const LgFrFilterDescriptor &,
         const RWCString & = LgFrFilterNothing,
         const RWCString & = LgFrFilterNothing );


  // Get the Order schedule.
  virtual
    const LgFrScheduleDescriptor&
      itemOrderSchedule() const;

  // Sort the current order schedule
  virtual
    RWBoolean
      sort (const LgFrSortDescriptor & = LgFrNullRWCString,
            int period = -1,
            const RWBoolean ascending = TRUE);

  // Set a (new) Order schedule.
  // If a sorting desriptor is specified, it is associated with the (new)
  // order schedule.
  virtual
    RWBoolean
      itemOrderSchedule(const LgFrScheduleDescriptor&,
			const LgFrSortDescriptor & = LgFrNullRWCString,
                        int period = -1,
                        const RWBoolean ascending = TRUE);

  // Set a (new) Order schedule.
  // If a LgFrPairCompareFloat is specified, it is associated with the (new)
  // order schedule.
  virtual
    RWBoolean
      itemOrderSchedule(const LgFrScheduleDescriptor&,
			LgFrPairCompareFloat* = NULL,
                        const RWBoolean ascending = TRUE);

  // Return index of next item.printingName() which matches the specified
  // regular expression.
  // RW_NPOS is returned if a matching item is not found.
  // If an invalid regular expression is passed, then a warning message
  // is written to cout and RW_POS is returned.
  virtual
    size_t
      index( 
        const RWCString & regularExpression,
        const size_t startingIndex = 0 )
          const;  
    

  // Return index of next item.printingName() which contains the specified      
  // search string.
  // RW_NPOS is returned if a matching item is not found.
  virtual
    size_t
      index( 
        const RWCString & searchString,
        const RWBoolean ignoreCase,
        const size_t startingIndex = 0 )
          const;
  
  // Return TRUE iff schedule is mutable
  virtual
    RWBoolean
      isMutable (const LgFrScheduleDescriptor&);

  // Return TRUE iff proposed schedule contains valid values only
  virtual
    LgFrValidity
      validity (const LgFrScheduleDescriptor& sd,
               const LgFrTimeVecFloat& proposedTimeVec
               );

  // Return TRUE : schedule is found and changed.
  //        FALSE: schedule is not found.
  virtual
    RWBoolean
      changeValueInSchedule(const LgFrItem& item,
			    const LgFrScheduleDescriptor& sd,
			    const int& index,
			    const float& newValue
			    );

  // Change a time-vector in the schedule for an item
  // Return TRUE : schedule is found and changed.
  //        FALSE: schedule is not found.
  virtual
    RWBoolean
      changeTimeVecInSchedule(const LgFrItem& item,
			      const LgFrScheduleDescriptor& sd,
			      const LgFrTimeVecFloat& newTimeVec
			      );

  // Return a string suitable for use as the description of the items
  // in the schedule
  virtual
  RWCString
  itemHeading ()
       const = 0;

  // Change a value in the schedule for an item
  // Return TRUE : schedule is found and changed.
  //        FALSE: schedule is not found.
  virtual
    RWBoolean
      changeValueInSchedule(const RWCString & guiName,
			    const LgFrScheduleDescriptor& sd,
			    const int& index,
			    const float& newValue
			    );

  // Change a time-vector in the schedule for an item
  // Return TRUE : schedule is found and changed.
  //        FALSE: schedule is not found.
  virtual
    RWBoolean
      changeTimeVecInSchedule(const RWCString & guiName,
			      const LgFrScheduleDescriptor& sd,
			      const LgFrTimeVecFloat& newTimeVec
			      );

  // Get a time-vector in the schedule for an item whose guiName() is guiName
  virtual
    const LgFrTimeVecFloat*
      getTimeVecFloat(const RWCString & guiName,
		      const LgFrScheduleDescriptor& sd
		      );

  // Get a time-vector in the schedule for an item
  virtual
    const LgFrTimeVecFloat*
      getTimeVecFloat(const LgFrItem& item,
		      const LgFrScheduleDescriptor& sd
		      );

  // Create a copy of the *this on the heap for a new and different scneario
  // and return a pointer to it. (deep copy)
  virtual
    LgFrMultiScheduleFloat*
      clone (LgFrScenarioSmartPointer)
       const
       = 0;

  // Constructor
  LgFrMultiScheduleFloat (LgFrScenarioSmartPointer);

  // Default constructor
  LgFrMultiScheduleFloat ();

  // Destructor
  virtual
    ~LgFrMultiScheduleFloat ();

  // print
  virtual void print() const;

  // print the data by item and attribute.
  // print it to *cofs if cofs is not NULL, otherwise use cout and
  // include a "banner" at the beginning
  virtual void printByItemAndAttribute(const LgFrSchedulePrintStyle = TEXT,
                                       ofstream * cofs = NULL);

  // Format the data and send it to the ostream specified.
  // The format will be:
  //                           Period1 heading..PeriodX heading
  // Item name--Schedule name--Period1 value  ..PeriodX value
  // cofs : if null then cout is used.
  // useGuiName : if FALSE then then printingName method is used to format
  //              items.
  //              if TRUE then guiName is used to format items. Using guiName
  //              works best when style = CSV.
  virtual
    void
      printMultiScheduleReport(
        const LgFrSchedulePrintStyle style = TEXT,
        ostream * cofs = NULL,
        RWBoolean useGuiName = FALSE )
      const;

  // Returns a RWCString representation of the multischedule.
  // The format of the string is the same format as printMultiScheduleReport.
  virtual
    RWCString format(
      const LgFrSchedulePrintStyle = TEXT,
      RWBoolean useGuiName = FALSE )
    const;

  // Context test this class
  static void contextTest(LgFrScenarioSmartPointer, LgFrScenarioSmartPointer);

// ---------------------------------------------------------------------
//  PROTECTED MEMBERS
// ---------------------------------------------------------------------
protected:

  // Return the pointer to the scenario
  virtual
    LgFrScenarioSmartPointerToConst
      scenario() const;

  // Return a pair compair strategy that is corresponding with the
  // sorting descriptor and optional second parameter period.
  virtual
    LgFrPairCompareFloat*
      makePairCompareStrategy(LgFrSortDescriptor sortDesc,
                              int period = -1)
        const;

  // Return the abbreviation of a schedule descriptor.

  RWCString
    abbreviationOf (const LgFrScheduleDescriptor & desc)
       const;

  // Return the index of the first schedule that matches sd.
  virtual
    int
      index(const LgFrScheduleDescriptor& sd) const;

  // Return the first item matches sd.
  // return NULL if not found, else return that item.
  virtual
    LgFrDescriptorSchedulePairFloat*
      find(const LgFrScheduleDescriptor& sd) const;

  // Return the list of LgFrDescriptorSchedulePairFloat
  virtual
    LgFrDescriptorSchedulePairFloatGSList&
      descSchedPairList();

    virtual
    const LgFrDescriptorSchedulePairFloatGSList&
      descSchedPairList() const;

  // Return a non-const schedule
  virtual
    LgFrSortingScheduleFloatSmartPointer
     schedule(const LgFrScheduleDescriptor& sd) const;

  // Copy constructor (deep copy to a new and different scenario)
  // Used by clone method only so that it can check if the new scenario
  // is different from the current one.
  LgFrMultiScheduleFloat (const LgFrMultiScheduleFloat &,
			  LgFrScenarioSmartPointer);

  // Assignment operator (not allowed, use clone(LgFrScenarioSmartPointer) method)
  LgFrMultiScheduleFloat &
    operator=(const LgFrMultiScheduleFloat& rhs);

  // Copy constructor (not allowed, use clone(LgFrScenarioSmartPointer) method)
  LgFrMultiScheduleFloat (const LgFrMultiScheduleFloat &);

  // Given the guiName of a part or demand, return a pointer to it or a null
  // pointer.  The pointer is valid until a part or demand
  // is added to or taken from the universal set of parts or demands.
  virtual
  const LgFrItem *
  findItem (const RWCString & guiName)
  const
  = 0;


// ---------------------------------------------------------------------
//  PRIVATE MEMBERS
// ---------------------------------------------------------------------
private:

  // Pointer to the scenario
  LgFrScenarioSmartPointer scenarioPtr_;

  // List of LgFrDescriptorSchedulePairFloat
  LgFrDescriptorSchedulePairFloatGSList descScheduleList_;

  // The selection schedule SD
  LgFrScheduleDescriptor itemSelectionSchedule_;

  // The sorting schedule SD
  LgFrScheduleDescriptor itemOrderSchedule_;

  // Create a RWString of the schedule names for this multiSchedule
  RWCString* LgFrCreateScheduleNamesRWCString(int nattrs) const;

  /* Create a matrix of ItemTimeVector pair float pointers for all
   the floats in this multi schedule*/
  LgFrItemTimeVecPairFloat* LgFrCreateITVMatrix(int totAttrs,int nperiods,
						int nattrs) const;


// ---------------------------------------------------------------------
//  PROTECTED MEMBERS
// ---------------------------------------------------------------------
protected:
  // Subscription of *this to sd
  virtual
    void
      addSubscription( LgFrDescriptorSchedulePairFloat*);
};

#endif
