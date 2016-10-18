#define _CRT_SECURE_NO_WARNINGS
#define COLOR_BALLZONEFLAME SetConsoleTextAttribute(hConsoleOutput,BACKGROUND_GREEN| BACKGROUND_INTENSITY)
#define COLOR_STRIKEZONE SetConsoleTextAttribute(hConsoleOutput,BACKGROUND_GREEN | BACKGROUND_RED |BACKGROUND_INTENSITY)
#define COLOR_DEFAULT printf("\x1b[49m"); printf("\x1b[39m");
#define COLOR_BALLCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_STRIKECOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_OUTCOUNT SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_INTENSITY)
#define COLOR_RUNNER SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
#define COLOR_BRAKINGBALL SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)

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
int _inning = 7;
int _turn = TURN_BOTTOM;
int score[2] = { 33,4 };

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

int display(int BSO[3], PLAYER* PITCHER, PLAYER* BATTER) {
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	printf("\n　G %d\n　H %d\t\t\t\t", score[0], score[1]);
	////ピッチャー　情報
	//printf("\t\tP %s\n\t\t\t\t\t", PITCHER->name);
	//printf("\t球速 ");	//ピッチャー　球速
	//switch (PITCHER->pitch_speed) {
	//case RANK_G:
	//	printf("G");
	//	break;
	//case RANK_F:
	//	printf("F");
	//	break;
	//case RANK_E:
	//	printf("E");
	//	break;
	//case RANK_D:
	//	printf("D");
	//	break;
	//case RANK_C:
	//	printf("C");
	//	break;
	//case RANK_B:
	//	printf("B");
	//	break;
	//case RANK_A:
	//	printf("A");
	//	break;
	//}
	//printf("\tコントロール ");	//ピッチャー　球速
	//switch (PITCHER->pitch_controll) {
	//case RANK_G:
	//	printf("G");
	//	break;
	//case RANK_F:
	//	printf("F");
	//	break;
	//case RANK_E:
	//	printf("E");
	//	break;
	//case RANK_D:
	//	printf("D");
	//	break;
	//case RANK_C:
	//	printf("C");
	//	break;
	//case RANK_B:
	//	printf("B");
	//	break;
	//case RANK_A:
	//	printf("A");
	//	break;
	//}
	printf("\n B ");
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
	////変化球表示　←◎→
	//COLOR_DEFAULT;
	//printf("\t\t\t\t\t　　");
	//if (PITCHER->breaking_ball[1] == 1) {
	//	COLOR_BRAKINGBALL;
	//	printf("―");	//変化球　左
	//	COLOR_DEFAULT;
	//}
	//else printf("―");
	//printf("　　◎　　");
	//if (PITCHER->breaking_ball[5] == 1) {
	//	COLOR_BRAKINGBALL;
	//	printf("―");//変化球　右
	//	COLOR_DEFAULT;
	//}
	//else printf("―");
	printf("\n S ");
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
	COLOR_BALLZONEFLAME;
	printf("\t\t\t");
	printf("　");	//ボールゾーン 1-1 ┏
	printf("　");	//ボールゾーン 1-2 ━
	printf("◆");	//ボールゾーン 1-3 ━
	printf("　");	//ボールゾーン 1-4 ━
	printf("　");	//ボールゾーン 1-5 ┓
	COLOR_DEFAULT;
	////変化球表示　／　＼
	//if (PITCHER->breaking_ball[2] == 1) {
	//	COLOR_BRAKINGBALL;
	//	printf("\t\t　　　／");	//変化球　左下
	//	COLOR_DEFAULT;
	//}
	//else printf("\t\t　　　／");
	//if (PITCHER->breaking_ball[4] == 1) {
	//	COLOR_BRAKINGBALL;
	//	printf("　　　＼\n");//変化球　右下
	//	COLOR_DEFAULT;
	//}
	//else printf("　　　＼\n");
	printf(" O ");
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
	COLOR_BALLZONEFLAME;
	printf("\t\t\t");
	printf("　");	//ボールゾーン2-1
	COLOR_STRIKEZONE;
	printf("／");	//ストライクゾーン2-2
	printf("　");	//ストライクゾーン2-3
	printf("＼");	//ストライクゾーン2-4
	COLOR_BALLZONEFLAME;
	printf("　");	//ボールゾーン2-5
	////変化球表示　↓
	//COLOR_DEFAULT;
	//if (PITCHER->breaking_ball[3] == 1) {
	//	COLOR_BRAKINGBALL;
	//	printf("\t\t\t　｜\n\t\t\t");	//変化球　下
	//	COLOR_DEFAULT;
	//}
	//else printf("\t\t\t　｜\n\t\t\t");
	COLOR_BALLZONEFLAME;
	printf("◆");	//ボールゾーン3-1
	COLOR_STRIKEZONE;
	printf("　");	//ストライクゾーン3-2
	printf("　");	//ストライクゾーン3-3
	printf("　");	//ストライクゾーン3-4
	COLOR_BALLZONEFLAME;
	printf("◆\n\t\t\t");	//ボールゾーン3-5
	printf("　");	//ボールゾーン4-1
	COLOR_STRIKEZONE;
	printf("＼");	//ストライクゾーン4-2
	printf("　");	//ストライクゾーン4-3
	printf("／");	//ストライクゾーン4-4
	COLOR_BALLZONEFLAME;
	printf("　\n");	//ボールゾーン4-4
	COLOR_RUNNER;
	printf("　　◆\t\t\t");	//塁表示　二塁
	COLOR_BALLZONEFLAME;
	printf("　");	//ボールゾーン 5-1 ┗
	printf("　");	//ボールゾーン 5-2 ━
	printf("▼");	//ボールゾーン 5-3 ━
	printf("　");	//ボールゾーン 5-4 ━
	printf("　");	//ボールゾーン 5-5 ┛
	COLOR_RUNNER;
	printf("\n　◆　");	//塁表示　三塁
	printf("◇");	//塁表示　一塁
	COLOR_DEFAULT;
	printf("\t\t\t\t\t%d %s\n　", BATTER->number, BATTER->name);
	printf("%d回", _inning);
	switch (_turn) {
	case TURN_TOP:
		printf("表");
		break;
	case TURN_BOTTOM:
		printf("ウラ");
		break;
	}
	printf("\t\t\t\t\tパワー ");
	switch (BATTER->power) {
	case RANK_G:
		printf("G");
		break;
	case RANK_F:
		printf("F");
		break;
	case RANK_E:
		printf("E");
		break;
	case RANK_D:
		printf("D");
		break;
	case RANK_C:
		printf("C");
		break;
	case RANK_B:
		printf("B");
		break;
	case RANK_A:
		printf("A");
		break;
	}
	printf("\t");
	printf("走力 ");	//バッター　走力
	switch (BATTER->speed) {
	case RANK_G:
		printf("G");
		break;
	case RANK_F:
		printf("F");
		break;
	case RANK_E:
		printf("E");
		break;
	case RANK_D:
		printf("D");
		break;
	case RANK_C:
		printf("C");
		break;
	case RANK_B:
		printf("B");
		break;
	case RANK_A:
		printf("A");
		break;
	}
	return 0;
}

int pitching_ball(PLAYER* PITCHER) {
	int command = 0;
	int enterFlag = FALSE;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PitchCursorPosition = {
		0,  // SHORT X
		21 }; // SHORT Y
	SetConsoleTextAttribute(hConsoleOutput, FOREGROUND_RED);
	printf("\n\n\n\n∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥∵‥∴‥∴‥∵‥∴‥\n\n");
	COLOR_DEFAULT;
	printf(" ＃ ピッチングフェイズ ＃\n\n");
	printf(" 球種を選択してください\n");
	while (enterFlag == FALSE)
	{
		SetConsoleCursorPosition(
			hConsoleOutput,     // HANDLE hConsoleOutput
			PitchCursorPosition);  // COORD dwCursorPosition
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
	printf("\nボール選択完了！\n");
	return 0;
}

int attack_turn() {
	pitching_ball(&_01_1);

	return 0;
}

int main() {
	title();
	teamSelect();
	display(BSOp, &_01_1, &_02_4);
	attack_turn();
	getchar();
	return 0;
}