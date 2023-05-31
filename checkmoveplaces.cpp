#include "allitems.h"

int tt;

void CheckPlace(int ni, int nj) {
	int pi = player.i, pj = player.j;
	bool eating = (f[ni][nj].hereIsFigure);
	cell A = f[pi][pj];
	cell B = f[ni][nj];

	f[ni][nj] = f[pi][pj];
	f[pi][pj] = cell();

	if (!CheckKing(A.getColor())) {
		if (eating)
			eatmove.insert(pair(ni, nj));
		else
			justmove.insert(pair(ni, nj));

		if (tt == 0) PaintRectangle((eating ? RED : GREEN), nj*CELLSIZE, ni*CELLSIZE, nj*CELLSIZE+CELLSIZE, ni*CELLSIZE+CELLSIZE);
	}
	f[pi][pj] = A;
	f[ni][nj] = B;
}

void rookmove() {
	int i = player.i, j = player.j;
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x == 0 && direct_y == 0);
			else if (direct_x == 0 || direct_y == 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) break;
					if (f[ni][nj].hereIsFigure) {
						if (f[ni][nj].getColor() != f[i][j].getColor())
							CheckPlace(ni, nj);
						break;
					} else {
						CheckPlace(ni, nj);
					}
				}
			}
		}
	}
}

void bishopmove() {
	int i = player.i, j = player.j;
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x != 0 && direct_y != 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) break;
					if (f[ni][nj].hereIsFigure) {
						if (f[ni][nj].getColor() != f[i][j].getColor())
							CheckPlace(ni, nj);
						break;
					} else {
						CheckPlace(ni, nj);
					}
				}
			}
		}
	}
}

void knightmove() {
	int i = player.i, j = player.j;
	for (int x = -2; x <= +2; x++) {
		for (int y = -2; y <= +2; y++) {
			if (abs(x * y) == 2) {
				int ni = i + x, nj = j + y;
				if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) continue;
				if (f[ni][nj].hereIsFigure && f[ni][nj].getColor() == f[i][j].getColor()) continue;
				CheckPlace(ni, nj);
			}
		}
	}
}

void kingmove() {
	int i = player.i, j = player.j;
	for (int x = -1; x <= +1; x++) {
		for (int y = -1; y <= +1; y++) {
			if (!(x == 0 && y == 0)) {
				int ni = i + x, nj = j + y;
				if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) continue;
				if (f[ni][nj].hereIsFigure && f[ni][nj].getColor() == f[i][j].getColor()) continue;
				CheckPlace(ni, nj);
			}
		}
	}
	if (f[i][j].getColor() == 'w' && !WhiteKingMoved && !checkw) {
		int ni = CHSIZE - 1, nj = CHSIZE - 1;
		if (!RightWhiteRookMoved && !f[i][j+1].hereIsFigure && !f[i][j+2].hereIsFigure) {
			if (Protected(i, j+1, 'b') && Protected(i, j+2, 'b')) {
				castling.insert(pair(ni, nj));
				if (tt == 0)
					PaintRectangle(YELLOW, nj*CELLSIZE, ni*CELLSIZE, nj*CELLSIZE+CELLSIZE, ni*CELLSIZE+CELLSIZE);
			}
		}
		ni = CHSIZE - 1, nj = 0;
		if (!LeftWhiteRookMoved && !f[i][j-1].hereIsFigure && !f[i][j-2].hereIsFigure && !f[i][j-3].hereIsFigure) {
			if (Protected(i, j-1, 'b') && Protected(i, j-2, 'b') && Protected(i, j-3, 'b')) {
				castling.insert(pair(ni, nj));
				if (tt == 0)
					PaintRectangle(YELLOW, nj*CELLSIZE, ni*CELLSIZE, nj*CELLSIZE+CELLSIZE, ni*CELLSIZE+CELLSIZE);
			}
		}
	}
	if (f[i][j].getColor() == 'b' && !BlackKingMoved && !checkb) {
		int ni = 0, nj = CHSIZE - 1;
		if (!RightBlackRookMoved && !f[i][j+1].hereIsFigure && !f[i][j+2].hereIsFigure) {
			if (Protected(i, j+1, 'w') && Protected(i, j+2, 'w')) {
				castling.insert(pair(ni, nj));
				if (tt == 0)
					PaintRectangle(YELLOW, nj*CELLSIZE, ni*CELLSIZE, nj*CELLSIZE+CELLSIZE, ni*CELLSIZE+CELLSIZE);
			}
		}
		ni = 0, nj = 0;
		if (!LeftBlackRookMoved && !f[i][j-1].hereIsFigure && !f[i][j-2].hereIsFigure && !f[i][j-3].hereIsFigure) {
			if (Protected(i, j-1, 'w') && Protected(i, j-2, 'w') && Protected(i, j-3, 'w')) {
				castling.insert(pair(ni, nj));
				if (tt == 0)
					PaintRectangle(YELLOW, nj*CELLSIZE, ni*CELLSIZE, nj*CELLSIZE+CELLSIZE, ni*CELLSIZE+CELLSIZE);
			}
		}
	}
}

void queenmove() {
	rookmove();
	bishopmove();
}

void pawnmove() {
	int i = player.i, j = player.j;
	int ni = (f[i][j].getColor() == 'w' ? i - 1 : i + 1), nj = j;

	if (ni >= 0 && ni < CHSIZE && !f[ni][nj].hereIsFigure) {
		CheckPlace(ni, nj);
		ni = (f[i][j].getColor() == 'w' ? i - 2 : i + 2), nj = j;
		if ((i == 1 || i == CHSIZE - 2) && ni >= 0 && ni < CHSIZE && !f[ni][nj].hereIsFigure) {
			CheckPlace(ni, nj);
		}
		ni = (f[i][j].getColor() == 'w' ? i - 1 : i + 1), nj = j;
	}

	nj = j - 1;
	if (ni >= 0 && ni < CHSIZE && nj >= 0 && f[ni][nj].hereIsFigure && f[ni][nj].getColor() != f[i][j].getColor()) {
		CheckPlace(ni, nj);
	}

	nj = j + 1;
	if (ni >= 0 && ni < CHSIZE && nj < CHSIZE && f[ni][nj].hereIsFigure && f[ni][nj].getColor() != f[i][j].getColor()) {
		CheckPlace(ni, nj);
	}

	if (f[i][j].getColor() == 'w' && i == CHSIZE / 2 - 1) {
		ni = i; nj = j + 1;
		if (nj < CHSIZE && b_jumppawn[nj] == numberofmovings - 1) {
			CheckPlace(ni, nj);
		}
		ni = i; nj = j - 1;
		if (nj >= 0 && b_jumppawn[nj] == numberofmovings - 1) {
			CheckPlace(ni, nj);
		}
	}
	if (f[i][j].getColor() == 'b' && i == CHSIZE / 2) {
		ni = i; nj = j + 1;
		if (nj < CHSIZE && w_jumppawn[nj] == numberofmovings - 1) {
			CheckPlace(ni, nj);
		}
		ni = i; nj = j - 1;
		if (nj >= 0 && w_jumppawn[nj] == numberofmovings - 1) {
			CheckPlace(ni, nj);
		}
	}
}

void CheckMovePlace() {

	static int lasttime = 0;

	if (player != Player(-1, -1)) {
		if (lasttime == -1) {
			justmove.clear();
			eatmove.clear();
			castling.clear();
			PaintRectangle(LIGHTCYAN, player.j*CELLSIZE, player.i*CELLSIZE, player.j*CELLSIZE+CELLSIZE, player.i*CELLSIZE+CELLSIZE);
			if (strcmp(f[player.i][player.j].getType(), "pawn") == 0) pawnmove();
			else if (strcmp(f[player.i][player.j].getType(), "king") == 0) kingmove();
			else if (strcmp(f[player.i][player.j].getType(), "knight") == 0) knightmove();
			else if (strcmp(f[player.i][player.j].getType(), "rook") == 0) rookmove();
			else if (strcmp(f[player.i][player.j].getType(), "queen") == 0) queenmove();
			else if (strcmp(f[player.i][player.j].getType(), "bishop") == 0) bishopmove();
			lasttime = 1;
		}
	} else {
		lasttime = -1;
	}
}

bool Protected(int ti, int tj, char FROM) {
	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			if (f[i][j].hereIsFigure && f[i][j].getColor() == FROM) {
				if (strcmp(f[i][j].getType(), "pawn") == 0) if (pawnbit(i, j, ti, tj)) return false;
				if (strcmp(f[i][j].getType(), "king") == 0) if (kingbit(i, j, ti, tj)) return false;
				if (strcmp(f[i][j].getType(), "knight") == 0) if (knightbit(i, j, ti, tj)) return false;
				if (strcmp(f[i][j].getType(), "rook") == 0) if (rookbit(i, j, ti, tj)) return false;
				if (strcmp(f[i][j].getType(), "queen") == 0) if (queenbit(i, j, ti, tj)) return false;
				if (strcmp(f[i][j].getType(), "bishop") == 0) if (bishopbit(i, j, ti, tj)) return false;
			}
		}
	}
	return true;
}

bool pawnbit(int i, int j, int ti, int tj) {
	int ni, nj;

	ni = (f[i][j].getColor() == 'w' ? i - 1 : i + 1);

	nj = j - 1;
	if (ni == ti && nj == tj) return true;

	nj = j + 1;
	if (ni == ti && nj == tj) return true;

	return false;
}

bool knightbit(int i, int j, int ti, int tj) {
	for (int x = -2; x <= +2; x++) {
		for (int y = -2; y <= +2; y++) {
			if (abs(x * y) == 2) {
				int ni = i + x, nj = j + y;
				if (ni == ti && nj == tj) return true;
			}
		}
	}
	return false;
}

bool kingbit(int i, int j, int ti, int tj) {
	for (int x = -1; x <= +1; x++) {
		for (int y = -1; y <= +1; y++) {
			if (!(x == 0 && y == 0)) {
				int ni = i + x, nj = j + y;
				if (ni == ti && nj == tj) return true;
			}
		}
	}
	return false;
}

bool rookbit(int i, int j, int ti, int tj) {
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x == 0 && direct_y == 0);
			else if (direct_x == 0 || direct_y == 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE || f[ni][nj].hereIsFigure) break;
					if (ni == ti && nj == tj) return true;
				}
			}
		}
	}
	return false;
}

bool bishopbit(int i, int j, int ti, int tj) {
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x != 0 && direct_y != 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE || f[ni][nj].hereIsFigure) break;
					if (ni == ti && nj == tj) return true;
				}
			}
		}
	}
	return false;
}

bool queenbit(int i, int j, int ti, int tj) {
	return (rookbit(i, j, ti, tj) || bishopbit(i, j, ti, tj));
}
