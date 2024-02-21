/*
**	Filename : DetectorData.h
**	2024-02-21
**	username : rsehgal
*/
#ifndef DetectorData_h
#define DetectorData_h

struct DetectorData {
  unsigned int fDetID;
  unsigned int fQNear;
  unsigned int fQFar;
  // unsigned long int fTNear;
  // unsigned long int fTFar;

  DetectorData(unsigned int detid)
  {
    fDetID = detid;
    fQNear = 0;
    fQFar  = 0;
  }

  DetectorData(unsigned int detid, unsigned int qnear, unsigned int qfar)
  {
    fDetID = detid;
    fQNear = qnear;
    fQFar  = qfar;
  }

  void Print() { std::cout << "DetID : " << fDetID << " : QNear : " << fQNear << " : QFar : " << fQFar << std::endl; }
};

#endif
