// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000//контроль версии
#pragma once
#endif // _MSC_VER > 1000
//разрешает использовать вин заголовки
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <string.h>
#include <stdio.h>

using namespace std;
#include <stdlib.h>
#include <ctime>
#include <vector>
#include "ADR.h"
#include "Vertex.h"
#include "resource.h"
void ShowM(HWND[], int[]);
#include "LibraryVertex.h"
#include <omp.h>
#include <thread>



LRESULT CALLBACK WFunc(HWND, UINT, WPARAM, LPARAM);



//буффер которым мы будем пользоватьс€
TCHAR str[256] = "";
TCHAR str2[256] = "";
TCHAR str3[256] = "";
TCHAR str_t[256] = "";


void AStar(int[], HWND[], HWND[]);
bool SolvabilityTest(int[]); //ѕроверка на решаемость.




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
