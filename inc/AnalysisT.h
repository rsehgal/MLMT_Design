/*
**	Filename : AnalysisT.h
**	2024-06-13
**	username : rsehgal
*/
#ifndef AnalysisT_h
#define AnalysisT_h

#include <string>

class TFile;
#include <TFile.h>
template <typename T>
class AnalysisT {

  T *fData;

private:
  static AnalysisT<T> *s_instance;

  AnalysisT(std::string filename)
  {
    fp    = new TFile(filename.c_str(), "RECREATE");
    fData = new T();
  }

  // ROOT objects
  TFile *fp;

public:
  static AnalysisT<T> *Instance()
  {
    if (!s_instance)
      std::cout << "Analysis object does not exist in memory, Please create it first..." << std::endl;
    else
      return s_instance;
  }
  static AnalysisT<T> *Create(std::string filename)
  {
    if (!s_instance) s_instance = new AnalysisT<T>(filename);
    return s_instance;
  }
  void Close()
  {
    fp->cd();
    fData->Write();
    fp->Close();
  }
  T *GetData() const { return fData; }

  TFile *GetFilePointer() const {return fp;}
};
template <typename T>
AnalysisT<T> *AnalysisT<T>::s_instance = nullptr;

#endif
