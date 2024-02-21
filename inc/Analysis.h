/*
**	Filename : Analysis.h
**	2024-02-21
**	username : rsehgal
*/
#ifndef Analysis_h
#define Analysis_h

#include <string>

class TFile;
class Data;

class Analysis {

  Data *fData;
private:
  static Analysis *s_instance;
  Analysis(std::string filename);

  // ROOT objects
  TFile *fp;

public:
  static Analysis *Instance();
  static Analysis *Create(std::string filename);
  void Close();
  Data* GetData() const;
};
#endif
