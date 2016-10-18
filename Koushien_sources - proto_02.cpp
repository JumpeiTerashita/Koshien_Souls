#define _CRT_SECURE_NO_WARNINGS
#define COLOR_DEFAULT printf("\x1b[49m"); printf("\x1b[39m");
#define COLOR_BALLCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_STRIKECOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_OUTCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_INTENSITY)
#define COLOR_RUNNER SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_STRAIGHTPITCHING SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY| BACKGROUND_RED)
#define COLOR_STRAIGHTPITCHING_FLAME SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED | FOREGROUND_INTENSITY)
#define COLOR_STRAIGHTPITCHING_EX SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_RED)
#define COLOR_BRAKINGPITCHING SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY| BACKGROUND_BLUE)
#define COLOR_BRAKINGPITCHING_FLAME SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define COLOR_BRAKINGPITCHING_EX SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE)
#define COLOR_OFFSPEEDPITCHING SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY| BACKGROUND_RED|BACKGROUND_GREEN)
#define COLOR_OFFSPEEDPITCHING_FLAME SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_OFFSPEEDPITCHING_EX SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_BLUE | FOREGROUND_INTENSITY| BACKGROUND_RED|BACKGROUND_GREEN)
#define NUMBER_PITCHER 9

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "MT.h"

enum {
	TEAM_YOU,
	TEAM_ENEMY
};

enum {
	RANK_E,
	RANK_D,
	RANK_C,
	RANK_B,
	RANK_A
};

enum {
	TURN_TOP,
	TURN_BOTTOM
};

typedef struct {
	int number;
	char name[16];
	int power;
	int tech;
	int speed;
}PLAYER;

PLAYER yourplayer[] = {
	{
		0,
		"���΂�",
		0,
		0,
		0
	},
	{
		1,
		"�܂���",
		RANK_D,
		RANK_C,
		RANK_A
	},
	{
		2,
		"���̂���",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		3,
		"����܂�",
		RANK_A,
		RANK_B,
		RANK_E
	},
	{
		4,
		"���̂�",
		RANK_A,
		RANK_C,
		RANK_D
	},
	{
		5,
		"�悵�ނ�",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		6,
		"�Ȃ��͂�",
		RANK_C,
		RANK_C,
		RANK_C
	},
	{
		7,
		"������",
		RANK_C,
		RANK_C,
		RANK_B
	},
	{
		8,
		"��܂���",
		RANK_B,
		RANK_C,
		RANK_D
	},
	{
		9,
		"������",
		RANK_B,
		RANK_C,
		RANK_B
	},
};
PLAYER enemyplayer[] = {
	{
		0,
		"���΂�",
		0,
		0,
		0
	},
	{
		1,
		"�܂��",
		RANK_A,
		RANK_A,
		RANK_B
	},
	{
		2,
		"�悵����",
		RANK_C,
		RANK_C,
		RANK_A
	},
	{
		3,
		"�΂���",
		RANK_A,
		RANK_A,
		RANK_E
	},
	{
		4,
		"������",
		RANK_A,
		RANK_B,
		RANK_D
	},
	{
		5,
		"������",
		RANK_B,
		RANK_B,
		RANK_C
	},
	{
		6,
		"����",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		7,
		"�Ђ炽",
		RANK_D,
		RANK_C,
		RANK_C
	},
	{
		8,
		"����",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		9,
		"������",
		RANK_C,
		RANK_B,
		RANK_B
	},
};


char title_Names[][16] = {
	"�N���C�}�b�N�X",
	"�_�C�W�F�X�g",
	"�t���v���C",
};

enum title_gameType {
	GAMETYPE_CLIMAX,
	GAMETYPE_DIGEST,
	GAMETYPE_FULLPLAY
};

typedef struct {
	int type;
	int power;
	int plus_type;
	int plus_power;
	int result_power;
}CHOICE_CARD;

typedef struct {
	int score;
	SHORT dispX, dispY;
}SCOREMANAGER;

SCOREMANAGER players[15];
SCOREMANAGER enemys[15];

CHOICE_CARD playersChoice = { 0 };
CHOICE_CARD enemysChoice = { 0 };

int BSO[3] = { 0,0,0 };
int RUNNER[4] = { 0,0,0,0 };
int _inning = 9;
int _turn = TURN_TOP;
int _hideScoreCounter = 0;
int score[2] = { 0,0 };
int outBox = 0;
int order[2] = { 1,1 };

char scoreBoardNumber[][16] = {
	"�O",
	"�P",
	"�Q",
	"�R",
	"�S",
	"�T",
	"�U",
	"�V",
	"�W",
	"�X",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
	"17",
	"18",
	"19",
	"20",
	"21",
	"22",
	"23",
	"24",
	"25"
};

char cardPowerNumber[][16] = {
	"�Z",
	"�@",
	"�A",
	"�B",
	"�C",
	"�D",
	"�E",
	"�F",
	"�G",
	"�H",
	"�I",
	"�J",
	"�K",
	"�L",
	"�M",
	"�N",
	"�O",
	"�P",
	"�Q",
	"�R",
	"�S"
};

char statusChar[][16] = {
	"�d",
	"�c",
	"�b",
	"�a",
	"�`"
};

HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition = {
	0,  // SHORT X
	0 }; // SHORT Y
COORD dwSize = { 9999, 9999 };


enum {
	CARDTYPE_STRAIGHT,
	CARDTYPE_BRAKING,
	CARDTYPE_OFFSPEED,
	CARDTYPE_NONE
};

enum {
	PLAYSIDE_PITCHING,
	PLAYSIDE_BATTING
};

enum {
	RESULT_WIN,
	RESULT_LOSE,
	RESULT_DRAW
};

enum {
	COUNT_BALL,
	COUNT_STRIKE,
	COUNT_OUT
};

enum {
	RUNNER_FIRST,
	RUNNER_SECOND,
	RUNNER_THIRD,
	RUNNER_HOME
};

void CursorPositionSet(SHORT x, SHORT y) {
	CursorPosition = {
		x,  // SHORT X
		y }; // SHORT Y
	SetConsoleCursorPosition(hConsoleOutput, CursorPosition);
}

void preTitle() {
	SetConsoleScreenBufferSize(
		hConsoleOutput, // HANDLE hConsoleOutput
		dwSize);        // COORD dwSize
	SMALL_RECT consoleWindow = { 40,10, 49,180 };
	SetConsoleWindowInfo(
		hConsoleOutput, // HANDLE hConsoleOutput
		TRUE,           // BOOL bAbsolute
		&consoleWindow);// CONST SMALL_RECT *lpConsoleWindow



	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t*�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\*\n");
	printf("\n\n\n\t\t\t\t\t\t\t�ő剻�\���ł́@�v���C�𐄏����܂�\n\t\t\t\t\t\t\t�ύX���I�������@�G���^�[�L�[���@�����Ă�������\n\n");
	printf("\n\n\t\t\t\t\t\t*�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\*");
	getchar();
}

int title() {
	int cursor = 0;
	bool enterFlag = FALSE;
	while (enterFlag == FALSE)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t�@oooo    oooo                    oooo         o8o                              .oooooo..o   .oooooo.   ooooo     ooo ooooo         .oooooo..o \n");
		printf("\t�@`888   .8P'                     `888         `\"'                             d8P'    `Y8  d8P'  `Y8b  `888'     `8' `888'        d8P'    `Y8 \n");
		printf("\t�@ 888  d8'     .ooooo.   .oooo.o  888 .oo.   oooo   .ooooo.  ooo. .oo.        Y88bo.      888      888  888       8   888         Y88bo.      \n");
		printf("\t�@ 88888[      d88' `88b d88(  \"8  888P\"Y88b  `888  d88' `88b `888P\"Y88b        `\"Y8888o.  888      888  888       8   888          `\"Y8888o.  \n");
		printf("\t�@ 888`88b.    888   888 `\"Y88b.   888   888   888  888ooo888  888   888            `\"Y88b 888      888  888       8   888              `\"Y88b \n");
		printf("\t�@ 888  `88b.  888   888 o.  )88b  888   888   888  888    .o  888   888       oo     .d8P `88b    d88'  `88.    .8'   888       o oo     .d8P \n");
		printf("\t�@o888o  o888o `Y8bod8P' 8\"\"888P' o888o o888o o888o `Y8bod8P' o888o o888o      8\"\"88888P'   `Y8bood8P'     `YbodP'    o888ooooood8 8\"\"88888P'  ");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t");
		for (int i = 0; i < 3; i++)
		{

			if (cursor == i)
			{
				printf("���@%s\t\t", title_Names[i]);
			}
			else
			{
				printf("�@�@%s\t\t", title_Names[i]);
			}
		}
		switch (cursor)
		{
		case GAMETYPE_CLIMAX:
			printf("\n\n\n\n\n\n\t\t9�񂩂�v���C���܂�\n");
			break;
		case GAMETYPE_DIGEST:
			printf("\n\n\n\n\n\n\t\t1�񂩂�@�s���`�E�`�����X���̂݃v���C���܂�\n");
			break;
		case GAMETYPE_FULLPLAY:
			printf("\n\n\n\n\n\n\t\t1�񂩂�@�S�ẴC�j���O���v���C���܂�\n");
			break;
		}
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:	//��
				if (cursor == GAMETYPE_CLIMAX)
				{
					cursor = GAMETYPE_FULLPLAY;
					break;
				}
				cursor--;
				break;
			case 0x4d:	//��
				if (cursor == GAMETYPE_FULLPLAY)
				{
					cursor = GAMETYPE_CLIMAX;
					break;
				}
				cursor++;
				break;
			}
			break;
		}
	}
	switch (cursor)
	{
	case GAMETYPE_CLIMAX:
		_inning = 9;
		_turn = TURN_TOP;
		break;
	case GAMETYPE_DIGEST:
		_inning = 1;
		_turn = TURN_TOP;
		break;
	case GAMETYPE_FULLPLAY:
		_inning = 1;
		_turn = TURN_TOP;
		break;
	}
	return 0;
}

void gameStandby() {
	for (int i = 0; i < 9; i++)
	{
		enemys[i].dispX = 34 + i * 4;
		enemys[i].dispY = 3;
		players[i].dispX = 34 + i * 4;
		players[i].dispY = 5;
		players[i].score = 0;
		enemys[i].score = 0;
	}
	for (int k = 0; k < 3; k++)
	{
		BSO[k] = 0;
	}
	for (int n = 0; n < 4; n++)
	{
		RUNNER[n] = 0;
	}
	score[0] = 0;
	score[1] = 0;
	_hideScoreCounter = 0;
}

void ballPark() {
	printf("\n\n\n\n\n\n\n");
	printf("888\n");
	printf("888�@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@  ��|\n");
	printf("888�@ �@ �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ �@__|�Q\n");
	printf("888�@ �@ �@ �@ �@�@ �@ �@ �@ �@ ��|    ���f���e��   ��| \n");
	printf("��||�@ �@ �@�@ �@ �@ �@ �@ �Q�Q�Q|�Q�Q| �F���@   |�Q_|�Q�Q�Q_\n");
	printf("�@|| �@ �@ �@�@�@�@�@�@�@�@| E EEEEEEE! �f �@�@�@EEEEEEEEE!  |\n");
	printf("�Q||.�Q�Q�Q�Q�Q�Q�Q___�Q�Q_| E EEEEEEE!�@=== �@�@   �c �c   _|�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q_\n");
	printf("| |�֐��߲��| | TMR |.|      E EEEEEEE!�@EEE!�@   �������@.|���Z���~�h|�ެ���݃����^�J�[|\n");
	printf("�O�O�O�O�O�O�O�O�O|�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\|�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
	printf("�O�O�O�O�O�O�O�O�O|�@ �@ �@ �g�сI�͎O�H�d�@�@ �@ �@�@�@�@�@�@ |�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
	printf("�O�O�O�O�O�O�O�O�O|�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\|�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
	printf(" �O�O�O�O�O�O�O�O�O�O�O/l�@ |�@�@�@�@ �@ �@ �@ �@|�@  |i�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
	printf("�O�O�O�O�O�O�O�O�O�O�O/_|�Q|�Q�Q�Q�Q�Q�Q�Q�Q�Q�Q|�Q|,l�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
	printf("�@�@ �@�@�@�a�����������������@�@i��i�@�@�@�@�@�@�@�@ �@ �@ �@ �@ �@ �����݌v\n");
	printf("�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P�P\n");
	printf("\n\n");
	printf("�@�@ _�Q_,,,,,,,,,,,,,,,,,.........�[�P�P�P�[--~.................,,,,,,,,,,,,,,,\n");
	printf("�P �P�@�@�@�@�@�@�@�@          �@�@�@�@ �@ �@�@ �@ �@ �@ �@ �@�@�@�@�@�@�P�P\"\"\"\n");
	printf("\n �@�@�@�@�@�@�@,. -�] сR�����ɰ' - ..");
	printf("\n\n");
	printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ _,,..� - �] '''' \n");
	printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@_,,..� - �] '''' \"�L\n");
	printf("�Q�Q�@�@�@�@ �Q�Q�Q_ ,,..� - �] '''' \"�L\n");
	printf("�@ �^ ���@�^�@�@�@ �^\n");
	printf("�^�@�@ �^�@�@ �@�^\n");
	printf("�@�@ �^�P�P�P\n");
	printf("_,�^\n");
}

void scoreDisp(SCOREMANAGER* scoremanager) {
	CursorPositionSet(scoremanager->dispX, scoremanager->dispY);
	printf("%s", scoreBoardNumber[scoremanager->score]);
}



int display(int* RUNNER) {
	system("cls");
	BSO[COUNT_OUT] = outBox;
	ballPark();
	SHORT baseLeft = 6, baseTop = 1;
	CursorPositionSet(baseLeft + 6, baseTop);
	if (RUNNER[RUNNER_SECOND] == TRUE) {
		COLOR_RUNNER;
		printf("��");
		COLOR_DEFAULT;
	}
	else printf("��");
	CursorPositionSet(baseLeft + 4, baseTop + 1);
	printf("�^�@�_");
	CursorPositionSet(baseLeft + 2, baseTop + 2);
	printf("�^�@�@�@�_");
	CursorPositionSet(baseLeft, baseTop + 3);
	if (RUNNER[RUNNER_THIRD] == TRUE) {
		COLOR_RUNNER;
		printf("��");
		COLOR_DEFAULT;
	}
	else printf("��");
	if (RUNNER[RUNNER_FIRST] == TRUE) {
		COLOR_RUNNER;
		printf("�@�@�@�@�@��");
		COLOR_DEFAULT;
	}
	else printf("�@�@�@�@�@��");
	CursorPositionSet(baseLeft + 2, baseTop + 4);
	printf("�_�@�@�@�^");
	CursorPositionSet(baseLeft + 4, baseTop + 5);
	SHORT scoreDispX = 8, scoreDispY = 6;
	CursorPositionSet(scoreDispX, scoreDispY);
	printf("�� %d - �n %d", score[TEAM_ENEMY], score[TEAM_YOU]);
	CursorPositionSet(scoreDispX + 3, scoreDispY + 1);
	printf("%d��", _inning);
	switch (_turn) {
	case TURN_TOP:
		printf("�\");
		break;
	case TURN_BOTTOM:
		printf("��");
		break;
	}
	SHORT ballCountDispX = 10, ballCountDispY = 3;
	CursorPositionSet(ballCountDispX, ballCountDispY);
	printf("B ");
	COLOR_BALLCOUNT;
	switch (BSO[COUNT_BALL])	//�{�[���J�E���g
	{
	case 0:
		printf("������");
		break;
	case 1:
		printf("������");
		break;
	case 2:
		printf("������");
		break;
	case 3:
		printf("������");
		break;
	}
	COLOR_DEFAULT;
	CursorPositionSet(ballCountDispX, ballCountDispY + 1);
	printf("S ");
	COLOR_STRIKECOUNT;
	switch (BSO[COUNT_STRIKE])	//�X�g���C�N�J�E���g
	{
	case 0:
		printf("����");
		break;
	case 1:
		printf("����");
		break;
	case 2:
		printf("����");
		break;
	}
	COLOR_DEFAULT;
	CursorPositionSet(ballCountDispX, ballCountDispY + 2);
	printf("O ");
	COLOR_OUTCOUNT;
	switch (BSO[COUNT_OUT])	//�A�E�g�J�E���g
	{
	case 0:
		printf("����");
		break;
	case 1:
		printf("����");
		break;
	case 2:
		printf("����");
		break;
	}
	COLOR_DEFAULT;
	SHORT scoreBoardDispX = 26, scoreBoardDispY = 2;
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY);
	printf("��������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 1);
	printf("�����n���@���@���@���@���@���@���@���@���@��\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 2);
	printf("��������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 3);
	printf("���n�����@���@���@���@���@���@���@���@���@��\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 4);
	printf("��������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX + 8, scoreBoardDispY - 1);
	printf("�P�@�Q�@�R�@�S�@�T�@�U�@�V�@�W�@�X");
	for (int i = 0; i < _inning - 1; i++)
	{
		scoreDisp(&players[i]);
		scoreDisp(&enemys[i]);
	}
	if (_turn == TURN_BOTTOM)
	{
		scoreDisp(&enemys[_inning - 1]);
	}
	return 0;
}


void pitchCardDisp(int cardPower, int cardType, int cardCursolIs) {
	SHORT cardPosX = 2, cardPosY = 41;
	switch (cardType) {
	case CARDTYPE_STRAIGHT:
		if (cardCursolIs == CARDTYPE_STRAIGHT) cardPosY -= 1;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���S ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" ���S ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �Ɂ@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�} ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	}

}

void pitchPlusCardDisp(int cardPower, int cardType, int cardCursolIs) {
	SHORT cardPosX = 2, cardPosY = 41;
	switch (cardType) {
	case CARDTYPE_STRAIGHT:
		if (cardCursolIs == CARDTYPE_STRAIGHT) cardPosY -= 1;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�^����");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�N�T�C");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�Ƃ���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �x�@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	}

}

int pitchingCardChoice() {
	int cardCommand = 0;
	bool enterFlag = FALSE;
	CursorPositionSet(0, 30);
	init_genrand((unsigned)time(NULL));
	SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	printf("\n\n\n\n���d��d���d��d���d���d��d���d��d���d���d��d���d��d���d���d��d���d\n�@�@�@�@�@�@\n");
	COLOR_DEFAULT;
	printf(" �� �s�b�`���O�t�F�C�Y ��\n\n");
	printf(" �J�[�h��I�����Ă�������\n");
	int cardPowerMaker;
	int cardPowerBox[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	pitchCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, CARDTYPE_NONE);
	pitchCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, CARDTYPE_NONE);
	pitchCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, CARDTYPE_NONE);

	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		pitchCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" �������S ");
			COLOR_DEFAULT;
			printf("�@    : �Ӑg�� �X�g���[�g�� �O�U�� �_���܂� �@");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" �ω������S ");
			COLOR_DEFAULT;
			printf("�@  : �ω����� �h���Ԃ� �O�U�� �_���܂��@�@ ");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" �ɋ} ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �������� ���Y���� ���킹�܂��@�@�@ �@ ");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		}
		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : �_���_���@�@");
			break;
		case 2:
			printf(" : �ł���₷��");
			break;
		case 3:
			printf(" : �t�c�E�@�@�@");
			break;
		case 4:
			printf(" : �ł���ɂ���");
			break;
		case 5:
			printf(" : �T�C�R�[�@�@");
			break;
		}

		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			playersChoice.power = cardPowerBox[cardCommand];
			playersChoice.type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_OFFSPEED;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				if (cardCommand == CARDTYPE_OFFSPEED)
				{
					cardCommand = CARDTYPE_STRAIGHT;
					break;
				}
				cardCommand++;
				break;
			}
			break;
		}
	}
	CursorPositionSet(0, 38);
	for (int i = 0; i < 9; i++)
	{
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
	}
	CursorPositionSet(0, 38);
	printf(" �v���X�J�[�h���@�I�����Ă�������\n");
	cardPowerMaker = 0;
	cardPowerBox[CARDTYPE_STRAIGHT] = 0;
	cardPowerBox[CARDTYPE_BRAKING] = 0;
	cardPowerBox[CARDTYPE_OFFSPEED] = 0;
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	pitchPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, CARDTYPE_NONE);
	pitchPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, CARDTYPE_NONE);
	pitchPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, CARDTYPE_NONE);
	enterFlag = FALSE;
	cardCommand = 0;
	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" �^�������� ");
			COLOR_DEFAULT;
			printf("�@  : ��_�ȃR�[�X�� �������݂܂��@�@�@�@�@�@");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" �N�T�C�Ƃ��� ");
			COLOR_DEFAULT;
			printf("�@: �X�g���C�N�]�[���M���M���� �_���܂��@�@");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" �x�� ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �o���g��@�X�N�C�Y���@�x�����܂��@");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		}

		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : �_���_���@�@");
			break;
		case 2:
			printf(" : �ł���₷��");
			break;
		case 3:
			printf(" : �t�c�E�@�@�@");
			break;
		case 4:
			printf(" : �ł���ɂ���");
			break;
		case 5:
			printf(" : �T�C�R�[�@�@");
			break;
		}
		CursorPositionSet(45, 44);
		switch (playersChoice.type)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		}
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			break;
		}
		printf(" ���� ");
		COLOR_DEFAULT;
		if (cardCommand == playersChoice.type)
		{
			printf(" :�@�ǍD�@");
		}
		else printf(" :�@�t�c�E");
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			playersChoice.plus_power = cardPowerBox[cardCommand];
			playersChoice.plus_type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_OFFSPEED;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				if (cardCommand == CARDTYPE_OFFSPEED)
				{
					cardCommand = CARDTYPE_STRAIGHT;
					break;
				}
				cardCommand++;
				break;
			}
			break;
		}
	}
	return 0;
}

void enemyCardChoice() {
	int cardPowerMaker;
	int cardPowerBox[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	switch (genrand_int32() % 3)
	{
	case CARDTYPE_STRAIGHT:
		enemysChoice.type = CARDTYPE_STRAIGHT;
		enemysChoice.power = cardPowerBox[CARDTYPE_STRAIGHT];
		break;
	case CARDTYPE_BRAKING:
		enemysChoice.type = CARDTYPE_BRAKING;
		enemysChoice.power = cardPowerBox[CARDTYPE_BRAKING];
		break;
	case CARDTYPE_OFFSPEED:
		enemysChoice.type = CARDTYPE_OFFSPEED;
		enemysChoice.power = cardPowerBox[CARDTYPE_OFFSPEED];
		break;
	}
	cardPowerMaker = 0;
	cardPowerBox[CARDTYPE_STRAIGHT] = 0;
	cardPowerBox[CARDTYPE_BRAKING] = 0;
	cardPowerBox[CARDTYPE_OFFSPEED] = 0;
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	int plusCardChooser = genrand_int32() % 3;
	enemysChoice.plus_type = plusCardChooser;
	enemysChoice.plus_power = cardPowerBox[plusCardChooser];
	return;
}

void dispCls_result() {
	CursorPositionSet(0, 34);
	for (int i = 0; i < 13; i++)
	{
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
	}
	CursorPositionSet(12, 9);
	printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	CursorPositionSet(12, 10);
	printf("�@���������������������������������������������������������������������@");
	for (int i = 11; i < 25; i++)
	{
		CursorPositionSet(12, (SHORT)i);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	}
	CursorPositionSet(12, 23);
	printf("�@���������������������������������������������������������������������@");
	CursorPositionSet(12, 24);
	printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
}

void resultCardDisp(SHORT cardPosX, SHORT cardPosY, bool cardSide, CHOICE_CARD* result) {
	CursorPositionSet(cardPosX, cardPosY);
	switch (cardSide)
	{
	case PLAYSIDE_PITCHING:
		if (result->plus_type == result->type)
		{
			switch (result->type)
			{
			case CARDTYPE_STRAIGHT:
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_STRAIGHTPITCHING_EX;
				printf("���Ȃ�");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_STRAIGHTPITCHING_EX;
				printf("������");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				CursorPositionSet(cardPosX, cardPosY);
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_BRAKINGPITCHING_EX;
				printf(" ���@ ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_BRAKINGPITCHING_EX;
				printf(" �@�� ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" �ό� ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" ���� ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			}
		}
		else
		{
			switch (result->type)
			{
			case CARDTYPE_STRAIGHT:
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf(" ���� ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf(" ���S ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�ω���");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf(" ���S ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");

				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf(" �Ɂ@ ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf(" �@�} ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			}
		}
		break;
	case PLAYSIDE_BATTING:
		if (result->plus_type == result->type)
		{
			switch (result->type)
			{
			case CARDTYPE_STRAIGHT:
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_STRAIGHTPITCHING_EX;
				printf("ΰ��� ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_STRAIGHTPITCHING_EX;
				printf("�@�_��");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				CursorPositionSet(cardPosX, cardPosY);
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_BRAKINGPITCHING_EX;
				printf(" ���� ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_BRAKINGPITCHING_EX;
				printf(" �ł� ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_OFFSPEEDPITCHING_EX;
				printf("�N�Z��");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" �̋Z ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			}
		}
		else
		{
			switch (result->type)
			{
			case CARDTYPE_STRAIGHT:
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf(" ���� ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf(" �_�� ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_STRAIGHTPITCHING;
				printf("�@�@�@");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�ω���");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf(" �_�� ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_BRAKINGPITCHING;
				printf("�@�@�@");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("��������");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf(" ���� ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf(" �_�o ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("��");
				COLOR_OFFSPEEDPITCHING;
				printf("�@�@�@");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("��");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("��������");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			}
		}
	}

}

int pitchCardResultDisp(CHOICE_CARD* playersResult, CHOICE_CARD* enemysResult) {
	int cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���S ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" ���S ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �Ɂ@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�} ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	}
	SHORT plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�^����");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�N�T�C");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�Ƃ���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �x�@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	SHORT equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");
	cardPosX = 64, cardPosY = 16;
	getchar();
	CursorPositionSet(cardPosX, cardPosY);
	if (playersResult->plus_type == playersResult->type)
	{
		switch (playersResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�s�b�`���[�@�����@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("���Ȃ�");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("������");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�s�b�`���[�@�ω����@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].tech - 2;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" ���@ ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" �@�� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�s�b�`���[�@�Z�I�@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" �ό� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" ���� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	else
	{
		playersResult->result_power = playersResult->power + playersResult->plus_power;
		switch (playersResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�s�b�`���[�@�����@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].power - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���S ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�s�b�`���[�@�ω����@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].tech - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�ω���");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf(" ���S ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�s�b�`���[�@�Z�I�@�␳�I�@%+d", yourplayer[NUMBER_PITCHER].speed - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �Ɂ@ ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �@�} ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@CPU�́@�I���J�[�h�@");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �_�� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" �_�� ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" ���� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �_�o ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	}
	plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���@ ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �@�U ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("���؂�");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("���ߎ�");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");
	getchar();
	cardPosX = 64, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	if (enemysResult->plus_type == enemysResult->type)
	{
		switch (enemysResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�o�b�^�[�@���ŗ́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("ΰ��� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("�@�_��");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�o�b�^�[�@�I�ŗ́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" ���� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" �ł� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�o�b�^�[�@���́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf("�N�Z��");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" �̋Z ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	else
	{
		enemysResult->result_power = enemysResult->power + enemysResult->plus_power;
		switch (enemysResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�o�b�^�[�@���ŗ́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].power - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" �_�� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�o�b�^�[�@�I�ŗ́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].tech - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�ω���");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf(" �_�� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�o�b�^�[�@���́@�␳�I�@%+d", enemyplayer[order[TEAM_ENEMY]].speed - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" ���� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �_�o ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@�J�[�h�o�g�����ʁI�@");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(20, 15, PLAYSIDE_PITCHING, &playersChoice);
	resultCardDisp(40, 15, PLAYSIDE_BATTING, &enemysChoice);
	if (playersResult->type == enemysResult->type)
	{
		CursorPositionSet(58, 12);
		printf("�z���Ɂ@���킳�ꂽ�I");
		CursorPositionSet(58, 13);
		printf("�����{�[�i�X�I�@+2");
		getchar();
		enemysResult->result_power += 2;
		resultCardDisp(40, 15, PLAYSIDE_BATTING, &enemysChoice);
	}
	CursorPositionSet(58, 15);
	printf("%d vs %d", playersResult->result_power, enemysResult->result_power);
	if (playersResult->result_power > enemysResult->result_power)
	{
		return RESULT_WIN;
	}
	if (playersResult->result_power < enemysResult->result_power)
	{
		return RESULT_LOSE;
	}
	if (playersResult->result_power == enemysResult->result_power)
	{
		return RESULT_DRAW;
	}
	return 0;
}

int pitchJudgeCompatibility() {
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@���Ȃ��́@�I���J�[�h�@");
	int result = pitchCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
		CursorPositionSet(58, 17);
		printf("�O�U�I");
		BSO[COUNT_OUT] += 1;
		outBox = BSO[COUNT_OUT];
		break;
	case RESULT_LOSE:
		CursorPositionSet(58, 17);
		printf("�ł��ꂽ�I");
		for (int i = 3; i >= 0; i--)
		{
			if (RUNNER[i - 1] == TRUE)
			{
				RUNNER[i - 1] = FALSE;
				RUNNER[i] = TRUE;
			}
		}
		RUNNER[RUNNER_FIRST] = 1;
		if (RUNNER[RUNNER_HOME] == TRUE)
		{
			RUNNER[RUNNER_HOME] = FALSE;
			score[TEAM_ENEMY]++;
			_hideScoreCounter++;
		}
		break;
	case RESULT_DRAW:
		CursorPositionSet(58, 17);
		printf("���������I");
		CursorPositionSet(58, 18);
		printf("�t�@�[���I");
		order[TEAM_ENEMY]--;
		if (BSO[COUNT_STRIKE] < 3)BSO[COUNT_STRIKE] += 1;
		getchar();
		/*int randomNum;
		while (_kbhit() != 1) {
			randomNum = 10 + genrand_int32() % 90;
			CursorPositionSet(58, 17);
			printf("%d �^ 99", randomNum);
		}
		int fortuneResult = randomNum;
		if (fortuneResult >= 50)
		{
			CursorPositionSet(58, 18);
			printf("�q�b�g�I");
			for (int i = 3; i >= 0; i--)
			{
				if (RUNNER[i - 1] == TRUE)
				{
					RUNNER[i - 1] = FALSE;
					RUNNER[i] = TRUE;
				}
			}
			RUNNER[RUNNER_FIRST] = 1;
			if (RUNNER[RUNNER_HOME] == TRUE)
			{
				RUNNER[RUNNER_HOME] = FALSE;
				score[TEAM_ENEMY]++;
				_hideScoreCounter++;
			}
		}
		else
		{
			CursorPositionSet(58, 18);
			printf("�A�E�g�I");
			BSO[COUNT_OUT] += 1;
			outBox = BSO[COUNT_OUT];
		}
		getchar();
		break;*/
	}
	return 0;
}

void battingCardDisp(int cardPower, int cardType, int cardCursolIs) {
	SHORT cardPosX = 2, cardPosY = 41;
	switch (cardType) {
	case CARDTYPE_STRAIGHT:
		if (cardCursolIs == CARDTYPE_STRAIGHT) cardPosY -= 1;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �_�� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" �_�� ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" ���� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �_�o ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	}

}

void battingPlusCardDisp(int cardPower, int cardType, int cardCursolIs) {
	SHORT cardPosX = 2, cardPosY = 41;
	switch (cardType) {
	case CARDTYPE_STRAIGHT:
		if (cardCursolIs == CARDTYPE_STRAIGHT) cardPosY -= 1;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���@ ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �@�U ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("���؂�");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("��������");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" ���� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("  ��  ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	}

}



int battingCardChoice() {
	int cardCommand = 0;
	bool enterFlag = FALSE;
	CursorPositionSet(0, 30);
	init_genrand((unsigned)time(NULL));
	SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	printf("\n\n\n\n���d��d���d��d���d���d��d���d��d���d���d��d���d��d���d���d��d���d\n�@�@�@�@�@�@\n");
	COLOR_DEFAULT;
	printf(" �� �o�b�e�B���O�t�F�C�Y ��\n\n");
	printf(" �J�[�h��I�����Ă�������\n");
	int cardPowerMaker;
	int cardPowerBox[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	battingCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, CARDTYPE_NONE);
	battingCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, CARDTYPE_NONE);
	battingCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, CARDTYPE_NONE);

	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		battingCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" �����_�� ");
			COLOR_DEFAULT;
			printf("�@    : �_������ ������ �i��܂��@�@�@�@�@");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" �ω������S ");
			COLOR_DEFAULT;
			printf("�@  : �_������ �ω����� �i��܂��@�@�@�@�@ ");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" ���ː_�o ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �_������ �i�炸 �X�C���O���܂��@ ");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		}
		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : �_���_���@�@");
			break;
		case 2:
			printf(" : �ł���₷��");
			break;
		case 3:
			printf(" : �t�c�E�@�@�@");
			break;
		case 4:
			printf(" : �ł���ɂ���");
			break;
		case 5:
			printf(" : �T�C�R�[�@�@");
			break;
		}
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			playersChoice.power = cardPowerBox[cardCommand];
			playersChoice.type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_OFFSPEED;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				if (cardCommand == CARDTYPE_OFFSPEED)
				{
					cardCommand = CARDTYPE_STRAIGHT;
					break;
				}
				cardCommand++;
				break;
			}
			break;
		}
	}
	CursorPositionSet(0, 38);
	for (int i = 0; i < 9; i++)
	{
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
	}
	CursorPositionSet(0, 38);
	printf(" �v���X�J�[�h���@�I�����Ă�������\n");
	cardPowerMaker = 0;
	cardPowerBox[CARDTYPE_STRAIGHT] = 0;
	cardPowerBox[CARDTYPE_BRAKING] = 0;
	cardPowerBox[CARDTYPE_OFFSPEED] = 0;
	for (int i = 0; i < 3; i++)
	{
		cardPowerMaker = genrand_int32() % 9;
		if (cardPowerMaker == 0) cardPowerBox[i] = 1;
		if ((cardPowerMaker == 1) || (cardPowerMaker == 5)) cardPowerBox[i] = 2;
		if ((cardPowerMaker == 2) || (cardPowerMaker == 6) || (cardPowerMaker == 8))	cardPowerBox[i] = 3;
		if ((cardPowerMaker == 3) || (cardPowerMaker == 7))			cardPowerBox[i] = 4;
		if (cardPowerMaker == 4)				cardPowerBox[i] = 5;
	}
	battingPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, CARDTYPE_NONE);
	battingPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, CARDTYPE_NONE);
	battingPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, CARDTYPE_NONE);
	enterFlag = FALSE;
	cardCommand = 0;
	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		battingPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" ���U ");
			COLOR_DEFAULT;
			printf("�@  : �v�������� �S�͂� �X�C���O���܂��@�@");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" ���؂� ");
			COLOR_DEFAULT;
			printf("�@: �������R�[�X�̋��� �悭���đΏ����܂��@");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" ���ߎ� ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �o���g��@�X�N�C�Y���@���݂܂��@");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		}

		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : �_���_���@�@");
			break;
		case 2:
			printf(" : �ł���₷��");
			break;
		case 3:
			printf(" : �t�c�E�@�@�@");
			break;
		case 4:
			printf(" : �ł���ɂ���");
			break;
		case 5:
			printf(" : �T�C�R�[�@�@");
			break;
		}
		CursorPositionSet(45, 44);
		switch (playersChoice.type)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			printf(" �I���ς݃J�[�h ");
			COLOR_DEFAULT;
			printf(" �Ƃ� ");
			break;
		}
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			break;
		}
		printf(" ���� ");
		COLOR_DEFAULT;
		if (cardCommand == playersChoice.type)
		{
			printf(" :�@�ǍD�@");
		}
		else printf(" :�@�t�c�E");
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			playersChoice.plus_power = cardPowerBox[cardCommand];
			playersChoice.plus_type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_OFFSPEED;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				if (cardCommand == CARDTYPE_OFFSPEED)
				{
					cardCommand = CARDTYPE_STRAIGHT;
					break;
				}
				cardCommand++;
				break;
			}
			break;
		}
	}
	return 0;
}

int battingCardResultDisp(CHOICE_CARD* playersResult, CHOICE_CARD* enemysResult) {
	int cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �_�� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" �_�� ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" ���� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �_�o ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	}
	SHORT plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���@ ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" �@�U ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("���؂�");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" ���� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("  ��  ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	SHORT equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");
	cardPosX = 64, cardPosY = 16;
	getchar();
	CursorPositionSet(cardPosX, cardPosY);
	if (playersResult->plus_type == playersResult->type)
	{
		switch (playersResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�o�b�^�[�@���ŗ́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("ΰ��� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("�@�_��");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�o�b�^�[�@�I�ŗ́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" ���� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" �ł� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�o�b�^�[�@���́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf("�N�Z��");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" �̋Z ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	else
	{
		playersResult->result_power = playersResult->power + playersResult->plus_power;
		switch (playersResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�o�b�^�[�@���ŗ́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].power - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" �_�� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�o�b�^�[�@�I�ŗ́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].tech - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�ω���");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf(" �_�� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�o�b�^�[�@���́@�␳�I�@%+d", yourplayer[order[TEAM_YOU]].speed - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" ���� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �_�o ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@CPU�́@�I���J�[�h�@");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���S ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�ω���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf(" ���S ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �Ɂ@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�} ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	}
	plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�^����");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf(" ���� ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_STRAIGHTPITCHING;
		printf("�@�@�@");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�N�T�C");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�Ƃ���");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_BRAKINGPITCHING;
		printf("�@�@�@");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �x�@ ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf(" �@�� ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_OFFSPEEDPITCHING;
		printf("�@�@�@");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");
	getchar();
	cardPosX = 64, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	if (enemysResult->plus_type == enemysResult->type)
	{
		switch (enemysResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�s�b�`���[�@�����@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("���Ȃ�");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING_EX;
			printf("������");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�s�b�`���[�@�ω����@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].tech - 2;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" ���@ ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING_EX;
			printf(" �@�� ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�s�b�`���[�@�Z�I�@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("�v���X�J�[�h�����{�[�i�X�I�@+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" �ό� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" ���� ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	else
	{
		enemysResult->result_power = enemysResult->power + enemysResult->plus_power;
		switch (enemysResult->type)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(46, 12);
			COLOR_STRAIGHTPITCHING;
			printf("�s�b�`���[�@�����@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].power - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���� ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf(" ���S ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_STRAIGHTPITCHING;
			printf("�@�@�@");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("�s�b�`���[�@�ω����@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].tech - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�ω���");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf(" ���S ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_BRAKINGPITCHING;
			printf("�@�@�@");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("�s�b�`���[�@�Z�I�@�␳�I�@%+d", enemyplayer[NUMBER_PITCHER].speed - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �Ɂ@ ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf(" �@�} ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_OFFSPEEDPITCHING;
			printf("�@�@�@");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@�J�[�h�o�g�����ʁI�@");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(cardPosX, cardPosY, PLAYSIDE_BATTING, &playersChoice);
	resultCardDisp(cardPosX+20, cardPosY, PLAYSIDE_PITCHING, &enemysChoice);
	if (playersResult->type == enemysResult->type)
	{
		CursorPositionSet(58, 12);
		printf("�z���Ɂ@���킹���I");
		CursorPositionSet(58, 13);
		printf("�����{�[�i�X�I�@+2");
		getchar();
		playersResult->result_power += 2;
		resultCardDisp(cardPosX, cardPosY, PLAYSIDE_BATTING, &playersChoice);
	}
	CursorPositionSet(58, 15);
	printf("%d vs %d", playersResult->result_power, enemysResult->result_power);
	if (playersResult->result_power > enemysResult->result_power)
	{
		return RESULT_WIN;
	}
	if (playersResult->result_power < enemysResult->result_power)
	{
		return RESULT_LOSE;
	}
	if (playersResult->result_power == enemysResult->result_power)
	{
		return RESULT_DRAW;
	}
	return 0;
}

void changeAct() {
	system("cls");
	printf("�X���[�A�E�g�I\n�`�F���W�I");
	getchar();
	for (int i = 0; i < 3; i++)
	{
		BSO[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		RUNNER[i] = 0;
	}
	outBox = 0;
	if (_turn == TURN_TOP)
	{
		enemys[_inning - 1].score = _hideScoreCounter;
		_turn = TURN_BOTTOM;
		_hideScoreCounter = 0;
	}
	else
	{
		players[_inning - 1].score = _hideScoreCounter;
		_turn = TURN_TOP;
		_hideScoreCounter = 0;
		_inning++;
	}

}

int battingJudgeCompatibility() {
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@���Ȃ��́@�I���J�[�h�@");
	int result = battingCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
		getchar();
		dispCls_result();
		CursorPositionSet(12, 10);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@/ /");
		CursorPositionSet(12, 11);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ / /");
		CursorPositionSet(12, 12);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@/�O�~} �");
		CursorPositionSet(12, 13);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@r'\"r��`�q");
		CursorPositionSet(12, 14);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@.| r�~~�M�@}�@�@�@�@");
		CursorPositionSet(12, 15);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@j�@(_)�@�@/");
		CursorPositionSet(12, 16);
		printf("�@�@�@�@ �Q,.-�]�]�]-'�R.�@�@ �^�@,�`_�@ �R.");
		CursorPositionSet(12, 17);
		printf("�@�@�@�^,.--�]�]�]��@�@�R.�@�^�@�@/�@ |�@�@�R.");
		CursorPositionSet(12, 18);
		printf("�@�@/�@/ �^>�@�@�R�@,..��R�^�@�@ /�@�@|�@�@ �R.");
		CursorPositionSet(12, 19);
		printf("�@ /�]��/,.-��@�@�@! | 6�^�@�@�@/�@�@�Q|�@�@�@�R");
		CursorPositionSet(12, 20);
		printf("�@ !�=_\"iO�@�R�@�@ �S�^�@�@�@�@. / �] - '\"i�@iZ�@�@}");
		CursorPositionSet(12, 21);
		printf("�@ !�sO�R�R�_�m __ �^|__�@�@�@�^�@{�@�R �R�SZ�@/");
		CursorPositionSet(12, 22);
		printf("�@ �R�R_�m�b�@�^�|�@�@ �k�@ /�Q__�R�@�R�R _���]'");
		CursorPositionSet(12, 23);
		printf("�@�@�R  �@(��݁L|�@�R��Q.�N�@�@�@�Q �R��^");
		for (int i = 3; i >= 0; i--)
		{
			if (RUNNER[i - 1] == TRUE)
			{
				RUNNER[i - 1] = FALSE;
				RUNNER[i] = TRUE;
			}
		}
		RUNNER[RUNNER_FIRST] = 1;
		if (RUNNER[RUNNER_HOME] == TRUE)
		{
			RUNNER[RUNNER_HOME] = FALSE;
			score[TEAM_YOU]++;
			_hideScoreCounter++;
		}
		break;
	case RESULT_LOSE:
		CursorPositionSet(58, 17);
		printf("�O�U�I");
		BSO[COUNT_OUT] += 1;
		outBox = BSO[COUNT_OUT];
		break;
	case RESULT_DRAW:
		CursorPositionSet(58, 17);
		printf("���������I");
		CursorPositionSet(58, 18);
		printf("�t�@�[���I");
		order[TEAM_YOU]--;
		if (BSO[COUNT_STRIKE] < 3)BSO[COUNT_STRIKE] += 1;
		getchar();
		/*int randomNum;
		while (_kbhit() != 1) {
			randomNum = 10 + genrand_int32() % 90;
			CursorPositionSet(58, 17);
			printf("%d �^ 99", randomNum);
		}
		int fortuneResult = randomNum;
		if (fortuneResult >= 50)
		{
			CursorPositionSet(58, 18);
			printf("�q�b�g�I");
			for (int i = 3; i >= 0; i--)
			{
				if (RUNNER[i - 1] == TRUE)
				{
					RUNNER[i - 1] = FALSE;
					RUNNER[i] = TRUE;
				}
			}
			RUNNER[RUNNER_FIRST] = 1;
			if (RUNNER[RUNNER_HOME] == TRUE)
			{
				RUNNER[RUNNER_HOME] = FALSE;
				score[TEAM_YOU]++;
				_hideScoreCounter++;
			}
		}
		else
		{
			CursorPositionSet(58, 18);
			printf("�A�E�g�I");
			BSO[COUNT_OUT] += 1;
			outBox = BSO[COUNT_OUT];
		}
		getchar();
		break;*/
	}
	return 0;
}

void playerStatusDisp(PLAYER* PITCHER, PLAYER* BATTER)
{
	SHORT pitcherX = 74, pitcherY = 8, batterX = 74, batterY = 29;
	//�s�b�`���[�@�\�͕\��
	CursorPositionSet(pitcherX - 2, pitcherY);
	printf("��������������������������������������");
	CursorPositionSet(pitcherX, pitcherY + 1);
	printf("�o�@%s�@�@�@", PITCHER->name);
	CursorPositionSet(pitcherX + 1, pitcherY + 3);
	COLOR_STRAIGHTPITCHING;
	printf(" ���� ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->power]);
	CursorPositionSet(pitcherX + 11, pitcherY + 3);
	COLOR_BRAKINGPITCHING;
	printf(" �ω��� ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->tech]);
	CursorPositionSet(pitcherX + 23, pitcherY + 3);
	COLOR_OFFSPEEDPITCHING;
	printf(" �Z�I ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->speed]);
	CursorPositionSet(pitcherX - 2, pitcherY + 4);
	printf("��������������������������������������");
	//�o�b�^�[�@�\�͕\��
	CursorPositionSet(batterX - 4, batterY);
	printf("�@��������������������������������������");
	CursorPositionSet(batterX - 2, batterY + 1);
	printf("�@%s�@%s�@�@�@", scoreBoardNumber[BATTER->number], BATTER->name);
	CursorPositionSet(batterX - 2, batterY + 3);
	printf("�@�@�@�@�@�@�@�@�@");
	CursorPositionSet(batterX, batterY + 3);
	COLOR_STRAIGHTPITCHING;
	printf(" ���ŗ� ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->power]);
	CursorPositionSet(batterX + 12, batterY + 3);
	COLOR_BRAKINGPITCHING;
	printf(" �I�ŗ� ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->tech]);
	CursorPositionSet(batterX + 24, batterY + 3);
	COLOR_OFFSPEEDPITCHING;
	printf(" ���� ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->speed]);
	CursorPositionSet(batterX - 2, batterY + 4);
	printf("��������������������������������������");

}

int main() {
	preTitle();
	while (1)
	{
		title();
		gameStandby();
		while (_inning <= 9)
		{
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0]);
				playerStatusDisp(&yourplayer[NUMBER_PITCHER], &enemyplayer[order[TEAM_ENEMY]]);
				pitchingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				pitchJudgeCompatibility();
				getchar();
				order[TEAM_ENEMY]++;
				if (order[TEAM_ENEMY] == 10) order[TEAM_ENEMY] = 1;
			}
			changeAct();
			while (BSO[COUNT_OUT] <= 2)
			{
				if (_inning >= 9 && score[TEAM_ENEMY] < score[TEAM_YOU])
				{
					system("cls");
					printf("�T���i�������I�I");
					goto GAMESET;
				}
				display(&RUNNER[0]);
				playerStatusDisp(&enemyplayer[NUMBER_PITCHER], &yourplayer[order[TEAM_YOU]]);
				battingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				if (enemysChoice.plus_power != 5) enemysChoice.plus_power += 1;
				battingJudgeCompatibility();
				getchar();
				order[TEAM_YOU]++;
				if (order[TEAM_YOU] == 10) order[TEAM_YOU] = 1;
			}
			changeAct();
		}
		system("cls");
		printf("�X���[�A�E�g�I\n�Q�[���Z�b�g�I");
		printf("%d �΁@%d\n", score[TEAM_YOU], score[TEAM_ENEMY]);
		if (score[TEAM_YOU] > score[TEAM_ENEMY]) printf("���Ȃ��̏����I�I");
		if (score[TEAM_YOU] < score[TEAM_ENEMY]) printf("���Ȃ��̕����I�I");
		if (score[TEAM_YOU] == score[TEAM_ENEMY]) printf("���������I�I");
	GAMESET:
		getchar();
	}

	return 0;
	//TODO �t�@�[�����@�X�g���C�N�J�E���g������̂͂������@���̌�ŎҌ�㎞���X�g���C�N�J�E���g���ێ�����Ă���
	//TODO ���ʂ���̓I�ɕ\���@�o���G�[�V�����@��ۑŁ`�{�ۑŁi���U�j�@�ł������Ǔ���S���E�t���C
	//TODO ���̂Ƃ���@�����J�[�h��I�ԈȊO�̐헪���@�I��f�[�^�i���ŗ́E�I�ŗ́E���́j�ɉe�� ����́i�����E�ω����E�Z�I�j
	//TODO �_�C�W�F�X�g���[�h�@������x�����Ői��Ł@�`�����X�E�s���`���̂݃v���C
	//TODO �G�𑝂₵�����@�e���r���p���ۂ����_�̊G�@�����Ă�G�@�ł��Ă�G�@���������ł��������ʁi�z�[�������Ȃ獋�؂ȉ��o�I�j


	//�z���g�ɗ]�T��������@SE OpenAL

}