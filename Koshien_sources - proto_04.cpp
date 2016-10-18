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
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t*�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\*\n");
	printf("\n\n\n\t\t\t\t\t\t\t�ő剻�\���ł́@�v���C�𐄏����܂�\n\t\t\t\t\t\t\t�ύX���I�������@�G���^�[�L�[���@�����Ă�������\n\n");
	printf("\n\n\t\t\t\t\t\t*�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\*");
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
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
			break;
		case 0xe0:
			switch (_getch()) {
			case 0x4b:	//��
				PlaySound("ku.wav", NULL, SND_FILENAME | SND_ASYNC);
				if (cursor == GAMETYPE_CLIMAX)
				{
					cursor = GAMETYPE_FULLPLAY;
					break;
				}
				cursor--;
				break;
			case 0x4d:	//��
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
	printf("\n\t\t�� ���[������ ��\n\n");
	printf("\n\n\t\t�J�[�h�E�v���X�J�[�h��I�����A�������i�s���܂�\n\n");
	CursorPositionSet(20, 8);
	printf("�` �J�[�h���� �`");
	int cardPosX = 20, cardPosY = 10;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	CursorPositionSet(34, 11);
	printf("�J�[�h�͎l��ނ���܂�");
	CursorPositionSet(34, 13);
	printf("�J�[�h�̍���ɂ́u�J�[�h�̋����v��������Ă��܂�");
	CursorPositionSet(34, 14);
	printf("�@�`�D�܂ł̋����̃J�[�h���@�����_���Ŕz���܂�");

	cardPosX = 20, cardPosY = 18;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 17, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[2]);
	printf("��������");
	CursorPositionSet(cardPosX + 17, cardPosY + 1);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�@�@�@");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 2);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�ω���");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 3);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf(" ���S ");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 4);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�@�@�@");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 5);
	printf("��������");
	printf("%s", cardPowerNumber[2]);
	CursorPositionSet(cardPosX + 34, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
	printf("��������");
	CursorPositionSet(cardPosX + 34, cardPosY + 1);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf("�@�@�@");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 2);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf(" �Ɂ@ ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 3);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf(" �@�} ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 4);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf("�@�@�@");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 5);
	printf("��������");
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 51, cardPosY);
	COLOR_ESCAPE_FLAME;
	printf("��");
	printf("��������");
	CursorPositionSet(cardPosX + 51, cardPosY + 1);
	printf("��");
	COLOR_ESCAPE;
	printf("�@�@�@");
	COLOR_ESCAPE_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 51, cardPosY + 2);
	printf("��");
	COLOR_ESCAPE;
	printf(" �ꋅ ");
	COLOR_ESCAPE_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 51, cardPosY + 3);
	printf("��");
	COLOR_ESCAPE;
	printf("�͂���");
	COLOR_ESCAPE_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 51, cardPosY + 4);
	printf("��");
	COLOR_ESCAPE;
	printf("�@�@�@");
	COLOR_ESCAPE_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 51, cardPosY + 5);
	printf("��������");
	printf("��");
	COLOR_DEFAULT;

	CursorPositionSet(14, 25);
	printf("�J�[�h�̎�ނ��ƂɁ@�I��̔\�͂��e�����܂�");
	CursorPositionSet(16, 27);
	COLOR_STRAIGHTPITCHING;
	printf(" �ԐF�̃J�[�h ");
	COLOR_DEFAULT;
	printf("�@�@�Ȃ�@�@");
	COLOR_STRAIGHTPITCHING;
	printf(" ���� ");
	COLOR_DEFAULT;
	printf(" �E ");
	COLOR_STRAIGHTPITCHING;
	printf(" ���ŗ� ");
	COLOR_DEFAULT;
	CursorPositionSet(16, 29);
	COLOR_BRAKINGPITCHING;
	printf(" �F�̃J�[�h ");
	COLOR_DEFAULT;
	printf("�@�@�Ȃ�@�@");
	COLOR_BRAKINGPITCHING;
	printf(" �ω��� ");
	COLOR_DEFAULT;
	printf(" �E ");
	COLOR_BRAKINGPITCHING;
	printf(" �I�ŗ� ");
	COLOR_DEFAULT;
	CursorPositionSet(16, 31);
	COLOR_OFFSPEEDPITCHING;
	printf(" ���F�̃J�[�h ");
	COLOR_DEFAULT;
	printf("�@�@�Ȃ�@�@");
	COLOR_OFFSPEEDPITCHING;
	printf(" �Z�I ");
	COLOR_DEFAULT;
	printf(" �E ");
	COLOR_OFFSPEEDPITCHING;
	printf(" ���� ");
	COLOR_DEFAULT;
	CursorPositionSet(14, 33);
	printf("�̒l�i �d�@�`�@�` �j�@�ɂ��@�␳�i -2�@�`�@+2 �j��������܂�");
	CursorPositionSet(14, 35);
	printf("���Ƃ��� ");
	COLOR_STRAIGHTPITCHING;
	printf(" �������S ");
	COLOR_DEFAULT;
	printf(" �� ");
	COLOR_STRAIGHTPITCHING;
	printf(" ���� ");
	COLOR_DEFAULT;
	printf(" �a �̃s�b�`���[�őI�Ԃ� �J�[�h�p���[�� +1 �̔\�͕␳�I");
	CursorPositionSet(16, 38);
	COLOR_ESCAPE;
	printf(" �ΐF�̃J�[�h ");
	COLOR_DEFAULT;
	printf("�@�@�́@�@");
	COLOR_DEFAULT;
	printf("�G�X�P�[�v�J�[�h�ł�");
	CursorPositionSet(16, 40);
	printf("�ꋅ�O���A�J�[�h��z�蒼���܂�");
	CursorPositionSet(16, 41);
	printf("�J�[�h�̋������@�C�}�C�`�ȂƂ��Ɂ@�L���ł�");
	CursorPositionSet(120, 43);
	printf("�� Enter�L�[�Ł@���̐����Ɂ@�ڂ�܂� ��");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	system("cls");
	printf("\n\t\t�� ���[������ ��\n\n");
	CursorPositionSet(20, 4);
	printf("�` �v���X�J�[�h���� �`");
	cardPosX = 20, cardPosY = 7;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	CursorPositionSet(34, 8);
	printf("�v���X�J�[�h�͎O��ނ���܂�");
	CursorPositionSet(34, 10);
	printf("�v���X�J�[�h�����l�Ɂ@�J�[�h�̍���Ɂu�J�[�h�̋����v��������Ă���");
	CursorPositionSet(34, 11);
	printf("�@�`�D�܂ł̋����̃J�[�h���@�����_���Ŕz���܂�");

	cardPosX = 20, cardPosY = 15;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	CursorPositionSet(cardPosX + 17, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[2]);
	printf("��������");
	CursorPositionSet(cardPosX + 17, cardPosY + 1);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�@�@�@");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 2);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�N�T�C");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 3);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�Ƃ���");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 4);
	printf("��");
	COLOR_BRAKINGPITCHING;
	printf("�@�@�@");
	COLOR_BRAKINGPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 17, cardPosY + 5);
	printf("��������");
	printf("%s", cardPowerNumber[2]);
	CursorPositionSet(cardPosX + 34, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
	printf("��������");
	CursorPositionSet(cardPosX + 34, cardPosY + 1);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf("�@�@�@");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 2);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf(" �x�@ ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 3);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf(" �@�� ");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 4);
	printf("��");
	COLOR_OFFSPEEDPITCHING;
	printf("�@�@�@");
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("��");
	CursorPositionSet(cardPosX + 34, cardPosY + 5);
	printf("��������");
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	CursorPositionSet(16, 23);
	printf("�J�[�h�ƃv���X�J�[�h�̋����𑫂����킹�����̂��@�ŏI�I�ȋ����ɂȂ�܂�");
	cardPosX = 20, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;
	SHORT plusMarkX = 33, plusMarkY = 27;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");

	cardPosX = 44, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[4]);
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
	printf("%s", cardPowerNumber[4]);
	COLOR_DEFAULT;

	SHORT equalMarkX = 58, equalMarkY = 27;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");

	cardPosX = 70, cardPosY = 25;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[8]);
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
	printf("%s", cardPowerNumber[8]);
	COLOR_DEFAULT;
	cardPosX = 20, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[5]);
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
	printf("%s", cardPowerNumber[5]);
	COLOR_DEFAULT;
	plusMarkX = 33, plusMarkY = 34;
	CursorPositionSet(plusMarkX, plusMarkY - 1);
	printf("�@�����@");
	CursorPositionSet(plusMarkX, plusMarkY);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 1);
	printf("��������");
	CursorPositionSet(plusMarkX, plusMarkY + 2);
	printf("�@�����@");

	cardPosX = 44, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[3]);
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
	printf("%s", cardPowerNumber[3]);
	COLOR_DEFAULT;

	equalMarkX = 58, equalMarkY = 34;
	CursorPositionSet(equalMarkX, equalMarkY - 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 1);
	printf("��������");
	CursorPositionSet(equalMarkX, equalMarkY + 2);
	printf("��������");

	cardPosX = 70, cardPosY = 32;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_OFFSPEEDPITCHING_FLAME;
	printf("%s", cardPowerNumber[10]);
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
	printf("%s", cardPowerNumber[10]);
	COLOR_DEFAULT;
	CursorPositionSet(16, 39);
	printf("�����F�̃J�[�h�E�v���X�J�[�h��I�Ԃ� �ŏI�J�[�h�� �p���[�A�b�v���܂��I�i+2�@�{�[�i�X�I�j");
	CursorPositionSet(16, 40);
	printf("�ϋɓI�Ɂ@�_���Ă����܂��傤�I");
	CursorPositionSet(120, 43);
	printf("�� Enter�L�[�Ł@���̐����Ɂ@�ڂ�܂� ��");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	system("cls");
	printf("\n\t\t�� ���[������ ��\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t�@ �Q�Q�@�@�@ �Q�Q\n");
	printf("\t`�ځQ�Q�_�@ �^�Q�Q�_\n");
	printf("\t�a��֥`|�b / |��֥|�b\n");
	printf("\t/�P�P�P�@�u/| �P����)\n");
	printf("\tL�񁽁@ |�� |�@�@�@�b\n");
	printf("\t�R�Q�� �m�@ |�@/�__�\n");
	printf("\t�Q_(_�^�@ �Q�RɁQ\n");
	CursorPositionSet(20, 4);
	printf("�` �J�[�h�o�g������ �`");
	cardPosX = 20, cardPosY = 8;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[7]);
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
	printf("%s", cardPowerNumber[7]);
	COLOR_DEFAULT;
	cardPosX = 40, cardPosY = 8;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_STRAIGHTPITCHING_FLAME;
	printf("%s", cardPowerNumber[6]);
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
	printf("%s", cardPowerNumber[6]);
	COLOR_DEFAULT;
	CursorPositionSet(65, 8);
	printf("�s�b�`���[�� �o�b�^�[�� �ŏI�J�[�h�̋������r����");
	CursorPositionSet(65, 10);
	printf("�s�b�`���[�̂ق��� �����Ƃ��́@�O�U�I");
	CursorPositionSet(65, 11);
	printf("�o�b�^�[�̂ق����@ �����Ƃ��́@�q�b�g�I");
	CursorPositionSet(65, 12);
	printf("���݂��́@�������@ �����Ƃ��́@�t�@�[���I");

	cardPosX = 20, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[7]);
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
	printf("%s", cardPowerNumber[7]);
	COLOR_DEFAULT;
	cardPosX = 40, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	COLOR_BRAKINGPITCHING_FLAME;
	printf("%s", cardPowerNumber[8]);
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
	printf("%s", cardPowerNumber[8]);
	COLOR_DEFAULT;
	CursorPositionSet(65, 16);
	printf("�s�b�`���[�Ɓ@�o�b�^�[���@�����F�̃J�[�h��I�������ꍇ");
	CursorPositionSet(65, 18);
	printf("�o�b�^�[���� �w�z����ǂ񂾁x���ƂɂȂ� �J�[�h�������Ȃ�܂� �i+2�@�{�[�i�X�j");
	CursorPositionSet(60, 31);
	printf("���Ȃ��̎�Ł@�`�[����D�������܂��傤�I");

	CursorPositionSet(120, 43);
	printf("�� Enter�L�[�Ł@�v���C�{�[���I�I ��");
	getchar();
	PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
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
	printf("�O�O�O�O�O�O�O�O�O|�@ �@ �@ �₪�Ă��̂��ɕς����́B�@�@�@�@ |�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O�O\n");
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

int display(int* RUNNER, static int* BSO) {
	system("cls");
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
	printf("��������������������������������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 1);
	printf("�����n���@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 2);
	printf("��������������������������������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 3);
	printf("���n�����@���@���@���@���@���@���@���@���@���@���@���@���@���@���@��\n");
	CursorPositionSet(scoreBoardDispX, scoreBoardDispY + 4);
	printf("��������������������������������������������������������������������\n");
	CursorPositionSet(scoreBoardDispX + 8, scoreBoardDispY - 1);
	printf("�P�@�Q�@�R�@�S�@�T�@�U�@�V�@�W�@�X�@10�@11�@12�@13�@14�@15");
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
	case CARDTYPE_ESCAPE:
		if (cardCursolIs == CARDTYPE_ESCAPE) cardPosY -= 1;
		CursorPositionSet(cardPosX + 39, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX + 39, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf("�͂���");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 5);
		printf("��������");
		printf("��");
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
	pitchCardDisp(0, CARDTYPE_ESCAPE, CARDTYPE_NONE);

	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		pitchCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		pitchCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		pitchCardDisp(0, CARDTYPE_ESCAPE, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" �������S ");
			COLOR_DEFAULT;
			printf("�@    : �Ӑg�� �X�g���[�g�� �O�U�� �_���܂� �@");
			CursorPositionSet(59, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_BRAKINGPITCHING;
			printf(" �ω������S ");
			COLOR_DEFAULT;
			printf("�@  : �ω����� �h���Ԃ� �O�U�� �_���܂��@�@ ");
			CursorPositionSet(59, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" �ɋ} ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �������� ���Y���� ���킹�܂��@�@�@ �@ ");
			CursorPositionSet(59, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_ESCAPE:
			CursorPositionSet(45, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_ESCAPE;
			printf(" �ꋅ�͂��� ");
			COLOR_DEFAULT;
			printf("    : �ꋅ�@�{�[�����𓊂��� �l�q�����܂�  ");
			CursorPositionSet(59, 42);
			COLOR_DEFAULT;
			printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@ ");
			break;
		}
		if (cardCommand != CARDTYPE_ESCAPE) {
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
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
	}
	if (playersChoice.type != CARDTYPE_ESCAPE) {
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
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@    �@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
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

//TODO �q�b�g���ʊm���֐�
int hitResultOutput(int cardType, int plusCardType) {
	
		CursorPositionSet(58, 18);
		int resultMaker = genrand_int32() % 100 + 1;
		if (resultMaker < 50)
		{
			printf("��ۑŁI");
			PlaySound("1ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_SINGLE;
		}
		else if (resultMaker < 75)
		{
			printf("��ۑŁI");
			PlaySound("2ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_TWO_BASE;
		}
		else if (resultMaker < 90)
		{
			printf("�O�ۑŁI");
			PlaySound("3ruid.wav", NULL, SND_FILENAME | SND_ASYNC);
			return HIT_THREE_BASE;
		}
		else
		{
			printf("�z�[�������I");
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
			printf("��");
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_ESCAPE;
			printf("�@�@�@");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_ESCAPE;
			printf(" �ꋅ ");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_ESCAPE;
			printf("�͂���");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_ESCAPE;
			printf("�@�@�@");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("��");
			COLOR_DEFAULT;
		}
		else if (result->plus_type == result->type)
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
		if (result->type == CARDTYPE_ESCAPE)
		{
			COLOR_ESCAPE_FLAME;
			printf("��");
			printf("��������");
			CursorPositionSet(cardPosX, cardPosY + 1);
			printf("��");
			COLOR_ESCAPE;
			printf("�@�@�@");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 2);
			printf("��");
			COLOR_ESCAPE;
			printf(" �ꋅ ");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 3);
			printf("��");
			COLOR_ESCAPE;
			printf(" �҂� ");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 4);
			printf("��");
			COLOR_ESCAPE;
			printf("�@�@�@");
			COLOR_ESCAPE_FLAME;
			printf("��");
			CursorPositionSet(cardPosX, cardPosY + 5);
			printf("��������");
			printf("��");
			COLOR_DEFAULT;
		}
		else if (result->plus_type == result->type)
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
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf("�͂���");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("��");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@CPU�́@�I���J�[�h�@");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf(" �҂� ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("��");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ENEMYESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ENEMYESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@�J�[�h�o�g�����ʁI�@");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(20, 15, PLAYSIDE_PITCHING, &playersChoice);
	resultCardDisp(40, 15, PLAYSIDE_BATTING, &enemysChoice);
	if (enemysChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("�ꋅ�@��肷�����ꂽ�I");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ENEMYESCAPE;
	}
	else if (playersChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("�{�[�����Ł@��肷�������I");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ESCAPE;
	}
	else
	{
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
	{
		CursorPositionSet(58, 17);
		printf("�O�U�I");
		PlaySound("bun.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_WIN;
	}
	case RESULT_LOSE:
	{
		CursorPositionSet(58, 17);
		printf("�ł��ꂽ�I");
		PlaySound("kin.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		int battingResult = hitResultOutput(enemysChoice.type, enemysChoice.plus_type);
		hitResultAct(battingResult);
		return RESULT_LOSE;
	}
	case RESULT_DRAW:
	{
		CursorPositionSet(58, 17);
		printf("���������I");
		PlaySound("tata.wav", NULL, SND_FILENAME | SND_ASYNC);
		CursorPositionSet(58, 18);
		printf("�t�@�[���I");
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
	case CARDTYPE_ESCAPE:
		if (cardCursolIs == CARDTYPE_ESCAPE) cardPosY -= 1;
		CursorPositionSet(cardPosX + 39, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX + 39, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf(" �҂� ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX + 39, cardPosY + 5);
		printf("��������");
		printf("��");
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
	battingCardDisp(0, CARDTYPE_ESCAPE, CARDTYPE_NONE);
	while (enterFlag == FALSE)
	{
		CursorPositionSet(0, 40);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		CursorPositionSet(0, 46);
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		battingCardDisp(cardPowerBox[CARDTYPE_STRAIGHT], CARDTYPE_STRAIGHT, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_BRAKING], CARDTYPE_BRAKING, cardCommand);
		battingCardDisp(cardPowerBox[CARDTYPE_OFFSPEED], CARDTYPE_OFFSPEED, cardCommand);
		battingCardDisp(0, CARDTYPE_ESCAPE, cardCommand);
		switch (cardCommand)
		{
		case CARDTYPE_STRAIGHT:
			CursorPositionSet(6, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_STRAIGHTPITCHING;
			printf(" �����_�� ");
			COLOR_DEFAULT;
			printf("�@    : �_������ ������ �i��܂��@�@�@�@�@");
			CursorPositionSet(59, 42);
			COLOR_STRAIGHTPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_BRAKING:
			CursorPositionSet(19, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_BRAKINGPITCHING;
			printf(" �ω������S ");
			COLOR_DEFAULT;
			printf("�@  : �_������ �ω����� �i��܂��@�@�@�@�@ ");
			CursorPositionSet(59, 42);
			COLOR_BRAKINGPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_OFFSPEED:
			CursorPositionSet(32, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_OFFSPEEDPITCHING;
			printf(" ���ː_�o ");
			COLOR_DEFAULT;
			printf("�@�@�@    : �_������ �i�炸 �X�C���O���܂��@ ");
			CursorPositionSet(59, 42);
			COLOR_OFFSPEEDPITCHING_FLAME;
			printf("�J�[�h�̋���  ");
			COLOR_DEFAULT;
			break;
		case CARDTYPE_ESCAPE:
			CursorPositionSet(45, 46);
			printf("��");
			CursorPositionSet(58, 40);
			COLOR_ESCAPE;
			printf(" �ꋅ�҂� ");
			COLOR_DEFAULT;
			printf("�@    : �ꋅ �l�q�����܂�  �@�@�@�@�@�@�@�@�@�@�@");
			CursorPositionSet(59, 42);
			COLOR_DEFAULT;
			printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@ ");
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
		printf("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@\n");
	}
	if (playersChoice.type != CARDTYPE_ESCAPE)
	{
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
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf(" �҂� ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("��");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@CPU�́@�I���J�[�h�@");
	cardPosX = 18, cardPosY = 16;
	CursorPositionSet(cardPosX, cardPosY);
	switch (enemysResult->type)
	{
	case CARDTYPE_ESCAPE:
		cardPosX = 40;
		CursorPositionSet(cardPosX, cardPosY);
		COLOR_ESCAPE_FLAME;
		printf("��");
		printf("��������");
		CursorPositionSet(cardPosX, cardPosY + 1);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 2);
		printf("��");
		COLOR_ESCAPE;
		printf(" �ꋅ ");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 3);
		printf("��");
		COLOR_ESCAPE;
		printf("�͂���");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 4);
		printf("��");
		COLOR_ESCAPE;
		printf("�@�@�@");
		COLOR_ESCAPE_FLAME;
		printf("��");
		CursorPositionSet(cardPosX, cardPosY + 5);
		printf("��������");
		printf("��");
		COLOR_DEFAULT;
		PlaySound("syp.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		goto ENEMYESCAPECHOSE;
		break;
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
	PlaySound("vin.wav", NULL, SND_FILENAME | SND_ASYNC);
	getchar();
ENEMYESCAPECHOSE:
	dispCls_result();
	CursorPositionSet(14, 12);
	printf("�@�J�[�h�o�g�����ʁI�@");
	cardPosX = 20, cardPosY = 15;
	resultCardDisp(cardPosX, cardPosY, PLAYSIDE_BATTING, &playersChoice);
	resultCardDisp(cardPosX + 20, cardPosY, PLAYSIDE_PITCHING, &enemysChoice);
	if (enemysChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("�ꋅ�@��肷�����ꂽ�I");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ENEMYESCAPE;
	}
	else if (playersChoice.type == CARDTYPE_ESCAPE)
	{
		CursorPositionSet(54, 15);
		printf("�ꋅ�@��肷�������I");
		PlaySound("gua.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_ESCAPE;
	}
	else
	{
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
}

void changeAct() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t�@�@�@ �Q�Q_\n\t�@�@ �^�Q�Q_�_\n");
	printf("\t�@�@/ | ��֥| �__\n");
	printf("\t�@ ( �R�P�P���@_ )\n");
	printf("\t�@ /�__���O)/�^\n");
	printf("\t�@/�@ �Q�Q�@ /\n");
	printf("\t`/�@�^�@ �_ �b\n");
	printf("\t(_�^�@�@ (_�^\n");
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
	printf("�@���Ȃ��́@�I���J�[�h�@");
	int result = battingCardResultDisp(&playersChoice, &enemysChoice);
	switch (result)
	{
	case RESULT_WIN:
	{
		CursorPositionSet(58, 17);
		printf("�ł����I");
		PlaySound("kin.wav", NULL, SND_FILENAME | SND_ASYNC);
		getchar();
		int battingResult = hitResultOutput(playersChoice.type, playersChoice.plus_type);
		hitResultAct(battingResult);
		return RESULT_WIN;
	}
	case RESULT_LOSE:
	{
		CursorPositionSet(58, 17);
		printf("�O�U�I");
		PlaySound("bun.wav", NULL, SND_FILENAME | SND_ASYNC);
		return RESULT_LOSE;
	}
	case RESULT_DRAW:
	{
		CursorPositionSet(58, 17);
		printf("���������I");
		PlaySound("tata.wav", NULL, SND_FILENAME | SND_ASYNC);
		CursorPositionSet(58, 18);
		printf("�t�@�[���I");
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
			printf("�t�H�A�{�[���I");
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
			printf("�X�g���C�N�I");
			CursorPositionSet(56, 18);
			PlaySound("pun.wav", NULL, SND_FILENAME | SND_ASYNC);
			printf("�o�b�^�[�A�E�g�I");
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
			printf("�t�H�A�{�[���I");
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
			printf("\n\n\n\n\n\n\n\n\n\t�@�@�@�Q�Q�@�Q�Q\n\t�@�@�ځQ�Q�R�Q�Q�_\n");
			printf("\t(�_�a��֥`||�^)�|�b\n");
			printf("\t`�_(�񁽁P����� �b\n");
			printf("\t�@ |�@�@�@ |�@�@ �b\n");
			printf("\t�@ �R�Q�� �m /�__�\n");
			printf("\t�@�@�@(_�^�R�\n");
			printf("\t�@�@�@�_�P�P�P�P�P�P\n");
			printf("\t�`�`�`�`�_�@(��)\n");
			printf("\t�@�@�@~�@~�_ �P\n");
			printf("\t�@~ ~�@~�@~~�`�`�`��\n");
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
			printf("\t                   %d��\�@����`�[���̍U��",_inning);
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
			printf("\n\n\n\n\n\n\n\n\n\t�@|�@_ |�a�@\n\t�@�@/ )�@/�R�Q\n");
			printf("\t�@ �b �_/�@|�Q�_�a|\n");
			printf("\t�a �b�@�@�@|�`| �R\n");
			printf("\t�@ (�� �����m|\n");
			printf("\t�@(�b�@�@�@ �^)�@|\n");
			printf("\t�@�R��)�@�@�@/�@�m\n");
			printf("\t�@�@ �_�Q�Q_(_�^\n\n");
			printf("\t������������������\n");
			printf("\t����������������||�_\n");
			printf("\t����������������||�_\n\t�@�@�@�@�@�@�@�@�@�_\n");
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
			printf("\t                   %d��ׁ@���Ȃ��̃`�[���̍U��", _inning);
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
			printf("\n\n\n\n\n\n\n\n\n\t�@�@�@�Q�Q�@�Q�Q\n\t�@�@�ځQ�Q�R�Q�Q�_\n");
			printf("\t(�_�a��֥`||�^)�|�b\n");
			printf("\t`�_(�񁽁P����� �b\n");
			printf("\t�@ |�@�@�@ |�@�@ �b\n");
			printf("\t�@ �R�Q�� �m /�__�\n");
			printf("\t�@�@�@(_�^�R�\n");
			printf("\t�@�@�@�_�P�P�P�P�P�P\n");
			printf("\t�`�`�`�`�_�@(��)\n");
			printf("\t�@�@�@~�@~�_ �P\n");
			printf("\t�@~ ~�@~�@~~�`�`�`��\n");
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
			printf("\t                   %d��\�@����`�[���̍U��", _inning);
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
			printf("\n\n\n\n\n\n\n\n\n\t�@|�@_ |�a�@\n\t�@�@/ )�@/�R�Q\n");
			printf("\t�@ �b �_/�@|�Q�_�a|\n");
			printf("\t�a �b�@�@�@|�`| �R\n");
			printf("\t�@ (�� �����m|\n");
			printf("\t�@(�b�@�@�@ �^)�@|\n");
			printf("\t�@�R��)�@�@�@/�@�m\n");
			printf("\t�@�@ �_�Q�Q_(_�^\n\n");
			printf("\t������������������\n");
			printf("\t����������������||�_\n");
			printf("\t����������������||�_\n\t�@�@�@�@�@�@�@�@�@�_\n");
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
			printf("\t                   %d��ׁ@���Ȃ��̃`�[���̍U��", _inning);
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
					printf("\n\n\n\n\n\n\n\n\n\t�@�@ �Q�Q\n\t�@ �^�Q�Q�_\n");
					printf("\t(�P |��֥| )\n");
					printf("\t`�_�_�P�P�^�@\n");
					printf("\t�@(�^�@�m�P)�@\n");
					printf("\t�@| /�P/ �^\n");
					printf("\t�Q|/�Q/�^\n");
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
					printf("                                                                   �T���i������ !!");
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
		printf("�X���[�A�E�g�I\n�Q�[���Z�b�g�I");
		printf("%d �΁@%d\n", score[TEAM_YOU], score[TEAM_ENEMY]);
		if (score[TEAM_YOU] > score[TEAM_ENEMY]) printf("���Ȃ��̏����I�I");
		if (score[TEAM_YOU] < score[TEAM_ENEMY]) printf("���Ȃ��̕����I�I");
		if (score[TEAM_YOU] == score[TEAM_ENEMY]) printf("���������I�I");
	GAMESET:
		getchar();
		PlaySound("ka.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
	return 0;
	
}