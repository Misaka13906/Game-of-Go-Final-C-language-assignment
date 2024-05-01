#include "../include/global.h"

//extern Situ situs[MAXMOVE];
extern Move moves[MAXMOVE];
static Move m[MAXMOVE];
static Situ tmp;
bool isLegal;

//void init();
//void placePiece(Situ,int,Color);
void createCopy(Situ now);
void markExi(int x, int y, int id);
void calcLiberty(Situ tmp, int id);
int findAncestor(int id);
void clearPieces(int id);
void clear(int x, int y);
bool isSame(Color previous[][Size]);
void copyBack(Situ *now);
void copyToPre(Situ *now, Color previous[][Size]);

bool placePiece(Situ *now, int x, int y, int id, Color previous[][Size])
{
	if(now->board[x][y] != blank) {
		return false;
	}
	isLegal = true;
	createCopy(*now);
	markExi(x, y, id);
	calcLiberty(tmp, id);
	clearPieces(id);
	isLegal &= !isSame((now-1)->board);
	if(!isLegal) {
		return false;
	}
	copyBack(now+1);
	showBoard(*(now+1));
	showTurn(moves[id].color, id);
	return true;
}

void createCopy(Situ now)
{
	tmp = now;
	for(int i=1; i<=tmp.lastMove.id; i++) {
		m[i] = moves[i];
	}
}

void markExi(int x, int y, int id)
{
	m[id].id = id;
	m[id].x = x;
	m[id].y = y;
	m[id].exist = true;
	if(id%2 == 1) {
		m[id].color = black;
	} else {
		m[id].color = white;
	}
	tmp.pieces[x][y] = id;
	tmp.board[x][y] = m[id].color;
	tmp.lastMove = m[id];
}

void calcLiberty(Situ tmp, int id)
{
	m[id].ancestor = id; //并查集初始化
	for(int i=0; i<4; i++) {
		int x = m[id].x + dx[i], y = m[id].y + dy[i];
		if(x<0 || y<0 || x>=Size || y>=Size) {
			continue;
		}
		if(tmp.board[x][y] == blank) {
			m[findAncestor(id)].liberty ++;
		} else if(tmp.board[x][y] != m[id].color) {
			m[findAncestor(tmp.pieces[x][y])].liberty --;
		} else {
			int an1 = findAncestor(id);
			int an2 = findAncestor(tmp.pieces[x][y]);
			if(an1 != an2) {
				m[an1].ancestor = an2;
				m[an2].liberty = m[an1].liberty + m[an2].liberty -1;
			}
		}
		int qwq = 0;//debug
	}
	m[id].ancestor = findAncestor(id);
	//return m[m[id].ancestor].liberty;
}

// findAncestor: 使用并查集查找棋子所在棋串集合的唯一标识（祖先的id）
int findAncestor(int id)
{
	if(m[id].ancestor == id) {
		return id;
	}
	return m[id].ancestor = findAncestor(m[id].ancestor);
}

void clearPieces(int id)
{
	for(int i=0; i<4; i++) {
		int x = m[id].x + dx[i], y = m[id].y + dy[i];
		if(x<0 || y<0 || x>=Size || y>=Size || tmp.board[x][y] == blank) {
			continue;
		}
		int liberty = m[findAncestor(tmp.pieces[x][y])].liberty;
		if(tmp.board[x][y] != m[id].color && liberty == 0) {
			clear(x, y);
		}
		int qwq = 0;//debug
	}
	if(m[findAncestor(id)].liberty == 0) {
		//clear(m[id].x, m[id].y); //Tromp-Taylor规则
		isLegal = false; //Chinese rule
	}
}

// clear: 使用深度优先搜索清除无气棋串
void clear(int x, int y)
{
	Color color = tmp.board[x][y];
	if(color == blank) {
		return;
	}
	if(color == black) {
		tmp.deadBlack ++;
	} else if (color == white) {
		tmp.deadWhite ++;
	}
	tmp.board[x][y] = blank;
	m[tmp.pieces[x][y]].exist = false;

	int an = 0;
	for(int i=0; i<4; i++) {
		int x2 = x + dx[i], y2 = y + dy[i];
		if(x2<0 || y2<0 || x2>=Size || y2>=Size || tmp.board[x2][y2] == blank) {
			continue;
		}
		if(tmp.board[x2][y2] == color) {
			clear(x2, y2);
		} else if(findAncestor(tmp.pieces[x2][y2]) != an) {
			an = m[tmp.pieces[x2][y2]].ancestor;
			m[an].liberty ++;
		}
	}
}

bool isSame(Color previous[][Size])
{
	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			if(tmp.board[i][j] != previous[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void copyBack(Situ *now)
{
	*(now) = tmp;
	for(int i=1; i<=tmp.lastMove.id; i++) {
		moves[i] = m[i];
	}
}

void copyToPre(Situ *now, Color previous[][Size])
{
	for(int i=0; i<Size; i++) {
		for(int j=0; j<Size; j++) {
			previous[i][j] = (now)->board[i][j];
		}
	}
}
