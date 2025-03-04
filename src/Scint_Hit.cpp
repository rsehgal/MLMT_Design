/*
**	Filename : Scint_Hit.cpp
**	2025-01-20
**	username : rsehgal
*/
#include <iostream>
#include "Scint_Hit.h"

Scint_Hit::Scint_Hit() {}

Scint_Hit::~Scint_Hit() {}

void Scint_Hit::Fill(uint32_t channelNum, uint64_t tm)
{
  fChannelNum = channelNum;
  fTime       = tm;
}
