// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
#ifndef ClpObjective_H
#define ClpObjective_H


//#############################################################################

/** Objective Abstract Base Class

Abstract Base Class for describing an objective function

*/

class ClpObjective  {
  
public:
  
  ///@name Stuff
  //@{
  
  /** Returns gradient.  If Linear then solution may be NULL,
      also returns an offset (to be added to current one)
  */
  virtual double * gradient(const double * solution, double & offset) = 0;
  /// Resize objective
  virtual void resize(int newNumberColumns) = 0; 
  /// Delete columns in  objective
  virtual void deleteSome(int numberToDelete, const int * which) = 0; 
  //@}
  
  
  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpObjective(); 
  
  /// Copy constructor 
  ClpObjective(const ClpObjective &);
  
  /// Assignment operator 
  ClpObjective & operator=(const ClpObjective& rhs);
  
  /// Destructor 
  virtual ~ClpObjective ();

  /// Clone
  virtual ClpObjective * clone() const = 0;
 
  //@}

  ///@name Other
  //@{
  /// Returns type (above 63 is extra information)
  inline int type()
  { return type_;};
  
  //@}

  //---------------------------------------------------------------------------
  
protected:
  ///@name Protected member data 
  //@{
  /// Type of objective - linear is 1
  int type_;
  //@}
};

#endif
