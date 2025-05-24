#include "allitems.h"

char figures[NFIGURES][7] = {"pawn", "knight", "bishop", "rook", "queen", "king"};
int w_eat[NFIGURES], b_eat[NFIGURES];

void EatFigure(char * type, char COLOR) {
	for (int i = 0; i < NFIGURES; i++) {
			if (strcmp(type, figures[i]) == 0) (COLOR == 'w' ? w_eat[i]++ : b_eat[i]++);
	}
	OutputEatTable(COLOR);
}

void OutputEatTable(char COLOR) {
	setcolor(LIGHTGRAY);
	setbkcolor(BLACK);
	settextstyle(8, 0, 1);
	for (int i = 0, y = (COLOR == 'w' ? MAXH - 20 : 0); i < 6; i++) {
		char buffer[30];
		sprintf(buffer, "%s:", figures[i]);
		outtextxy(MAXH+4, y, buffer);
		sprintf(buffer, "%2d", (COLOR == 'w' ? w_eat[i] : b_eat[i]));
		outtextxy(MAXW-25, y, buffer);
		y += (COLOR == 'w' ? -20 : +20);
	}
}

void SureButton(char ch) {
	Beep(100, 30);
	void *buffer = saverectangle(MAXW/3, MAXH/3, 2*MAXW/3, 2*MAXH/3);

	setfillstyle(1, BLACK);
	bar(MAXW/3, MAXH/3, 2*MAXW/3, 2*MAXH/3);
	setcolor(LIGHTGRAY);
	rectangle(MAXW/3, MAXH/3, 2*MAXW/3, 2*MAXH/3);
	setbkcolor(BLACK);
	settextstyle(8, 0, 1);
	outtextxy(MAXW/3+5, 280, "YES");
	outtextxy(2*MAXW/3-32, 280, "NO");
	if (ch == 'n') {
		outtextxy(MAXW/3+5, MAXH/3+10, "Are you sure? you");
		outtextxy(MAXW/3+35, MAXH/3+30, "want start");
		outtextxy(MAXW/3+60, MAXH/3+50, "new game");
		while (true) {
			int xm = -1, ym = -1;
			getmouseclick(WM_LBUTTONDOWN, xm, ym);
			if (xm != -1) {
				if (xm >= MAXW/3+5 && ym >= 280 && xm <= MAXW/3+40 && ym <= 300) {
					setfillstyle(1, BLACK);
					bar(0, 0, MAXW, MAXH);
					StartGame();
					Beep(100, 30);
					break;
				}
				if (xm >= 2*MAXW/3-32 && ym >= 280 && ym <= 300 && xm <= 2*MAXW/3+3) {
					putrectangle(MAXW/3, MAXH/3, buffer);
					free(buffer);
					Beep(100, 30);
					break;
				}
			}
		}
	} else {
		outtextxy(MAXW/3+5, MAXH/3+10, "Are you sure? you");
		outtextxy(MAXW/3+35, MAXH/3+30, "want exit");
		outtextxy(MAXW/3+65, MAXH/3+50, "game");
		while (true) {
			int xm = -1, ym = -1;
			getmouseclick(WM_LBUTTONDOWN, xm, ym);
			if (xm != -1) {
				if (xm >= MAXW/3+5 && ym >= 280 && xm <= MAXW/3+40 && ym <= 300) {
					Beep(100, 30);
					closegraph();
					exit(0);
				}
				if (xm >= 2*MAXW/3-32 && ym >= 280 && ym <= 300 && xm <= 2*MAXW/3+3) {
					putrectangle(MAXW/3, MAXH/3, buffer);
					free(buffer);
					break;
				}
			}
		}
	}
}

void NewGameButton() {
	readimagefile("Images\\new.bmp", MAXH+10, 3*CELLSIZE, MAXW-10, 4*CELLSIZE-10);
}

void ExitGameButton() {
	readimagefile("Images\\exit.bmp", MAXH+10, 4*CELLSIZE+10, MAXW-10, 5*CELLSIZE);
}

void WriteWhiteMove() {
	setfillstyle(1, BLACK);
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(8, 0, 2);
	outtextxy(MAXH+10, 5*CELLSIZE+36, " WHITE MOVE");
	bar(MAXH+4, 2*CELLSIZE, MAXW, 2*CELLSIZE+50);
}

void WriteBlackMove() {
	setfillstyle(1, BLACK);
	setbkcolor(BLACK);
	setcolor(LIGHTGRAY);
	settextstyle(8, 0, 2);
	outtextxy(MAXH+10, 2*CELLSIZE, " BLACK MOVE");
	bar(MAXH+4, 5*CELLSIZE, MAXW, 6*CELLSIZE);
}

void WriteCheckToWhite() {
	setfillstyle(1, BLACK);
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(8, 0, 2);
	outtextxy(MAXH+6, 5*CELLSIZE+36, "CHECKtoWHITE");
	bar(MAXH+4, 2*CELLSIZE, MAXW, 2*CELLSIZE+50);
}

void WriteCheckToBlack() {
	setfillstyle(1, BLACK);
	setbkcolor(BLACK);
	setcolor(LIGHTGRAY);
	settextstyle(8, 0, 2);
	outtextxy(MAXH+6, 2*CELLSIZE, "CHECKtoBLACK");
	bar(MAXH+4, 5*CELLSIZE, MAXW, 6*CELLSIZE);
}

