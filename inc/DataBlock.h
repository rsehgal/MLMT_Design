/*
**	Filename : DataBlock.h
**	2024-02-21
**	username : rsehgal
*/
#ifndef DataBlock_h
#define DataBlock_h

#include <string>

class TTree;

class DataBlock {
public:
  unsigned int fEvNo;
  unsigned long int fTNorth;
  unsigned long int fTSouth;
  unsigned long int fTEast;
  unsigned long int fTWest;
  unsigned int fQNorth;
  unsigned int fQSouth;
  unsigned int fQEast;
  unsigned int fQWest;

  TTree *fTree;

public:
  DataBlock();
  ~DataBlock();
  unsigned int GetCount() const;
  void Fill(unsigned int evNo,  unsigned int qnorth, unsigned int qsouth, unsigned int qeast, unsigned int qwest);
  void Fill();
  void Write();
  void Reset();
  void Print();
};

#endif
