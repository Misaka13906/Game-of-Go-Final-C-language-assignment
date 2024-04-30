#include "../include/global.h"

const int VK_A = 0x41;

Mode mode = inGame;
Btn btns[9][9];
Situ situs[MAXMOVE];
Move moves[MAXMOVE];
Color prev[Size][Size];
int id;
extern double diff;

void handleClickInBoard(int x, int y);
void handleClickInSidebar(int x, int y);
void handlePressingAlpha(char alpha);

void init()
{
	initBoard();
	id = 0;
	memset(situs, 0, sizeof situs);
	memset(moves, 0, sizeof moves);

	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			situs[0].board[i][j] = blank;
			situs[1].board[i][j] = blank;
		}
	}
}

bool handleMsg()
{
	ExMessage m = getmessage(EX_MOUSE | EX_KEY);
	if(m.message == WM_LBUTTONDOWN) {
		int x = (m.x - PADDING + CELL/2) / CELL;
		int y = (m.y - PADDING + CELL/2) / CELL;
		if(x>=0 && y>=0 && x<Size && y<Size) {
			handleClickInBoard(x, y);
		} else {
			handleClickInSidebar(m.x, m.y);
		}
	} else if(m.message == WM_KEYDOWN) {
		if(m.vkcode == VK_ESCAPE) {
			return false;
		}
		char alpha = m.vkcode - VK_A + 'A';
		if(alpha >= 'A' && alpha <= 'Z') {
			handlePressingAlpha(alpha);
		}
	}
	return true;
}

void handleClickInBoard(int x, int y)
{
	if(mode == inGame) {
		bool success = placePiece(situs+id, x, y, id+1, prev);
		if(success) {
			id++;
		} else {
			showMsg(7, L"不正确的落子");
		}
	} else if(mode == markingDead) {
		selectDead(x, y);
	}
}

static bool insideBtn(int x, int y, int px, int py)
{
	Btn b = btns[px][py];
	return x > b.x1 && x < b.x2 && y > b.y1 && y < b.y2;
}

void handleClickInSidebar(int x, int y)
{
	if(insideBtn(x, y, 1, 1)) {
		system("start docs/help.txt");
	} else if(insideBtn(x, y, 2, 1)) {
		system("start docs/info.txt");
	} else if(insideBtn(x, y, 2, 2)) {
		save(mode);
	} else if(insideBtn(x, y, 1, 2)) {
		mode = endGame;
		redrawText(1, 3, 7, L"重新开始对局(R)");
		showResult(moves[id-1].color);
		diff = 0;
	} else if(insideBtn(x, y, 1, 3)) {
		if(mode == inGame) {
			mode = markingDead;
			redrawText(1, 3, 7, L"确认标记完成(E)");
			startMark(situs[id]);
		} else if(mode == markingDead) {
			mode = endGame;
			redrawText(1, 3, 7, L"重新开始对局(R)");
			confirmMark(situs+id);
			handleResult(situs[id]);
		} else if(mode == endGame) {
			mode = inGame;
			init();
		}
	}
}

void handlePressingAlpha(char alpha)
{
	switch(alpha) {
		case 'H':	system("start docs/help.txt");	break;
		case 'I':	system("start docs/info.txt");	break;
		case 'S':	save(mode);		break;
		case 'M':
			mode = markingDead;
			redrawText(1, 3, 7, L"确认标记完成(E)");
			startMark(situs[id]);
			break;
		case 'E':
			mode = endGame;
			redrawText(1, 3, 7, L"重新开始对局(R)");
			confirmMark(situs+id);
			handleResult(situs[id]);
			break;
		case 'G':
			mode = endGame;
			redrawText(1, 3, 7, L"重新开始对局(R)");
			showResult(moves[id-1].color);
			diff = 0;
			break;
		case 'R':
			mode = inGame;
			init();
			break;
		default: break;
	}
}