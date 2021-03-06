#include "Option.h"

//カーソル移動関数
void CursorPositionSet(SHORT x, SHORT y) {
	CursorPosition = {
		x,  // SHORT X
		y }; // SHORT Y
	SetConsoleCursorPosition(hConsoleOutput, CursorPosition);
}

//構造体たち　実体宣言
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
PLAYER extraplayer[] = {
	{
		0,
		"けつばん",
		0,
		0,
		0
	},
	{
		1,
		"いちろー",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		2,
		"なかじま",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		3,
		"あおき",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		4,
		"じょうじま",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		5,
		"おがさわら",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		6,
		"うちかわ",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		7,
		"いわむら",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		8,
		"かたおか",
		RANK_A,
		RANK_A,
		RANK_A
	},
	{
		9,
		"ダルビ",
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
//変数たち　宣言
int outBox = 0;
int RUNNER[4] = { 0,0,0,0 };
int _inning = 9;
int _turn = TURN_TOP;
int _hideScoreCounter = 0;
int score[2] = { 0,0 };
int order[2] = { 1,1 };


//文字テーブル
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
	"Ｅ",
	"Ｄ",
	"Ｃ",
	"Ｂ",
	"Ａ"
};
char title_Names[][16] = {
	"クライマックス",
	"ダイジェスト",
	"フルプレイ",
	"エクストリーム"
};

