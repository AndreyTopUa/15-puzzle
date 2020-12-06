#include "stdafx.h"
#include "Vertex.h"


Vertex::Vertex()
{
	for (int i = 0; i < size(mas); i++)
		mas[i] = -1;
	dfs = trip = -1;
}

Vertex & Vertex::operator=(Vertex & obj)
{
	this->dfs = obj.dfs;
	this->parent = obj.parent;
	this->trip = obj.trip;
	for (int i = 0; i < 16; i++)
		this->mas[i] = obj.mas[i];
	return *this;
}

bool Vertex::operator==(Vertex & obj) 
{
	int i = 0;
	while ((this->mas[i] == obj.mas[i]))
	{
		i++;
		if (i == 16)
			return true;
	}
	return false;
}

bool Vertex::operator!=(Vertex & obj)
{
	return !(*this==obj);
}


Vertex::~Vertex()
{
}


double Vertex::HeDTE()
{
	//Эврестическое предположение о минимально необходимом колличестве ходов до терминального состояния.
	//Метод Манхетонского растояния.
	int coord_end[16][2] = { { 1,1 },{ 2,1 },{ 3,1 },{ 4,1 },{ 1,2 },{ 2,2 },{ 3,2 },{ 4,2 },{ 1,3 },{ 2,3 },{ 3,3 },{ 4,3 },{ 1,4 },{ 2,4 },{ 3,4 },{ 4,4 } };
	int e = 0;
	int iter = 0;
	for (int i = 0; i <= 15; i++)
	{
		if (this->mas[i] == 0)
			iter = 16;
		else
			iter = this->mas[i];
		e += (abs(coord_end[i][0] - coord_end[iter - 1][0]) + abs(coord_end[i][1] - coord_end[iter - 1][1]));
	}

	return (e*2);//х2 - коррекция для соглавования эвристики со стоимостю одного хода.

};

//Проверка на соответствие комбинации терминальному состоянию
bool Vertex::Check_End()
{
	int end[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
	int ind = 0;
	for (int i = 0; i < 16; i++)
	{
		if (this->mas[i] == end[i])
			ind++;
	}
	if (ind == 16)
		return true;

	return false;
}


//Получение соседей текущей комбинации (мин = 2, макс = 4).
void Vertex::Get_Neighbors(vector <Vertex> &Neighbors)
{
	int zero_pozition = -1;
	int mas_tmp[16];
	Vertex V_tmp;
	for (int i = 0; i < 16; i++)
	{
		if (this->mas[i] == 0)
			zero_pozition = i;
	}
	if (zero_pozition != -1)
	{
		if (zero_pozition + 1 <= 15 && ((zero_pozition + 1 + 1) % 4 != 1))
		{
			memcpy(V_tmp.mas, this->mas, sizeof(V_tmp.mas));
			swap(V_tmp.mas[zero_pozition], V_tmp.mas[zero_pozition + 1]);
			V_tmp.dfs = this->dfs + 1;
			V_tmp.trip = V_tmp.dfs + V_tmp.HeDTE();
			Neighbors.push_back(V_tmp);
		}
		if (zero_pozition - 1 >= 0 && ((zero_pozition) % 4 != 0))
		{
			memcpy(V_tmp.mas, this->mas, sizeof(V_tmp.mas));
			swap(V_tmp.mas[zero_pozition], V_tmp.mas[zero_pozition - 1]);
			V_tmp.dfs = this->dfs + 1;
			V_tmp.trip = V_tmp.dfs + V_tmp.HeDTE();
			Neighbors.push_back(V_tmp);
		}
		if (zero_pozition + 4 <= 15)
		{
			memcpy(V_tmp.mas, this->mas, sizeof(V_tmp.mas));
			swap(V_tmp.mas[zero_pozition], V_tmp.mas[zero_pozition + 4]);
			V_tmp.dfs = this->dfs + 1;
			V_tmp.trip = V_tmp.dfs + V_tmp.HeDTE();
			Neighbors.push_back(V_tmp);
		}
		if (zero_pozition - 4 >= 0)
		{
			memcpy(V_tmp.mas, this->mas, sizeof(V_tmp.mas));
			swap(V_tmp.mas[zero_pozition], V_tmp.mas[zero_pozition - 4]);
			V_tmp.dfs = this->dfs + 1;
			V_tmp.trip = V_tmp.dfs + V_tmp.HeDTE();
			Neighbors.push_back(V_tmp);
		}

	}
}
;
