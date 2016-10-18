#include "Option.h"

//ÉJÅ[É\Éãà⁄ìÆä÷êî
void CursorPositionSet(SHORT x, SHORT y) {
	CursorPosition = {
		x,  // SHORT X
		y }; // SHORT Y
	SetConsoleCursorPosition(hConsoleOutput, CursorPosition);
}

//ç\ë¢ëÃÇΩÇøÅ@é¿ëÃêÈåæ
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
		"ÇØÇ¬ÇŒÇÒ",
		0,
		0,
		0
	},
	{
		1,
		"Ç‹Ç¬Ç‡Ç∆",
		RANK_D,
		RANK_C,
		RANK_A
	},
	{
		2,
		"ÇµÇÃÇ∑Ç©",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		3,
		"Ç≠ÇÎÇ‹Çƒ",
		RANK_A,
		RANK_B,
		RANK_E
	},
	{
		4,
		"ÇΩÇ¬ÇÃÇË",
		RANK_A,
		RANK_C,
		RANK_D
	},
	{
		5,
		"ÇÊÇµÇﬁÇÁ",
		RANK_C,
		RANK_B,
		RANK_C
	},
	{
		6,
		"Ç»Ç©ÇÕÇΩ",
		RANK_C,
		RANK_C,
		RANK_C
	},
	{
		7,
		"Ç±Ç§ÇÃ",
		RANK_C,
		RANK_C,
		RANK_B
	},
	{
		8,
		"Ç‚Ç‹Ç≠ÇÁ",
		RANK_B,
		RANK_C,
		RANK_D
	},
	{
		9,
		"Ç¶Ç™ÇÌ",
		RANK_B,
		RANK_C,
		RANK_B
	},
};
PLAYER enemyplayer[] = {
	{
		0,
		"ÇØÇ¬ÇŒÇÒ",
		0,
		0,
		0
	},
	{
		1,
		"Ç‹Ç‰Ç›",
		RANK_A,
		RANK_A,
		RANK_B
	},
	{
		2,
		"ÇÊÇµÇΩÇØ",
		RANK_C,
		RANK_C,
		RANK_A
	},
	{
		3,
		"ÇŒÇ†Ç∑",
		RANK_A,
		RANK_A,
		RANK_E
	},
	{
		4,
		"Ç©ÇØÇ”",
		RANK_A,
		RANK_B,
		RANK_D
	},
	{
		5,
		"Ç®Ç©Çæ",
		RANK_B,
		RANK_B,
		RANK_C
	},
	{
		6,
		"Ç≥ÇÃ",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		7,
		"Ç–ÇÁÇΩ",
		RANK_D,
		RANK_C,
		RANK_C
	},
	{
		8,
		"Ç´Ç«",
		RANK_C,
		RANK_C,
		RANK_D
	},
	{
		9,
		"Ç¢ÇØÇæ",
		RANK_C,
		RANK_B,
		RANK_B
	},
};
PLAYER extraplayer[] = {
	{
		0,
		"ÇØÇ¬ÇŒÇÒ",
		0,
		0,
		0
	},
	{
		1,
		"Ç¢ÇøÇÎÅ[",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		2,
		"Ç»Ç©Ç∂Ç‹",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		3,
		"Ç†Ç®Ç´",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		4,
		"Ç∂ÇÂÇ§Ç∂Ç‹",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		5,
		"Ç®Ç™Ç≥ÇÌÇÁ",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		6,
		"Ç§ÇøÇ©ÇÌ",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		7,
		"Ç¢ÇÌÇﬁÇÁ",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		8,
		"Ç©ÇΩÇ®Ç©",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		9,
		"É_ÉãÉr",
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
//ïœêîÇΩÇøÅ@êÈåæ
int outBox = 0;
int RUNNER[4] = { 0,0,0,0 };
int _inning = 9;
int _turn = TURN_TOP;
int _hideScoreCounter = 0;
int score[2] = { 0,0 };
int order[2] = { 1,1 };


//ï∂éöÉeÅ[ÉuÉã
char scoreBoardNumber[][16] = {
	"ÇO",
	"ÇP",
	"ÇQ",
	"ÇR",
	"ÇS",
	"ÇT",
	"ÇU",
	"ÇV",
	"ÇW",
	"ÇX",
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
	"ÅZ",
	"á@",
	"áA",
	"áB",
	"áC",
	"áD",
	"áE",
	"áF",
	"áG",
	"áH",
	"áI",
	"áJ",
	"áK",
	"áL",
	"áM",
	"áN",
	"áO",
	"áP",
	"áQ",
	"áR",
	"áS"
};
char statusChar[][16] = {
	"Çd",
	"Çc",
	"Çb",
	"Ça",
	"Ç`"
};
char title_Names[][16] = {
	"ÉNÉâÉCÉ}ÉbÉNÉX",
	"É_ÉCÉWÉFÉXÉg",
	"ÉtÉãÉvÉåÉC",
	"ÉGÉNÉXÉgÉäÅ[ÉÄ"
};

