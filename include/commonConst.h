#ifndef MY_COMMON_CONST_H
#define MY_COMMON_CONST_H

typedef int Color;
#define black BLACK //使用easyx的宏
#define white WHITE //使用easyx的宏
#define blank 0x1000000

typedef enum {
	CN, JP
} Rule;

typedef enum {
	inGame, markingDead, endGame, readingManual
} Mode;

const int Size = 19;
const int MAXMOVE = 1000;
//const double Komi = 7.5;

const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

#endif