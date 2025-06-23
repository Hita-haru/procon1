
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
#include <stdlib.h>
#include <curses.h>

// �g�p���ϐ��ꗗ
// startwin => main�֐����A�X�^�[�g�E�B���h�E WINDOW*�^
// inpch1 => main�֐����Aswitch�����͗p char�^
// msgwin => msgbox�֐����A���b�Z�[�W�{�b�N�X WINDOW*�^
// msg => msgbox�֐����A���b�Z�[�W���e const char*�^
// ch => msgbox�֐����A���b�Z�[�W�{�b�N�X���͗p int�^
// y, x => msgbox�֐����A���b�Z�[�W�{�b�N�X�̈ʒu int�^
// helpwin => main�֐����A�w���v�E�B���h�E WINDOW*�^
// inpstr1 => chkwnd�֐����A�F�؃E�B���h�E���� char[]�^
// inpch2 => chkwnd�֐����A�F�؃E�B���h�E���͗p char�^
// chkwnd1 => chkwnd�֐����A�F�؃E�B���h�E WINDOW*�^
// stat1 => chkwnd�֐����A�F�؃X�e�[�^�X int�^
// level => chkwnd�֐����A�F�؃��x�� int�^

//�v���g�^�C�v�錾
int msgbox(int y, int x, const char* msg);
int errorbox(int y, int x, const char* msg);
int successbox(int y, int x, const char* msg);
int chkwnd(int level);
int errorex(int errorcode);

//�O���[�o���ϐ�
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
		case '#':
			if (chkwnd(2) == 1) {
				errorex(2);
			}
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
				errorbox(6, 12, "�L�����Z������܂����B");
			}
			break;
		default:
			errorbox(6, 10, "�����ȓ��͂ł��BH�L�[�Ńw���v��\��");
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
	mvwprintw(chkwnd1, 2, 2, "�F�؃E�B���h�E");
	switch (level) {
	case 1:
		mvwprintw(chkwnd1, 4, 2, "�����܂����H(y/n)");
		break;
	case 2:
		wbkgd(chkwnd1, COLOR_PAIR(2));
		mvwprintw(chkwnd1, 4, 2, "�Ǘ��җp�p�X���[�h�����");
		break;
	case 3:
		wbkgd(chkwnd1, COLOR_PAIR(3));
		mvwprintw(chkwnd1, 4, 2, "�댯�ȑ���ł��B�����܂����H(y/n)");
		break;
	default:
		errorbox(6, 10, "�����Ȓl�ł̌Ăяo��");
		endwin();
		return -1;
		break;
	}
	mvwprintw(chkwnd1, 6, 2, "���x��: %d", level);
	wmove(chkwnd1, 8, 2);
	if (level == 2) {
		wprintw(chkwnd1, "�p�X���[�h: ");
		echo();
		wgetstr(chkwnd1, inpstr1); // �p�X���[�h����
		noecho();
		if (atoi(inpstr1) == 79417432) {
			stat1 = 1;
		}
		else {
			stat1 = 0;
		}
	} else {
		wprintw(chkwnd1, "����: ");
		inpch2 = wgetch(chkwnd1); // ���[�U�[����
		if (inpch2 == 'y' || inpch2 == 'Y') {
			stat1 = 1;
		}
		else {
			stat1 = 0;
		}
	}
	if (stat1 == 1) {
		successbox(8, 8, "�F�؂ɐ������܂���");
		return 1;
	}
	else {
		errorbox(8, 8, "�F�؂Ɏ��s���܂���");
		return 0;
	}
}

int errorex(int errorcode) {
	WINDOW* sod = newwin(min_y, min_x, 2, 2);
	box(sod, '|', '=');
	mvwprintw(sod, 2, 2, ":(");
	mvwprintw(sod, 4, 2, "�G���[���������܂����B�\�t�g���I�����܂��B");
	mvwprintw(sod, 10, 2, "�����L�[�������ďI��...");
	switch (errorcode) {
	case 1:
		mvwprintw(sod, 6, 2, "�s���ȃG���[");
		mvwprintw(sod, 8, 2, "Unknown error");
		wbkgd(sod, COLOR_PAIR(2));
	default:
		mvwprintw(sod, 6, 2, "�G���[�����擾�ł��܂���ł���");
		mvwprintw(sod, 8, 2, "Undefined error");
		wbkgd(sod, COLOR_PAIR(2));
	}
	wrefresh(sod);
	wgetch(sod);
	exit(-1);
}