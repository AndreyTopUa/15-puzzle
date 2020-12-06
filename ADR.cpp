#include "stdafx.h"
#include "ADR.h"


ADR::ADR()
{
	for (int i=0;i<4;i++)
		this->adr[i] = -1;
}

ADR::ADR(int a[4])
{
	for (int i = 0; i<4; i++)
		this->adr[i] = a[i];
}
ADR::ADR(const ADR & obj)
{
	for (int i = 0; i<4; i++)
		this->adr[i] = obj.adr[i];
}

ADR::~ADR()
{
}

ADR & ADR::operator=(ADR & obj)
{
	for (int i=0;i<4;i++)
		this->adr[i] = obj.adr[i];
	return *this;
}

ADR & ADR::operator=(int obj[])
{
	for (int i = 0; i<4; i++)
		this->adr[i] = obj[i];
	return *this;
}
