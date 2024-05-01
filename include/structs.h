#ifndef MY_STRUCTS_H
#define MY_STRUCTS_H

typedef struct {
	Color color;
	int x, y, id; // 坐标及id
	int ancestor; // 该棋子并查集意义上的祖先的id
	int liberty;
		// 若为祖先(.ancestor=.id)，则存储祖先id所标识的棋串的气的数量
		// 若非祖先，则无意义
	bool exist; // 标识该棋子是否在棋盘上
} Move;

typedef struct {
	Color board[Size][Size]; // 储存各位置的状态（黑子、白子、空）
	int pieces[Size][Size];  // 储存各位置上当前最后一次落子的id，空则为0
	Move lastMove;  // 储存当前最后一次落子的信息
	int deadBlack;
	int deadWhite;
} Situ;

typedef struct {
	char id;
	int px, py;
	int x1, y1, x2, y2;  // 按钮左上角和右下角的坐标
	//wchar_t* s;  // text content
	bool disabled;
}Btn;

#endif