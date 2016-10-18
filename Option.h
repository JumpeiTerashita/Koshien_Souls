#pragma once

#pragma comment(lib,"winmm")
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
#define COLOR_DEFAULT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN)
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
#define COLOR_ESCAPE SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY| BACKGROUND_GREEN)
#define COLOR_ESCAPE_FLAME SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define NUMBER_PITCHER 9



//列挙体たち
enum teams {
	TEAM_YOU,
	TEAM_ENEMY
};
enum statusRANK {
	RANK_E,
	RANK_D,
	RANK_C,
	RANK_B,
	RANK_A
};
enum turns {
	TURN_TOP,
	TURN_BOTTOM
};
enum cardtypes {
	CARDTYPE_STRAIGHT,
	CARDTYPE_BRAKING,
	CARDTYPE_OFFSPEED,
	CARDTYPE_ESCAPE,
	CARDTYPE_NONE
};
enum playside {
	PLAYSIDE_PITCHING,
	PLAYSIDE_BATTING
};
enum result {
	RESULT_WIN,
	RESULT_LOSE,
	RESULT_DRAW,
	RESULT_ESCAPE,
	RESULT_ENEMYESCAPE
};
enum count {
	COUNT_BALL,
	COUNT_STRIKE,
	COUNT_OUT
};
enum runner {
	RUNNER_FIRST,
	RUNNER_SECOND,
	RUNNER_THIRD,
	RUNNER_HOME
};
enum title_gameType {
	GAMETYPE_CLIMAX,
	GAMETYPE_DIGEST,
	GAMETYPE_FULLPLAY,
	GAMETYPE_EXTREME
};
enum hit {
	HIT_NO,
	HIT_SINGLE,
	HIT_TWO_BASE,
	HIT_THREE_BASE,
	HIT_HOMERUN
};


//構造体定義たち
typedef struct {
	int number;
	char name[16];
	int power;
	int tech;
	int speed;
}PLAYER;
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
typedef struct {
	int inning;
	int turn;
	int outCount;
	int orderStart;
	int runnerSet[4];
}DIGEST_MANAGER;

//変数・構造体たち extern
extern HANDLE hConsoleOutput;
extern COORD CursorPosition , dwSize;
extern SMALL_RECT consoleWindow;
extern PLAYER yourplayer[],enemyplayer[],extraplayer[];
extern CHOICE_CARD playersChoice,enemysChoice;
extern SCOREMANAGER players[15],enemys[15];
extern DIGEST_MANAGER pinch[], chance[];
extern void CursorPositionSet(SHORT x, SHORT y);
extern int outBox, RUNNER[4], _inning, _turn, _hideScoreCounter, score[2], order[2];
extern char scoreBoardNumber[][16], cardPowerNumber[][16], statusChar[][16], title_Names[][16];
static int BSO[3];
static int* BSOp;



