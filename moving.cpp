#include "allitems.h"

int numberofmovings, w_jumppawn[CHSIZE], b_jumppawn[CHSIZE];
bool checkw, checkb;
bool WhiteKingMoved, BlackKingMoved;
bool LeftWhiteRookMoved, RightWhiteRookMoved;
bool LeftBlackRookMoved, RightBlackRookMoved;

void melody() {
	Beep(329,30);
	Beep(493,30);
	Beep(698,30);
	Beep(659,60);

	Beep(783,30);
	Beep(698,30);
	Beep(659,60);

	Beep(329,10);
	Beep(493,30);
	Beep(698,30);
	Beep(659,60);

	Beep(392,25);
	Beep(440,20);
	Beep(587,30);

	Beep(349,25);
	Beep(587,50);

	Beep(329,30);
	Beep(493,30);
	Beep(698,30);
	Beep(659,60);

	Beep(783,30);
	Beep(698,30);
	Beep(659,60);

	Beep(329,10);
	Beep(493,30);
	Beep(698,30);
	Beep(659,60);

	Beep(392,25);
	Beep(440,20);
	Beep(587,30);

	Beep(349,25);
	Beep(587,40);
}

void Result(char * file) {
	static void* buffer = saverectangle(2*CELLSIZE, 2*CELLSIZE, 6*CELLSIZE, 6*CELLSIZE);
	readimagefile(file, 2*CELLSIZE, 2*CELLSIZE, 6*CELLSIZE, 6*CELLSIZE);
	melody();
	delay(3000);
	putrectangle(2*CELLSIZE, 2*CELLSIZE, buffer);
	free(buffer);
}

void Moving(int ti, int tj) {
	if (!eatmove.count(pair(ti, tj)) && !justmove.count(pair(ti, tj)) && !castling.count(pair(ti, tj))) return;
	int pi = player.i, pj = player.j;
	if (eatmove.count(pair(ti, tj))) {
		EatFigure(f[pi][pj].getType(), f[ti][tj].getColor());
	}
	Beep(100, 100);

	// 2 POSITION
	if (castling.count(pair(ti, tj))) {
		if (ti == CHSIZE - 1) {
			WhiteKingMoved = true;
			if (tj == CHSIZE - 1) {
				RightWhiteRookMoved = true;
				f[pi][pj + 2] = f[pi][pj];
				f[ti][tj - 2] = f[ti][tj];
				OutputFigure(pi, pj + 2);
				OutputFigure(ti, tj - 2);
			} else if (tj == 0) {
				LeftWhiteRookMoved = true;
				f[pi][pj - 2] = f[pi][pj];
				f[ti][tj + 3] = f[ti][tj];
				OutputFigure(pi, pj - 2);
				OutputFigure(ti, tj + 3);
			}
		} else {
			BlackKingMoved = true;
			if (tj == CHSIZE - 1) {
				RightBlackRookMoved = true;
				f[pi][pj + 2] = f[pi][pj];
				f[ti][tj - 2] = f[ti][tj];
				OutputFigure(pi, pj + 2);
				OutputFigure(ti, tj - 2);
			} else if (tj == 0) {
				LeftBlackRookMoved = true;
				f[pi][pj - 2] = f[pi][pj];
				f[ti][tj + 3] = f[ti][tj];
				OutputFigure(pi, pj - 2);
				OutputFigure(ti, tj + 3);
			}
		}
		f[pi][pj] = f[ti][tj] = cell();
		OutputCell(pi, pj);
		OutputCell(ti, tj);
	} else {
		if (strcmp(f[pi][pj].getType(), "king") == 0) {
			if (f[pi][pj].getColor() == 'w') WhiteKingMoved = true;
			else BlackKingMoved = true;
		}
		if (strcmp(f[pi][pj].getType(), "rook") == 0) {
			if (f[pi][pj].getColor() == 'b') {
				if (pi == 0 && pj == 0) LeftBlackRookMoved = true;
				if (pi == 0 && pj == CHSIZE - 1) RightBlackRookMoved = true;
			} else {
				if (pi == CHSIZE - 1 && pj == 0) LeftWhiteRookMoved = true;
				if (pi == CHSIZE - 1 && pj == CHSIZE - 1) RightBlackRookMoved = true;
			}
		}

		if (strcmp(f[pi][pj].getType(), "pawn") == 0 && pi == ti) {
			if (pi == CHSIZE / 2) {
				f[ti+1][tj] = f[pi][pj];
				OutputFigure(ti+1, tj);
			} else if (pi == CHSIZE / 2 - 1) {
				f[ti-1][tj] = f[pi][pj];
				OutputFigure(ti-1, tj);
			}
			f[pi][pj] = f[ti][tj] = cell();
			OutputCell(pi, pj);
			OutputCell(ti, tj);
		} else {
			f[ti][tj] = f[pi][pj];

			if (strcmp(f[pi][pj].getType(), "pawn") == 0 && abs(ti - pi) == 2) {
				(pi == 1 ? b_jumppawn[tj] = numberofmovings : w_jumppawn[tj] = numberofmovings);
			}

			if (strcmp(f[pi][pj].getType(), "pawn") == 0 && ((f[pi][pj].getColor() == 'w' && ti == 0) || (f[pi][pj].getColor() == 'b' && ti == CHSIZE - 1))) {
				if (ti == 0) {
					readimagefile("Images\\whitequeeninwhite.bmp", tj*CELLSIZE, ti*CELLSIZE, tj*CELLSIZE+CELLSIZE, ti*CELLSIZE+CELLSIZE);
					readimagefile("Images\\whiteknightinwhite.bmp", tj*CELLSIZE, (ti+1)*CELLSIZE, tj*CELLSIZE+CELLSIZE, (ti+1)*CELLSIZE+CELLSIZE);
					PaintRectangle(WHITE, tj*CELLSIZE, ti*CELLSIZE, tj*CELLSIZE+CELLSIZE, ti*CELLSIZE+CELLSIZE);
					PaintRectangle(WHITE, tj*CELLSIZE, (ti+1)*CELLSIZE, tj*CELLSIZE+CELLSIZE, (ti+1)*CELLSIZE+CELLSIZE);
				} else {
					readimagefile("Images\\blackqueeninwhite.bmp", tj*CELLSIZE, ti*CELLSIZE, tj*CELLSIZE+CELLSIZE, ti*CELLSIZE+CELLSIZE);
					readimagefile("Images\\blackknightinwhite.bmp", tj*CELLSIZE, (ti-1)*CELLSIZE, tj*CELLSIZE+CELLSIZE, (ti-1)*CELLSIZE+CELLSIZE);
					PaintRectangle(WHITE, tj*CELLSIZE, ti*CELLSIZE, tj*CELLSIZE+CELLSIZE, ti*CELLSIZE+CELLSIZE);
					PaintRectangle(WHITE, tj*CELLSIZE, (ti-1)*CELLSIZE, tj*CELLSIZE+CELLSIZE, (ti-1)*CELLSIZE+CELLSIZE);
				}
				while (true) {
					int xm = -1, ym = -1;
					getmouseclick(WM_LBUTTONDOWN, xm, ym);
					if (xm != -1) {
						if (ti == 0) {
							if (xm > tj*CELLSIZE && xm < tj*CELLSIZE+CELLSIZE && ym > ti*CELLSIZE && ym < ti*CELLSIZE+CELLSIZE) {
								f[ti][tj].setType("queen"); break;
							}
							else if (xm > tj*CELLSIZE && xm < tj*CELLSIZE+CELLSIZE && ym > (ti+1)*CELLSIZE && ym < (ti+1)*CELLSIZE+CELLSIZE) {
								f[ti][tj].setType("knight"); break;
							}
						} else {
							if (xm > tj*CELLSIZE && xm < tj*CELLSIZE+CELLSIZE && ym > ti*CELLSIZE && ym < ti*CELLSIZE+CELLSIZE) {
								f[ti][tj].setType("queen"); break;
							}
							else if(xm > tj*CELLSIZE && xm < tj*CELLSIZE+CELLSIZE && ym > (ti-1)*CELLSIZE && ym < (ti-1)*CELLSIZE+CELLSIZE) {
								f[ti][tj].setType("knight"); break;
							}
						}
					}
				}
			}
			OutputFigure(ti, tj);

			f[pi][pj] = cell();
			OutputCell(pi, pj);
		}
	}

	++numberofmovings;


	REZHIM = (REZHIM + 1) % 4;

	ClearRectangles();

	if (REZHIM < 2) {
		if (CheckKing('w')) {
			if (!CanMoveAnywhere('w')) {
				Result("Images\\blackwins.bmp");
				REZHIM = -1;
			} else {
				WriteCheckToWhite();
				checkw = true;
				Beep(100, 600);
			}
		} else {
			if (!CanMoveAnywhere('w')) {
				Result("Images\\draw.bmp");
				REZHIM = -1;
			} else {
				WriteWhiteMove();
				checkw = false;
			}
		}
	} else {
		if (CheckKing('b')) {
			if (!CanMoveAnywhere('b')) {
				Result("Images\\whitewins.bmp");
				REZHIM = -1;
			} else {
				WriteCheckToBlack();
				checkb = true;
				Beep(100, 600);
			}
		} else {
			if (!CanMoveAnywhere('b')) {
				Result("Images\\draw.bmp");
				REZHIM = -1;
			} else {
				WriteBlackMove();
				checkb = false;
			}
		}
	}

	player = Player(-1, -1);
}
