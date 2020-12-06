#pragma once
class Vertex
{
private:

public:
	int mas[16];
	//dfs = Distance from start, ���������� ����� �� �������� (������) ������� �� �������. 
	//trip - ����. ������� �� dfs+HDTE.
	int dfs, trip;   
	//parent - ������ ������������ ���������� � �������� (�������������) ������.
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

