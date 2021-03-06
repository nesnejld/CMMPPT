#include <iostream.h>

#include <scenario/src/partNmFS.h>
#include <scenario/src/itemTimV.h>
#include <scenario/src/part.h>
#include <scenario/src/machdep.h>
#include <scenario/src/idnumber.h>

// Do Filtering
RWBoolean
LgFrPartNameFilterStrategy::exclude(
   const LgFrItemTimeVecPairFloat & itvpf)
const
{
   assert( itvpf.item().isA() == __LGFRPART );

#ifdef WIN32   
   const LgFrPart (& thePart) (itvpf.part());
#else  
   const LgFrPart & thePart = itvpf.part();
#endif   

   RWCString partName (thePart.name());

   if (partName.compareTo(partName(partRegexp_)) != 0)
      return TRUE;

   return FALSE;
}

// Get the Part Regexp as a RWCString associated with this Filter
RWCString
LgFrPartNameFilterStrategy::partRE()
const
{
   return partREstring_;
}

// Get the partRegexp  associated with this filter
RWCRegexp
LgFrPartNameFilterStrategy::partRegexp()
const
{
   return partRegexp_;
}

// Make clone copy of object
LgFrFilterStrategy *
LgFrPartNameFilterStrategy::clone()
const
{
  LgFrPartNameFilterStrategy* newInst = 
      new LgFrPartNameFilterStrategy(*this);
  return (newInst);
}

// Make clone copy of object with new Scenario
LgFrFilterStrategy *
LgFrPartNameFilterStrategy::clone(LgFrScenario & newScenario)
const
{
  LgFrPartNameFilterStrategy* newInst = 
      new LgFrPartNameFilterStrategy(*this, newScenario);
  return (newInst);
}

// Return comparison strategy identifier
isAReturnType
LgFrPartNameFilterStrategy::isA()
const
{
   return id_;
}

// Assignment operator
LgFrPartNameFilterStrategy &
LgFrPartNameFilterStrategy::operator=(
			  const LgFrPartNameFilterStrategy& rhs)
{
  assert( id_ == rhs.id_ );
  if (this != &rhs) {		// Check for assignment to self
     (this->LgFrFilterStrategy::operator= ) (rhs);
     partREstring_   = rhs.partREstring_;
     partRegexp_ = rhs.partRegexp_;
  }
  return *this;
}


// Copy constructor
LgFrPartNameFilterStrategy::
   LgFrPartNameFilterStrategy (
      const LgFrPartNameFilterStrategy & source)
:  
   LgFrFilterStrategy( source ),
   id_(__LGFRPARTNAMEFILTERSTRATEGY),
   partREstring_(source.partREstring_),
   partRegexp_(source.partRegexp_)
{
  assert( id_ == source.id_ );
}

// Copy constructor with new Scenario
LgFrPartNameFilterStrategy::
   LgFrPartNameFilterStrategy (
      const LgFrPartNameFilterStrategy & source,
      LgFrScenario & newScenario )
:  
   LgFrFilterStrategy( source, newScenario ),
   id_(__LGFRPARTNAMEFILTERSTRATEGY),
   partREstring_(source.partREstring_),
   partRegexp_(source.partRegexp_)
{
  assert( id_ == source.id_ );
}

// Preferred Constructor
LgFrPartNameFilterStrategy::
   LgFrPartNameFilterStrategy (
          const RWCString & partREstring )
:  
   LgFrFilterStrategy(), 
   id_(__LGFRPARTNAMEFILTERSTRATEGY),
   partREstring_(partREstring),
   partRegexp_(partREstring)
{
   if (partRegexp_.status() != RWCRegexp::OK)
   {
      cerr << "\nIllegal RWCRegexp specified for part ---> " 
           << partREstring
           << "\n";
      assert( partRegexp_.status() == RWCRegexp::OK);
   }
}


// Default Constructor -- this will match anything
LgFrPartNameFilterStrategy::
   LgFrPartNameFilterStrategy ()
:  
   LgFrFilterStrategy(),
   id_(__LGFRPARTNAMEFILTERSTRATEGY),
   partREstring_(".*"),
   partRegexp_(".*")
{
  // Nothing to do here
}

// Destructor
LgFrPartNameFilterStrategy::
   ~LgFrPartNameFilterStrategy ()
{
   // Nothing to do here
}


#ifdef NDEBUG
#undef NDEBUG
#endif

// test LgFrPartNameFilterStrategy methods.
void
LgFrPartNameFilterStrategy::test()
{
  // Test Preferred constructor
  LgFrPartNameFilterStrategy cs1("USA");
  assert( cs1.id_ == __LGFRPARTNAMEFILTERSTRATEGY );

  // Test isA method
  assert( cs1.isA() == __LGFRPARTNAMEFILTERSTRATEGY );

  // Test copy constructor
  LgFrPartNameFilterStrategy cs2(cs1);
  assert( cs2.isA() == __LGFRPARTNAMEFILTERSTRATEGY );
  assert( cs2.partRegexp().status() == RWCRegexp::OK);
  assert(! cs2.partRE().compareTo(cs1.partRE()));

  // Test assignment operator
  LgFrPartNameFilterStrategy cs3("abc");
  cs3 = cs2;
  assert( cs3.isA() == cs2.isA() );
  assert( cs2.partRegexp().status() == RWCRegexp::OK);
//  assert( cs3.partRegexp_ == cs2.partRegexp_ );  No == method exists
  assert(! cs3.partRE().compareTo(cs2.partRE()) );

  // Test clone method
  LgFrFilterStrategy *cs4Ptr = cs1.clone();
  assert( cs4Ptr->isA() == cs1.isA() );
  
  // cast the clone back down to a PartNameFS
  LgFrPartNameFilterStrategy *cs5Ptr = 
         (LgFrPartNameFilterStrategy *) cs4Ptr; 
  assert(  cs1.partRegexp().status() == RWCRegexp::OK);
  assert(! cs1.partRE().compareTo(cs5Ptr->partRE()) );

  // Test destructor
  delete cs4Ptr;

  // Test exclude
  LgFrPart aPart("abc45");
  LgFrTimeVecFloat aTVF(2,2.);
  LgFrItemTimeVecPairFloat itvp1( aPart, aTVF);
  assert( cs1.exclude( itvp1 ) );
  assert( cs3.exclude( itvp1 ) );

  LgFrPartNameFilterStrategy cs6(".*45");
  assert( ! cs6.exclude( itvp1 ) );
  LgFrPartNameFilterStrategy cs7("abc.*");
  assert( ! cs7.exclude( itvp1 ) );
  LgFrPartNameFilterStrategy cs8(".*");
  assert( !cs8.exclude( itvp1 ) );
  LgFrPartNameFilterStrategy csA("ABC");
  assert( csA.exclude( itvp1 ) );

  // default constructor should let anything through
  LgFrPartNameFilterStrategy cs10;
  assert( ! cs10.exclude( itvp1 ) );
  
}
