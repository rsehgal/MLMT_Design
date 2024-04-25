/*
**	Filename : AnalysisBlock.h
**	2024-02-21
**	username : rsehgal
*/
#ifndef AnalysisBlock_h
#define AnalysisBlock_h

#include <string>

class TFile;
class DataBlock;

class AnalysisBlock {

  DataBlock *fData;
private:
  static AnalysisBlock *s_instance;
  AnalysisBlock(std::string filename);

  // ROOT objects
  TFile *fp;

public:
  static AnalysisBlock *Instance();
  static AnalysisBlock *Create(std::string filename);
  void Close();
  DataBlock* GetData() const;
};
#endif
