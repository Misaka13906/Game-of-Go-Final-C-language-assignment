#ifndef MY_DRAWING_CONST_H
#define MY_DRAWING_CONST_H

#include "commonConst.h"

const int GREY = 0x555555;

const int
	//IMGLEN = 50,

	BTN_MARGIN = 20,
	BTN_PADDING = 5,

	TEXT_H = 30,
	TEXT_W = 20,

	SIDEBAR = TEXT_W * 15 + BTN_MARGIN,

	RADIUS = 28/2,
	SQUARE = 12,

	PADDING = 20,
	CELL = 30,

	BOARD = CELL*(Size-1) + PADDING*2,
	HEIGHT = BOARD,
	WIDTH = BOARD + SIDEBAR;

#endif