
/************************************************
*                                               *
*                P r o c o n 1                  *
*           ���[�U�[�C���^�[�t�F�[�X            *
*                                               *
*      (c)  Shogo Yazawa, Haruki Hirasawa       *
*                                               *
*************************************************/

#include <stdio.h>
#include <iostream>
#include <curses.h>

// �g�p���ϐ��ꗗ
// startwin => main�֐����A�X�^�[�g�E�B���h�E WINDOW*�^
// inputch1 => main�֐����Aswitch�����͗p char�^

//�v���g�^�C�v�錾
int msgbox(int y, int x, const char* msg);

int main() {
	char inpch1;
	initscr();
	cbreak();
	echo();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwin�̍쐬
	WINDOW* startwin = newwin(20, 60, 2, 2);
	mvwprintw(startwin,2,4,"Procon1"); //"Procon1"�͌�قǕύX
	mvwprintw(startwin, 4, 4, "h�L�[�������ăw���v��\��");
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
			inpch1 = msgbox(4, 10, "�I�����܂��H (y/n)");
			if (inpch1 == 'y' || inpch1 == 'Y') {
				delwin(startwin);
				endwin();
				return 0;
			} else {
				msgbox(6, 12, "�L�����Z������܂����B");
			}
		default:
			mvwprintw(startwin, 6, 2, "�����ȃL�[�ł��B������x���͂��Ă��������B");
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