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

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	UTIL
int key;

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setColor(unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	GAME
void init() {
	setColor(BLUE);
}

void update() {
	if (kbhit()) {
		key = getch();
		switch (key) {
			case LEFT:
				printf("LEFT");
				break;
			case RIGHT:
				printf("RIGHT");
				break;
			case UP:
				printf("UP");
				break;
			case DOWN:
				printf("DOWN");
				break;
		}
	}
}

void render() {
	system("cls");
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