#include <iostream>
#include <math.h>
#include <graphics.h>

using namespace std;

void Create(float _x1, float _y1, float _x2, float _y2) {
    int x1 = round(_x1);
    int y1 = round(_y1);
    int x2 = round(_x2);
    int y2 = round(_y2);

    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int er2 = err;

    for(;;) {
        putpixel(x1, y1, 2);
        if(x1 == x2 && y1 == y2) break;
        er2 = err;
        if(er2 > -dx) {err -= dy; x1 += sx;}
        if(er2 < dy) {err += dx; y1 += sy;}
    }
}

void Umnoj (float *A, float *M, float *B) {
    int i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            B[i*3 + j] = 0;
            for(int k = 0; k < 3; k++) {
                B[i * 3 + j] += A[i * 3 + k] * M[k * 3 + j];
			}
        }
	}
}

void Ravn (float *A, float *B) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            A[i * 3 + j] = B[i * 3 + j];
		}
	}
}

void Pov (float alpha, float *MR, float *MD, float *B, float *A) {
    float tmp1[9];
    float tmp2[9];

    MR[0] = cos(alpha);
    MR[1] = sin(alpha);
    MR[3] = -sin(alpha);
    MR[4] = cos(alpha);
    MD[6] = -((A[0] + A[3] + A[6]) / 3);
    MD[7] = -((A[1] + A[4] + A[7]) / 3);
    Umnoj(MD, MR, tmp1);

    MD[6] = (A[0] + A[3] + A[6]) / 3;
    MD[7] = (A[1] + A[4] + A[7]) / 3;
    Umnoj(tmp1, MD, tmp2);
    Umnoj(A, tmp2, B);
    Ravn(A, B);
}

void Mash (float k, float *MS, float *MD, float *B, float *A) {
    float tmp1[9];
    float tmp2[9];
    MS[0] = k;
    MS[4] = k;
    MD[6] = -((A[0] + A[3] + A[6]) / 3);
    MD[7] = -((A[1] + A[4] + A[7]) / 3);
    Umnoj(MD, MS, tmp1);

    MD[6] = (A[0] + A[3] + A[6]) / 3;
    MD[7] = (A[1] + A[4] + A[7]) / 3;
    Umnoj(tmp1, MD, tmp2);
    Umnoj(A, tmp2, B);
    Ravn(A, B);
}

void Nach(float *A, float *B) {
    A[0] = 300; A[1] = 200; A[2] = 1;
    A[3] = 300; A[4] = 300; A[5] = 1;
    A[6] = 350; A[7] = 250; A[8] = 1;
    Ravn(B,A);
}

void Dvij(int dx, int dy, float *pA, float *pMD, float *pB) {
    pMD[6] = dx;
    pMD[7] = dy;
    Umnoj(pA, pMD, pB);
    Ravn(pA, pB);
}

void Zakr(float *B) {
	float minX = B[0];
	float maxX = minX;
	float minY = B[1];
	float maxY = minY;

	for (int i = 1; i < 5; i++) {
		if (B[i * 3] < minX) {
			minX = B[i * 3];
		}
		else if (B[i * 3] > maxX) {
			maxX = B[i * 3];
		}
		if (B[i * 3 + 1] < minY) {
			minY = B[i * 3 + 1];
		}
		else if (B[i * 3 + 1] > maxY) {
			maxY = B[i * 3 + 1];
		}
	}
	int x1, x2;

	for (int y = minY; y < maxY; y++) {
		for (int x = minX; x < maxX; x++) {
			if (getpixel(x, y) > 0) {
				x1 = x2 = x;
				if (getpixel(x + 1, y) > 0) {
					x++;
					while (getpixel(x + 1, y) > 0) {
						x++;
					}
				}
				while (x < maxX) {
					if (getpixel(++x, y) > 0) {
						x2 = x;
						break;
					}
				}
				while (x1 < x2) {
					putpixel(++x1, y, 2);
				}
			}
		}
	}
}

void Ris(float *B) {
    Create(B[0], B[1], B[3], B[4]);
    Create(B[3], B[4], B[6], B[7]);
    Create(B[6], B[7], B[0], B[1]);
    Zakr(B);
}

int Main() {
    int driver, mode;
    float A[9];
    float B[9];
    float MD[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    float MS[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 1 };
    float MR[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 1 };
    Nach(A, B);

    driver = DETECT;
    mode = 0;

    initgraph(&driver, &mode, " " );
    setbkcolor(0);
    cleardevice();

    while(1) {
        Ris(B);
        char c = getch();
        switch(c) {
            case 'w': Dvij(0, -5, A, MD, B); break;
            case 's': Dvij(0, 5, A, MD, B); break;
            case 'a': Dvij(-5, 0, A, MD, B); break;
            case 'd': Dvij(5, 0, A, MD, B); break;

            case 'q': Pov(-0.1, MR, MD, B, A); break;
            case 'e': Pov(0.1, MR, MD, B, A); break;

            case 'r': Mash(1.1, MS, MD, B, A); break;
            case 'f': Mash(0.9, MS, MD, B, A); break;

            case 'o': Nach(A, B); break;
        }
        if(c == 27) break;
        cleardevice();
    }
    closegraph();
    return 0;
}