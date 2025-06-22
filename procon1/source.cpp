
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

//使用中変数一覧
//inputch1 => main関数内、switch文入力用 char型

int main() {
	initscr();
	cbreak();
	echo();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwinの作成
	WINDOW* startwin = newwin(10, 50, 2, 2);
	mvwprintw(startwin,2,4,"Procon1"); //"Procon1"は後ほど変更
	mvwprintw(startwin, 4, 4, "hキーを押してヘルプを表示");
	bkgd(COLOR_PAIR(1));
	box(startwin, '|', '=');
	refresh();
	
	char inpch1 = wgetch(startwin);

	while (1) {
		switch (inpch1) {
		case 'h':
		case 'H':
			clear();
			break;
		case 'x':
		case 'X':
			endwin();
			return 0;
			break;
		default:
			mvwprintw(startwin, 6, 2, "無効なキーです。もう一度入力してください。");
			wrefresh(startwin);
			inpch1 = wgetch(startwin);
			continue;
		}
	}
	return 0;
}