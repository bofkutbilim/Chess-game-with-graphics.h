#include "allitems.h"

bool pawneatking(int i, int j) {
	int ni, nj;

	ni = (f[i][j].getColor() == 'w' ? i - 1 : i + 1);

	nj = j - 1;
	if (ni >= 0 && ni < CHSIZE && nj >= 0) {
		if (f[ni][nj].hereIsFigure)
			if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
				return true;
	}

	nj = j + 1;
	if (ni >= 0 && ni < CHSIZE && nj < CHSIZE) {
		if (f[ni][nj].hereIsFigure)
			if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
				return true;
	}
	return false;
}

bool knighteatking(int i, int j) {
	for (int x = -2; x <= +2; x++) {
		for (int y = -2; y <= +2; y++) {
			if (abs(x * y) == 2) {
				int ni = i + x, nj = j + y;
				if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) continue;
				if (f[ni][nj].hereIsFigure) {
					if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
						return true;
				}
			}
		}
	}
	return false;
}

bool kingeatking(int i, int j) {
	for (int x = -1; x <= +1; x++) {
		for (int y = -1; y <= +1; y++) {
			if (!(x == 0 && y == 0)) {
				int ni = i + x, nj = j + y;
				if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) continue;
				if (f[ni][nj].hereIsFigure) {
					if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
						return true;
				}
			}
		}
	}
	return false;
}

bool rookeatking(int i, int j) {
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x == 0 && direct_y == 0);
			else if (direct_x == 0 || direct_y == 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) break;
					if (f[ni][nj].hereIsFigure) {
						if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
							return true;
						break;
					}
				}
			}
		}
	}
	return false;
}

bool bishopeatking(int i, int j) {
	for (int direct_x = -1; direct_x <= 1; direct_x++) {
		for (int direct_y = -1; direct_y <= 1; direct_y++) {
			if (direct_x != 0 && direct_y != 0) {
				for (int x = direct_x, y = direct_y; ; x += direct_x, y += direct_y) {
					int ni = i + x, nj = j + y;
					if (ni < 0 || ni >= CHSIZE || nj < 0 || nj >= CHSIZE) break;
					if (f[ni][nj].hereIsFigure) {
						if (strcmp(f[ni][nj].getType(), "king") == 0 && f[ni][nj].getColor() != f[i][j].getColor())
							return true;
						break;
					}
				}
			}
		}
	}
	return false;
}

bool queeneatking(int i, int j) {
	return (rookeatking(i, j) || bishopeatking(i, j));
}

bool CanItEatKing(int i, int j) {
	if (strcmp(f[i][j].getType(), "pawn") == 0) return pawneatking(i, j);
	if (strcmp(f[i][j].getType(), "knight") == 0) return knighteatking(i, j);
	if (strcmp(f[i][j].getType(), "rook") == 0) return rookeatking(i, j);
	if (strcmp(f[i][j].getType(), "bishop") == 0) return bishopeatking(i, j);
	if (strcmp(f[i][j].getType(), "king") == 0) return kingeatking(i, j);
	if (strcmp(f[i][j].getType(), "queen") == 0) return queeneatking(i, j);
}

bool CheckKing(char COLOR) {
	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			if (f[i][j].hereIsFigure == true && f[i][j].getColor() != COLOR && CanItEatKing(i, j))
				return true;
		}
	}
	return false;
}

bool CanMoveAnywhere(char COLOR) {
	tt = 1;
	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			if (f[i][j].hereIsFigure == true && f[i][j].getColor() == COLOR) {
				player.i = i;
				player.j = j;

				if (strcmp(f[i][j].getType(), "pawn") == 0) pawnmove();
				else if (strcmp(f[i][j].getType(), "king") == 0) kingmove();
				else if (strcmp(f[i][j].getType(), "knight") == 0) knightmove();
				else if (strcmp(f[i][j].getType(), "rook") == 0) rookmove();
				else if (strcmp(f[i][j].getType(), "queen") == 0) queenmove();
				else if (strcmp(f[i][j].getType(), "bishop") == 0) bishopmove();

				if (eatmove.size() > 0 || justmove.size() > 0) {
					ClearRectangles();
					tt = 0;
					return true;
				}
			}
		}
	}
	tt = 0;
	return false;
}
