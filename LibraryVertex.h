#pragma once
class LibraryVertex
{
private:

public:
	
	vector <Vertex> list[16][16][16];//4096 ��������� �����. ������������� ������.
	int my_size;
	vector <ADR> last_adr_add;//������ ������� ���� ����������� ���������� � �������������� �����.
	int adr_min_trip[4];

	LibraryVertex();
	virtual ~LibraryVertex();

	bool Check_In_List(Vertex,int []);//�������� �� ���������� � �������.
	void Min_Trip(int[]);//��������� ���������� � ����������� trip. 


	void operator +=(Vertex&);
	void operator -=(int[]);
};
inline void ShowSolution(Vertex Curr, LibraryVertex Close, HWND hB[])
{
	char str[256] = "";
	sprintf(str, "%s %d %s", "���������� ����� �� ������� - ", Curr.dfs, " !\n������� ��������� ����������� �������?");
	int res = MessageBox(NULL, str, "���������� ���������", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
	if (res == IDYES)
	{
		vector <Vertex> Solution;
		while (Curr.dfs > 0)
		{
			Solution.push_back(Curr);
			Curr = Close.list[Curr.parent.adr[0]][Curr.parent.adr[1]][Curr.parent.adr[2]][Curr.parent.adr[3]];
		}
		while (Solution.size())
		{
			Sleep(500);
			ShowM(hB, Solution[(Solution.size() - 1)].mas);
			Solution.erase(Solution.begin() + (Solution.size() - 1));
		}
		MessageBox(NULL, "��-����� !", "���������", MB_OK);
	}
}

inline int Open_element_not_empty(LibraryVertex* Open, int m_t_f)
{
	for (int i = 0; i < 300; i++)
		if (Open[i].my_size != 0 && i < m_t_f)//����������� ����� ����������� ������� Open �� 300 �� ����.
		{
			m_t_f = i;
			i = 299;
		}
	return m_t_f;
}
