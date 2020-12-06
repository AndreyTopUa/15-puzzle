#pragma once
class ADR
{
public:
	int adr[4];
	ADR();
	ADR(int[4]);
	ADR(const ADR&);
	
	virtual ~ADR();

	ADR& operator = (ADR&);
	ADR& operator = (int[]);
};

