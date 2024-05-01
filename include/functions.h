#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include "commonConst.h"
#include "structs.h"

void startUp();

void init();
void initBoard();
void showBoard(Situ now);
void drawPiece(int x, int y, Color color);
void drawMark(int x, int y, Color color);
void showTurn(Color color, int id);
void showMsg(int len, const wchar_t* s);
void drawButton(int py, int px, int len, const wchar_t* s, bool disabled = false);
//				  row, column, text length, text content
void redrawText(int py, int px, int len, const wchar_t* s, bool disabled = false);

bool handleMsg();

bool placePiece(Situ *now, int x, int y, int id, Color previous[][Size]);

void startMark(Situ now);
void selectDead(int x, int y);
void confirmMark(Situ *now);

void handleResult(Situ finalSitu, Rule goRule = CN);
void showResult(Color winner, double diff = 0);
void save(Mode mode);

#endif