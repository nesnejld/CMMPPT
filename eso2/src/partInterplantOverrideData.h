#ifndef ESO2_partInterplantOverrideData_h
#define ESO2_partInterplantOverrideData_h

#include "scoFile.h"


class ESO2partInterplantOverrideData : public SCOcsvFormatFile {
public:

  // Fields
  getFieldH(part);
  getFieldH(srcLoc);
  getFieldH(destLoc);
  getIntFieldH(period);
  getFloatFieldH(moveCost);
  getFloatFieldH(moveTime);
  
  // preferred constructor
  ESO2partInterplantOverrideData(std::string filename)
    : SCOcsvFormatFile(filename)
  {  
    fieldSeperator(',');
    strip(true);
    //insertField("feature");
    //insertField("plantLoc");
    //insertField("period");
    //insertField("supply");
    //insertField("wfmv");
    hasHeaderRecord(6);
    commentRecords(true);
  };

  // compute key for storing record in dictionary
  static std::string key( 
    const std::string & part, 
    const std::string & srcLoc, 
    const std::string & destLoc, 
    int period ) 
  {
    char periodchar[100];
    sprintf( periodchar, "%d", period );
    std::string retVal = 
      part+"$+&"
      +srcLoc+"$+&"
      +destLoc+"$+&"
      +periodchar;
    return retVal;
  };
  
  // destructor
  ~ESO2partInterplantOverrideData(){/*nothing to do here*/};
  
  // Self-test
  static void test()
  {
    ESO2partInterplantOverrideData file("../data/example1/partInterplantOverrideData.csv");
    
    // Test reading first record

    assert( file.part(0)=="p2");
    assert( file.srcLoc(0) == "pok" );
    assert( file.destLoc(0) == "wat" );
    assert( file.periodAsInt(0) == 0 );
    assert( file.moveCostAsFloat(0) == 2.0f );
    assert( file.moveTimeAsFloat(0) == 1.0f );

    std::string k = file.key("p2","wat","pok",2);
    assert( file.part(k)=="p2");
    assert( file.srcLoc(k) == "wat" );
    assert( file.destLoc(k) == "pok" );
    assert( file.periodAsInt(k) == 2 );
    assert( file.moveCostAsFloat(k) == 1.0f );
    assert( file.moveTimeAsFloat(k) == 2.0f );

  }
  
protected:
  
  // compute key for storing record in dictionary
  virtual std::string key( unsigned int recNum ) const
  {
    std::string retVal = key(
      part(recNum),
      srcLoc(recNum),
      destLoc(recNum),
      periodAsInt(recNum) );
    return retVal;
  };

private:
  
  // default constructor -- don't use!
  ESO2partInterplantOverrideData();
  
  // copy constructor  -- don't use!
  ESO2partInterplantOverrideData( const ESO2partInterplantOverrideData& source );
  
  // assignment operator -- don't use!
  ESO2partInterplantOverrideData&
  operator=(const ESO2partInterplantOverrideData& rhs);

  
};



class ESO2partInterplantOverrideDataIterator : public SCOfileIterator {
public:
    
  // Fields
  getFieldFileWithIteratorH(part);
  getFieldFileWithIteratorH(srcLoc);
  getFieldFileWithIteratorH(destLoc);
  getIntFieldFileWithIteratorH(period);
  getFloatFieldFileWithIteratorH(moveCost);
  getFloatFieldFileWithIteratorH(moveTime);

  
  // preferred constructor
  ESO2partInterplantOverrideDataIterator(const ESO2partInterplantOverrideData & file)
    :SCOfileIterator(file)
  { /* Nothing to do here */};
  
  // destructor
  ~ESO2partInterplantOverrideDataIterator(){/* nothing to do here */};
  
  // Self-test
  static void test()
  {
    ESO2partInterplantOverrideData file("../data/example1/partInterplantOverrideData.csv");
    ESO2partInterplantOverrideDataIterator fileIter(file);
    
    // loop once for each record
    int recNo=0;
    for ( ; fileIter()!=NULL; ) {    
      if ( recNo == 0 ) {
        
        assert( fileIter.part()=="p2");
        assert( fileIter.srcLoc() == "pok" );
        assert( fileIter.destLoc() == "wat" );
        assert( fileIter.periodAsInt() == 0 );
        assert( fileIter.moveCostAsFloat() == 2.0f );
        assert( fileIter.moveTimeAsFloat() == 1.0f );
          
      }
      recNo++;
    }
    
  }

private:
  
  
  // default constructor -- don't use!
  ESO2partInterplantOverrideDataIterator();
  
  // copy constructor  -- don't use!
  ESO2partInterplantOverrideDataIterator( const ESO2partInterplantOverrideDataIterator& source );
  
  // assignment operator -- don't use!
  ESO2partInterplantOverrideDataIterator&
  operator=(const ESO2partInterplantOverrideDataIterator& rhs);

  
};
#endif
