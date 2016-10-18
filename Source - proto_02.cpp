#define _CRT_SECURE_NO_WARNINGS
#define COLOR_BALLZONEFLAME SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_GREEN)
#define COLOR_STRIKEZONE SetConsoleTextAttribute(hConsoleOutput,FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_GREEN | BACKGROUND_RED)
#define COLOR_DEFAULT printf("\x1b[49m"); printf("\x1b[39m");
#define COLOR_BALLCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_STRIKECOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_OUTCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_INTENSITY)
#define COLOR_RUNNER SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_BRAKINGBALL SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define CORSOL_SET SetConsoleCursorPosition(hConsoleOutput,CursorPosition)

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "MT.h"

enum {
	RANK_G,
	RANK_F,
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
	int team_number;
	int number;
	char name[16];
	int power;
	int speed;
	int pitch_speed;
	int pitch_controll;
	int breaking_ball[6];
}PLAYER;

PLAYER _01_1{
	1,
	9,
	"しげの",
	RANK_B,
	RANK_C,
	RANK_A,
	RANK_B,
	{1,0,0,1,0,0}
};

PLAYER _02_4{
	2,
	4,
	"ギブソンJr",
	RANK_A,
	RANK_C,
	RANK_F,
	RANK_F,
	{0}
};

int BSO[3] = { 3,1,2 };
int* BSOp = BSO;
int RUNNER[4] = { 0,1,1,1 };
int* RUNp = RUNNER;
int _inning = 7;
int _turn = TURN_BOTTOM;
int score[2] = { 3,4 };
HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition = {
	0,  // SHORT X
	0 }; // SHORT Y

enum {
	BALL_STRAIGHT,
	BALL_SLIDER,
	BALL_CURVE,
	BALL_FORKBALL,
	BALL_SINKER,
	BALL_SHOOT,
	BALL_MAX			//コマンドの数
};

char breaking_ball_Names[][16] = {
	"ストレート",
	"スライダー",
	"カーブ",
	"フォーク",
	"シンカー",
	"シュート"
};

void CursorPositionSet(SHORT x, SHORT y) {
	CursorPosition = {
		x,  // SHORT X
		y }; // SHORT Y
	CORSOL_SET;
}

int title() {
	printf("タイトル");
	getchar();
	return 0;
}

int teamSelect() {
	system("cls");
	printf("チーム選択");
	getchar();
	return 0;
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
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　 _,,..､ - ‐ '''' \"´\n");
	printf("　　　　　　　　　　　　　　　　　　　　_,,..､ - ‐ '''' \"´\n");
	printf("＿＿　　　　 ＿＿＿_ ,,..､ - ‐ '''' \"´\n");
	printf("　 ／ ＝　／　　　 ／\n");
	printf("／　　 ／　　 　／\n");
	printf("　　 ／￣￣￣\n");
	printf("_,／\n");
}

int display(int BSO[3], int RUNNER[4], PLAYER* PITCHER, PLAYER* BATTER) {
	system("cls");
	ballPark();
	SHORT baseLeft = 6, baseTop = 1;
	CursorPositionSet(baseLeft + 6, baseTop);
	if (RUNNER[2] == TRUE) {
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
	printf("◆");
	printf("　　　　　◆");
	CursorPositionSet(baseLeft + 2, baseTop + 4);
	printf("＼　　　／");
	CursorPositionSet(baseLeft + 4, baseTop + 5);
	SHORT scoreDispX = 8, scoreDispY = 6;
	CursorPositionSet(scoreDispX, scoreDispY);
	printf("作 %d - 北 %d", score[0], score[1]);
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
	switch (BSO[0])	//ボールカウント
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
	switch (BSO[1])	//ストライクカウント
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
	switch (BSO[2])	//アウトカウント
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
	printf("│作新┃　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 2);
	printf("├──╂─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 3);
	printf("│北海┃　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 4);
	printf("└──┸─┴─┴─┴─┴─┴─┴─┴─┴─┘\n");
	CursorPositionSet(scoreBoardDispX + 8, scoreBoardDispY - 1);
	printf("１　２　３　４　５　６　７　８　９");



	return 0;
}

int pitching_ball(PLAYER* PITCHER) {
CHOICE:
	int command = 0;
	int enterFlag = FALSE;
	CursorPositionSet(0, 30);
	SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	printf("\n\n\n\n∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥\n　　　　　　\n");
	COLOR_DEFAULT;
	printf(" ＃ ピッチングフェイズ ＃\n\n");
	printf(" 球種を選択してください\n");
	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		for (int i = 0; i < 6; i++)
		{

			if (PITCHER->breaking_ball[i] == 1) {
				if (i == command)
				{
					printf(" > %s\n", breaking_ball_Names[i]);
				}
				else printf("   %s\n", breaking_ball_Names[i]);
			}
			else {
				if (i == command) {
					printf(" >");
				}
				else printf("  ");
				SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
				printf(" %s\n", breaking_ball_Names[i]);
				COLOR_DEFAULT;
			}
		}
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x48:
				if (command != 0) command--;
				break;
			case 0x50:
				if (command != 5) command++;
				break;
			}
			break;
		}
	}
	if (PITCHER->breaking_ball[command] == 0) {
		printf("その球種は　ピッチャーが覚えていません！\n球種を再選択してください");
		getchar();
		display(BSOp, RUNp, &_01_1, &_02_4);
		goto CHOICE;
	}
	printf("\n球種選択　完了！\n");
	getchar();
	display(BSOp, RUNp, &_01_1, &_02_4);
	CursorPositionSet(0, 30);
	SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	printf("\n\n\n\n∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥\n　　　　　　\n");
	COLOR_DEFAULT;
	printf(" ＃ ピッチングフェイズ ＃\n\n");
	printf(" 投げるコースを選択してください\n");
	enterFlag = FALSE;
	int pitchArea[5][5] = { 0 };
	pitchArea[2][2] = 1;
	int pitchAreaX = 2, pitchAreaY = 2;
	while (enterFlag == FALSE)
	{
		CursorPositionSet(2, 40);
		for (int i = 0; i < 5; i++)
		{
			for (int k = 0; k < 5; k++)
			{
				if ((i >= 1 && i <= 3) && (k >= 1 && k <= 3)) COLOR_STRIKEZONE; 
				else COLOR_BALLZONEFLAME;
				if (pitchArea[k][i] == 1)
				{
					printf("●");
				}
				else printf("　");
				COLOR_DEFAULT;
			}
			printf("\n　");
		}
		switch (_getch()) {
		case 0x0d:
			enterFlag = TRUE;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x48:
				if (pitchAreaY != 0)
				{
					pitchArea[pitchAreaX][pitchAreaY] = 0;
					pitchAreaY--;
					pitchArea[pitchAreaX][pitchAreaY] = 1;
				}
				break;
			case 0x50:
				if (pitchAreaY != 4)
				{
					pitchArea[pitchAreaX][pitchAreaY] = 0;
					pitchAreaY++;
					pitchArea[pitchAreaX][pitchAreaY] = 1;
				}
				break;
			case 0x4b:
				if (pitchAreaX != 0)
				{
					pitchArea[pitchAreaX][pitchAreaY] = 0;
					pitchAreaX--;
					pitchArea[pitchAreaX][pitchAreaY] = 1;
				}

				break;
			case 0x4d:
				if (pitchAreaX != 4)
				{
					pitchArea[pitchAreaX][pitchAreaY] = 0;
					pitchAreaX++;
					pitchArea[pitchAreaX][pitchAreaY] = 1;
				}
				break;
			}
			break;
		}
	}

	getchar();
	return 0;
}

int attack_turn() {
	pitching_ball(&_01_1);

	return 0;
}

int main() {
	title();
	teamSelect();
	display(BSOp, RUNp, &_01_1, &_02_4);
	getchar();
	pitching_ball(&_01_1);
	return 0;
}