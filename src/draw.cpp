#include "../include/global.h"

extern Btn btns[9][9];

void drawSidebar();
void drawBoard();

void initBoard()
{
	setbkcolor(YELLOW);
	setlinestyle(PS_SOLID | PS_JOIN_MITER);
	cleardevice();
	drawSidebar();
	drawBoard();
	/*
	IMAGE img;	loadimage(&img, _T("./img/board-default.bmp"));
	for(int i = 0; i < BOARD; i += IMGLEN)
		for(int j = 0; j < BOARD; j += IMGLEN)
			putimage(i, j, &img);
	*/
}

void drawBoard()
{
	setlinecolor(BLACK);
	setfillcolor(BLACK);

	//draw lines
	for(int i=0; i<Size; i++) {
		line(PADDING + i*CELL, PADDING, PADDING + i*CELL, BOARD - PADDING);
		line(PADDING, PADDING + i*CELL, BOARD - PADDING, PADDING + i*CELL);
	}
	//draw dots
	int step = (Size-7)/2, start = 3;
	if(step<start) {
		step = Size-7;
	}
	if(step<start) {
		start = 2;
	}
	for(int i=start; i<Size-start; i+=step) {
		for(int j=start; j<Size-start; j+=step) {
			fillcircle(PADDING + i*CELL, PADDING + j*CELL, 2);
		}
	}
}

void showBoard(Situ now)
{
	clearrectangle(0, 0, BOARD, BOARD);
	drawBoard();
	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			if(now.board[i][j] != blank) {
				drawPiece(i, j, now.board[i][j]);
			}
		}
	}
}

static int cal(int x)
{
	return x*CELL + PADDING;
}

void drawPiece(int x, int y, Color color)
{
	setfillcolor(color);
	fillcircle(cal(x), cal(y), RADIUS);
}

void drawMark(int x, int y, Color color)
{
	setfillcolor(color);
	solidrectangle(cal(x) - SQUARE/2, cal(y) - SQUARE/2, 
				   cal(x) + SQUARE/2, cal(y) + SQUARE/2);
}

void drawSidebar()
{
	setfillcolor(WHITE);
	fillrectangle(BOARD, 0, WIDTH, HEIGHT);
	setbkmode(TRANSPARENT);

	btns[1][0].y2 = 0;
	for(int i=1; i<9; i++) {
		btns[0][i].x2 = BOARD;
	}
	
	drawButton(1, 1, 3, _T("帮助(H)"));  // help
	drawButton(2, 1, 3, _T("关于(I)"));  // info
	drawButton(1, 2, 3, _T("认输(G)"));  // give up
	drawButton(2, 2, 5, _T("保存棋谱(S)"));
	//drawButton(1, 3, 7, _T("切换"), true);
	drawButton(1, 3, 10, _T("结束对局并标记死子(M)"));
	btns[1][4].y1 = btns[1][3].y2 + BTN_MARGIN;
	btns[1][4].y2 = btns[1][4].y1 + TEXT_H;
	//drawButton()
	showTurn(white, 0);
}

void drawButton(int px, int py, int len, const wchar_t* s, bool disabled)
{
	int x1, y1, x2, y2, row=1;
	x1 = btns[px][py].x1 = btns[px-1][py].x2 + BTN_MARGIN;
	y1 = btns[px][py].y1 = btns[1][py-1].y2 + BTN_MARGIN;
	x2 = btns[px][py].x2 = x1 + len * TEXT_W + BTN_PADDING *2;
	y2 = btns[px][py].y2 = y1 + row * TEXT_H;

	if(disabled) {
		setlinecolor(GREY);
		settextcolor(GREY);
	} else {
		setlinecolor(BLACK);
		settextcolor(BLACK);
	}
	line(x1, y1, x2, y1);
	line(x1, y1, x1, y2);
	line(x1, y2, x2, y2);
	line(x2, y1, x2, y2);
	RECT r = { x1, y1, x2, y2 };
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void redrawText(int px, int py, int len, const wchar_t* s, bool disabled)
{
	Btn b = btns[px][py];
	setfillcolor(WHITE);
	solidrectangle(b.x1, b.y1, b.x2, b.y2);
	drawButton(px, py, len, s, disabled);
}

void showMsg(int len, const wchar_t* s)
{
	int x1, y1, x2, y2, row = 1;
	x1 = btns[0][5].x2 + BTN_MARGIN;
	y1 = btns[1][4].y2 + BTN_MARGIN;
	x2 = x1 + len * TEXT_W + BTN_PADDING * 2;
	y2 = y1 + row * TEXT_H;

	setfillcolor(WHITE);
	solidrectangle(x1, y1, x2, y2);
	drawButton(1, 5, len, s, true);
	Sleep(500);
	solidrectangle(x1, y1, x2, y2);
}

void showTurn(Color last, int id)
{
	int x1, y1, x2, y2, row = 1, len = 8;
	x1 = btns[0][4].x2 + BTN_MARGIN;
	y1 = btns[1][3].y2 + BTN_MARGIN;
	x2 = x1 + len * TEXT_W + BTN_PADDING * 2;
	y2 = y1 + row * TEXT_H;

	wchar_t s[20] = L"";
	const wchar_t* c = NULL;
	const wchar_t fmt[20] = _T("已下%d手，轮%ls下");

	if(last == white) {
		c = _T("黑");
	} else {
		c = _T("白");
	}
	swprintf(s, 20, fmt, id, c);
	setfillcolor(WHITE);
	settextcolor(BLACK);
	RECT r = { x1, y1, x2, y2 };
	solidrectangle(x1, y1, x2, y2);
	drawtext(s, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//#define _CRT_NON_CONFORMING_SWPRINTFS
void showResult(Color winner, double diff)
{
	int x1, y1, x2, y2, row = 1, len = 8;
	x1 = btns[0][4].x2 + BTN_MARGIN;
	y1 = btns[1][3].y2 + BTN_MARGIN;
	x2 = x1 + len * TEXT_W + BTN_PADDING * 2;
	y2 = y1 + row * TEXT_H;

	wchar_t res[20] = L"";
	const wchar_t* win = NULL;

	if(winner == black) {
		win = L"黑";
	} else {
		win = L"白";
	}
	if(diff == 0) {
		swprintf(res, 20, L"%ls中盘胜", win);
	} else {
		swprintf(res, 20, L"%ls胜%.1lf目", win, diff);
	}
	setfillcolor(WHITE);
	settextcolor(BLACK);
	RECT r = { x1, y1, x2, y2 };
	solidrectangle(x1, y1, x2, y2);
	drawtext(res, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}