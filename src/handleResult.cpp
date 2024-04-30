#include "../include/global.h"
static bool vis[Size][Size];
int sumB, sumW; //总目数
int totB, totW; //棋块数
double diff;
Color winner;
Rule rule;

void countResult(Color board[][Size]);
void search(int x, int y, Color color, Color board[][Size]);
void count(Color color, Color now);
void calResult(int deadB, int deadW);

void handleResult(Situ finalSitu, Rule goRule)
{
	memset(vis, 0, sizeof vis);
	sumB = sumW = totB = totW = 0;
	diff = 0;
	rule = goRule;
	countResult(finalSitu.board);
	calResult(finalSitu.deadBlack, finalSitu.deadWhite);
	showResult(winner, diff);
}

void countResult(Color board[][Size])
{
	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			if(vis[i][j] || board[i][j] == blank) {
				continue;
			}
			if(board[i][j] == black) {
				totB++;
			} else {
				totW++;
			}
			search(i, j, board[i][j], board);
		}
	}
}

// 使用深度优先搜索统计一块棋所占目数
void search(int x, int y, Color color, Color board[][Size])
{
	vis[x][y] = true;
	count(color, board[x][y]);
	if(board[x][y] == blank) {
		drawMark(x, y, color);
	}

	for(int i=0; i<4; i++) {
		int x2 = x + dx[i], y2 = y + dy[i];
		if(x2<0 || y2<0 || x2>=Size || y2>=Size || vis[x2][y2]) {
			continue;
		}
		if(board[x2][y2] == color || board[x2][y2] == blank) {
			search(x2, y2, color, board);
		}
	}
}

void count(Color color, Color now)
{
	if(rule == JP && now != blank) {
		return;  //Japanese rule, only count blank points
	}
	if(color == black) {
		sumB++;
	} else if(color == white) {
		sumW++;
	}
}

void calResult(int deadB, int deadW)
{
	if(rule == CN) { // using Chinese rule, do not count dead pieces
		diff = sumB - sumW - 7.5;
	} else if(rule == JP) {
		diff = (sumB + deadW) - (sumW + deadB) - 6.5;
	}

	if(diff > 0) {
		winner = black;
	} else {
		winner = white;
		diff = - diff;
	}
}
