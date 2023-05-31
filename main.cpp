#include "allitems.h"

cell f[CHSIZE][CHSIZE];
setpair justmove, eatmove, castling;

int REZHIM;
Player player = Player(-1, -1);

int main() {
	srand(time(NULL));
	int GRDR, GRMOD, result;
	GRDR = DETECT;
	initgraph(&GRDR, &GRMOD, "");
	result = graphresult();
	if (result != grOk) {
		puts("ERROR!");
		return 0;
	}

	Loading();
	StartGame();
	Control();

	getch();
	closegraph();
	return 0;
}
