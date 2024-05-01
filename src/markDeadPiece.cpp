#include "../include/global.h"
#define mark true
#define cancelMark false
typedef bool operation;

extern Move moves[MAXMOVE];
static Situ tmp;
bool isMarked[Size][Size];

void markDead(int x, int y, Color color, operation op);
void remove(int x, int y);

void startMark(Situ now) {
	tmp = now;
	memset(isMarked, 0, sizeof isMarked);
}

void selectDead(int x, int y)
{
	if(tmp.board[x][y] == blank) {
		return;
	}
	if(!isMarked[x][y]) {
		markDead(x, y, tmp.board[x][y], mark);
	} else {
		markDead(x, y, tmp.board[x][y], cancelMark);
	}
}

void confirmMark(Situ *now) {
	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			if(isMarked[i][j]) {
				remove(i, j);
			}
		}
	}
	*now = tmp;
}

void markDead(int x, int y, Color color, operation op)
{
	if(x<0 || y<0 || x>=Size || y>=Size) {
		return;
	}
	if(tmp.board[x][y] != color && tmp.board[x][y] != blank) {
		return;
	}

	if(op == mark) {
		if(isMarked[x][y]) {
			return;
		}
		isMarked[x][y] = true;
		if(tmp.board[x][y] == black) {
			tmp.deadBlack ++;
			drawMark(x, y, white);
		} else if(tmp.board[x][y] == white) {
			tmp.deadWhite ++;
			drawMark(x, y, black);
		}
	} else {
		if(!isMarked[x][y]) {
			return;
		}
		isMarked[x][y] = false;
		if(tmp.board[x][y] == black) {
			tmp.deadBlack --;
			drawMark(x, y, black);
		} else if(tmp.board[x][y] == white) {
			tmp.deadWhite --;
			drawMark(x, y, white);
		}
	}

	for(int i=0; i<4; i++) {
		markDead(x+dx[i], y+dy[i], color, op);
	}
}

void remove(int x0, int y0) {
	if(!moves[tmp.pieces[x0][y0]].exist) {
		return;
	}
	moves[tmp.pieces[x0][y0]].exist = false;

	for(int i=0; i<4; i++) {
		int x = x0 + dx[i], y = y0 + dy[i];
		if(x<0 || y<0 || x>=Size || y>=Size) {
			continue;
		}
		if(tmp.board[x][y] == tmp.board[x][y]) {
			remove(x, y);
		}
	}

	tmp.board[x0][y0] = blank;
}