#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define BLUE 9
#define GREEN 10
#define SKY 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15

//	TODO
#define GAME_WIDTH 30
#define GAME_HEIGHT 30

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	UTIL
px = 30;
py = 30;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	UTIL
int key;

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void playerClear() {
	gotoxy(px, py);
	printf(" ");
}

void playerMov() {
	if (kbhit()) {
		key = getch();
		switch (key) {
		case LEFT:
			playerClear();
			px--;
			break;
		case RIGHT:
			playerClear();
			px++;
			break;
		case UP:
			playerClear();
			py--;
			break;
		case DOWN:
			playerClear();
			py++;
			break;
		}
	}
}

void playerRender() {
	setColor(YELLOW);
	gotoxy(px, py);
	printf("@");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	GAME
void init() {
	setColor(BLUE);
	//system("mode con: lines=40");
}

void update() {
	playerMov();
}

void render() {
	playerRender();
}

void free() {

}

int main() {
	init();

	for (;;) {
		update();
		render();
	}
	free();

	return 0;
}