#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "MT.h"
#include "Option.h"

#pragma comment(lib,"winmm")

void preTitle() {
	SetConsoleScreenBufferSize(
		hConsoleOutput, // HANDLE hConsoleOutput
		dwSize);        // COORD dwSize
	SetConsoleWindowInfo(
		hConsoleOutput, // HANDLE hConsoleOutput
		TRUE,           // BOOL bAbsolute
		&consoleWindow);// CONST SMALL_RECT *lpConsoleWindow

	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t*―――――――――――――――――――――――――――――――――*\n");
	printf("\n\n\n\t\t\t\t\t\t\t最大化表示での　プレイを推奨します\n\t\t\t\t\t\t\t変更し終わったら　エンターキーを　押してください\n\n");
	printf("\n\n\t\t\t\t\t\t*―――――――――――――――――――――――――――――――――*");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC );
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
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:	//←
				PlaySound("ku.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cursor == GAMETYPE_CLIMAX)
				{
					cursor = GAMETYPE_FULLPLAY;
					break;
				}
				cursor--;
				break;
			case 0x4d:	//→
				PlaySound("ku.wav", NULL, SND_FILENAME | SND_ASYNC);
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
	return cursor;
}

void gameStandby() {
	for (int i = 0; i < 15; i++)
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
	order[TEAM_ENEMY] = 1;
	order[TEAM_YOU] = 1;
}

void ruleDescription() {
	system("cls");
	printf("\n\t\t＃ ルール説明 ＃\n\n");
	printf("\n\n\t\tカード・プラスカードを選択し、試合が進行します\n\n");
	CursorPositionSet(20, 8);
	printf("～ カード説明 ～");
	int cardPosX = 20, cardPosY = 10;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	CursorPositionSet(34, 11);
	printf("カードは四種類あります");
	CursorPositionSet(34, 13);
	printf("カードの左上には「カードの強さ」が書かれています");
	CursorPositionSet(34, 14);
	printf("①～⑤までの強さのカードが　ランダムで配られます");

	cardPosX = 20, cardPosY = 18;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 17, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[2]);
	printf("───┓");
	CursorPositionSet(cardPosX + 17, cardPosY + 1);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("　　　");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 2);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("変化球");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 3);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf(" 中心 ");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 4);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("　　　");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 5);
	printf("┗───");
	printf("%s", cardPowerNumber[2]);
	CursorPositionSet(cardPosX + 34, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
	printf("───┓");
	CursorPositionSet(cardPosX + 34, cardPosY + 1);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf("　　　");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 2);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf(" 緩　 ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 3);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf(" 　急 ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 4);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf("　　　");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 5);
	printf("┗───");
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 51, cardPosY);
	COLOR_ESCAPE_FLAME;
	printf("●");
	printf("───┓");
	CursorPositionSet(cardPosX + 51, cardPosY + 1);
	printf("│");
	COLOR_ESCAPE;
	printf("　　　");
	COLOR_ESCAPE_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 51, cardPosY + 2);
	printf("│");
	COLOR_ESCAPE;
	printf(" 一球 ");
	COLOR_ESCAPE_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 51, cardPosY + 3);
	printf("│");
	COLOR_ESCAPE;
	printf("はずせ");
	COLOR_ESCAPE_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 51, cardPosY + 4);
	printf("│");
	COLOR_ESCAPE;
	printf("　　　");
	COLOR_ESCAPE_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 51, cardPosY + 5);
	printf("┗───");
	printf("●");
	COLOR_DEFAULT;

	CursorPositionSet(14, 25);
	printf("カードの種類ごとに　選手の能力も影響します");
	CursorPositionSet(16, 27);
	COLOR_STRAIGHTPITCHING;
	printf(" 赤色のカード ");
	COLOR_DEFAULT;
	printf("　　なら　　");
	COLOR_STRAIGHTPITCHING;
	printf(" 球速 ");
	COLOR_DEFAULT;
	printf(" ・ ");
	COLOR_STRAIGHTPITCHING;
	printf(" 長打力 ");
	COLOR_DEFAULT;
	CursorPositionSet(16, 29);
	COLOR_BRAKINGPITCHING;
	printf(" 青色のカード ");
	COLOR_DEFAULT;
	printf("　　なら　　");
	COLOR_BRAKINGPITCHING;
	printf(" 変化球 ");
	COLOR_DEFAULT;
	printf(" ・ ");
	COLOR_BRAKINGPITCHING;
	printf(" 巧打力 ");
	COLOR_DEFAULT;
	CursorPositionSet(16, 31);
	COLOR_OFFSPEEDPITCHING;
	printf(" 黄色のカード ");
	COLOR_DEFAULT;
	printf("　　なら　　");
	COLOR_OFFSPEEDPITCHING;
	printf(" 技巧 ");
	COLOR_DEFAULT;
	printf(" ・ ");
	COLOR_OFFSPEEDPITCHING;
	printf(" 走力 ");
	COLOR_DEFAULT;
	CursorPositionSet(14, 33);
	printf("の値（ Ｅ　～　Ａ ）　により　補正（ -2　～　+2 ）がかかります");
	CursorPositionSet(14, 35);
	printf("たとえば ");
	COLOR_STRAIGHTPITCHING;
	printf(" 球速中心 ");
	COLOR_DEFAULT;
	printf(" を ");
	COLOR_STRAIGHTPITCHING;
	printf(" 球速 ");
	COLOR_DEFAULT;
	printf(" Ｂ のピッチャーで選ぶと カードパワーに +1 の能力補正！");
	CursorPositionSet(16, 38);
	COLOR_ESCAPE;
	printf(" 緑色のカード ");
	COLOR_DEFAULT;
	printf("　　は　　");
	COLOR_DEFAULT;
	printf("エスケープカードです");
	CursorPositionSet(16, 40);
	printf("一球外し、カードを配り直します");
	CursorPositionSet(16, 41);
	printf("カードの強さが　イマイチなときに　有効です");
	CursorPositionSet(120, 43);
	printf("＃ Enterキーで　次の説明に　移ります ＃");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	system("cls");
	printf("\n\t\t＃ ルール説明 ＃\n\n");
	CursorPositionSet(20, 4);
	printf("～ プラスカード説明 ～");
	cardPosX = 20, cardPosY = 7;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	CursorPositionSet(34, 8);
	printf("プラスカードは三種類あります");
	CursorPositionSet(34, 10);
	printf("プラスカードも同様に　カードの左上に「カードの強さ」が書かれていて");
	CursorPositionSet(34, 11);
	printf("①～⑤までの強さのカードが　ランダムで配られます");

	cardPosX = 20, cardPosY = 15;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 17, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[2]);
	printf("───┓");
	CursorPositionSet(cardPosX + 17, cardPosY + 1);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("　　　");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 2);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("クサイ");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 3);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("ところ");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 4);
	printf("│");
	COLOR_BRAKINGPITCHING;
	printf("　　　");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 17, cardPosY + 5);
	printf("┗───");
	printf("%s", cardPowerNumber[2]);
	CursorPositionSet(cardPosX + 34, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
	printf("───┓");
	CursorPositionSet(cardPosX + 34, cardPosY + 1);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf("　　　");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 2);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf(" 警　 ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 3);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf(" 　戒 ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 4);
	printf("│");
	COLOR_OFFSPEEDPITCHING;
	printf("　　　");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("│");
	CursorPositionSet(cardPosX + 34, cardPosY + 5);
	printf("┗───");
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	CursorPositionSet(16, 23);
	printf("カードとプラスカードの強さを足し合わせたものが　最終的な強さになります");
	cardPosX = 20, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	SHORT plusMarkX = 33, plusMarkY = 27;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");

	cardPosX = 44, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	SHORT equalMarkX = 58, equalMarkY = 27;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");

	cardPosX = 70, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[8]);
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
	printf("%s", cardPowerNumber[8]);
	COLOR_DEFAULT;
	cardPosX = 20, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	plusMarkX = 33, plusMarkY = 34;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("　┏┓　");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("┏┛┗┓");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("┗┓┏┛");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("　┗┛　");

	cardPosX = 44, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[3]);
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
	printf("%s", cardPowerNumber[3]);
	COLOR_DEFAULT;

	equalMarkX = 58, equalMarkY = 34;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("┗━━┛");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("┏━━┓");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("┗━━┛");

	cardPosX = 70, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[10]);
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
	printf("%s", cardPowerNumber[10]);
	COLOR_DEFAULT;
	CursorPositionSet(16, 39);
	printf("同じ色のカード・プラスカードを選ぶと 最終カードが パワーアップします！（+2　ボーナス！）");
	CursorPositionSet(16, 40);
	printf("積極的に　狙っていきましょう！");
	CursorPositionSet(120, 43);
	printf("＃ Enterキーで　次の説明に　移ります ＃");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	system("cls");
	printf("\n\t\t＃ ルール説明 ＃\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t　 ＿＿　　　 ＿＿\n");
	printf("\t`∠＿＿＼　 ／＿＿＼\n");
	printf("\t∥･ω･`|｜ / |･ω･|｜\n");
	printf("\t/￣￣￣　Ｖ/| ￣⊂二)\n");
	printf("\tL二⊃　 |∪ |　　　｜\n");
	printf("\tヽ＿⊃ ノ　 |　/＼_ﾉ\n");
	printf("\t＿_(_／　 ＿ヽﾉ＿\n");
	CursorPositionSet(20, 4);
	printf("～ カードバトル説明 ～");
	cardPosX = 20, cardPosY = 8;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[7]);
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
	printf("%s", cardPowerNumber[7]);
	COLOR_DEFAULT;
	cardPosX = 40, cardPosY = 8;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[6]);
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
	printf("%s", cardPowerNumber[6]);
	COLOR_DEFAULT;
	CursorPositionSet(65, 8);
	printf("ピッチャーと バッターの 最終カードの強さを比較して");
	CursorPositionSet(65, 10);
	printf("ピッチャーのほうが 強いときは　三振！");
	CursorPositionSet(65, 11);
	printf("バッターのほうが　 強いときは　ヒット！");
	CursorPositionSet(65, 12);
	printf("お互いの　強さが　 同じときは　ファール！");

	cardPosX = 20, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[7]);
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
	printf("%s", cardPowerNumber[7]);
	COLOR_DEFAULT;
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[8]);
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
	printf("%s", cardPowerNumber[8]);
	COLOR_DEFAULT;
	CursorPositionSet(65, 16);
	printf("ピッチャーと　バッターが　同じ色のカードを選択した場合");
	CursorPositionSet(65, 18);
	printf("バッター側は 『配球を読んだ』ことになり カードが強くなります （+2　ボーナス）");
	CursorPositionSet(60, 31);
	printf("あなたの手で　チームを優勝させましょう！");

	CursorPositionSet(120, 43);
	printf("＃ Enterキーで　プレイボール！！ ＃");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
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
	printf("三三三三三三三三三|　 　 　 やがていのちに変わるもの。　　　　 |三三三三三三三三三三三三三三三三三三三\n");
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

int display(int* RUNNER, static int* BSO) {
	system("cls");
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
	printf("┌──┰─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 1);
	printf("│来馬┃　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 2);
	printf("├──╂─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 3);
	printf("│地文┃　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 4);
	printf("└──┸─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘\n");
	CursorPositionSet(scoreBoardDispX + 8, scoreBoardDispY - 1);
	printf("１　２　３　４　５　６　７　８　９　10　11　12　13　14　15");
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
	case CARDTYPE_ESCAPE:
		if (cardCursolIs == CARDTYPE_ESCAPE) cardPosY -= 1;
		CursorPositionSet(cardPosX + 39, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX + 39, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf("はずせ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 5);
		printf("┗───");
		printf("●");
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
	pitchCardDisp(0, CARDTYPE_ESCAPE, CARDTYPE_NONE);

	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		pitchCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		pitchCardDisp(0, CARDTYPE_ESCAPE, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 速球中心 ");
			COLOR_DEFAULT;
			printf("　    : 渾身の ストレートで 三振を 狙います 　");
			CursorPositionSet(59, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_BRAKINGPITCHING;
			printf(" 変化球中心 ");
			COLOR_DEFAULT;
			printf("　  : 変化球で 揺さぶり 三振を 狙います　　 ");
			CursorPositionSet(59, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 緩急 ");
			COLOR_DEFAULT;
			printf("　　　    : 球速差で リズムを 狂わせます　　　 　 ");
			CursorPositionSet(59, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_ESCAPE:
			CursorPositionSet(45, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_ESCAPE;
			printf(" 一球はずせ ");
			COLOR_DEFAULT;
			printf("    : 一球　ボール球を投げて 様子を見ます  ");
			CursorPositionSet(59, 42);
			COLOR_DEFAULT;
			printf("　　　　　　　　　　　　　　 ");
			break;
		}
		if (cardCommand != CARDTYPE_ESCAPE) {
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
		}
		switch (_getch()) {
		case 0x0d:
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			enterFlag = TRUE;
			playersChoice.power = cardPowerBox[cardCommand];
			playersChoice.type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_ESCAPE;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cardCommand == CARDTYPE_ESCAPE)
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
	if (playersChoice.type != CARDTYPE_ESCAPE) {
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
				PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
				enterFlag = TRUE;
				playersChoice.plus_power = cardPowerBox[cardCommand];
				playersChoice.plus_type = cardCommand;
				break;
			case 0xe0:
				switch (_getch()) {
				case 0x4b:
					PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
					if (cardCommand == CARDTYPE_STRAIGHT)
					{
						cardCommand = CARDTYPE_OFFSPEED;
						break;
					}
					cardCommand--;
					break;
				case 0x4d:
					PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
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
	}
	return 0;
}

void enemyCardChoice() {
	int cardPowerMaker;
	int cardPowerBox[3] = { 0 };
	if ((genrand_int32() % 100 + 1) <= 18)
	{
		enemysChoice.type = CARDTYPE_ESCAPE;
		return;
	}
	else
	{
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
	}
	return;
}

void dispCls_result() {
	CursorPositionSet(0, 34);
	for (int i = 0; i < 13; i++)
	{
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　    　　　　　　　　　　　　　　\n");
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

//TODO ヒット結果確率関数
int hitResultOutput(int cardType, int plusCardType) {
	
		CursorPositionSet(58, 18);
		int resultMaker = genrand_int32() % 100 + 1;
		if (resultMaker < 50)
		{
			printf("一塁打！");
			PlaySound("1ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_SINGLE;
		}
		else if (resultMaker < 75)
		{
			printf("二塁打！");
			PlaySound("2ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_TWO_BASE;
		}
		else if (resultMaker < 90)
		{
			printf("三塁打！");
			PlaySound("3ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_THREE_BASE;
		}
		else
		{
			printf("ホームラン！");
			PlaySound("karan.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_HOMERUN;
		}

}

void hitResultAct(int resultBox) {
	for (int n = 0; n < resultBox; n++)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (RUNNER[i - 1] == TRUE)
			{
				RUNNER[i - 1] = FALSE;
				RUNNER[i] = TRUE;
			}
		}
		if (RUNNER[RUNNER_HOME] == TRUE)
		{
			RUNNER[RUNNER_HOME] = FALSE;
			int getScore;
			if (_turn == TURN_TOP) getScore = TEAM_ENEMY;
			else getScore = TEAM_YOU;
			score[getScore]++;
			_hideScoreCounter++;
		}
	}
	RUNNER[resultBox - 1] = 1;
	if (RUNNER[RUNNER_HOME] == TRUE)
	{
		RUNNER[RUNNER_HOME] = FALSE;
		int getScore;
		if (_turn == TURN_TOP) getScore = TEAM_ENEMY;
		else getScore = TEAM_YOU;
		score[getScore]++;
		_hideScoreCounter++;
	}
}

void resultCardDisp(SHORT cardPosX, SHORT cardPosY, bool cardSide, CHOICE_CARD* result) {
	CursorPositionSet(cardPosX, cardPosY);
	switch (cardSide)
	{
	case PLAYSIDE_PITCHING:
		if (result->type == CARDTYPE_ESCAPE)
		{
			COLOR_ESCAPE_FLAME;
			printf("●");
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_ESCAPE;
			printf("　　　");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_ESCAPE;
			printf(" 一球 ");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_ESCAPE;
			printf("はずせ");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_ESCAPE;
			printf("　　　");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("●");
			COLOR_DEFAULT;
		}
		else if (result->plus_type == result->type)
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
		if (result->type == CARDTYPE_ESCAPE)
		{
			COLOR_ESCAPE_FLAME;
			printf("●");
			printf("───┓");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("│");
			COLOR_ESCAPE;
			printf("　　　");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("│");
			COLOR_ESCAPE;
			printf(" 一球 ");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("│");
			COLOR_ESCAPE;
			printf(" 待て ");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("│");
			COLOR_ESCAPE;
			printf("　　　");
			COLOR_ESCAPE_FLAME;
			printf("│");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("┗───");
			printf("●");
			COLOR_DEFAULT;
		}
		else if (result->plus_type == result->type)
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
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf("はずせ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("●");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　CPUの　選択カード　");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf(" 待て ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("●");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ENEMYESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ENEMYESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　カードバトル結果！　");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(20, 15, PLAYSIDE_PITCHING, &playersChoice);
	resultCardDisp(40, 15, PLAYSIDE_BATTING, &enemysChoice);
	if (enemysChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("一球　やりすごされた！");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ENEMYESCAPE;
	}
	else if (playersChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("ボール球で　やりすごした！");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ESCAPE;
	}
	else
	{
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
	{
		CursorPositionSet(58, 17);
		printf("三振！");
		PlaySound("bun.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_WIN;
	}
	case RESULT_LOSE:
	{
		CursorPositionSet(58, 17);
		printf("打たれた！");
		PlaySound("kin.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		int battingResult = hitResultOutput(enemysChoice.type, enemysChoice.plus_type);
		hitResultAct(battingResult);
		return RESULT_LOSE;
	}
	case RESULT_DRAW:
	{
		CursorPositionSet(58, 17);
		printf("引き分け！");
		PlaySound("tata.wav", NULL, SND_FILENAME | SND_ASYNC);
		CursorPositionSet(58, 18);
		printf("ファール！");
		return RESULT_DRAW;
	}
	case RESULT_ENEMYESCAPE:
		return RESULT_ENEMYESCAPE;
	case RESULT_ESCAPE:
		return RESULT_ESCAPE;
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
	case CARDTYPE_ESCAPE:
		if (cardCursolIs == CARDTYPE_ESCAPE) cardPosY -= 1;
		CursorPositionSet(cardPosX + 39, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX + 39, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf(" 待て ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX + 39, cardPosY + 5);
		printf("┗───");
		printf("●");
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
	battingCardDisp(0, CARDTYPE_ESCAPE, CARDTYPE_NONE);
	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		CursorPositionSet(0, 46);
		printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
		battingCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		battingCardDisp(0, CARDTYPE_ESCAPE, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" 速球狙い ");
			COLOR_DEFAULT;
			printf("　    : 狙い球を 直球に 絞ります　　　　　");
			CursorPositionSet(59, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_BRAKINGPITCHING;
			printf(" 変化球中心 ");
			COLOR_DEFAULT;
			printf("　  : 狙い球を 変化球に 絞ります　　　　　 ");
			CursorPositionSet(59, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" 反射神経 ");
			COLOR_DEFAULT;
			printf("　　　    : 狙い球を 絞らず スイングします　 ");
			CursorPositionSet(59, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("カードの強さ  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_ESCAPE:
			CursorPositionSet(45, 46);
			printf("▲");
			CursorPositionSet(58, 40);
			COLOR_ESCAPE;
			printf(" 一球待て ");
			COLOR_DEFAULT;
			printf("　    : 一球 様子を見ます  　　　　　　　　　　　");
			CursorPositionSet(59, 42);
			COLOR_DEFAULT;
			printf("　　　　　　　　　　　　　　 ");
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
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			enterFlag = TRUE;
			playersChoice.power = cardPowerBox[cardCommand];
			playersChoice.type = cardCommand;
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:
				PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cardCommand == CARDTYPE_STRAIGHT)
				{
					cardCommand = CARDTYPE_ESCAPE;
					break;
				}
				cardCommand--;
				break;
			case 0x4d:
				PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cardCommand == CARDTYPE_ESCAPE)
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
	if (playersChoice.type != CARDTYPE_ESCAPE)
	{
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
				PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
				enterFlag = TRUE;
				playersChoice.plus_power = cardPowerBox[cardCommand];
				playersChoice.plus_type = cardCommand;
				break;
			case 0xe0:
				switch (_getch()) {
				case 0x4b:
					PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
					if (cardCommand == CARDTYPE_STRAIGHT)
					{
						cardCommand = CARDTYPE_OFFSPEED;
						break;
					}
					cardCommand--;
					break;
				case 0x4d:
					PlaySound("syu.wav", NULL, SND_FILENAME | SND_ASYNC);
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
	}
	return 0;
}

int battingCardResultDisp(CHOICE_CARD* playersResult, CHOICE_CARD* enemysResult) {
	int cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (playersResult->type)
	{
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf(" 待て ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("●");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　CPUの　選択カード　");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("●");
		printf("───┓");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("│");
		COLOR_ESCAPE;
		printf(" 一球 ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("│");
		COLOR_ESCAPE;
		printf("はずせ");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("│");
		COLOR_ESCAPE;
		printf("　　　");
		COLOR_ESCAPE_FLAME;
		printf("│");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("┗───");
		printf("●");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ENEMYESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ENEMYESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　カードバトル結果！　");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(cardPosX, cardPosY, PLAYSIDE_BATTING, &playersChoice);
	resultCardDisp(cardPosX + 20, cardPosY, PLAYSIDE_PITCHING, &enemysChoice);
	if (enemysChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("一球　やりすごされた！");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ENEMYESCAPE;
	}
	else if (playersChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("一球　やりすごした！");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ESCAPE;
	}
	else
	{
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
}

void changeAct() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t　　　 ＿＿_\n\t　　 ／＿＿_＼\n");
	printf("\t　　/ | ･ω･| ＼_\n");
	printf("\t　 ( ヽ￣￣∩　_ )\n");
	printf("\t　 /＼_二二三)/／\n");
	printf("\t　/　 ＿＿　 /\n");
	printf("\t`/　／　 ＼ ｜\n");
	printf("\t(_／　　 (_／\n");
	CursorPositionSet(32, 4);
	printf("######## ##     ## ########  ######## ########     #######  ##     ## ######## ");
	CursorPositionSet(32, 5);
	printf("   ##    ##     ## ##     ## ##       ##          ##     ## ##     ##    ##    ");
	CursorPositionSet(32, 6);
	printf("   ##    ##     ## ##     ## ##       ##          ##     ## ##     ##    ##    ");
	CursorPositionSet(32, 7);
	printf("   ##    ######### ########  ######   ######      ##     ## ##     ##    ##    ");
	CursorPositionSet(32, 8);
	printf("   ##    ##     ## ##   ##   ##       ##          ##     ## ##     ##    ##    ");
	CursorPositionSet(32, 9);
	printf("   ##    ##     ## ##    ##  ##       ##          ##     ## ##     ##    ##    ");
	CursorPositionSet(32, 10);
	printf("   ##    ##     ## ##     ## ######## ########     #######   #######     ##    ");
	CursorPositionSet(32, 14);
	printf("                                        CHANGE !!");
	PlaySound("karan.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	for (int i = 0; i < 3; i++)
	{
		BSO[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		RUNNER[i] = 0;
	}
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
	outBox = 0;

}

int battingJudgeCompatibility() {
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("　あなたの　選択カード　");
	int result = battingCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
	{
		CursorPositionSet(58, 17);
		printf("打った！");
		PlaySound("kin.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		int battingResult = hitResultOutput(playersChoice.type, playersChoice.plus_type);
		hitResultAct(battingResult);
		return RESULT_WIN;
	}
	case RESULT_LOSE:
	{
		CursorPositionSet(58, 17);
		printf("三振！");
		PlaySound("bun.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_LOSE;
	}
	case RESULT_DRAW:
	{
		CursorPositionSet(58, 17);
		printf("引き分け！");
		PlaySound("tata.wav", NULL, SND_FILENAME | SND_ASYNC);
		CursorPositionSet(58, 18);
		printf("ファール！");
		return RESULT_DRAW;
	}
	case RESULT_ESCAPE:
		return RESULT_ESCAPE;
	case RESULT_ENEMYESCAPE:
		return RESULT_ENEMYESCAPE;
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

void pitchResultAct(int resultNum) {
	switch (resultNum) {
	case RESULT_WIN:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = 0;
		BSOp++;
		*BSOp = 0;
		BSOp++;
		*BSOp = BSO[COUNT_OUT] + 1;
		BSOp = 0;
		order[TEAM_ENEMY]++;
		break;
	case RESULT_LOSE:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = 0;
		BSOp++;
		*BSOp = 0;
		BSOp++;
		*BSOp = BSO[COUNT_OUT];
		outBox = BSO[COUNT_OUT];
		BSOp = 0;
		order[TEAM_ENEMY]++;
		break;
	case RESULT_DRAW:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = BSO[COUNT_BALL];
		BSOp++;
		if (BSO[COUNT_STRIKE] <= 1) *BSOp = BSO[COUNT_STRIKE] + 1;
		else *BSOp = BSO[COUNT_STRIKE];
		BSOp++;
		*BSOp = BSO[COUNT_OUT];
		break;
	case RESULT_ESCAPE:
		if (BSO[COUNT_BALL] <= 2)
		{
			BSOp = &BSO[COUNT_BALL];
			*BSOp = BSO[COUNT_BALL] + 1;
			BSOp++;
			*BSOp = BSO[COUNT_STRIKE];
			BSOp++;
			*BSOp = BSO[COUNT_OUT];
			BSOp = 0;
		}
		else
		{
			CursorPositionSet(58, 17);
			printf("フォアボール！");
			PlaySound("pun.wav", NULL, SND_FILENAME | SND_ASYNC);
			BSOp = &BSO[COUNT_BALL];
			*BSOp = 0;
			BSOp++;
			*BSOp = 0;
			BSOp = &BSO[COUNT_OUT];
			*BSOp = BSO[COUNT_OUT];
			BSOp = 0;
			order[TEAM_ENEMY]++;
			hitResultAct(HIT_SINGLE);
			getchar();
		}
		break;
	case RESULT_ENEMYESCAPE:
		if (BSO[COUNT_STRIKE] <= 1)
		{
			BSOp = &BSO[COUNT_BALL];
			*BSOp = BSO[COUNT_BALL];
			BSOp++;
			*BSOp = BSO[COUNT_STRIKE] + 1;
			BSOp++;
			*BSOp = BSO[COUNT_OUT];
			BSOp = 0;
		}
		else
		{
			CursorPositionSet(58, 17);
			printf("ストライク！");
			CursorPositionSet(56, 18);
			PlaySound("pun.wav", NULL, SND_FILENAME | SND_ASYNC);
			printf("バッターアウト！");
			BSOp = &BSO[COUNT_BALL];
			*BSOp = 0;
			BSOp++;
			*BSOp = 0;
			BSOp = &BSO[COUNT_OUT];
			*BSOp = BSO[COUNT_OUT] + 1;
			BSOp = 0;
			order[TEAM_ENEMY]++;
			getchar();
		}
		break;
	}

	if (order[TEAM_ENEMY] == 10) order[TEAM_ENEMY] = 1;
	return;
}

void battingResultAct(int resultNum) {
	switch (resultNum) {
	case RESULT_ENEMYESCAPE:
		if (BSO[COUNT_BALL] <= 2)
		{
			BSOp = &BSO[COUNT_BALL];
			*BSOp = BSO[COUNT_BALL] + 1;
			BSOp++;
			*BSOp = BSO[COUNT_STRIKE];
			BSOp++;
			*BSOp = BSO[COUNT_OUT];
			BSOp = 0;
		}
		else
		{
			CursorPositionSet(58, 17);
			printf("フォアボール！");
			PlaySound("pun.wav", NULL, SND_FILENAME | SND_ASYNC);
			BSOp = &BSO[COUNT_BALL];
			*BSOp = 0;
			BSOp++;
			*BSOp = 0;
			BSOp = &BSO[COUNT_OUT];
			*BSOp = BSO[COUNT_OUT];
			BSOp = 0;
			order[TEAM_YOU]++;
			hitResultAct(HIT_SINGLE);
			getchar();
		}
		break;
	case RESULT_ESCAPE:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = BSO[COUNT_BALL];
		BSOp++;
		*BSOp = BSO[COUNT_STRIKE] + 1;
		BSOp++;
		*BSOp = BSO[COUNT_OUT];
		if (BSO[COUNT_STRIKE] >= 3)
		{
			BSOp = &BSO[COUNT_BALL];
			*BSOp = 0;
			BSOp++;
			*BSOp = 0;
			BSOp++;
			*BSOp = BSO[COUNT_OUT] + 1;
			BSOp = 0;
			order[TEAM_YOU]++;
		}
		break;
	case RESULT_LOSE:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = 0;
		BSOp++;
		*BSOp = 0;
		BSOp++;
		*BSOp = BSO[COUNT_OUT] + 1;
		BSOp = 0;
		order[TEAM_YOU]++;
		break;
	case RESULT_WIN:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = 0;
		BSOp++;
		*BSOp = 0;
		BSOp++;
		*BSOp = BSO[COUNT_OUT];
		BSOp = 0;
		order[TEAM_YOU]++;
		break;
	case RESULT_DRAW:
		BSOp = &BSO[COUNT_BALL];
		*BSOp = BSO[COUNT_BALL];
		BSOp++;
		if (BSO[COUNT_STRIKE] <= 1) *BSOp = BSO[COUNT_STRIKE] + 1;
		else *BSOp = BSO[COUNT_STRIKE];
		BSOp++;
		*BSOp = BSO[COUNT_OUT];
		break;
	}
	if (order[TEAM_YOU] == 10) order[TEAM_YOU] = 1;
	return;
}

int main() {
	preTitle();
	while (1)
	{
		int gametype = title();
		gameStandby();
		ruleDescription();
		if (gametype == GAMETYPE_DIGEST)
		{
			_inning = 3;
			_turn = TURN_TOP;
			RUNNER[1] = 1;
			BSO[COUNT_OUT] = 0;
			order[TEAM_ENEMY] = 8;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\t　　　＿＿　＿＿\n\t　　∠＿＿ヽ＿＿＼\n");
			printf("\t(＼∥･ω･`||／)･|｜\n");
			printf("\t`＼(二⊃￣⊂二二 ｜\n");
			printf("\t　 |　　　 |　　 ｜\n");
			printf("\t　 ヽ＿⊃ ノ /＼_ﾉ\n");
			printf("\t　　　(_／ヽﾉ\n");
			printf("\t　　　＼￣￣￣￣￣￣\n");
			printf("\t～～～～＼　(ψ)\n");
			printf("\t　　　~　~＼ ￣\n");
			printf("\t　~ ~　~　~~～～～⌒\n");
			CursorPositionSet(32, 4);
			printf("\t########  #### ##    ##  ######  ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 5);
			printf("\t##     ##  ##  ###   ## ##    ## ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 6);
			printf("\t##     ##  ##  ####  ## ##       ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 7);
			printf("\t########   ##  ## ## ## ##       #########     ##   ##   ##   ##   ##  ");
			CursorPositionSet(32, 8);
			printf("\t##         ##  ##  #### ##       ##     ##                             ");
			CursorPositionSet(32, 9);
			printf("\t##         ##  ##   ### ##    ## ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 10);
			printf("\t##        #### ##    ##  ######  ##     ##    #### #### #### #### ####");
			CursorPositionSet(32, 14);
			printf("\t                   %d回表　相手チームの攻撃",_inning);
			getchar();
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&yourplayer[NUMBER_PITCHER], &enemyplayer[order[TEAM_ENEMY]]);
				pitchingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = pitchJudgeCompatibility();
				getchar();
				pitchResultAct(resultBox);
			}
			changeAct();
			_inning = 5;
			_turn = TURN_BOTTOM;
			RUNNER[1] = 1;
			RUNNER[2] = 1;
			BSO[COUNT_OUT] = 2;
			order[TEAM_YOU] = 9;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\t　|　_ |∥　\n\t　　/ )　/ヽ＿\n");
			printf("\t　 ｜ ＼/　|＿＼∥|\n");
			printf("\t∥ ｜　　　|･`| ヽ\n");
			printf("\t　 (二⊃ ⊂二二ノ|\n");
			printf("\t　(｜　　　 ／)　|\n");
			printf("\t　ヽ二)　　　/　ノ\n");
			printf("\t　　 ＼＿＿_(_／\n\n");
			printf("\t━━━━━━━━Π\n");
			printf("\t━━━━━━━━||＼\n");
			printf("\t━━━━━━━━||＼\n\t　　　　　　　　　＼\n");
			CursorPositionSet(32, 4);
			printf("\t .d8888b.  888    888        d8888 888b    888  .d8888b.  8888888888      888 888 888 888 888 ");
			CursorPositionSet(32, 5);
			printf("\td88P  Y88b 888    888       d88888 8888b   888 d88P  Y88b 888             888 888 888 888 888 ");
			CursorPositionSet(32, 6);
			printf("\t888    888 888    888      d88P888 88888b  888 888    888 888             888 888 888 888 888 ");
			CursorPositionSet(32, 7);
			printf("\t888        8888888888     d88P 888 888Y88b 888 888        8888888         888 888 888 888 888 ");
			CursorPositionSet(32, 8);
			printf("\t888        888    888    d88P  888 888 Y88b888 888        888             888 888 888 888 888 ");
			CursorPositionSet(32, 9);
			printf("\t888    888 888    888   d88P   888 888  Y88888 888    888 888             Y8P Y8P Y8P Y8P Y8P ");
			CursorPositionSet(32, 10);
			printf("\tY88b  d88P 888    888  d8888888888 888   Y8888 Y88b  d88P 888              \"   \"   \"   \"   \"  ");
			CursorPositionSet(32, 11);
			printf("\t \"Y8888P\"  888    888 d88P     888 888    Y888  \"Y8888P\"  8888888888      888 888 888 888 888 ");
			CursorPositionSet(32, 15);
			printf("\t                   %d回ｳﾗ　あなたのチームの攻撃", _inning);
			getchar();
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&enemyplayer[NUMBER_PITCHER], &yourplayer[order[TEAM_YOU]]);
				battingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = battingJudgeCompatibility();
				getchar();
				battingResultAct(resultBox);
			}
			changeAct();
			_inning = 7;
			_turn = TURN_TOP;
			RUNNER[1] = 1;
			RUNNER[0] = 1;
			BSO[COUNT_OUT] = 0;
			order[TEAM_ENEMY] = 6;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\t　　　＿＿　＿＿\n\t　　∠＿＿ヽ＿＿＼\n");
			printf("\t(＼∥･ω･`||／)･|｜\n");
			printf("\t`＼(二⊃￣⊂二二 ｜\n");
			printf("\t　 |　　　 |　　 ｜\n");
			printf("\t　 ヽ＿⊃ ノ /＼_ﾉ\n");
			printf("\t　　　(_／ヽﾉ\n");
			printf("\t　　　＼￣￣￣￣￣￣\n");
			printf("\t～～～～＼　(ψ)\n");
			printf("\t　　　~　~＼ ￣\n");
			printf("\t　~ ~　~　~~～～～⌒\n");
			CursorPositionSet(32, 4);
			printf("\t########  #### ##    ##  ######  ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 5);
			printf("\t##     ##  ##  ###   ## ##    ## ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 6);
			printf("\t##     ##  ##  ####  ## ##       ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 7);
			printf("\t########   ##  ## ## ## ##       #########     ##   ##   ##   ##   ##  ");
			CursorPositionSet(32, 8);
			printf("\t##         ##  ##  #### ##       ##     ##                             ");
			CursorPositionSet(32, 9);
			printf("\t##         ##  ##   ### ##    ## ##     ##    #### #### #### #### #### ");
			CursorPositionSet(32, 10);
			printf("\t##        #### ##    ##  ######  ##     ##    #### #### #### #### ####");
			CursorPositionSet(32, 14);
			printf("\t                   %d回表　相手チームの攻撃", _inning);
			getchar();
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&yourplayer[NUMBER_PITCHER], &enemyplayer[order[TEAM_ENEMY]]);
				pitchingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = pitchJudgeCompatibility();
				getchar();
				pitchResultAct(resultBox);
			}
			changeAct();
			_inning = 8;
			_turn = TURN_BOTTOM;
			RUNNER[0] = 1;
			RUNNER[1] = 1;
			RUNNER[2] = 1;
			BSO[COUNT_OUT] = 2;
			order[TEAM_YOU] = 2;
			system("cls");
			printf("\n\n\n\n\n\n\n\n\n\t　|　_ |∥　\n\t　　/ )　/ヽ＿\n");
			printf("\t　 ｜ ＼/　|＿＼∥|\n");
			printf("\t∥ ｜　　　|･`| ヽ\n");
			printf("\t　 (二⊃ ⊂二二ノ|\n");
			printf("\t　(｜　　　 ／)　|\n");
			printf("\t　ヽ二)　　　/　ノ\n");
			printf("\t　　 ＼＿＿_(_／\n\n");
			printf("\t━━━━━━━━Π\n");
			printf("\t━━━━━━━━||＼\n");
			printf("\t━━━━━━━━||＼\n\t　　　　　　　　　＼\n");
			CursorPositionSet(32, 4);
			printf("\t .d8888b.  888    888        d8888 888b    888  .d8888b.  8888888888      888 888 888 888 888 ");
			CursorPositionSet(32, 5);
			printf("\td88P  Y88b 888    888       d88888 8888b   888 d88P  Y88b 888             888 888 888 888 888 ");
			CursorPositionSet(32, 6);
			printf("\t888    888 888    888      d88P888 88888b  888 888    888 888             888 888 888 888 888 ");
			CursorPositionSet(32, 7);
			printf("\t888        8888888888     d88P 888 888Y88b 888 888        8888888         888 888 888 888 888 ");
			CursorPositionSet(32, 8);
			printf("\t888        888    888    d88P  888 888 Y88b888 888        888             888 888 888 888 888 ");
			CursorPositionSet(32, 9);
			printf("\t888    888 888    888   d88P   888 888  Y88888 888    888 888             Y8P Y8P Y8P Y8P Y8P ");
			CursorPositionSet(32, 10);
			printf("\tY88b  d88P 888    888  d8888888888 888   Y8888 Y88b  d88P 888              \"   \"   \"   \"   \"  ");
			CursorPositionSet(32, 11);
			printf("\t \"Y8888P\"  888    888 d88P     888 888    Y888  \"Y8888P\"  8888888888      888 888 888 888 888 ");
			CursorPositionSet(32, 15);
			printf("\t                   %d回ｳﾗ　あなたのチームの攻撃", _inning);
			getchar();
			PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&enemyplayer[NUMBER_PITCHER], &yourplayer[order[TEAM_YOU]]);
				battingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = battingJudgeCompatibility();
				getchar();
				battingResultAct(resultBox);
			}
			changeAct();
			order[TEAM_ENEMY] = 3;
			_inning = 9;
			_turn = TURN_TOP;

		}
		while (_inning <= 9 || ((_inning > 9 && _inning != 16) && score[TEAM_ENEMY] == score[TEAM_YOU]))
		{
			while (BSO[COUNT_OUT] <= 2)
			{
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&yourplayer[NUMBER_PITCHER], &enemyplayer[order[TEAM_ENEMY]]);
				pitchingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = pitchJudgeCompatibility();
				getchar();
				pitchResultAct(resultBox);
			}
			changeAct();
			while (BSO[COUNT_OUT] <= 2)
			{
				if (_inning >= 9 && score[TEAM_ENEMY] < score[TEAM_YOU])
				{

					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\t　　 ＿＿\n\t　 ／＿＿＼\n");
					printf("\t(￣ |･ω･| )\n");
					printf("\t`＼＼￣￣／　\n");
					printf("\t　(／　ノ￣)　\n");
					printf("\t　| /￣/ ／\n");
					printf("\t＿|/＿/／\n");
					CursorPositionSet(32, 4);
					printf("db   d8b   db  .d8b.  db      db   dD         .d88b.  d88888b d88888b      db    db d888888b  .o88b. d888888b  .d88b.  d8888b. db    db      db    db    db ");
					CursorPositionSet(32, 5);
					printf("88   I8I   88 d8' `8b 88      88 ,8P'        .8P  Y8. 88'     88'          88    88   `88'   d8P  Y8 `~~88~~' .8P  Y8. 88  `8D `8b  d8'      88    88    88 ");
					CursorPositionSet(32, 6);
					printf("88   I8I   88 88ooo88 88      88,8P          88    88 88ooo   88ooo        Y8    8P    88    8P         88    88    88 88oobY'  `8bd8'       YP    YP    YP ");
					CursorPositionSet(32, 7);
					printf("Y8   I8I   88 88~~~88 88      88`8b   C8888D 88    88 88~~~   88~~~        `8b  d8'    88    8b         88    88    88 88`8b      88                            ");
					CursorPositionSet(32, 8);
					printf("`8b d8'8b d8' 88   88 88booo. 88 `88.        `8b  d8' 88      88            `8bd8'    .88.   Y8b  d8    88    `8b  d8' 88 `88.    88         db    db    db ");
					CursorPositionSet(32, 9);
					printf(" `8b8' `8d8'  YP   YP Y88888P YP   YD         `Y88P'  YP      YP              YP    Y888888P  `Y88P'    YP     `Y88P'  88   YD    YP         YP    YP    YP    ");
					CursorPositionSet(32, 14);
					printf("                                                                   サヨナラ勝ち !!");
					goto GAMESET;
				}
				display(&RUNNER[0], &BSO[0]);
				playerStatusDisp(&enemyplayer[NUMBER_PITCHER], &yourplayer[order[TEAM_YOU]]);
				battingCardChoice();
				enemyCardChoice();
				if (enemysChoice.power != 5) enemysChoice.power += 1;
				int resultBox = battingJudgeCompatibility();
				getchar();
				battingResultAct(resultBox);
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
		PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	return 0;
	
}