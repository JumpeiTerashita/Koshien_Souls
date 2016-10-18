#include "Option.h"

//�J�[�\���ړ��֐�
void CursorPositionSet(SHORT x, SHORT y) {
	CursorPosition = {
		x,  // SHORT X
		y }; // SHORT Y
	SetConsoleCursorPosition(hConsoleOutput, CursorPosition);
}

//�\���̂����@���̐錾
HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition = { 0,0 };
COORD dwSize = { 9999, 9999 };
SMALL_RECT consoleWindow = { 40,10, 49,180 };
SCOREMANAGER players[15];
SCOREMANAGER enemys[15];
CHOICE_CARD playersChoice = { 0 };
CHOICE_CARD enemysChoice = { 0 };
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
PLAYER extraplayer[] = {
	{
		0,
		"���΂�",
		0,
		0,
		0
	},
	{
		1,
		"������[",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		2,
		"�Ȃ�����",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		3,
		"������",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		4,
		"���傤����",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		5,
		"���������",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		6,
		"��������",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		7,
		"����ނ�",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		8,
		"��������",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		9,
		"�_���r",
		RANK_A,
		RANK_A,
		RANK_A
	},
};
DIGEST_MANAGER pinch[] = {
	{
		3,
		TURN_TOP,
		0,
		8,
		{0,1,0,0}
	},
	{
		7,
		TURN_TOP,
		1,
		6,
		{1,1,0,0}
	}
};
DIGEST_MANAGER chance[] = {
	{
		5,
		TURN_BOTTOM,
		1,
		9,
		{0,1,1,0}
	},
	{
		8,
		TURN_BOTTOM,
		2,
		2,
		{1,1,1,0}
	}
};
//�ϐ������@�錾
int outBox = 0;
int RUNNER[4] = { 0,0,0,0 };
int _inning = 9;
int _turn = TURN_TOP;
int _hideScoreCounter = 0;
int score[2] = { 0,0 };
int order[2] = { 1,1 };


//�����e�[�u��
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
char title_Names[][16] = {
	"�N���C�}�b�N�X",
	"�_�C�W�F�X�g",
	"�t���v���C",
	"�G�N�X�g���[��"
};

