#define _CRT_SECURE_NO_WARNINGS
#include "../include/global.h"

extern Move moves[MAXMOVE];
extern int id;
extern Color winner;
extern double diff;

static wchar_t fileName[MAX_PATH];

bool saveFile();
void write(Mode mode);

void save(Mode mode)
{
	if(saveFile()) {
		write(mode);
		showMsg(4, L"保存成功");
	} else {
		showMsg(4, L"保存失败");
	}
}

bool saveFile()
{
	setlocale(LC_ALL, "zh_CN.utf8");
	HWND hwnd = CreateWindow(L"EDIT", NULL,
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 500, NULL, NULL,
		GetModuleHandle(NULL), NULL);

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.hwndOwner = hwnd;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = sizeof(fileName);
	ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = TEXT("SGF file\0*.sgf\0All\0*.*\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = fileName;

	return GetSaveFileName(&ofn);
}

void write(Mode mode)
{
	FILE *fp = _wfopen(fileName, L"w,ccs=UTF-8");
	//fputs("\n", fp);
	fwprintf(fp, L"(;SZ[%d]\n", Size);
	if(mode == endGame) {
		char win;
		if(winner == black) {
			win = 'B';
		} else {
			win = 'W';
		}
		if(diff == 0) {
			fwprintf(fp, L";RE[%c+R]\n", win);
		} else {
			fwprintf(fp, L";RE[%c+%.1lf]\n", win, diff);
		}
	}
	for(int i=1; i<=id; i++) {
		char color, x, y;
		if(moves[i].color == black) {
			color = 'B';
		} else {
			color = 'W';
		}
		x = 'a' + moves[i].x;
		y = 'a' + moves[i].y;
		fwprintf(fp, L";%c[%c%c]", color, x, y);
		if(i%10 == 0) {
			fwprintf(fp, L"\n");
		}
	}
	fclose(fp);
}