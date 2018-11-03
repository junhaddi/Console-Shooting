#pragma region HEAD
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define GAME_WIDTH 79
#define GAME_HEIGHT 34

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define EXTENDASCII -32

#define MAXBULLET 10	
#define MAXENEMY 15

enum {
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VOILET,
	DAKR_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};
#pragma endregion

#pragma region UTIL
//==============================================
//	UTIL
//==============================================
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
#pragma endregion

#pragma region INV
//==============================================
//	INV
//==============================================	
//	SYS
BOOL isGameOver = FALSE;
int score = 0;
int bossHpMax = 100;
int bossHp = 100;

//	PLAYER
int px = GAME_WIDTH / 2;
int py = GAME_HEIGHT / 2;

//	BULLET
struct {
	BOOL isExist;
	int x, y;
} Bullet[MAXBULLET];

//	BOSS
int bx = GAME_WIDTH / 2 - 3;
int bw = 7;
int by = 5;

//	ENEMY NORMAL
struct {
	BOOL isExist;
	int x, y, dir;
} Enemy[MAXENEMY];

void colBoss();
void colEnemy();
void colPlayer();
void bossRender();
void enemyClear(int);
void enemyGen();
void enemyMove();
void bulletClear(int);
void bulletRender(int);
void bulletMove();
void playerClear();
void playerRender();
void playerAction();
void drawBossHp();
void ui();
#pragma endregion

#pragma region MAIN
//==============================================
//	MAIN
//==============================================	
void init() {
	setcursortype(NOCURSOR);
	system("mode con:cols=80 lines=40");
	ui();
	drawBossHp();
	srand(time(NULL));
}

void update() {
	playerAction();
	bulletMove();
	enemyMove();
	enemyGen();
	colBoss();
	colEnemy();
	colPlayer();
}

void render() {
	playerRender();
	bossRender();
}

int main() {
	init();
	for (;;) {
		update();
		render();
		Sleep(30);
	}
	getch();
	return 0;
}
#pragma endregion

#pragma region ENGINE
//	COLISION
void colBoss() {
	for (int i = 0; i < MAXBULLET; i++) {
		if (Bullet[i].isExist == FALSE) {
			continue;
		}
		if (Bullet[i].x >= bx && Bullet[i].x <= bx + bw && Bullet[i].y <= by) {
			//	HIT
			bulletClear(i);
			Bullet[i].isExist = FALSE;
			bossHp -= 10;
			drawBossHp();
		}
	}
}

void colEnemy() {
	int i;
	for (i = 0; i < MAXENEMY; i++) {
		if (Enemy[i].isExist == FALSE) {
			continue;
		}
		for (int j = 0; j < MAXBULLET; j++) {
			if (Bullet[j].isExist == FALSE) {
				continue;
			}
			if (Enemy[i].x == Bullet[j].x && Enemy[i].y == Bullet[j].y) {
				enemyClear(i);
				Enemy[i].isExist = FALSE;
				bulletClear(j);
				Bullet[j].isExist = FALSE;
			}
		}
	}
}

void colPlayer() {
	for (int i = 0; i < MAXBULLET; i++) {
		if (Enemy[i].isExist == FALSE) {
			continue;
		}
		if (px == Enemy[i].x && py == Enemy[i].y) {
			exit(0);
		}
	}
}

// BOSS
void bossRender() {
	gotoxy(bx, 2);
	printf("|||||||");
	gotoxy(bx, 3);
	printf("OOOOOOO");
	gotoxy(bx, 4);
	printf("O     O");
	gotoxy(bx, by);
	printf("OOOOOOO");
}

//	ENEMY
void enemyClear(int i) {
	gotoxy(Enemy[i].x, Enemy[i].y);
	printf(" ");
}

void enemyGen() {
	int i;
	if (rand() % 20 == 0) {
		for (i = 0; i < MAXENEMY && Enemy[i].isExist == TRUE; i++) { ;; }
		if (i != MAXENEMY) {
			if (rand() % 2 == 0) {
				Enemy[i].x = 1;
				Enemy[i].y = rand() % (GAME_HEIGHT - 1);
				Enemy[i].dir = 1;
			}
			else {
				Enemy[i].x = GAME_WIDTH - 1;
				Enemy[i].y = rand() % (GAME_HEIGHT - 1);
				Enemy[i].dir = -1;
			}
		}
		Enemy[i].isExist = TRUE;
	}
}

void enemyMove() {
	int i, move = 0;
	if (rand() % 5 == 0) {
		move = 1;
	}
	for (i = 0; i < MAXENEMY; i++) {
		if (Enemy[i].isExist == FALSE) {
			continue;
		}
		if (Enemy[i].x < 1 || Enemy[i].x > GAME_WIDTH - 1) {
			//	DESTROY
			Enemy[i].isExist = FALSE;
			enemyClear(i);
			score++;
		}
		else {
			//	MOVE
			enemyClear(i);
			Enemy[i].x += Enemy[i].dir * move;
			setColor(RED);
			gotoxy(Enemy[i].x, Enemy[i].y);
			printf("M");
		}
	}
}

//	BULLET
void bulletClear(int i) {
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf(" ");
}

void bulletRender(int i) {
	setColor(RED);
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf("+");
}

void bulletMove() {
	for (int i = 0; i < MAXBULLET; i++) {
		if (Bullet[i].isExist == TRUE) {
			bulletClear(i);
			if (Bullet[i].y <= 0) {
				Bullet[i].isExist = FALSE;
			}
			else {
				Bullet[i].y--;
				bulletRender(i);
			}
		}
	}
}

//	PLAYER
void playerClear() {
	gotoxy(px, py);
	printf(" ");
}

void playerRender() {
	setColor(YELLOW);
	gotoxy(px, py);
	printf("@");
}

void playerAction() {
	if (GetAsyncKeyState(VK_LEFT) < 0 && px > 0) {
		playerClear();
		px--;
		playerRender();
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0 && px < GAME_WIDTH) {
		playerClear();
		px++;
		playerRender();
	}
	if (GetAsyncKeyState(VK_UP) < 0 && py > 0) {
		playerClear();
		py--;
		playerRender();
	}
	if (GetAsyncKeyState(VK_DOWN) < 0 && py < GAME_HEIGHT - 1) {
		playerClear();
		py++;
		playerRender();
	}

	if (kbhit()) {
		int ch = getch();
		switch (ch) {
			int i;
		case ' ':
			for (i = 0; i < MAXBULLET && Bullet[i].isExist == TRUE; i++) { ;; }
			if (i != MAXBULLET) {
				Bullet[i].x = px;
				Bullet[i].y = py;
				Bullet[i].isExist = TRUE;
			}
			break;
		case ESC:
			exit(0);
		}
	}
}

//	UI
void drawBossHp() {
	//	CLEAR
	for (int i = 0; i < 3; i++) {
		for (int j = 9; j < GAME_WIDTH - 1; j++) {
			setColor(GREEN);
			gotoxy(j, GAME_HEIGHT + 2 + i);
			printf(" ");
		}
	}
	//	DRAW
	for (int i = 0; i < 3; i++) {
		for (int j = 9; j < ((float)bossHp / bossHpMax) * (GAME_WIDTH - 1); j++) {
			setColor(GREEN);
			gotoxy(j, GAME_HEIGHT + 2 + i);
			printf("#");
		}
	}
}

void ui() {
	//	FRAME
	for (int i = 0; i < GAME_WIDTH; i++) {
		setColor(WHITE);
		gotoxy(i, GAME_HEIGHT);
		printf("=");
	}

	//	ICO
	setColor(WHITE);
	gotoxy(2, GAME_HEIGHT + 2);
	printf("=");
	gotoxy(3, GAME_HEIGHT + 2);
	printf("=");
	gotoxy(4, GAME_HEIGHT + 2);
	printf("=");
	gotoxy(5, GAME_HEIGHT + 2);
	printf("=");

	gotoxy(1, GAME_HEIGHT + 3);
	printf("=");
	setColor(RED);
	gotoxy(2, GAME_HEIGHT + 3);
	printf("=");
	setColor(WHITE);
	gotoxy(3, GAME_HEIGHT + 3);
	printf("=");
	gotoxy(4, GAME_HEIGHT + 3);
	printf("=");
	setColor(RED);
	gotoxy(5, GAME_HEIGHT + 3);
	printf("=");
	setColor(WHITE);
	gotoxy(6, GAME_HEIGHT + 3);
	printf("=");

	gotoxy(3, GAME_HEIGHT + 4);
	printf("=");
	gotoxy(4, GAME_HEIGHT + 4);
	printf("=");
}
#pragma endregion