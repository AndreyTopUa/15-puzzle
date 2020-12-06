#include "stdafx.h"
#include "LibraryVertex.h"


LibraryVertex::LibraryVertex()
{
	this->my_size = 0;
}


LibraryVertex::~LibraryVertex()
{
}


bool LibraryVertex::Check_In_List(Vertex v, int adr[])
{
	for (int i = 0; i<this->list[v.mas[0]][v.mas[4]][v.mas[9]].size(); i++)

		if (this->list[v.mas[0]][v.mas[4]][v.mas[9]][i] == v)
		{
			adr[0] = v.mas[0];
			adr[1] = v.mas[4];
			adr[2] = v.mas[9];
			adr[3] = i;
			return true;
		}
	return false;
}

void LibraryVertex::Min_Trip(int adr[])
{
	int trip_tmp = 100000;
#pragma omp parallel for
	for (int i0 = 0; i0 < 16; i0++)
#pragma omp parallel for
		for(int i1=0;i1<16;i1++)
#pragma omp parallel for
			for(int i2=0; i2<16;i2++)
				for (int i3=0;i3<this->list[i0][i1][i2].size();i3++)
				{
					if (this->list[i0][i1][i2][i3].trip< trip_tmp)
					{
						trip_tmp = this->list[i0][i1][i2][i3].trip;
						adr[0] = i0;
						adr[1] = i1;
						adr[2] = i2;
						adr[3] = i3;
					}
				}
}

void LibraryVertex::operator+=(Vertex &v)
{
	this->list[v.mas[0]][v.mas[4]][v.mas[9]].push_back(v);
	this->my_size++;
	int tmp[4];
	ADR tmp_adr;
	tmp[0] = v.mas[0];
	tmp[1] = v.mas[4];
	tmp[2] = v.mas[9];
	tmp[3] = (this->list[v.mas[0]][v.mas[4]][v.mas[9]].size() - 1);
	tmp_adr = tmp;
	this->last_adr_add.push_back(tmp_adr);
}

void LibraryVertex::operator-=(int adr[])
{
	this->list[adr[0]][adr[1]][adr[2]].erase(this->list[adr[0]][adr[1]][adr[2]].begin() + adr[3]);
	this->my_size--;
	this->last_adr_add.pop_back();
}

