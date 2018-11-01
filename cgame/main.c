#define GAME_WIDTH 80
#define GAME_HEIGHT 24

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define ESC 27
#define EXTENDASCII -32

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

//==============================================
//	UTIL
//==============================================
//	PLAYER
int px = GAME_WIDTH / 2;
int py = GAME_HEIGHT / 2;

//	BULLET
int bx = -1, by = -1;
enum dir {
	East = 0,
	West,
	South,
	North
};
struct {
	BOOL isExist;
	int x, y, dir;
} Bullet;

//==============================================
//	FUNC
//==============================================	
//	INV
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

// CREATE
void bulletCreate() {
	Bullet.x = px;
	Bullet.y = py;
	Bullet.isExist = TRUE;
}

//	PLAYER
void playerClear() {
	gotoxy(px, py);
	printf(" ");
}

void playerAction() {
	if (kbhit()) {
		int key = getch();
		
		//	MOVE
		switch (key) {
		case 'a':
		case 'A':
			if (px > 1) {
				playerClear();
				px--;
			}
			break;
		case 'd':
		case 'D':
			if (px < GAME_WIDTH) {
				playerClear();
				px++;
			}
			break;
		case 'w':
		case 'W':
			if (py > 1) {
				playerClear();
				py--;
			}
			break;
		case 's':
		case 'S':
			if (py < GAME_HEIGHT) {
				playerClear();
				py++;
			}
			break;

		//	SHOOT
		case LEFT:
			bulletCreate();
			Bullet.dir = East;
			break;
		case RIGHT:
			bulletCreate();
			Bullet.dir = West;
			break;
		case UP:
			bulletCreate();
			Bullet.dir = North;
			break;
		case DOWN:
			bulletCreate();
			Bullet.dir = South;
			break;

		//	EXIT
		case ESC:
			exit(0);
		}
	}
}

void playerRender() {
	setColor(YELLOW);
	gotoxy(px, py);
	printf("@");
}

//	BULLET
void bulletClear() {
	gotoxy(Bullet.x, Bullet.y);
	printf(" ");
}

void bulletMove() {
	if (Bullet.isExist == TRUE) {
		bulletClear();

		if (Bullet.x <= 1 || Bullet.x >= GAME_WIDTH || Bullet.y <= 1 || Bullet.y >= GAME_HEIGHT) {
			Bullet.isExist = FALSE;
		}
		else {
			switch (Bullet.dir) {
			case East:
				Bullet.x--;
				break;
			case West:
				Bullet.x++;
				break;
			case South:
				Bullet.y++;
				break;
			case North:
				Bullet.y--;
				break;
			}
		}
	}
}

void bulletRender() {
	//if (Bullet.isExist == TRUE) {
		setColor(RED);
		gotoxy(Bullet.x, Bullet.y);
		printf("+");
	//}
}

//==============================================
//	GAME
//==============================================	
void init() {
	setColor(BLUE);
	//system("mode con: lines=40");
}

void update() {
	playerAction();
	bulletMove();
}

void render() {
	playerRender();
	bulletRender();
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