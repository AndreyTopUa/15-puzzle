#pragma once
class Vertex
{
private:

public:
	int mas[16];
	//dfs = Distance from start, количество ходов от заданной (первой) позиции до текущей. 
	//trip - путь. Состоит из dfs+HDTE.
	int dfs, trip;   
	//parent - адресс родительской комбинации в закрытом (просмотренном) списке.
	ADR parent;
	Vertex();
	virtual ~Vertex();
	
Vertex& operator = (Vertex&);
bool operator ==(Vertex&);
bool operator !=(Vertex&);

double HeDTE(); //Heuristic distance to the end.
void Get_Neighbors(vector<Vertex>&);
bool Check_End();

};

