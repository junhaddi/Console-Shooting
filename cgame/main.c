#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define GAME_WIDTH 80
#define GAME_HEIGHT 40

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ESC 27
#define EXTENDASCII -32
#define MAXBULLET 3

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

enum {
	EAST,
	WEST,
	SOUTH,
	NORTH
};

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

//==============================================
//	FUNC
//==============================================	
//	PLAYER
int px = GAME_WIDTH / 2;
int py = GAME_HEIGHT / 2;

//	BULLET
int bx = -1, by = -1;
int mx = -1, my;

struct {
	BOOL isExist;
	int x, y, dir;
} Bullet[MAXBULLET];

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
			if (Bullet[i].y <= 0 || Bullet[i].x >= GAME_WIDTH || Bullet[i].y >= GAME_HEIGHT || Bullet[i].x <= 0) {
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
	if (GetAsyncKeyState(VK_RIGHT) < 0 && px < GAME_WIDTH - 1) {
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
			for (i = 0; i < MAXBULLET && Bullet[i].isExist == TRUE; i++) { ; }
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

//==============================================
//	MAIN
//==============================================	
void update() {
	playerAction();
	bulletMove();
}

void init() {
	//setcursortype(NOCURSOR);
	system("mode con:cols=80 lines=40");
	//randomize();
}

void render() {
	playerRender();
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