#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <graphics.h>
#include <assert.h>
#include <time.h>

#define CHSIZE 8
#define MAXH 480
#define MAXW 640
#define CELLSIZE 60
#define NFIGURES 6

struct Player {
	int i, j;
	int x, y;
	Player() {}
	Player(int _i, int _j) {
		i = _i, j = _j, x = _j * CELLSIZE, y = _i * CELLSIZE;
	}
	bool operator == (Player ss) {
		return (i == ss.i && j == ss.j && x == ss.x && y == ss.y);
	}
	bool operator != (Player ss) {
		return !(*this == ss);
	}
};

extern int REZHIM;
extern Player player;

// face.cpp
void* saverectangle(int, int, int, int);
void putrectangle(int, int, void*);
void Loading();
void PaintRectangle(int, int, int, int, int);
void OutputCell(int, int);
void OutputFigure(int, int);
void ClearRectangles();
void StartGame();
void ShowMap();
void Control();

struct cell {
	public:
		bool hereIsFigure;
		void setColor(char ch) {
			chcolor = ch;
		}
		char getColor() {
			return chcolor;
		}
		char * getType() {
			return type;
		}
		void setType(char * t) {
			strcpy(type, t);
		}
		cell () {hereIsFigure = false; type[0] = '\0';}
	private:
		char chcolor;
		char type[64];
};
extern cell f[CHSIZE][CHSIZE];

struct pair {
	int first, second;
	pair() {}
	pair(int _first, int _second) {first = _first; second = _second;}
	bool operator == (pair x) {
		return (first == x.first && second == x.second);
	}
};

struct setpair {
	pair a[100];
	size_t setsize = 0;
	void clear() {
		setsize = 0;
	}
	size_t size() {
		return setsize;
	}
	bool count(pair x) {
		for (int i = 0; i < setsize; i++) {
			if (a[i] == x) return true;
		}
		return false;
	}
	void insert(pair x) {
		if (!count(x)) {
			a[setsize++] = x;
		}
	}
	pair at(int it) {
		assert(it < size());
		return a[it];
	}
};
extern setpair justmove, eatmove, castling;

// checkmoveplaces.cpp
extern int tt;
void CheckPlace(int, int);
void rookmove();
void bishopmove();
void knightmove();
void kingmove();
void queenmove();
void pawnmove();
void CheckMovePlace();
bool Protected(int, int, char);
bool rookbit(int,int,int,int);
bool bishopbit(int,int,int,int);
bool knightbit(int,int,int,int);
bool kingbit(int,int,int,int);
bool queenbit(int,int,int,int);
bool pawnbit(int,int,int,int);

// moving.cpp
extern int numberofmovings;
extern int w_jumppawn[CHSIZE], b_jumppawn[CHSIZE];
extern bool BlackKingMoved, WhiteKingMoved;
extern bool LeftBlackRookMoved, RightBlackRookMoved;
extern bool LeftWhiteRookMoved, RightWhiteRookMoved;
void Moving(int, int);

// rightside.cpp
extern int w_eat[NFIGURES], b_eat[NFIGURES];
void EatFigure(char*, char);
void OutputEatTable(char);
void SureButton(char );
void NewGameButton();
void ExitGameButton();
void WriteWhiteMove();
void WriteBlackMove();
void WriteCheckToWhite();
void WriteCheckToBlack();

// checkmate.cpp
extern bool checkw, checkb;
bool CanItEatKing(int, int);
bool CheckKing(char);
bool CanMoveAnywhere(char);

void* saverectangle(int, int, int, int);
void putrectangle(int, int, void *);
