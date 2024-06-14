/*
**	Filename : DataBasic.h
**	2024-06-13
**	username : rsehgal
*/
#ifndef DataBasic_h
#define DataBasic_h

class TTree;

#include "Point3D.h"

class DataBasic
{
    TTree *fTree;
    Point3D fPoint;
    unsigned long int fTime;

public:
    DataBasic();
    DataBasic(Point3D *pt, unsigned long int tm);
    DataBasic(double x, double y, double z, unsigned long int tm);
    void Fill();
    void Fill(Point3D *pt, unsigned long int tm);
    void Fill(double x, double y, double z, unsigned long int tm);
    void Write();
};

#endif
