
/************************************************
*                                               *
*                P r o c o n 1                  *
*           ユーザーインターフェース            *
*                                               *
*      (c)  Shogo Yazawa, Haruki Hirasawa       *
*                                               *
*************************************************/

#include <stdio.h>
#include <iostream>
#include <curses.h>

// 使用中変数一覧
// startwin => main関数内、スタートウィンドウ WINDOW*型
// inputch1 => main関数内、switch文入力用 char型

//プロトタイプ宣言
int msgbox(int y, int x, const char* msg);

int main() {
	char inpch1;
	initscr();
	cbreak();
	echo();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwinの作成
	WINDOW* startwin = newwin(20, 60, 2, 2);
	mvwprintw(startwin,2,4,"Procon1"); //"Procon1"は後ほど変更
	mvwprintw(startwin, 4, 4, "hキーを押してヘルプを表示");
	bkgd(COLOR_PAIR(1));
	box(startwin, '|', '=');
	refresh();
	
	inpch1 = wgetch(startwin);

	while (1) {
		clear();
		switch (inpch1) {
		case 'h':
		case 'H':
			clear();
			break;
		case 'x':
		case 'X':
			inpch1 = msgbox(4, 10, "終了しまか？ (y/n)");
			if (inpch1 == 'y' || inpch1 == 'Y') {
				delwin(startwin);
				endwin();
				return 0;
			} else {
				msgbox(6, 12, "キャンセルされました。");
			}
		default:
			mvwprintw(startwin, 6, 2, "無効なキーです。もう一度入力してください。");
			wrefresh(startwin);
			inpch1 = wgetch(startwin);
			continue;
		}
	}
	return 0;
}

int msgbox(int y, int x, const char* msg) {
	WINDOW* msgwin = newwin(10, 40, y, x);
	box(msgwin, '|', '=');
	mvwprintw(msgwin, 2, 2, "%s", msg);
	wrefresh(msgwin);
	int ch = wgetch(msgwin);
	delwin(msgwin);
	return ch;
}