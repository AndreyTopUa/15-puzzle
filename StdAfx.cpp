// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;


LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HWND hBut_[16];
	static HWND inf_wind[4];
	int res = 0;
	static int mas[16];
	static int mas_2[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 15 };
	static int mas_3[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 14, 0 };
	static int hard[16] = { 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 1, 2, 0 };
	static int start[16];
	static LONG sx, sy;
	static HDC hdc;
	PAINTSTRUCT ps;
	int i, j, sh;
	static HMENU hMenu;
	//thread l;



	switch (message)
	{

	case WM_CREATE:
		hMenu = LoadMenu(hInst, (TCHAR*)IDR_MENU1);
		SetMenu(hwnd, hMenu);
		srand(time(0));
		for (i = 0; i < 16; i++)
			hBut_[i] = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 0, 0, 0, 0, hwnd, 0, hInst, 0);
		for (int i = 0; i<4; i++)
			inf_wind[i] = CreateWindow("Static", " ", WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER, 0,0,0,0, hwnd, 0, hInst, 0);


		for (i = 0; i < 16; i++)
		{
		xyz:			mas[i] = rand() % 16;
			for (j = 0; j < i; j++)
				if (mas[i] == mas[j])
					goto xyz;
		}
		memcpy(start, mas, sizeof(start));

		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam)-50;
		break;

	case WM_COMMAND:
		for (i = 0; i < 16; i++)
			if ((HWND)lParam == hBut_[i])
			{
				if (mas[i + 1] == 0 && i + 1 <= 15 && ((i + 1 + 1) % 4 != 1))
				{
					swap(mas[i], mas[i + 1]);
					InvalidateRect(hwnd, 0, 1);
					break;
				}
				if (mas[i - 1] == 0 && i - 1 >= 0 && ((i) % 4 != 0))
				{
					swap(mas[i], mas[i - 1]);
					InvalidateRect(hwnd, 0, 1);
					break;
				}
				if (mas[i + 4] == 0 && i + 4 <= 15)
				{
					swap(mas[i], mas[i + 4]);
					InvalidateRect(hwnd, 0, 1);
					break;
				}
				if (mas[i - 4] == 0 && i - 4 >= 0)
				{
					swap(mas[i], mas[i - 4]);
					InvalidateRect(hwnd, 0, 1);
					break;
				}
			}
		switch (LOWORD(wParam))
		{
		case ID_40001:
		xyv:		for (i = 0; i < 16; i++)
		{
		xyw:			mas[i] = rand() % 16;
			for (j = 0; j < i; j++)
				if (mas[i] == mas[j])
					goto xyw;
		}
					InvalidateRect(hwnd, 0, 1);
					break;
		case ID_40002:
			for (i = 0; i < 16; i++)
				mas[i] = mas_2[i];
			InvalidateRect(hwnd, 0, 1);
			break;
		case ID_40003:
		{
			res = MessageBox(NULL, "Желаете проверить эту комбинацию\nна решаемость?", "Просто беспокоюсь о Вашем потеряном времени", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
			if (res == IDYES)
				if (SolvabilityTest(mas))
				{
					res = MessageBox(NULL, "Комбинация нерешаема.\nЖелаете пересобрать?", "Результат проверки", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
					if (res == IDYES)
						goto xyv;
				}
				else
				{
					MessageBox(NULL, "Комбинация решаема!", "Результат проверки", MB_OK | MB_ICONINFORMATION);
				}
				//sh = 
				//AStar(mas, inf_wind, hBut_);
			thread l(AStar, std::ref(mas), std::ref(inf_wind), std::ref(hBut_));
			l.detach();
			break;
		}

		case 40004:
			for (i = 0; i < 16; i++)
				mas[i] = hard[i];
			InvalidateRect(hwnd, 0, 1);
			break;
		case 40005:

xyb:		if (SolvabilityTest(mas))
			{
				res = MessageBox(NULL, "Комбинация нерешаема.\nЖелаете пересобрать?", "Результат проверки", MB_YESNO | MB_ICONINFORMATION | MB_DEFBUTTON2);
				if (res == IDYES)
					goto xyv;
			}
			else
				MessageBox(NULL, "Комбинация решаема!", "Результат проверки", MB_OK | MB_ICONINFORMATION);
			break;
		case 40006:
			for (i = 0; i < 16; i++)
				mas[i] = mas_3[i];
			InvalidateRect(hwnd, 0, 1);
			break;
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (i = 0; i < 16; i++)
		{
			MoveWindow(hBut_[i], (i % 4)*sx / 4, (i / 4)*sy / 4, sx / 4, sy / 4, 1);

		}
		for (int i = 0; i<4; i++)
			MoveWindow(inf_wind[i], (i % 4)*sx / 4, sy, sx / 4, 50, 1);


		EndPaint(hwnd, &ps);
		ShowM(hBut_, mas);

		for (i = 0; i < 15; i++)
		{
			if (mas[i] == i + 1)
			{
				if (i == 14)
				{
					MessageBox(hwnd, "Поздравляю, Вы Победили !", "info_1", MB_OK);
					system("start https://www.youtube.com/watch?v=q3nGTpHS0gA");
				}
			}
			else
				break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0); //корректная обработка окончания сообщения
		break;
	default:
		return
			DefWindowProc(hwnd, message, wParam, lParam);//возврат неотработанного сообщения
	}
	return 0L;
}


void ShowM(HWND hB[], int m[])
{
	for (int i = 0; i < 16; i++)
	{
		if (m[i] != 0)
			sprintf(str, "%d", m[i]);
		else
			strcpy(str, "");
		SetWindowText(hB[i], str);
	}
}


void AStar(int mas[], HWND iw[], HWND hB[])
{
	clock_t clock_start=clock();
	clock_t clock_out;
	int time_1, time_2, time_3;
	int ind = 0, iter = 0, res_of_check = 0;
	int min_trip[4]{ -1,-1,-1,-1 };
	int m_t_f = 10000;
	int adr[4]{ -1,-1,-1,-1 };
	int ila = -1;//iter_last_adr
	LibraryVertex Close;//Закрытый список. Помещаются отработанные комбинации.	
	LibraryVertex* Open=new LibraryVertex[300];//Открытый список. Помещаются все новые комбинации для дальнейшей обработки. Разбит ещё на 300 ячеек для разделения по trip.
	vector <Vertex> Neighbors;//Список заполняется соседями.
	Vertex V_Start;
	memcpy(V_Start.mas, mas, sizeof(V_Start.mas));
	V_Start.dfs = 0;
	V_Start.trip = V_Start.dfs + V_Start.HeDTE();
	Open[V_Start.trip] += V_Start;
	
	while (Open)
	{
		iter++;
		m_t_f = 10000;
		for (int i = 0; i < 300; i++)
			if (Open[i].my_size != 0 && i < m_t_f)//Определение какой минамальный элемент Open из 300 не пуст.
			{
				m_t_f = i;
				i = 299;
			}
		//m_t_f = Open_element_not_empty(Open, m_t_f);
		ila = (Open[m_t_f].last_adr_add.size() - 1);
		//Curr - Комбинация взятая в работу.
		Vertex Curr = Open[m_t_f].list[Open[m_t_f].last_adr_add[ila].adr[0]][Open[m_t_f].last_adr_add[ila].adr[1]][Open[m_t_f].last_adr_add[ila].adr[2]][Open[m_t_f].last_adr_add[ila].adr[3]];

		if (Curr.Check_End())
		{
			ShowSolution(Curr, Close, hB);
			delete[] Open;
			//return Curr.dfs;
		}

		else
		{
			ind = 0;
			Close += Open[m_t_f].list[Open[m_t_f].last_adr_add[ila].adr[0]][Open[m_t_f].last_adr_add[ila].adr[1]][Open[m_t_f].last_adr_add[ila].adr[2]][Open[m_t_f].last_adr_add[ila].adr[3]];			
			Open[m_t_f] -= Open[m_t_f].last_adr_add[ila].adr;
		}
		if (iter % 1000==0)
		{
			clock_start = clock();

			if (iter != 1000)
			{
				double time_4 = (clock_start - clock_out)/1000.00;
				sprintf(str_t, "iter=%d", iter);
				sprintf(str, "1000 iter per \n%g sec", time_4);
				sprintf(str2, "Last adr \n%d %d %d", Curr.mas[0],Curr.mas[4], Curr.mas[9]);
				sprintf(str3, "dfs=%d\ntrip=%d", Curr.dfs,Curr.trip);
			}
			SetWindowText(iw[0], str_t);
			SetWindowText(iw[1], str);
			SetWindowText(iw[2], str2);
			SetWindowText(iw[3], str3);
			clock_out = clock();
		}
		Curr.Get_Neighbors(Neighbors);
		for (int i = 0; i < size(Neighbors);)
		{
			res_of_check = Open[Neighbors[i].trip].Check_In_List(Neighbors[i], adr); 
			if (res_of_check == 0)
				if (Close.Check_In_List(Neighbors[i], adr) == 0)
				{
					int size_laad = 0;
					size_laad = (Close.last_adr_add.size() - 1);
					Neighbors[i].parent = Close.last_adr_add[size_laad];
					Open[Neighbors[i].trip] +=Neighbors[i];
					Neighbors.erase(Neighbors.begin());
				}
				else
					Neighbors.erase(Neighbors.begin());
			else
				if (Neighbors[i].trip < Open[Neighbors[i].trip].list[adr[0]][adr[1]][adr[2]][adr[3]].trip)
				{
					Open[Neighbors[i].trip].list[adr[0]][adr[1]][adr[2]][adr[3]] = Neighbors[i];
					Neighbors.erase(Neighbors.begin());
				}
				else
					Neighbors.erase(Neighbors.begin());
		}
	}
	delete[] Open;
	//return 0;
}

bool SolvabilityTest(int mas[])
{
	int zero = 0;
	int sum = 0;
	for (int i = 0; i < 16; i++)
		if (!mas[i])zero = i / 4 + 1;
		else
			for (int j = i + 1; j < 16; j++)
				if (mas[i] > mas[j] && mas[j])sum++;
	if ((sum + zero) % 2)
		return true;
	else
		return false;
}

