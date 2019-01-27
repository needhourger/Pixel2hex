#include<EasyX.h>
#include<string>
#include<iostream>
#define PIXEL 30
#define n 8
using namespace std;

char map[10][10] = {'0'};

struct BUTTOM {
	int left;
	int right;
	int top;
	int bottom;
	BUTTOM() {
		left = 240;
		top = 300;
		right = 300;
		bottom = 330;
	}
};

struct BOX {
	int left;
	int right;
	int top;
	int bottom;
	COLORREF color;
	BOX() {}
	BOX(int a, int b, int c, int d) {
		left = a;
		top = b;
		right = c;
		bottom = d;
	}
};
BOX Bmap[10][10];

void generate() {
	char temp[4];
	long ans[16];
	int i = 1, j = 1;
	int p = 0;
	string msg="                    ";
	while (i <= n) {
		while (j <= n) {
			temp[0] = map[i + 1][j + 1];
			temp[1] = map[i + 1][j];
			temp[2] = map[i][j + 1];
			temp[3] = map[i][j];
			j += 2;
			ans[p++] = strtol(temp, NULL, 2);
		}
		i += 2;
		j = 1;
	}
	p--;
	i = 0;
	while (p >= 0) {
		switch (ans[p--]) {
			case 0: msg[i++] = '0'; break;
			case 1: msg[i++] = '1'; break;
			case 2: msg[i++] = '2'; break;
			case 3: msg[i++] = '3'; break;
			case 4: msg[i++] = '4'; break;
			case 5: msg[i++] = '5'; break;
			case 6: msg[i++] = '6'; break;
			case 7: msg[i++] = '7'; break;
			case 8: msg[i++] = '8'; break;
			case 9: msg[i++] = '9'; break;
			case 10: msg[i++] = 'A'; break;
			case 11: msg[i++] = 'B'; break;
			case 12: msg[i++] = 'C'; break;
			case 13: msg[i++] = 'D'; break;
			case 14: msg[i++] = 'E'; break;
			case 15: msg[i++] = 'F'; break;
		}
	}
		
	outtextxy(10, 300, "½á¹û£º");
	outtextxy(60, 300, msg.c_str());
}

int main() {
	BUTTOM b;
	initgraph(311, 340,0);
	int x = PIXEL/4;
	int y = PIXEL/4;
	int i = 1;
	int j = 1;
	while (i <= 8) {
		while (j <= 8) {
			fillrectangle(x, y, x + PIXEL, y + PIXEL);
			Bmap[i][j]=BOX(x, y, x + PIXEL, y + PIXEL);
			Bmap[i][j].color = getfillcolor();
			map[i][j] = '0';
			y = y + PIXEL + PIXEL / 4;
			j++;
		}
		i++;
		x = x + PIXEL + PIXEL / 4;
		y = PIXEL/4;
		j = 1;
	}
	setfillcolor(BLACK);
	fillrectangle(b.left, b.top, b.right, b.bottom);
	outtextxy(b.left + 10, b.top + 6, "Clear");
	setfillcolor(WHITE);

	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		switch (m.uMsg) {
		case WM_LBUTTONDOWN: 
			if (m.x >= b.left && m.x <= b.right && m.y <= b.bottom && m.y >= b.top) {
				setfillcolor(WHITE);
				cout << "clear" << endl;
				for (i=1;i<=8;i++)
					for (j = 1; j <= 8; j++) {
						Bmap[i][j].color = WHITE;
						fillrectangle(Bmap[i][j].left, Bmap[i][j].top, Bmap[i][j].right, Bmap[i][j].bottom);
						map[i][j] = '0';
					}
				generate();
			}
			else {
				i = 1;
				j = 1;
				while (Bmap[i][j].left <= m.x && i <= 8) i++;
				i--;
				while (Bmap[i][j].top <= m.y && j <= 8) j++;
				j--;
				BOX t = Bmap[i][j];
				if (Bmap[i][j].color == WHITE) {
					setfillcolor(GREEN);
					map[i][j] = '1';
				}
				if (Bmap[i][j].color == GREEN) {
					setfillcolor(WHITE);
					map[i][j] = '0';
				}
				fillrectangle(t.left, t.top, t.right, t.bottom);
				Bmap[i][j].color = getfillcolor();
				generate();
			}
		break;
		}
	}
	return 0;
}