
/************************************************
*                                               *
*                P r o c o n 1                  *
*         U s e r   I n t e r f a c e           *
*                                               *
*      (c)  Shogo Yazawa, Haruki Hirasawa       *
*                                               *
*************************************************/

//仕様定義
//通常ユーザーに表示するUIには基本日本語を使用する。
//Adminユーザーに表示するUIには英語を使用する。
//メッセージを表示する際はメッセージボックスを基本使用する。

#include <stdio.h>
#include <iostream>
#include <curses.h>

// 使用中変数一覧
// startwin => main関数内、スタートウィンドウ WINDOW*型
// inpch1 => main関数内、switch文入力用 char型
// msgwin => msgbox関数内、メッセージボックス WINDOW*型
// msg => msgbox関数内、メッセージ内容 const char*型
// ch => msgbox関数内、メッセージボックス入力用 int型
// y, x => msgbox関数内、メッセージボックスの位置 int型


//プロトタイプ宣言
int msgbox(int y, int x, const char* msg);
WINDOW* helpwin;

int main() {
	
	char inpch1;
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwinの作成
	WINDOW* startwin = newwin(20, 60, 2, 2);
	bkgd(COLOR_PAIR(1));

	while (1) {
		clear();
		box(startwin, '|', '=');
		mvwprintw(startwin, 2, 4, "Procon1"); //"Procon1"は後ほど変更
		mvwprintw(startwin, 4, 4, "Hキーを押してヘルプを表示");
		refresh();
		inpch1 = wgetch(startwin);
		switch (inpch1) {
		case 'h':
		case 'H':
			helpwin = newwin(20, 60, 4, 4);
			box(helpwin, '|', '=');
			mvwprintw(helpwin, 2, 2, "ヘルプメニュー");
			mvwprintw(helpwin, 4, 2, "キー\t説明");
			mvwprintw(helpwin, 6, 2, "H\tヘルプメニューを表示");
			mvwprintw(helpwin, 7, 2, "X\t終了");
			refresh();
			wrefresh(helpwin);
			wgetch(helpwin);
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
			msgbox(6, 10, "無効な入力です。Hキーでヘルプを表示");
			break;
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