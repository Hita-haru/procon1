
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

//�g�p���ϐ��ꗗ
//inputch1 => main�֐����Aswitch�����͗p char�^

int main() {
	initscr();
	cbreak();
	echo();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwin�̍쐬
	WINDOW* startwin = newwin(10, 50, 2, 2);
	mvwprintw(startwin,2,4,"Procon1"); //"Procon1"�͌�قǕύX
	mvwprintw(startwin, 4, 4, "h�L�[�������ăw���v��\��");
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
			mvwprintw(startwin, 6, 2, "�����ȃL�[�ł��B������x���͂��Ă��������B");
			wrefresh(startwin);
			inpch1 = wgetch(startwin);
			continue;
		}
	}
	return 0;
}