#pragma once

#include <Windows.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

extern HINSTANCE g_hInst;
extern HWND hWndMain;
extern HBITMAP hBit;
enum DRAW_TYPE { WALL, FOOD, EMPTY };


struct PLAYER {
	int x, y;
	int Index_X, Index_Y;
	int way, next_way;
};

struct ENEMY {
	int x, y;
	int Number;
	int Index_X, Index_Y;
	int way, next_way;
	int UpImage, DownImage, LeftImage, RightImage;
};

struct TILE {
	int x, y;
	DRAW_TYPE draw_type;//{WALL,FOOD,EMPTY}
};
typedef class PlayManager {
private:
	PLAYER player;
	ENEMY enemy[4];
	TILE tile[17][17];
public:
	PlayManager();
	HBITMAP bit_wall, bit_eating, bit_empty;
	HBITMAP bit_player;
	HBITMAP bit_enemy[4];
	bool Player_Rotaion(int n);
	void Player_Move();
	void Eat();
	bool Win_Check();
	bool Enemy_Rotaion(int way, int num);
	void Enemy_Move(int EnemyNum);
	void startMenue();
	bool Catch_Player();
	void Set_Way(int n) { player.way = n; }
	void Set_NextWay(int n) { player.next_way = n; }
	void OnTimer();
	void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
	void DrawBitmap(HDC hdc, int x, int y, int n, HBITMAP hBit);
}PM;

