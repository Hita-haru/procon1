
/************************************************
*                                               *
*                P r o c o n 1                  *
*         U s e r   I n t e r f a c e           *
*                                               *
*      (c)  Shogo Yazawa, Haruki Hirasawa       *
*                                               *
*************************************************/

//�d�l��`
//�ʏ탆�[�U�[�ɕ\������UI�ɂ͊�{���{����g�p����B
//Admin���[�U�[�ɕ\������UI�ɂ͉p����g�p����B
//���b�Z�[�W��\������ۂ̓��b�Z�[�W�{�b�N�X����{�g�p����B

#include <stdio.h>
#include <iostream>
#include <curses.h>

// �g�p���ϐ��ꗗ
// startwin => main�֐����A�X�^�[�g�E�B���h�E WINDOW*�^
// inpch1 => main�֐����Aswitch�����͗p char�^
// msgwin => msgbox�֐����A���b�Z�[�W�{�b�N�X WINDOW*�^
// msg => msgbox�֐����A���b�Z�[�W���e const char*�^
// ch => msgbox�֐����A���b�Z�[�W�{�b�N�X���͗p int�^
// y, x => msgbox�֐����A���b�Z�[�W�{�b�N�X�̈ʒu int�^


//�v���g�^�C�v�錾
int msgbox(int y, int x, const char* msg);
WINDOW* helpwin;

int main() {
	
	char inpch1;
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);

	//startwin�̍쐬
	WINDOW* startwin = newwin(20, 60, 2, 2);
	bkgd(COLOR_PAIR(1));

	while (1) {
		clear();
		box(startwin, '|', '=');
		mvwprintw(startwin, 2, 4, "Procon1"); //"Procon1"�͌�قǕύX
		mvwprintw(startwin, 4, 4, "H�L�[�������ăw���v��\��");
		refresh();
		inpch1 = wgetch(startwin);
		switch (inpch1) {
		case 'h':
		case 'H':
			helpwin = newwin(20, 60, 4, 4);
			box(helpwin, '|', '=');
			mvwprintw(helpwin, 2, 2, "�w���v���j���[");
			mvwprintw(helpwin, 4, 2, "�L�[\t����");
			mvwprintw(helpwin, 6, 2, "H\t�w���v���j���[��\��");
			mvwprintw(helpwin, 7, 2, "X\t�I��");
			refresh();
			wrefresh(helpwin);
			wgetch(helpwin);
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
			msgbox(6, 10, "�����ȓ��͂ł��BH�L�[�Ńw���v��\��");
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