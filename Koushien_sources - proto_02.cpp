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
		"けつばん",
		0,
		0,
		0
	},
	{
		1,
		"まつもと",
		RANK_D,
		RANK_C,
		RANK_A
	},
	{
		2,
		"しのすか",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		3,
		"くろまて",
		RANK_A,
		RANK_B,
		RANK_E
	},
	{
		4,
		"たつのり",
		RANK_A,
		RANK_C,
		RANK_D
	},
	{
		5,
		"よしむら",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		6,
		"なかはた",
		RANK_C,
		RANK_C,
		RANK_C
	},
	{
		7,
		"こうの",
		RANK_C,
		RANK_C,
		RANK_B
	},
	{
		8,
		"やまくら",
		RANK_B,
		RANK_C,
		RANK_D
	},
	{
		9,
		"えがわ",
		RANK_B,
		RANK_C,
		RANK_B
	},
};
PLAYER enemyplayer[] = {
	{
		0,
		"けつばん",
		0,
		0,
		0
	},
	{
		1,
		"まゆみ",
		RANK_A,
		RANK_A,
		RANK_B
	},
	{
		2,
		"よしたけ",
		RANK_C,
		RANK_C,
		RANK_A
	},
	{
		3,
		"ばあす",
		RANK_A,
		RANK_A,
		RANK_E
	},
	{
		4,
		"かけふ",
		RANK_A,
		RANK_B,
		RANK_D
	},
	{
		5,
		"おかだ",
		RANK_B,
		RANK_B,
		RANK_C
	},
	{
		6,
		"さの",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		7,
		"ひらた",
		RANK_D,
		RANK_C,
		RANK_C
	},
	{
		8,
		"きど",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		9,
		"いけだ",
		RANK_C,
		RANK_B,
		RANK_B
	},
};


char title_Names[][16] = {
	"クライマックス",
	"ダイジェスト",
	"フルプレイ",
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
	"０",
	"１",
	"２",
	"３",
	"４",
	"５",
	"６",
	"７",
	"８",
	"９",
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
	"〇",
	"①",
	"②",
	"③",
	"④",
	"⑤",
	"⑥",
	"⑦",
	"⑧",
	"⑨",
	"⑩",
	"⑪",
	"⑫",
	"⑬",
	"⑭",
	"⑮",
	"⑯",
	"⑰",
	"⑱",
	"⑲",
	"⑳"
};

char statusChar[][16] = {
	"Ｅ",
	"Ｄ",
	"Ｃ",
	"Ｂ",
	"Ａ"
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
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t*―――――――――――――――――――――――――――――――――*\n");
	printf("\n\n\n\t\t\t\t\t\t\t最大化表示での　プレイを推奨します\n\t\t\t\t\t\t\t変更し終わったら　エンターキーを　押してください\n\n");
	printf("\n\n\t\t\t\t\t\t*―――――――――――――――――――――――――――――――――*");
	getchar();
}

int title() {
	int cursor = 0;
	bool enterFlag = FALSE;
	while (enterFlag == FALSE)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t　oooo    oooo                    oooo         o8o                              .oooooo..o   .oooooo.   ooooo     ooo ooooo         .oooooo..o \n");
		printf("\t　`888   .8P'                     `888         `\"'                             d8P'    `Y8  d8P'  `Y8b  `888'     `8' `888'        d8P'    `Y8 \n");
		printf("\t　 888  d8'     .ooooo.   .oooo.o  888 .oo.   oooo   .ooooo.  ooo. .oo.        Y88bo.      888      888  888       8   888         Y88bo.      \n");
		printf("\t　 88888[      d88' `88b d88(  \"8  888P\"Y88b  `888  d88' `88b `888P\"Y88b        `\"Y8888o.  888      888  888       8   888          `\"Y8888o.  \n");
		printf("\t　 888`88b.    888   888 `\"Y88b.   888   888   888  888ooo888  888   888            `\"Y88b 888      888  888       8   888              `\"Y88b \n");
		printf("\t　 888  `88b.  888   888 o.  )88b  888   888   888  888    .o  888   888       oo     .d8P `88b    d88'  `88.    .8'   888       o oo     .d8P \n");
		printf("\t　o888o  o888o `Y8bod8P' 8\"\"888P' o888o o888o o888o `Y8bod8P' o888o o888o      8\"\"88888P'   `Y8bood8P'     `YbodP'    o888ooooood8 8\"\"88888P'  ");
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t");
		for (int i = 0; i < 3; i++)
		{

			if (cursor == i)
			{
				printf("＞　%s\t\t", title_Names[i]);
			}
			else
			{
				printf("　　%s\t\t", title_Names[i]);
			}
		}
		switch (cursor)
		{
		case GAMETYPE_CLIMAX:
			printf("\n\n\n\n\n\n\t\t9回からプレイします\n");
			break;
		case GAMETYPE_DIGEST:
			printf("\n\n\n\n\n\n\t\t1回から　ピンチ・チャンス時のみプレイします\n");
			break;
		case GAMETYPE_FULLPLAY:
			printf("\n\n\n\n\n\n\t\t1回から　全てのイニングをプレイします\n");
			break;
		}
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:	//←
				if (cursor == GAMETYPE_CLIMAX)
				{
					cursor = GAMETYPE_FULLPLAY;
					break;
				}
				cursor--;
				break;
			case 0x4d:	//→
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
	printf("888　 　　　　　　　　　　　　　　　　 　  に|\n");
	printf("888　 　 　　　　　　　　　　　　　　　 　__|＿\n");
	printf("888　 　 　 　 　　 　 　 　 　 に|    ┌’㊦‘┐   に| \n");
	printf("＝||　 　 　　 　 　 　 　 ＿＿＿|＿＿| ：｡｡　   |＿_|＿＿＿_\n");
	printf("　|| 　 　 　　　　　　　　| E EEEEEEE! ’ 　　　EEEEEEEEE!  |\n");
	printf("＿||.＿＿＿＿＿＿＿___＿＿_| E EEEEEEE!　=== 　　   … …   _|＿＿＿＿＿＿＿＿＿＿＿＿_\n");
	printf("| |関数ﾍﾟｲﾝﾀ| | TMR |.|      E EEEEEEE!　EEE!　   ｡｡｡｡｡｡　.|京セラミド|ｼﾞｬｯﾊﾟﾝレンタカー|\n");
	printf("三三三三三三三三三|――――――――――――――――――――――|三三三三三三三三三三三三三三三三三三三三三三\n");
	printf("三三三三三三三三三|　 　 　 携帯！は三菱電機　 　 　　　　　　 |三三三三三三三三三三三三三三三三三三三\n");
	printf("三三三三三三三三三|――――――――――――――――――――――|三三三三三三三三三三三三三三三三\n");
	printf(" 三三三三三三三三三三三/l　 |　　　　 　 　 　 　|　  |i三三三三三三三三三三三三三三三三三三\n");
	printf("三三三三三三三三三三三/_|＿|＿＿＿＿＿＿＿＿＿＿|＿|,l三三三三三三三三三三三三三三三三\n");
	printf("　　 　　　Ｂａｎａｎａｔｉｃ　　i⌒i　　　　　　　　 　 　 　 　 　 将来設計\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	printf("\n\n");
	printf("　　 _＿_,,,,,,,,,,,,,,,,,.........ー￣￣￣ー--~.................,,,,,,,,,,,,,,,\n");
	printf("￣ ￣　　　　　　　　          　　　　 　 　　 　 　 　 　 　　　　　　￣￣\"\"\"\n");
	printf("\n 　　　　　　　,. -‐ ﾑヽ──ﾆﾉｰ' - ..");
	printf("\n\n");
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　 _,,..､ - ‐ '''' \n");
	printf("　　　　　　　　　　　　　　　　　　　　_,,..､ - ‐ '''' \"´\n");
	printf("＿＿　　　　 ＿＿＿_ ,,..､ - ‐ '''' \"´\n");
	printf("　 ／ ＝　／　　　 ／\n");
	printf("／　　 ／　　 　／\n");
	printf("　　 ／￣￣￣\n");
	printf("_,／\n");
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
		printf("◆");
		COLOR_DEFAULT;
	}
	else printf("◆");
	CursorPositionSet(baseLeft + 4, baseTop + 1);
	printf("／　＼");
	CursorPositionSet(baseLeft + 2, baseTop + 2);
	printf("／　　　＼");
	CursorPositionSet(baseLeft, baseTop + 3);
	if (RUNNER[RUNNER_THIRD] == TRUE) {
		COLOR_RUNNER;
		printf("◆");
		COLOR_DEFAULT;
	}
	else printf("◆");
	if (RUNNER[RUNNER_FIRST] == TRUE) {
		COLOR_RUNNER;
		printf("　　　　　◆");
		COLOR_DEFAULT;
	}
	else printf("　　　　　◆");
	CursorPositionSet(baseLeft + 2, baseTop + 4);
	printf("＼　　　／");
	CursorPositionSet(baseLeft + 4, baseTop + 5);
	SHORT scoreDispX = 8, scoreDispY = 6;
	CursorPositionSet(scoreDispX, scoreDispY);
	printf("来 %d - 地 %d", score[TEAM_ENEMY], score[TEAM_YOU]);
	CursorPositionSet(scoreDispX + 3, scoreDispY + 1);
	printf("%d回", _inning);
	switch (_turn) {
	case TURN_TOP:
		printf("表");
		break;
	case TURN_BOTTOM:
		printf("ｳﾗ");
		break;
	}
	SHORT ballCountDispX = 10, ballCountDispY = 3;
	CursorPositionSet(ballCountDispX, ballCountDispY);
	printf("B ");
	COLOR_BALLCOUNT;
	switch (BSO[COUNT_BALL])	//ボールカウント
	{
	case 0:
		printf("○○○");
		break;
	case 1:
		printf("●○○");
		break;
	case 2:
		printf("●●○");
		break;
	case 3:
		printf("●●●");
		break;
	}
	COLOR_DEFAULT;
	CursorPositionSet(ballCountDispX, ballCountDispY + 1);
	printf("S ");
	COLOR_STRIKECOUNT;
	switch (BSO[COUNT_STRIKE])	//ストライクカウント
	{
	case 0:
		printf("○○");
		break;
	case 1:
		printf("●○");
		break;
	case 2:
		printf("●●");
		break;
	}
	COLOR_DEFAULT;
	CursorPositionSet(ballCountDispX, ballCountDispY + 2);
	printf("O ");
	COLOR_OUTCOUNT;
	switch (BSO[COUNT_OUT])	//アウトカウント
	{
	case 0:
		printf("○○");
		break;
	case 1:
		printf("●○");
		break;
	case 2:
		printf("●●");
		break;
	}
	COLOR_DEFAULT;
	SHORT scoreBoardDispX = 26, scoreBoardDispY = 2;
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY);
	printf("┌──┰─┬─┬─┬─┬─┬─┬─┬─┬─┐\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 1);
	printf("│来馬┃　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 2);
	printf("├──╂─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 3);
	printf("│地文┃　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 4);
	printf("└──┸─┴─┴─┴─┴─┴─┴─┴─┴─┘\n");
	CursorPositionSet(scoreBoardDispX + 8, scoreBoardDispY - 1);
	printf("１　２　３　４　５　６　７　８　９");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 中心 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 中心 ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 緩　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　急 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("┗───");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("真っ向");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 勝負 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("クサイ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("ところ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 警　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　戒 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("┗───");
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
	printf("\n\n\n\n∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥\n　　　　　　\n");
	COLOR_DEFAULT;
	printf(" ＃ ピッチングフェイズ ＃\n\n");
	printf(" カードを選択してください\n");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		pitchCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 速球中心 ");
			COLOR_DEFAULT;
			printf("　    : 渾身の ストレートで 三振を 狙います 　");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" 変化球中心 ");
			COLOR_DEFAULT;
			printf("　  : 変化球で 揺さぶり 三振を 狙います　　 ");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 緩急 ");
			COLOR_DEFAULT;
			printf("　　　    : 球速差で リズムを 狂わせます　　　 　 ");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		}
		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : ダメダメ　　");
			break;
		case 2:
			printf(" : 打たれやすい");
			break;
		case 3:
			printf(" : フツウ　　　");
			break;
		case 4:
			printf(" : 打たれにくい");
			break;
		case 5:
			printf(" : サイコー　　");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n");
	}
	CursorPositionSet(0, 38);
	printf(" プラスカードを　選択してください\n");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 真っ向勝負 ");
			COLOR_DEFAULT;
			printf("　  : 大胆なコースに 投げ込みます　　　　　　");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" クサイところ ");
			COLOR_DEFAULT;
			printf("　: ストライクゾーンギリギリを 狙います　　");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 警戒 ");
			COLOR_DEFAULT;
			printf("　　　    : バントや　スクイズを　警戒します　");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		}

		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : ダメダメ　　");
			break;
		case 2:
			printf(" : 打たれやすい");
			break;
		case 3:
			printf(" : フツウ　　　");
			break;
		case 4:
			printf(" : 打たれにくい");
			break;
		case 5:
			printf(" : サイコー　　");
			break;
		}
		CursorPositionSet(45, 44);
		switch (playersChoice.type)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
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
		printf(" 相性 ");
		COLOR_DEFAULT;
		if (cardCommand == playersChoice.type)
		{
			printf(" :　良好　");
		}
		else printf(" :　フツウ");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n");
	}
	CursorPositionSet(12, 9);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	CursorPositionSet(12, 10);
	printf("　〓━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━〓　");
	for (int i = 11; i < 25; i++)
	{
		CursorPositionSet(12, (SHORT)i);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	}
	CursorPositionSet(12, 23);
	printf("　〓━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━〓　");
	CursorPositionSet(12, 24);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
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
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_STRAIGHTPITCHING_EX;
				printf("うなる");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_STRAIGHTPITCHING_EX;
				printf("豪速球");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				CursorPositionSet(cardPosX, cardPosY);
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_BRAKINGPITCHING_EX;
				printf(" 魔　 ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_BRAKINGPITCHING_EX;
				printf(" 　球 ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" 変幻 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" 自在 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
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
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf(" 速球 ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf(" 中心 ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("変化球");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf(" 中心 ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");

				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf(" 緩　 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf(" 　急 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
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
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_STRAIGHTPITCHING_EX;
				printf("ﾎｰﾑﾗﾝ ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_STRAIGHTPITCHING_EX;
				printf("　狙い");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				CursorPositionSet(cardPosX, cardPosY);
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_BRAKINGPITCHING_EX;
				printf(" 悪球 ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_BRAKINGPITCHING_EX;
				printf(" 打ち ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_OFFSPEEDPITCHING_EX;
				printf("クセ者");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_OFFSPEEDPITCHING_EX;
				printf(" の技 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
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
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf(" 速球 ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf(" 狙い ");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_STRAIGHTPITCHING;
				printf("　　　");
				COLOR_STRAIGHTPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_BRAKING:
				COLOR_BRAKINGPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("変化球");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf(" 狙い ");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_BRAKINGPITCHING;
				printf("　　　");
				COLOR_BRAKINGPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
				printf("%s", cardPowerNumber[result->result_power]);
				COLOR_DEFAULT;
				break;
			case CARDTYPE_OFFSPEED:
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("%s", cardPowerNumber[result->result_power]);
				printf("───┓");
				CursorPositionSet(cardPosX, cardPosY + 1);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 2);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf(" 反射 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 3);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf(" 神経 ");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 4);
				printf("│");
				COLOR_OFFSPEEDPITCHING;
				printf("　　　");
				COLOR_OFFSPEEDPITCHING_FLAME;
				printf("│");
				CursorPositionSet(cardPosX, cardPosY + 5);
				printf("┗───");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 中心 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 中心 ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 緩　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　急 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	}
	SHORT plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("真っ向");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 勝負 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("クサイ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("ところ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 警　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　戒 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	SHORT equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");
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
			printf("ピッチャー　球速　補正！　%+d", yourplayer[NUMBER_PITCHER].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("うなる");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("豪速球");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("ピッチャー　変化球　補正！　%+d", yourplayer[NUMBER_PITCHER].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].tech - 2;
			printf("プラスカード相性ボーナス！　+2");
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 魔　 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 　球 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("ピッチャー　技巧　補正！　%+d", yourplayer[NUMBER_PITCHER].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" 変幻 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" 自在 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
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
			printf("ピッチャー　球速　補正！　%+d", yourplayer[NUMBER_PITCHER].power - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 速球 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 中心 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("ピッチャー　変化球　補正！　%+d", yourplayer[NUMBER_PITCHER].tech - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("変化球");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf(" 中心 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("ピッチャー　技巧　補正！　%+d", yourplayer[NUMBER_PITCHER].speed - 2);
			playersResult->result_power += yourplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 緩　 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 　急 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　CPUの　選択カード　");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 狙い ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 狙い ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 反射 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 神経 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	}
	plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 強　 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 　振 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("見切り");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("搦め手");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");
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
			printf("バッター　長打力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("ﾎｰﾑﾗﾝ ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("　狙い");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("バッター　巧打力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 悪球 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 打ち ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("バッター　走力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf("クセ者");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" の技 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
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
			printf("バッター　長打力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].power - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 速球 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 狙い ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("バッター　巧打力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].tech - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("変化球");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf(" 狙い ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("バッター　走力　補正！　%+d", enemyplayer[order[TEAM_ENEMY]].speed - 2);
			enemysResult->result_power += enemyplayer[order[TEAM_ENEMY]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 反射 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 神経 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　カードバトル結果！　");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(20, 15, PLAYSIDE_PITCHING, &playersChoice);
	resultCardDisp(40, 15, PLAYSIDE_BATTING, &enemysChoice);
	if (playersResult->type == enemysResult->type)
	{
		CursorPositionSet(58, 12);
		printf("配球に　合わされた！");
		CursorPositionSet(58, 13);
		printf("相性ボーナス！　+2");
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
	printf("　あなたの　選択カード　");
	int result = pitchCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
		CursorPositionSet(58, 17);
		printf("三振！");
		BSO[COUNT_OUT] += 1;
		outBox = BSO[COUNT_OUT];
		break;
	case RESULT_LOSE:
		CursorPositionSet(58, 17);
		printf("打たれた！");
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
		printf("引き分け！");
		CursorPositionSet(58, 18);
		printf("ファール！");
		order[TEAM_ENEMY]--;
		if (BSO[COUNT_STRIKE] < 3)BSO[COUNT_STRIKE] += 1;
		getchar();
		/*int randomNum;
		while (_kbhit() != 1) {
			randomNum = 10 + genrand_int32() % 90;
			CursorPositionSet(58, 17);
			printf("%d ／ 99", randomNum);
		}
		int fortuneResult = randomNum;
		if (fortuneResult >= 50)
		{
			CursorPositionSet(58, 18);
			printf("ヒット！");
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
			printf("アウト！");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 狙い ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 狙い ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 反射 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 神経 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("┗───");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 強　 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 　振 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		if (cardCursolIs == CARDTYPE_BRAKING) cardPosY -= 1;
		CursorPositionSet(cardPosX + 13, cardPosY);
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 13, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("見切り");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 13, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[cardPower]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		if (cardCursolIs == CARDTYPE_OFFSPEED) cardPosY -= 1;
		CursorPositionSet(cardPosX + 26, cardPosY);
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[cardPower]);
		printf("───┓");
		CursorPositionSet(cardPosX + 26, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 搦め ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("  手  ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 26, cardPosY + 5);
		printf("┗───");
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
	printf("\n\n\n\n∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥\n　　　　　　\n");
	COLOR_DEFAULT;
	printf(" ＃ バッティングフェイズ ＃\n\n");
	printf(" カードを選択してください\n");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		battingCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 速球狙い ");
			COLOR_DEFAULT;
			printf("　    : 狙い球を 直球に 絞ります　　　　　");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" 変化球中心 ");
			COLOR_DEFAULT;
			printf("　  : 狙い球を 変化球に 絞ります　　　　　 ");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 反射神経 ");
			COLOR_DEFAULT;
			printf("　　　    : 狙い球を 絞らず スイングします　 ");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		}
		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : ダメダメ　　");
			break;
		case 2:
			printf(" : 打たれやすい");
			break;
		case 3:
			printf(" : フツウ　　　");
			break;
		case 4:
			printf(" : 打たれにくい");
			break;
		case 5:
			printf(" : サイコー　　");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　\n");
	}
	CursorPositionSet(0, 38);
	printf(" プラスカードを　選択してください\n");
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
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		battingPlusCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingPlusCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingPlusCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 強振 ");
			COLOR_DEFAULT;
			printf("　  : 思いっきり 全力で スイングします　　");
			CursorPositionSet(46, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_BRAKINGPITCHING;
			printf(" 見切り ");
			COLOR_DEFAULT;
			printf("　: 厳しいコースの球も よく見て対処します　");
			CursorPositionSet(46, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(45, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 搦め手 ");
			COLOR_DEFAULT;
			printf("　　　    : バントや　スクイズを　試みます　");
			CursorPositionSet(46, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		}

		switch (cardPowerBox[cardCommand])
		{
		case 1:
			printf(" : ダメダメ　　");
			break;
		case 2:
			printf(" : 打たれやすい");
			break;
		case 3:
			printf(" : フツウ　　　");
			break;
		case 4:
			printf(" : 打たれにくい");
			break;
		case 5:
			printf(" : サイコー　　");
			break;
		}
		CursorPositionSet(45, 44);
		switch (playersChoice.type)
		{
		case CARDTYPE_STRAIGHT:
			COLOR_STRAIGHTPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
			break;
		case CARDTYPE_BRAKING:
			COLOR_BRAKINGPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
			break;
		case CARDTYPE_OFFSPEED:
			COLOR_OFFSPEEDPITCHING;
			printf(" 選択済みカード ");
			COLOR_DEFAULT;
			printf(" との ");
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
		printf(" 相性 ");
		COLOR_DEFAULT;
		if (cardCommand == playersChoice.type)
		{
			printf(" :　良好　");
		}
		else printf(" :　フツウ");
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
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 狙い ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 狙い ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 反射 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 神経 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->power]);
		COLOR_DEFAULT;
		break;
	}
	SHORT plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 強　 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 　振 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("見切り");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 搦め ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("  手  ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[playersResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	SHORT equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");
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
			printf("バッター　長打力　補正！　%+d", yourplayer[order[TEAM_YOU]].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("ﾎｰﾑﾗﾝ ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("　狙い");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("バッター　巧打力　補正！　%+d", yourplayer[order[TEAM_YOU]].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 悪球 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 打ち ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("バッター　走力　補正！　%+d", yourplayer[order[TEAM_YOU]].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			playersResult->result_power = playersResult->power + playersResult->plus_power + 2;
			playersResult->result_power += yourplayer[order[TEAM_YOU]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf("クセ者");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" の技 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
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
			printf("バッター　長打力　補正！　%+d", yourplayer[order[TEAM_YOU]].power - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 速球 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 狙い ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("バッター　巧打力　補正！　%+d", yourplayer[order[TEAM_YOU]].tech - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("変化球");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf(" 狙い ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("バッター　走力　補正！　%+d", yourplayer[order[TEAM_YOU]].speed - 2);
			playersResult->result_power += yourplayer[order[TEAM_YOU]].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[playersResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 反射 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 神経 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[playersResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　CPUの　選択カード　");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 速球 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 中心 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("変化球");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf(" 中心 ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 緩　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　急 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->power]);
		COLOR_DEFAULT;
		break;
	}
	plusMarkX = 30, plusMarkY = 18;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->plus_type) {
	case CARDTYPE_STRAIGHT:
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("真っ向");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf(" 勝負 ");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_STRAIGHTPITCHING;
		printf("　　　");
		COLOR_STRAIGHTPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_BRAKING:
		COLOR_BRAKINGPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("クサイ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("ところ");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_BRAKINGPITCHING;
		printf("　　　");
		COLOR_BRAKINGPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;
	case CARDTYPE_OFFSPEED:
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 警　 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf(" 　戒 ");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_OFFSPEEDPITCHING;
		printf("　　　");
		COLOR_OFFSPEEDPITCHING_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("%s", cardPowerNumber[enemysResult->plus_power]);
		COLOR_DEFAULT;
		break;

	}
	equalMarkX = 53, equalMarkY = 18;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");
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
			printf("ピッチャー　球速　補正！　%+d", enemyplayer[NUMBER_PITCHER].power - 2);
			CursorPositionSet(46, 14);
			COLOR_STRAIGHTPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("うなる");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING_EX;
			printf("豪速球");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("ピッチャー　変化球　補正！　%+d", enemyplayer[NUMBER_PITCHER].tech - 2);
			CursorPositionSet(46, 14);
			COLOR_BRAKINGPITCHING;
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].tech - 2;
			printf("プラスカード相性ボーナス！　+2");
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 魔　 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING_EX;
			printf(" 　球 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("ピッチャー　技巧　補正！　%+d", enemyplayer[NUMBER_PITCHER].speed - 2);
			CursorPositionSet(46, 14);
			COLOR_OFFSPEEDPITCHING;
			printf("プラスカード相性ボーナス！　+2");
			enemysResult->result_power = enemysResult->power + enemysResult->plus_power + 2;
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" 変幻 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING_EX;
			printf(" 自在 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
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
			printf("ピッチャー　球速　補正！　%+d", enemyplayer[NUMBER_PITCHER].power - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].power - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 速球 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf(" 中心 ");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_STRAIGHTPITCHING;
			printf("　　　");
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(46, 12);
			COLOR_BRAKINGPITCHING;
			printf("ピッチャー　変化球　補正！　%+d", enemyplayer[NUMBER_PITCHER].tech - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].tech - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("変化球");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf(" 中心 ");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_BRAKINGPITCHING;
			printf("　　　");
			COLOR_BRAKINGPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(46, 12);
			COLOR_OFFSPEEDPITCHING;
			printf("ピッチャー　技巧　補正！　%+d", enemyplayer[NUMBER_PITCHER].speed - 2);
			enemysResult->result_power += enemyplayer[NUMBER_PITCHER].speed - 2;
			CursorPositionSet(cardPosX, cardPosY);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 緩　 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf(" 　急 ");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_OFFSPEEDPITCHING;
			printf("　　　");
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("%s", cardPowerNumber[enemysResult->result_power]);
			COLOR_DEFAULT;
			break;
		}
	}
	getchar();
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　カードバトル結果！　");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(cardPosX, cardPosY, PLAYSIDE_BATTING, &playersChoice);
	resultCardDisp(cardPosX+20, cardPosY, PLAYSIDE_PITCHING, &enemysChoice);
	if (playersResult->type == enemysResult->type)
	{
		CursorPositionSet(58, 12);
		printf("配球に　合わせた！");
		CursorPositionSet(58, 13);
		printf("相性ボーナス！　+2");
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
	printf("スリーアウト！\nチェンジ！");
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
	printf("　あなたの　選択カード　");
	int result = battingCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
		getchar();
		dispCls_result();
		CursorPositionSet(12, 10);
		printf("　　　　　　　　　　　　　　　　　　　　/ /");
		CursorPositionSet(12, 11);
		printf("　　　　　　　　　　　　　　　　　　　 / /");
		CursorPositionSet(12, 12);
		printf("　　　　　　　　　　　　　　　　　　/三ミ} ﾌ");
		CursorPositionSet(12, 13);
		printf("　　　　　　　　　　　　　　　　　r'\"rﾆﾆ`〈");
		CursorPositionSet(12, 14);
		printf("　　　　　　　　　　　　　　　　.| rﾆ~~｀　}　　　　");
		CursorPositionSet(12, 15);
		printf("　　　　　　　　　　　　　　　　j　(_)　　/");
		CursorPositionSet(12, 16);
		printf("　　　　 ＿,.-‐‐‐-'ヽ.　　 ／　,Ａ_　 ヽ.");
		CursorPositionSet(12, 17);
		printf("　　　／,.--‐‐‐､　　ヽ.　／　　/　 |　　ヽ.");
		CursorPositionSet(12, 18);
		printf("　　/　/ ／>　　ヽ　,..､ヽ／　　 /　　|　　 ヽ.");
		CursorPositionSet(12, 19);
		printf("　 /‐┘/,.-､　　　! | 6／　　　/　　＿|　　　ヽ");
		CursorPositionSet(12, 20);
		printf("　 !ﾆ=_\"iO　ヽ　　 ヾ／　　　　. / ‐ - '\"i　iZ　　}");
		CursorPositionSet(12, 21);
		printf("　 !ＴOヽヽ､_ノ __ ／|__　　　／　{　ヽ ヽヾZ　/");
		CursorPositionSet(12, 22);
		printf("　 ヽヽ_ノＣ　／ﾝ|　　 Ｌ　 /＿__ヽ　ヽヽ _＞‐'");
		CursorPositionSet(12, 23);
		printf("　　ヽ  　(∠ﾝ´|　ヽ､＿.ク　　　＿ ヽ､／");
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
		printf("三振！");
		BSO[COUNT_OUT] += 1;
		outBox = BSO[COUNT_OUT];
		break;
	case RESULT_DRAW:
		CursorPositionSet(58, 17);
		printf("引き分け！");
		CursorPositionSet(58, 18);
		printf("ファール！");
		order[TEAM_YOU]--;
		if (BSO[COUNT_STRIKE] < 3)BSO[COUNT_STRIKE] += 1;
		getchar();
		/*int randomNum;
		while (_kbhit() != 1) {
			randomNum = 10 + genrand_int32() % 90;
			CursorPositionSet(58, 17);
			printf("%d ／ 99", randomNum);
		}
		int fortuneResult = randomNum;
		if (fortuneResult >= 50)
		{
			CursorPositionSet(58, 18);
			printf("ヒット！");
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
			printf("アウト！");
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
	//ピッチャー　能力表示
	CursorPositionSet(pitcherX - 2, pitcherY);
	printf("┏─────────────────┓");
	CursorPositionSet(pitcherX, pitcherY + 1);
	printf("Ｐ　%s　　　", PITCHER->name);
	CursorPositionSet(pitcherX + 1, pitcherY + 3);
	COLOR_STRAIGHTPITCHING;
	printf(" 球速 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->power]);
	CursorPositionSet(pitcherX + 11, pitcherY + 3);
	COLOR_BRAKINGPITCHING;
	printf(" 変化球 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->tech]);
	CursorPositionSet(pitcherX + 23, pitcherY + 3);
	COLOR_OFFSPEEDPITCHING;
	printf(" 技巧 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[PITCHER->speed]);
	CursorPositionSet(pitcherX - 2, pitcherY + 4);
	printf("┗─────────────────┛");
	//バッター　能力表示
	CursorPositionSet(batterX - 4, batterY);
	printf("　┏─────────────────┓");
	CursorPositionSet(batterX - 2, batterY + 1);
	printf("　%s　%s　　　", scoreBoardNumber[BATTER->number], BATTER->name);
	CursorPositionSet(batterX - 2, batterY + 3);
	printf("　　　　　　　　　");
	CursorPositionSet(batterX, batterY + 3);
	COLOR_STRAIGHTPITCHING;
	printf(" 長打力 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->power]);
	CursorPositionSet(batterX + 12, batterY + 3);
	COLOR_BRAKINGPITCHING;
	printf(" 巧打力 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->tech]);
	CursorPositionSet(batterX + 24, batterY + 3);
	COLOR_OFFSPEEDPITCHING;
	printf(" 走力 ");
	COLOR_DEFAULT;
	printf(" %s ", statusChar[BATTER->speed]);
	CursorPositionSet(batterX - 2, batterY + 4);
	printf("┗─────────────────┛");

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
					printf("サヨナラ勝ち！！");
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
		printf("スリーアウト！\nゲームセット！");
		printf("%d 対　%d\n", score[TEAM_YOU], score[TEAM_ENEMY]);
		if (score[TEAM_YOU] > score[TEAM_ENEMY]) printf("あなたの勝ち！！");
		if (score[TEAM_YOU] < score[TEAM_ENEMY]) printf("あなたの負け！！");
		if (score[TEAM_YOU] == score[TEAM_ENEMY]) printf("引き分け！！");
	GAMESET:
		getchar();
	}

	return 0;
	//TODO ファール時　ストライクカウントあげるのはいいが　その後打者交代時もストライクカウントが維持されている
	//TODO 結果を具体的に表示　バリエーション　一塁打～本塁打（強振）　打ったけど内野ゴロ・フライ
	//TODO 今のところ　強いカードを選ぶ以外の戦略性　選手データ（長打力・巧打力・走力）に影響 投手は（球速・変化球・技巧）
	//TODO ダイジェストモード　ある程度自動で進んで　チャンス・ピンチ時のみプレイ
	//TODO 絵を増やしたい　テレビ中継っぽい視点の絵　投げてる絵　打ってる絵　投げた→打った→結果（ホームランなら豪華な演出！）


	//ホントに余裕あったら　SE OpenAL

}