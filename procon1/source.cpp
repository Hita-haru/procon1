
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
#include <stdlib.h>
#include <curses.h>

// 使用中変数一覧
// startwin => main関数内、スタートウィンドウ WINDOW*型
// inpch1 => main関数内、switch文入力用 char型
// msgwin => msgbox関数内、メッセージボックス WINDOW*型
// msg => msgbox関数内、メッセージ内容 const char*型
// ch => msgbox関数内、メッセージボックス入力用 int型
// y, x => msgbox関数内、メッセージボックスの位置 int型
// helpwin => main関数内、ヘルプウィンドウ WINDOW*型
// inpstr1 => chkwnd関数内、認証ウィンドウ入力 char[]型
// inpch2 => chkwnd関数内、認証ウィンドウ入力用 char型
// chkwnd1 => chkwnd関数内、認証ウィンドウ WINDOW*型
// stat1 => chkwnd関数内、認証ステータス int型
// level => chkwnd関数内、認証レベル int型
// errorcode => errorex関数内、エラーコード int型
// sod => errorex関数内、エラーメッセージウィンドウ WINDOW*型
// adwin => adminmenu関数内、管理者メニュー WINDOW*型
// inpch3 => adminmenu関数内、入力用 char型

//プロトタイプ宣言
int msgbox(int y, int x, const char* msg);
int errorbox(int y, int x, const char* msg);
int successbox(int y, int x, const char* msg);
int chkwnd(int level);
int errorex(int errorcode);
int adminmenu();
int promptbox(int y, int x, const char* msg, char* ret);

//グローバル変数
int max_x,max_y,min_x,min_y;
WINDOW* helpwin;

int main() {
	char inpch1;
	initscr();
	getmaxyx(stdscr, max_y, max_x);
	min_x = max_x - 4;
	min_y = max_y - 4;
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);

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
		case '#':
			if (chkwnd(2) == 1) {
				adminmenu();
			}
			else {
				break;
			}
			break;
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
				errorbox(6, 12, "キャンセルされました。");
			}
			break;
		default:
			errorbox(6, 10, "無効な入力です。Hキーでヘルプを表示");
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

int errorbox(int y, int x, const char* msg) {
	WINDOW* msgwin = newwin(10, 40, y, x);
	box(msgwin, '|', '=');
	wbkgd(msgwin, COLOR_PAIR(2));
	mvwprintw(msgwin, 2, 2, "%s", msg);
	wrefresh(msgwin);
	int ch = wgetch(msgwin);
	delwin(msgwin);
	return ch;
}

int successbox(int y, int x, const char* msg) {
	WINDOW* msgwin = newwin(10, 40, y, x);
	box(msgwin, '|', '=');
	wbkgd(msgwin, COLOR_PAIR(3));
	mvwprintw(msgwin, 2, 2, "%s", msg);
	wrefresh(msgwin);
	int ch = wgetch(msgwin);
	delwin(msgwin);
	return ch;
}

int chkwnd(int level) {
	char inpstr1[20] = "NULL";
	char inpch2;
	int stat1;
	WINDOW* chkwnd1 = newwin(10, 30, 5, 5);
	box(chkwnd1, '|', '=');
	mvwprintw(chkwnd1, 2, 2, "認証ウィンドウ");
	switch (level) {
	case 1:
		mvwprintw(chkwnd1, 4, 2, "続けますか？(y/n)");
		break;
	case 2:
		wbkgd(chkwnd1, COLOR_PAIR(2));
		mvwprintw(chkwnd1, 4, 2, "管理者用パスワードを入力");
		break;
	case 3:
		wbkgd(chkwnd1, COLOR_PAIR(3));
		mvwprintw(chkwnd1, 4, 2, "危険な操作です。続けますか？(y/n)");
		break;
	default:
		errorex(2);
		break;
	}
	mvwprintw(chkwnd1, 6, 2, "レベル: %d", level);
	wmove(chkwnd1, 8, 2);
	if (level == 2) {
		wprintw(chkwnd1, "パスワード: ");
		echo();
		wgetstr(chkwnd1, inpstr1); // パスワード入力
		noecho();
		if (atoi(inpstr1) == 79417432) {
			stat1 = 1;
		}
		else {
			stat1 = 0;
		}
	} else {
		wprintw(chkwnd1, "入力: ");
		inpch2 = wgetch(chkwnd1); // ユーザー入力
		if (inpch2 == 'y' || inpch2 == 'Y') {
			stat1 = 1;
		}
		else {
			stat1 = 0;
		}
	}
	if (stat1 == 1) {
		successbox(8, 8, "認証に成功しました");
		return 1;
	}
	else {
		errorbox(8, 8, "認証に失敗しました");
		return 0;
	}
}

int errorex(int errorcode) {
	WINDOW* sod = newwin(min_y, min_x, 2, 2);
	box(sod, '|', '=');
	mvwprintw(sod, 2, 2, ":(");
	mvwprintw(sod, 4, 2, "エラーが発生しました。ソフトを終了します。");
	mvwprintw(sod, 10, 2, "何かキーを押して終了...");
	switch (errorcode) {
	case 1:
		mvwprintw(sod, 6, 2, "不明なエラー");
		mvwprintw(sod, 8, 2, "Unknown error");
		wbkgd(sod, COLOR_PAIR(2));
		break;
	case 2:
		mvwprintw(sod, 6, 2, "例外を処理できません");
		mvwprintw(sod, 8, 2, "Unhandled exception");
		wbkgd(sod, COLOR_PAIR(1));
		break;
	default:
		mvwprintw(sod, 6, 2, "エラー情報を取得できませんでした");
		mvwprintw(sod, 8, 2, "Undefined error");
		wbkgd(sod, COLOR_PAIR(2));
		break;
	}
	wrefresh(sod);
	wgetch(sod);
	exit(-1);
}

int adminmenu() {
	char inpch3;
	WINDOW* adwin = newwin(20, 60, 5, 5);
	box(adwin, '|', '=');
	mvwprintw(adwin, 2, 2, "Admin menu");
	mvwprintw(adwin, 4, 2, "Error display demo: 1");
	mvwprintw(adwin, 5, 2, "Error display demo: 2");
	mvwprintw(adwin, 6, 2, "Error display demo: -");
	mvwprintw(adwin, 7, 2, "MsgBox demo: 3");
	mvwprintw(adwin, 8, 2, "Check Window demo: 4");
	mvwprintw(adwin, 9, 2, "ErrorBox demo: 5");
	mvwprintw(adwin, 10, 2, "SuccessBox demo: 6");
	mvwprintw(adwin, 11, 2, "PromptBox demo: 7");
	mvwprintw(adwin, 13, 2, "Exit: X");
	refresh();
	while (1) {
		inpch3 = wgetch(adwin);
		switch (inpch3) {
		case '1':
			errorex(1);
			break;
		case '2':
			errorex(2);
			break;
		case '-':
			errorex(-1);
			break;
		case '3':
			msgbox(6, 10, "DEMO");
			break;
		case '4':
			chkwnd(1);
			break;
		case '5':
			errorbox(6, 10, "DEMO");
			break;
		case '6':
			successbox(6, 10, "DEMO");
			break;
		case '7':
			{
				char ret[20];
				promptbox(6, 10, "Input something:", ret);
				msgbox(8, 10, ret);
			}
			break;
		case 'X':
		case 'x':
			delwin(adwin);
			endwin();
			return 0;
		default:
			errorbox(6, 8, "Undefined value");
			break;
		}
	}
	return 0;
}

int promptbox(int y, int x, const char* msg,char* ret) {
	WINDOW* msgwin = newwin(10, 40, y, x);
	box(msgwin, '|', '=');
	mvwprintw(msgwin, 2, 2, "%s", msg);
	wrefresh(msgwin);
	echo();
	wgetstr(msgwin,ret);
	noecho();
	delwin(msgwin);
	return 0;
}