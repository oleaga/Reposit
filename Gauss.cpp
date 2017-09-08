// Gauss.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <windows.h>
#include <time.h>

HANDLE handle;
COORD SizeWin, Pos, StartPos;

int Dist[7]={1,8,25,50,75,93,106};

enum KeyCode
	{
		KDown    = 0x50,
		KUp      = 0x48,
		KLeft    = 0x4b,
		KRight   = 0x4d,
		KEnter   = 0x0d,
		KEsc     = 0x1b,
		KDefault = 0x00,
		KBackspase=0x08
	};

struct TextAttribute
	{
		unsigned char PurpleTextAttr;
		unsigned char YellowTextAttr;
		unsigned char WhiteTextAttr;
		unsigned char GrayTextAttr;
		unsigned char SilverTextAttr;
	} TA;

int shell();
void Preset();
void Pause();
void GetCurPos(COORD *Pos);
void SetCurPos(const COORD *Pos);
void PrintGauss(double *Matr, double *Vect, int N);
void InitGauss3(double *Matr, double *Vect, int N);
void InitGauss5(double *Matr, double *Vect, int N);
void Gauss(double *Matr, double *Vect, int N);

int main()
{
	return shell();
}

int shell()
{
	int N=5;
	double *M=(double *)malloc(sizeof(double)*N*N);
	double *V=(double *)malloc(sizeof(double)*N);
	Preset();
	InitGauss5(M, V, N);
	PrintGauss(M, V, N);
	Pause();
	Gauss(M, V, N);
	PrintGauss(M, V, N);
	//Pause();
	free(M);
	free(V);
	Pause();
	return 0;
}

void Gauss(double *Matr, double *Vect, int N)
{
	int i, j, k;
	double A, B;

	for(i=0; i<N; i++)
	{
		Pos.Y=StartPos.Y + i;
		A = *(Matr + N*i + i);
		for(j=i; j<N; j++)
		{
			*(Matr + N*i + j) = *(Matr + N*i + j)/A;
			
			Pos.X = StartPos.X + j*10 - 1;
			SetCurPos(&Pos);
			printf(" ");
			if(*(Matr + N*i + j)<0)
			{
				SetCurPos(&Pos);
			}
			printf("%.2f", *(Matr + N*i + j));
		}
		Vect[i] = Vect[i]/A;

		Pos.X = StartPos.X + N*10 -1;
		SetCurPos(&Pos);
		printf(" ");
		if(Vect[i]<0)
		{
			SetCurPos(&Pos);
		}
		printf("  %.2f", Vect[i]);
		getch();

		for(k=i+1; k<N; k++)
		{
			Pos.Y=StartPos.Y + k;
			B = *(Matr + N*k + i);
			Vect[k] = Vect[k]/B - Vect[i];
			for(j=i; j<N; j++)
			{
				*(Matr + N*k + j) = *(Matr + N*k + j)/B - *(Matr + N*i + j);
				Pos.X = StartPos.X + j*10 - 1;
				SetCurPos(&Pos);
				printf(" ");
				if(*(Matr + N*k + j)<0)
				{
					SetCurPos(&Pos);
				}
				printf("%.2f", *(Matr + N*k + j));
			}

			Pos.X = StartPos.X + N*10 - 1;
			SetCurPos(&Pos);
			printf(" ");
			if(Vect[k]<0)
			{
				SetCurPos(&Pos);
			}
			printf("  %.2f", Vect[k]);
			getch();
		}
		
		
	}
	for(i=N-1; i>0; i--)
	{
		for(j=i-1; j>-1; j--)
		{
			*(Matr + N*j + i) = 0.0;
			Vect[j] = Vect[j] - *(Matr + N*i + i) * Vect[i];
		}
	}
}

void Preset()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hwnd = GetConsoleWindow();
	
	CONSOLE_SCREEN_BUFFER_INFO CSBI;
	GetConsoleScreenBufferInfo(handle, &CSBI);
	SizeWin=CSBI.dwSize;
	GetCurPos(&StartPos);
	StartPos.X+=2;
	StartPos.Y+=2;

	TA.PurpleTextAttr = 0x0d;
	TA.YellowTextAttr = 0x0e;
	TA.WhiteTextAttr = 0x0f;
	TA.GrayTextAttr = 0x08;
	TA.SilverTextAttr = 0x07;

	SetConsoleTitle(_T("Решение систем уравнений"));
	SetConsoleTextAttribute(handle, TA.SilverTextAttr);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SizeWin.X = 130;
	SizeWin.Y = 240;
	SetConsoleScreenBufferSize(handle,SizeWin);
	MoveWindow(hwnd, 10, 10, 1400, 700,true);
}

void Pause()
{
	printf("\n\n");
	SetConsoleTextAttribute(handle, TA.GrayTextAttr);
	system("pause");
	SetConsoleTextAttribute(handle, TA.SilverTextAttr);
}

void GetCurPos(COORD *Pos)
{
	CONSOLE_SCREEN_BUFFER_INFO CSBI;
	GetConsoleScreenBufferInfo(handle, &CSBI);
	*Pos=CSBI.dwCursorPosition;
}

void SetCurPos(const COORD *Pos)
{
	SetConsoleCursorPosition(handle,*Pos);
}

void PrintGauss(double *Matr, double *Vect, int N)
{
	int i, j;
	double A, B;

	for(i=0; i<N; i++)
	{
		Pos.Y=StartPos.Y + i;
		for(j=0; j<N; j++)
		{
			Pos.X = StartPos.X + j*10;
			if(*(Matr + 3*i + j)<0) Pos.X--;
			SetCurPos(&Pos);
			printf("%.2f", *(Matr + 3*i + j));
		}
		Pos.X = StartPos.X + j*10;
		if(Vect[i]<0) Pos.X--;
		SetCurPos(&Pos);
		printf("  %.2f", Vect[i]);
	}
}

void InitGauss3(double *Matr, double *Vect, int N)
{
	int i,j;
	double Matrix[3][3]={	{2.0, 3.0, 1.0},
							{3.0, -1.0, 2.0},
							{1.0, 4.0, -1.0}};
	double Vector[3]={1.0, 1.0, 2.0 };

	for(i=0; i<3; i++)
	{
		Vect[i]=Vector[i];
		for(j=0; j<3; j++) *(Matr + 3*i + j)=Matrix[i][j];
		
	}
}

void InitGauss5(double *Matr, double *Vect, int N)
{
	int i, j;
	double Matrix[5][5] = { { 1,-1,-1, 2, 1 },
							{ 1, 0,-1, 1,-1 },
							{-1, 1, 2,-1,-2 },
							{ 1, 0, 0, 2,-2 },
							{ 1, 1, 2, 3,-6}};
	double Vector[5] = { 5, 2, -7, 0, 7};

	for (i = 0; i<N; i++)
	{
		Vect[i] = Vector[i];
		for (j = 0; j<3; j++) *(Matr + 3 * i + j) = Matrix[i][j];

	}
}