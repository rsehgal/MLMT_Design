/*
**	Filename : Data.h
**	2024-02-21
**	username : rsehgal
*/
#ifndef Data_h
#define Data_h

#include <string>

class TTree;

class Data {

  unsigned int fEvNo;
  unsigned int fDetNo;
  unsigned long int fTNear;
  unsigned long int fTFar;
  unsigned int fQNear;
  unsigned int fQFar;

  TTree *fTree;

public:
  Data();
  ~Data();
  unsigned int GetCount() const;
  void Fill(unsigned int evNo, unsigned int detNo, unsigned long int tnear, unsigned long int tfar, unsigned int qnear, unsigned int qfar);
  void Fill();
  void Write();
};

#endif
