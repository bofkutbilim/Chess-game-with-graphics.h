#include "allitems.h"

void* saverectangle(int x, int y, int x2, int y2) {
	void *buffer;
	unsigned sz = imagesize(x, y, x2, y2);
	buffer = malloc(sz);
	getimage(x, y, x2, y2, buffer);
	return buffer;
}

void putrectangle(int x, int y, void * buffer) {
	putimage(x, y, buffer, COPY_PUT);
}

char * rezhim_string = "w b ";

void Loading() {
	int S = (MAXH>MAXW?MAXH:MAXW);
	for (int i = 0, x = 0; i < S; i += S/CHSIZE, x++) {
		for (int j = 0, y = 0; j < S; j += S/CHSIZE, y++) {
			if (x % 2 == y % 2)
				readimagefile("Images\\blackcell.bmp", i, j, i+S/CHSIZE, j+S/CHSIZE);
			else
				readimagefile("Images\\whitecell.bmp", i, j, i+S/CHSIZE, j+S/CHSIZE);
		}
	}
	readimagefile("Images\\loading.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(500);
	readimagefile("Images\\loading1.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(100);
	readimagefile("Images\\loading2.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(200);
	readimagefile("Images\\loading3.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(100);
	readimagefile("Images\\loading4.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(300);
	readimagefile("Images\\loading5.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(200);
	readimagefile("Images\\loading6.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(300);
	readimagefile("Images\\loading7.bmp", 1.2*MAXW/8, 2*MAXH/8, 6.8*MAXW/8, 6*MAXH/8); delay(500);

	setfillstyle(1, BLACK);
	bar(0, 0, MAXW, MAXH);
}

void StartGame() {
	REZHIM = 0;
  for (int i = 0; i < NFIGURES; i++) {
		w_eat[i] = b_eat[i] = 0;
  }
  for (int i = 0; i < CHSIZE; i++) {
    for (int j = 0; j < CHSIZE; j++) {
      if (i == 1) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('b');
        f[i][j].setType("pawn");
      } else if (i == CHSIZE - 2) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('w');
        f[i][j].setType("pawn");
      } else if (i == 0 && (j == 1 || j == CHSIZE - 2)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('b');
        f[i][j].setType("knight");
      } else if (i == CHSIZE - 1 && (j == 1 || j == CHSIZE - 2)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('w');
        f[i][j].setType("knight");
      } else if (i == 0 && (j == 0 || j == CHSIZE - 1)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('b');
        f[i][j].setType("rook");
      } else if (i == CHSIZE - 1 && (j == 0 || j == CHSIZE - 1)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('w');
        f[i][j].setType("rook");
      } else if (i == 0 && (j == 2 || j == CHSIZE - 3)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('b');
        f[i][j].setType("bishop");
      } else if (i == CHSIZE - 1 && (j == 2 || j == CHSIZE - 3)) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('w');
        f[i][j].setType("bishop");
      } else if (i == 0 && j == 3) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('b');
        f[i][j].setType("queen");
      } else if (i == 0 && j == 4) {
      	f[i][j].hereIsFigure = true;
      	f[i][j].setColor('b');
      	f[i][j].setType("king");
      } else if (i == CHSIZE - 1 && j == 3) {
        f[i][j].hereIsFigure = true;
        f[i][j].setColor('w');
        f[i][j].setType("queen");
      } else if (i == CHSIZE - 1 && j == 4) {
      	f[i][j].hereIsFigure = true;
      	f[i][j].setColor('w');
      	f[i][j].setType("king");
      } else {
				f[i][j].hereIsFigure = false;
      }
    }
  }
	checkw = checkb = false;
	WhiteKingMoved = BlackKingMoved = false;
	LeftWhiteRookMoved = RightWhiteRookMoved = false;
	LeftBlackRookMoved = RightBlackRookMoved = false;

  ShowMap();
  OutputEatTable('w');
  OutputEatTable('b');
  NewGameButton();
  ExitGameButton();
  WriteWhiteMove();
}

void OutputCell(int i, int j) {
	readimagefile((i%2 == j%2 ? "Images\\whitecell.bmp" : "Images\\blackcell.bmp"), j*CELLSIZE, i*CELLSIZE, j*CELLSIZE+CELLSIZE, i*CELLSIZE+CELLSIZE);
}

void OutputFigure(int i, int j) {
	char fig[100] = "Images\\";

	if (f[i][j].getColor() == 'w') strcat(fig, "white");
    else strcat(fig, "black");

	strcat(fig, f[i][j].getType());

	if (i%2 == j%2) strcat(fig, "inwhite.bmp");
	else strcat(fig, "inblack.bmp");

	readimagefile(fig, j*CELLSIZE, i*CELLSIZE, j*CELLSIZE+CELLSIZE, i*CELLSIZE+CELLSIZE);
}


void PaintRectangle(int COLOR, int x, int y, int x2, int y2) {
	setcolor(COLOR);
	rectangle(x, y, x2, y2);
	rectangle(x+1, y+1, x2-1, y2-1);
	rectangle(x+2, y+2, x2-2, y2-2);
	rectangle(x+3, y+3, x2-3, y2-3);
}

void ClearRectangles() {
	if (tt == 0) {
		for (int it = 0; it < eatmove.size(); it++) {
			int ni = eatmove.at(it).first;
			int nj = eatmove.at(it).second;
			if (f[ni][nj].hereIsFigure) {
				OutputFigure(ni, nj);
			} else {
				OutputCell(ni, nj);
			}
		}
		for (int it = 0; it < justmove.size(); it++) {
			int ni = justmove.at(it).first;
			int nj = justmove.at(it).second;
			if (f[ni][nj].hereIsFigure) {
				OutputFigure(ni, nj);
			} else {
				OutputCell(ni, nj);
			}
		}
		for (int it = 0; it < castling.size(); it++) {
			int ni = castling.at(it).first;
			int nj = castling.at(it).second;
			if (f[ni][nj].hereIsFigure) {
				OutputFigure(ni, nj);
			} else {
				OutputCell(ni, nj);
			}
		}
		OutputCell(player.i, player.j);
	}
	castling.clear();
	eatmove.clear();
	justmove.clear();
}

void ShowMap() {
  for (int i = 0; i < CHSIZE; i++) {
    for (int j = 0; j < CHSIZE; j++) {
			if (f[i][j].hereIsFigure) {
        OutputFigure(i, j);
      } else {
				OutputCell(i, j);
      }
      Beep(80, 1);
      delay(40);
    }
  }
}


void Control() {
	bool _exit = false;
	do {

		if (REZHIM != -1) CheckMovePlace();

		//
		int xm = -1, ym = -1, ti, tj;
		getmouseclick(WM_RBUTTONDOWN, xm, ym);
		if (xm != -1) {
			if (REZHIM != -1 && REZHIM % 2) {
				REZHIM = ((REZHIM - 1) % 4 + 4) % 4;
				ClearRectangles();
				OutputFigure(player.i, player.j);
				player = Player(-1, -1);
			}
		}

		xm = -1, ym = -1;
		getmouseclick(WM_LBUTTONDOWN, xm, ym);
		if (xm != -1) {
			if (xm < MAXH && ym < MAXH) {
				if (REZHIM != -1) {
					switch (REZHIM % 2) {
						case 0:
							ti = ym / CELLSIZE;
							tj = xm / CELLSIZE;
							if (f[ti][tj].hereIsFigure && f[ti][tj].getColor() == rezhim_string[REZHIM]) {
								player = Player(ti, tj);
								REZHIM = (REZHIM + 1) % 4;
							}
							break;
						case 1:
							ti = ym / CELLSIZE;
							tj = xm / CELLSIZE;
							Moving(ti, tj);
							break;
					};
				}
			} else if (xm > MAXH+10 && xm < MAXW-10 && ym > 3*CELLSIZE && ym < 4*CELLSIZE-10) {
				SureButton('n');
			} else if (xm > MAXH+10 && xm < MAXW-10 && ym > 4*CELLSIZE+10 && ym < 5*CELLSIZE) {
				SureButton('e');
			}
		}

	} while (_exit == false);
}

