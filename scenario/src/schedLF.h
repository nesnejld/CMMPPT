#ifndef LGFR_SCHED_H
#define LGFR_SCHED_H
// RW2STL -- inserted:
#include <map>
#include <string>
// End of RW2STL -- inserted includes.

// This is a base class for representing schedules of items.
// Items are parts or demands.

// The structure used for
// representing a schedule is an ordered vector of Pairs 
// of Item - TimeVecFloat.



#include <scenario/src/timeVecs.h>
#include <scenario/src/itemTimV.h>
#include <scenario/src/filtStrt.h>

// Typedef for 
typedef  LGFR_DECLSPEC
         LgFrTimeVecFloat (LgFrTimeVecFloat::*LgFrTimeVecFloatOpFunction)
         ( const LgFrTimeVecFloat &) const;
typedef  LGFR_DECLSPEC
         LgFrTimeVecFloat (*LgFrTimeVecFloatRhsScalarOpFunction)
         ( const LgFrTimeVecFloat &, const float &);
typedef  LGFR_DECLSPEC
         LgFrTimeVecFloat (*LgFrTimeVecFloatLhsScalarOpFunction)
         ( const float &, const LgFrTimeVecFloat & );

class LGFR_DECLSPEC LgFrScheduleFloat {

private:

  static const LgFrScheduleFloat  emptySched; 
  static const LgFrFilterStrategy defaultFilterStrategy; 
                                // Used for default arg because SUN
                                // compiler fails when passed
                                // LgFrScheduleFloat(), LgFrFilterStrategy

public:


  // Is item in the schedule?
  virtual
    bool
      contains (const LgFrItem& item)
	const;

  // If item is in the table, set tv to be its timeVec and return true,
  // else return false.
  virtual
    bool
      findValue (const LgFrItem& item, LgFrTimeVecFloat& retVal)
	const;

  // Add pair of item - TimeVecFloat's to the end of the collection.
  virtual
     void
       insert (const LgFrItemTimeVecPairFloat pair);

  // Add single ItemTimeVecPairFloat to the collection at position index.  
  // Everything afterwards is shifted to a higher index.
  // If item is already in the table, it's timeVec is changed.
  virtual
     void
       insertAt (const size_t index,
                 const LgFrItemTimeVecPairFloat pptvf);

  // Insert Item if it isn't already in the schedule.  In any case,
  // associate timeVec with item.
  void
    insertKeyAndValue(const LgFrItem& item, const LgFrTimeVecFloat& value);

  // Obtain upper bound on number of entries which the schedule can
  // contain before resizing is required.  The client does not have
  // to manage the resizing, but may for better performance.
  virtual
    size_t 
      capacity()
          const;

  // Increase the amount of storage allocated to the set
  virtual
     void
       reserve (const size_t newCapacity);

  // Return the i'th ItemTimeVecPairFloat
  virtual
     LgFrItemTimeVecPairFloat 
       operator[](
          const size_t& i)
             const;
  virtual
     LgFrItemTimeVecPairFloat &
       operator[](
          const size_t& i );

  // Return the LgFrItemTimeVecPairFloat whose item matches item.
  // If there is no such LgFrItemTimeVecPairFloat, a new one is created
  // (using the default LgFrTimeVecFloat constructor) and inserted at
  // the end.
  // There is no const version of this method because it might have to
  // insert a new ItemTimeVecPairFloat.
  virtual
     LgFrItemTimeVecPairFloat &
       operator[](
          const LgFrItem& item);

  // Return the LgFrItemTimeVecPairFloat whose item matches item.
  // If there is no such LgFrItemTimeVecPairFloat, an assert exeception 
  // occurs.
  virtual
     const LgFrItemTimeVecPairFloat &
       operator[](
          const LgFrItem& item)
  const;


  // Return number of pairs in schedule
  virtual
     size_t
        size()
           const;
  
   // Perform diadic schedule operation.
   //   schedule operation schedule
   // vectorOp is the operation applied to the timeVecFloat portions
   // of the same items in the lhs and rhs schedule.
   // If an item is not in the lhs or rhs schedule then a vector of
   // zero is used.
   //
   // For example:
   //
   //   LgFrScheduleFloat lhs, rhs;
   //   LgFrScheduleFloat diff( lhs.op(rhs,LgFrTimeVecFloat::subtract);
   //
   //   diff contains lhs - rhs 
   //
   // If an item is not in both the lhs and rhs schedules, then a timeVec
   // timeVec with value defaultValue is used. 
   LgFrScheduleFloat
      op(
         LgFrTimeVecFloatOpFunction vectorOp,
         const LgFrScheduleFloat& rhs,
         float defaultValue = 0.0f )
      const;

   // Perform operation on column (timePeriod) of schedule.
   //
   // period is the column (period) where scalarOp is applied.
   //
   // scalarOp is the operation applied to the timeVecFloat portions
   // of each item in the schedule.
   //
   // For example 1:
   //
   //   LgFrScheduleFloat schedA;
   //   LgFrScheduleFloat schedB = schedA.columnOp( 1, ::LgFrAssign, 3.1415 );
   //
   //   schedB is equivalent to schedA, except for the 2nd time period where
   //   which has been assigned the value 3.1415. 
   //
   // For example 2:
   //
   //   LgFrScheduleFloat schedC = schedB.columnOp( 1, ::LgFrMultiply, 2.0 );
   //
   //   schedC is equivalent to schedB, except for the 2nd time period where
   //   which has been assigned the value 2*3.1415. 
   //
   LgFrScheduleFloat
      columnOp(
         const size_t period,
         float (*scalarOperation) (const float, const float),
         const float rhs )
      const;
  
#if 0
   // Perform diadic schedule operation.
   //   schedule operation float
   // scalarOp is the operation applied to the timeVecFloat portions
   // of each item in the schedule.
   //
   // For example:
   //
   //   LgFrScheduleFloat lhs;
   //   LgFrScheduleFloat DoubleLhs( lhs.op(rhs,::operation*);
   //
   //   DoubleLhs contains lhs * 2
   //
   LgFrScheduleFloat
      op(
         const LgFrScheduleFloat& rhs,
         LgFrTimeVecFloatScalarOpFunction scalarOp )
      const;
#endif

   // reduceItems method.
   // Named after APL reduce operator /.
   //
   // Original purpose is to implement method
   // for summing timeVec entries in a schedule.
   //
   // A filter strategy can be specified to selectively exclude 
   // itemTimeVecs from the reduction.
   //
   //
   // Returned timveVec is:
   //      result[0] = this[0].timeVec[0] "scalarOp" this[1].timeVec[0] 
   //                                     "scalarOp" this[2].timeVec[0] 
   //                                     "scalarOp" this[3].timeVec[0] ...
   //
   //      result[1] = this[0].timeVec[1] "scalarOp" this[1].timeVec[1] 
   //                                     "scalarOp" this[2].timeVec[1] 
   //                                     "scalarOp" this[3].timeVec[1] ...
   //
   //      result[2] = this[0].timeVec[2] "scalarOp" this[1].timeVec[2] 
   //                                     "scalarOp" this[2].timeVec[2] ...
   //                                     "scalarOp" this[3].timeVec[2] ...
   //      ...
   //
   // For example:
   //   LgFrScheduleFloat sched;
   //   LgFrTimeVecFloat  sum(sched.reduceItems(LgFrAdd));
   LgFrTimeVecFloat
      reduceItems(
         float (*scalarOp) ( const float, const float),
         const LgFrFilterStrategy & filter = defaultFilterStrategy )
            const;

   // Return schedule whose timeVec elements are the maximum of the elements
   // in *this and rhs.
   //
   // example:  
   //  on entry *this:  "item 1"  -1  0  5
   //                   "item 2"   1  1 -5
   //           rhs:    "item 1"  -2  1  6 
   //                   "item 3"   3 -1  6 
   // Returned schedule: "item 1"  -1  1  6
   //                    "item 2"   1  1 -5
   //                    "item 3"   3 -1  6 
   virtual
     LgFrScheduleFloat
       maximum(
         const LgFrScheduleFloat & rhs )
           const;


  // Determine if two schedules are equal.
  // Return true if both schedules contain the same itemTimeVec pairs.
  virtual
     bool
        isEqual(
           const LgFrScheduleFloat& rhs)
              const;
  virtual
     bool
        operator ==(
           const LgFrScheduleFloat& rhs)
              const;

  virtual
     bool
        operator !=(
           const LgFrScheduleFloat& rhs)
              const;

  // Assignment operator
  LgFrScheduleFloat &
    operator=(
	      const LgFrScheduleFloat& rhs);

  // Copy constructor
  LgFrScheduleFloat (const LgFrScheduleFloat &);

  // Constructor for a set expected to have up to n parts 
  // (and default constructor)
  LgFrScheduleFloat (const size_t n = DEFAULT_VECTOR_CAPACITY);

  // Destructor
  virtual
    ~LgFrScheduleFloat ();

  // print
  virtual void print() const;

   // Format a schedule for display.
   // Returns a string representing the schedule.
   //
   // highLight:
   //   If an item being formatted is contined in highLight and if
   //   highLight[item].timeVecFloat[i] != 0.0 then
   //   the i'th element of the timeVec
   //   is emphasized by following the number with an "*",
   //   or a client specified character.
   //
   // truncate: true indicates that item names all have the same length
   //           and are truncated if they can not fit in the alloted
   //           width.
   //
   // highLightFlag: character to follow a highlighted timeVec entry.
   //
   // width: ios width used to format each timeVec entry.
   //
   // precision: ios precision used to format each timeVec entry.
   //
   // iosFlags: ios formating flags used to format each timeVec entry.
   //
   std::string format(
      const LgFrScheduleFloat & highLight = LgFrScheduleFloat::emptySched,
      const bool truncate = true,
      const char highLightFlag = '*',
      const int width = 10,
      const int precision = 1 )//,
      //const long iosFlags = std::ios_base::fixed | std::ios_base::showpoint | std::ios_base::right )
   const;

  // test this class
  static void test();

protected:

   // Used to implement op methods.
   void
   kernalOfOp(
      LgFrTimeVecFloatOpFunction,
      const LgFrScheduleFloat& rhs,
      LgFrScheduleFloat &,
      float defaultValue )
         const;

   void
   kernalOfOp(
      LgFrTimeVecFloatRhsScalarOpFunction,
      const float rhs,
      LgFrScheduleFloat & )
         const;

   void
   kernalOfOp(
      const float lhs,
      LgFrTimeVecFloatLhsScalarOpFunction,
      LgFrScheduleFloat & )
         const;
   void
   kernalOfColumnOp(
      const size_t period,
      float (*scalarOperation) (const float, const float),
      const float rhs,              
      LgFrScheduleFloat & )
         const;
  
  // Remove all pairs from schedule.
  // Used to implement localClear in derived classes.
  virtual
     void
        clear();

private:

  virtual
  void
  fillDictionary();

  LgFrItemTimeVecPairFloatVector schedule_;
  size_t capacity_;              // Upper bound on number of schedule
                                 // entries, without resizing.

  struct Less
  {
      bool operator() (const LgFrItem* left, const LgFrItem* right) const
      {
          return ( left->compareTo( right ) < 0 );
      }
  };
 
  typedef std::pair<LgFrItem*,LgFrItemTimeVecPairFloat*> ItemItemTimeVecPair;
  typedef std::map<LgFrItem*,LgFrItemTimeVecPairFloat*,Less> ItemItemTimeVecDictionary;
  ItemItemTimeVecDictionary itemToEntry_; // Used to implement the mapping from 
	 			 // item to entry-in-schedule
  
};

// Addition Operator
LgFrScheduleFloat
   operator+ (const LgFrScheduleFloat& lhs, const LgFrScheduleFloat& rhs);

// Subtraction Operator
LgFrScheduleFloat
   operator- (const LgFrScheduleFloat& lhs, const LgFrScheduleFloat& rhs);

// Maximum 
//LgFrScheduleFloat
//   maximum (const LgFrScheduleFloat& lhs, const LgFrScheduleFloat& rhs);

#endif
