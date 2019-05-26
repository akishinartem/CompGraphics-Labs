#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cmath>

#define _USE_MATH_DEFINES
#define round(x) floor((x)+0.5)  

using namespace std;

void Create(double _x1, double _y1, double _x2, double _y2, COLORREF color)
{
	static HDC device = GetDC(GetConsoleWindow());
	int x1 = round(_x1);
	int x2 = round(_x2);
	int y1 = round(_y1);
	int y2 = round(_y2);
	int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
	int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2 = err;
	for (;;)
	{
		SetPixel(device, x1, y1, color);
		if (x1 == x2 && y1 == y2) break;
		e2 = err;
		if (e2 > -dx)
			err -= dy, x1 += sx;
		if (e2 < dy)
			err += dx, y1 += sy;
	}
}

void Umnoj(double x[2][3], double y[3][3])
{
	double temp = 0;
	double z[3][3];
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			z[i][j] = 0;
			for (int k = 0; k < 3; k++)
				z[i][j] += x[i][k] * y[k][j];
		}
	}
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			x[i][j] = z[i][j];
}

int main(void)
{
	double temp[3][3];

	double line[2][3];
	line[0][0] = 10.0;
	line[0][1] = 20.0;
	line[0][2] = 1.0;
	line[1][0] = 10.0;
	line[1][1] = 40.0;
	line[1][2] = 1.0;

	double moveTo[3][3];
	moveTo[0][0] = 1.0;
	moveTo[0][1] = 0.0;
	moveTo[0][2] = 0.0;
	moveTo[1][0] = 0.0;
	moveTo[1][1] = 1.0;
	moveTo[1][2] = 0.0;
	moveTo[2][0] = 0.0;
	moveTo[2][1] = 0.0;
	moveTo[2][2] = 1.0;

	double moveFrom[3][3];
	moveFrom[0][0] = 1.0;
	moveFrom[0][1] = 0.0;
	moveFrom[0][2] = 0.0;
	moveFrom[1][0] = 0.0;
	moveFrom[1][1] = 1.0;
	moveFrom[1][2] = 0.0;
	moveFrom[2][0] = 0.0;
	moveFrom[2][1] = 0.0;
	moveFrom[2][2] = 1.0;

	double moveL[3][3];
	moveL[0][0] = 1.0;
	moveL[0][1] = 0.0;
	moveL[0][2] = 0.0;
	moveL[1][0] = 0.0;
	moveL[1][1] = 1.0;
	moveL[1][2] = 0.0;
	moveL[2][0] = -5.0;
	moveL[2][1] = 0.0;
	moveL[2][2] = 1.0;

	double moveR[3][3];
	moveR[0][0] = 1.0;
	moveR[0][1] = 0.0;
	moveR[0][2] = 0.0;
	moveR[1][0] = 0.0;
	moveR[1][1] = 1.0;
	moveR[1][2] = 0.0;
	moveR[2][0] = 5.0;
	moveR[2][1] = 0.0;
	moveR[2][2] = 1.0;

	double moveT[3][3];
	moveT[0][0] = 1.0;
	moveT[0][1] = 0.0;
	moveT[0][2] = 0.0;
	moveT[1][0] = 0.0;
	moveT[1][1] = 1.0;
	moveT[1][2] = 0.0;
	moveT[2][0] = 0.0;
	moveT[2][1] = -5.0;
	moveT[2][2] = 1.0;

	double moveB[3][3];
	moveB[0][0] = 1.0;
	moveB[0][1] = 0.0;
	moveB[0][2] = 0.0;
	moveB[1][0] = 0.0;
	moveB[1][1] = 1.0;
	moveB[1][2] = 0.0;
	moveB[2][0] = 0.0;
	moveB[2][1] = 5.0;
	moveB[2][2] = 1.0;

	double scaleL[3][3];
	scaleL[0][0] = 0.5;
	scaleL[0][1] = 0.0;
	scaleL[0][2] = 0.0;
	scaleL[1][0] = 0.0;
	scaleL[1][1] = 0.5;
	scaleL[1][2] = 0.0;
	scaleL[2][0] = 0.0;
	scaleL[2][1] = 0.0;
	scaleL[2][2] = 1.0;

	double scaleM[3][3];
	scaleM[0][0] = 2.0;
	scaleM[0][1] = 0.0;
	scaleM[0][2] = 0.0;
	scaleM[1][0] = 0.0;
	scaleM[1][1] = 2.0;
	scaleM[1][2] = 0.0;
	scaleM[2][0] = 0.0;
	scaleM[2][1] = 0.0;
	scaleM[2][2] = 1.0;

	double rotL[3][3];
	rotL[0][0] = cos(-5 * 3.14 / 180);
	rotL[0][1] = sin(-5 * 3.14 / 180);
	rotL[0][2] = 0.0;
	rotL[1][0] = -sin(-5 * 3.14 / 180);
	rotL[1][1] = cos(-5 * 3.14 / 180);
	rotL[1][2] = 0.0;
	rotL[2][0] = 0.0;
	rotL[2][1] = 0.0;
	rotL[2][2] = 1.0;

	double rotR[3][3];
	rotR[0][0] = cos(5 * 3.14 / 180);
	rotR[0][1] = sin(5 * 3.14 / 180);
	rotR[0][2] = 0.0;
	rotR[1][0] = -sin(5 * 3.14 / 180);
	rotR[1][1] = cos(5 * 3.14 / 180);
	rotR[1][2] = 0.0;
	rotR[2][0] = 0.0;
	rotR[2][1] = 0.0;
	rotR[2][2] = 1.0;

	for (;;)
	{
		char c = _getch();
		Create(line[0][0], line[0][1], line[1][0], line[1][1], 0x000000);
		switch (c)
		{
		case 'w':
			Umnoj(line, moveT);
			break;
		case 'a':
			Umnoj(line, moveL);
			break;
		case 's':
			Umnoj(line, moveB);
			break;
		case 'd':
			Umnoj(line, moveR);
			break;
		case 'q':
			moveTo[2][0] = -(line[0][0] + line[1][0]) / 2;
			moveTo[2][1] = -(line[0][1] + line[1][1]) / 2;
			moveFrom[2][0] = -moveTo[2][0];
			moveFrom[2][1] = -moveTo[2][1];
			Umnoj(line, moveTo);
			Umnoj(line, rotL);
			Umnoj(line, moveFrom);
			break;
		case 'e':
			moveTo[2][0] = -(line[0][0] + line[1][0]) / 2;
			moveTo[2][1] = -(line[0][1] + line[1][1]) / 2;
			moveFrom[2][0] = -moveTo[2][0];
			moveFrom[2][1] = -moveTo[2][1];
			Umnoj(line, moveTo);
			Umnoj(line, rotR);
			Umnoj(line, moveFrom);
			break;
		case 'z':
			moveTo[2][0] = -(line[0][0] + line[1][0]) / 2;
			moveTo[2][1] = -(line[0][1] + line[1][1]) / 2;
			moveFrom[2][0] = -moveTo[2][0];
			moveFrom[2][1] = -moveTo[2][1];
			Umnoj(line, moveTo);
			Umnoj(line, scaleM);
			Umnoj(line, moveFrom);
			break;
		case 'x':
			moveTo[2][0] = -(line[0][0] + line[1][0]) / 2;
			moveTo[2][1] = -(line[0][1] + line[1][1]) / 2;
			moveFrom[2][0] = -moveTo[2][0];
			moveFrom[2][1] = -moveTo[2][1];
			Umnoj(line, moveTo);
			Umnoj(line, scaleL);
			Umnoj(line, moveFrom);
			break;
		case 'r':
			return 0;
			break;
		case 'c':
			line[0][0] = 10.0;
			line[0][1] = 20.0;
			line[0][2] = 1.0;
			line[1][0] = 10.0;
			line[1][1] = 40.0;
			line[1][2] = 1.0;
			break;
		}
		Create(line[0][0], line[0][1], line[1][0], line[1][1], 0x00ff00);
	}
}