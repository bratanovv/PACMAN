#include "PlayerManager.h"
#include"resource.h"
#include "resource1.h"

#pragma comment(lib,"msimg32.lib")
HINSTANCE g_hInst;
HWND hWndMain;
HBITMAP hBit;

#define SIZE 20
double LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}


int MapInfo[17][17] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1 },
	{ 1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1 },
	{ 1,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1 },
	{ 1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,0,1 },
	{ 1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1 },
	{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1 },
	{ 1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1 },
	{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};


PlayManager::PlayManager() {
	int tempx = 40;
	int tempy = 40;
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (MapInfo[i][j] == 1) {
				tile[i][j].draw_type = WALL;
			}
			else
				tile[i][j].draw_type = FOOD;
			tile[i][j].x = tempx;
			tile[i][j].y = tempy;
			tempx += 40;
		}
		tempx = 40;
		tempy += 40;
	}

	player.x = 320;
	player.y = 640;
	player.Index_X = 7;
	player.Index_Y = 15;
	player.way = 0;
	player.next_way = 0;


	enemy[0].x = 80;
	enemy[0].y = 80;
	enemy[0].Index_X = 1;
	enemy[0].Index_Y = 1;
	enemy[0].way = 1;
	enemy[0].next_way = 1;

	enemy[1].x = 640;
	enemy[1].y = 80;
	enemy[1].Index_X = 15;
	enemy[1].Index_Y = 1;
	enemy[1].way = 2;
	enemy[1].next_way = 2;

	enemy[2].x = 80;
	enemy[2].y = 640;
	enemy[2].Index_X = 1;
	enemy[2].Index_Y = 15;
	enemy[2].way = 0;
	enemy[2].next_way = 0;

	enemy[3].x = 640;
	enemy[3].y = 320;
	enemy[3].Index_X = 15;
	enemy[3].Index_Y = 7;
	enemy[3].way = 1;
	enemy[3].next_way = 1;


	for (int i = 0; i < 4; i++)
	{
		enemy[i].UpImage = IDB_BITMAP_ENEMY1_UP + (i * 4);
		enemy[i].DownImage = IDB_BITMAP_ENEMY1_DOWN + (i * 4);
		enemy[i].LeftImage = IDB_BITMAP_ENEMY1_LEFT + (i * 4);
		enemy[i].RightImage = IDB_BITMAP_ENEMY1_RIGHT + (i * 4);
	}
	srand(clock());

}
bool PlayManager::Player_Rotaion(int n)//n:сторона поворота
{
	switch (n)
	{
	case 0://вверх
		if (tile[player.Index_Y - 1][player.Index_X].draw_type != WALL)//if next up is not wall
		{
			DeleteObject(bit_player);
			bit_player = nullptr;
			bit_player = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_UP));
			player.way = player.next_way;
			return true;
		}
		else
			return false;
		break;
	case 1://вниз
		if (tile[player.Index_Y + 1][player.Index_X].draw_type != WALL)
		{
			DeleteObject(bit_player);
			bit_player = nullptr;
			bit_player = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_DOWN));
			player.way = player.next_way;
			return true;
		}
		else
			return false;
		break;
	case 2://лево
		if (tile[player.Index_Y][player.Index_X - 1].draw_type != WALL)
		{
			DeleteObject(bit_player);
			bit_player = nullptr;
			bit_player = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_LEFT));
			player.way = player.next_way;
			return true;
		}
		else
			return false;
		break;
	case 3://право
		if (tile[player.Index_Y][player.Index_X + 1].draw_type != WALL)
		{
			DeleteObject(bit_player);
			bit_player = nullptr;
			bit_player = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_RIGHT));
			player.way = player.next_way;
			return true;
		}
		else
			return false;
		break;
	}
	return false;
}
void PlayManager::Player_Move()
{
	switch (player.way)
	{
	case 0:
		if ((player.y % 40) == 0) {
			Eat();
			if (player.way != player.next_way)// если след поворот не совпадает с нынешним направлением то поворачиваем
			{
				if (Player_Rotaion(player.next_way))
					break;
			}
			if (tile[player.Index_Y - 1][player.Index_X].draw_type != WALL) // если совпадает направление то проверяем не стена ли дальше
			{
				player.y -= 10;
				player.Index_Y -= 1;
			}
		}
		else//ecли не в клетке
		{
			player.y -= 10;//двигаемся чуть вперед
		}
		break;
	case 1:
		if ((player.y % 40) == 0) {
			Eat();
			if (player.way != player.next_way)
			{
				if (Player_Rotaion(player.next_way))
					break;
			}
			if (tile[player.Index_Y + 1][player.Index_X].draw_type != WALL)
			{
				player.y += 10;
				player.Index_Y += 1;
			}
		}
		else
		{
			player.y += 10;
		}
		break;
	case 2:
		if ((player.x % 40) == 0) {
			Eat();
			if (player.way != player.next_way)
			{
				if (Player_Rotaion(player.next_way))
					break;
			}
			if (tile[player.Index_Y][player.Index_X - 1].draw_type != WALL)
			{
				player.x -= 10;
				player.Index_X -= 1;
			}
		}
		else
		{
			player.x -= 10;
		}
		break;
	case 3:
		if ((player.x % 40) == 0) {
			Eat();
			if (player.way != player.next_way)
			{
				if (Player_Rotaion(player.next_way))
					break;
			}
			if (tile[player.Index_Y][player.Index_X + 1].draw_type != WALL)
			{
				player.x += 10;
				player.Index_X += 1;
			}
		}
		else
		{
			player.x += 10;
		}
		break;
	}
}
bool PlayManager::Enemy_Rotaion(int way, int num)
{

	switch (way)
	{
	case 0://вверх
		if (tile[enemy[num].Index_Y - 1][enemy[num].Index_X].draw_type != WALL)
		{
			DeleteObject(bit_enemy[num]);
			bit_enemy[num] = nullptr;
			bit_enemy[num] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(enemy[num].UpImage));
			enemy[num].way = way;
			return true;
		}
		else
			return false;
		break;
	case 1:
		if (tile[enemy[num].Index_Y + 1][enemy[num].Index_X].draw_type != WALL)
		{
			DeleteObject(bit_enemy[num]);
			bit_enemy[num] = nullptr;
			bit_enemy[num] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(enemy[num].DownImage));
			enemy[num].way = way;
			return true;
		}
		else
			return false;
		break;
	case 2://лево
		if (tile[enemy[num].Index_Y][enemy[num].Index_X - 1].draw_type != WALL)
		{
			DeleteObject(bit_enemy[num]);
			bit_enemy[num] = nullptr;
			bit_enemy[num] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(enemy[num].LeftImage));
			enemy[num].way = way;
			return true;
		}
		else
			return false;
		break;
	case 3:
		if (tile[enemy[num].Index_Y][enemy[num].Index_X + 1].draw_type != WALL)
		{
			DeleteObject(bit_enemy[num]);
			bit_enemy[num] = nullptr;
			bit_enemy[num] = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(enemy[num].RightImage));
			enemy[num].way = way;
			return true;
		}
		else
			return false;
		break;
	}
	return false;
}
void PlayManager::Enemy_Move(int num)
{
	int ran = rand();
	switch (enemy[num].way)
	{
	case 0:
		if ((enemy[num].y % 40) == 0) {
			enemy[num].next_way = (ran % 2) + 2;//рандомим след путь
			if (tile[enemy[num].Index_Y - 1][enemy[num].Index_X].draw_type != WALL)
			{
				enemy[num].y -= 10;
				enemy[num].Index_Y -= 1;
			}
			else if (enemy[num].way != enemy[num].next_way)
			{
				if (Enemy_Rotaion(enemy[num].next_way, num))
					break;
			}
		}
		else //если не стоит в клетке
		{
			enemy[num].y -= 10;
		}
		break;
	case 1:
		if ((enemy[num].y % 40) == 0) {
			enemy[num].next_way = (ran % 2) + 2;
			if (tile[enemy[num].Index_Y + 1][enemy[num].Index_X].draw_type != WALL)
			{
				enemy[num].y += 10;
				enemy[num].Index_Y += 1;
			}
			else if (enemy[num].way != enemy[num].next_way)
			{
				if (Enemy_Rotaion(enemy[num].next_way, num))
					break;
			}
		}
		else
		{
			enemy[num].y += 10;
		}
		break;
	case 2:
		if ((enemy[num].x % 40) == 0) {
			enemy[num].next_way = (ran % 2);
			if (tile[enemy[num].Index_Y][enemy[num].Index_X - 1].draw_type != WALL)
			{
				enemy[num].x -= 10;
				enemy[num].Index_X -= 1;
			}
			else if (enemy[num].way != enemy[num].next_way)
			{
				if (Enemy_Rotaion(enemy[num].next_way, num))
					break;
			}
		}
		else
		{
			enemy[num].x -= 10;
		}
		break;
	case 3:
		if ((enemy[num].x % 40) == 0) {
			enemy[num].next_way = (ran % 2);
			if (tile[enemy[num].Index_Y][enemy[num].Index_X + 1].draw_type != WALL)
			{
				enemy[num].x += 10;
				enemy[num].Index_X += 1;
			}
			else if (enemy[num].way != enemy[num].next_way)
			{
				if (Enemy_Rotaion(enemy[num].next_way, num))
					break;
			}
		}
		else
		{
			enemy[num].x += 10;
		}
		break;
	}
}
void PlayManager::startMenue()
{
	RECT crt;
	HDC hDC, hMemDC;
	HBITMAP OldBit;
	static int n = 0;
	static int m = 0;
	GetClientRect(hWndMain, &crt);
	hDC = GetDC(hWndMain);

	hBit = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);

	hMemDC = CreateCompatibleDC(hDC);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	for (int i = 0; i < 17; i++)//отрисовка карты
	{
		for (int j = 0; j < 17; j++)
		{
			if (tile[i][j].draw_type == WALL) {
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_wall);
			}
			else if (tile[i][j].draw_type == FOOD)
			{
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_eating);

			}
			else if (tile[i][j].draw_type == EMPTY)
			{
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_empty);
			}
		}
	}
	DrawBitmap(hMemDC, player.x, player.y, n, bit_player);//игрок


	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hDC);
	InvalidateRect(hWndMain, NULL, FALSE);
}



void PlayManager::OnTimer()
{
	RECT crt;
	HDC hDC, hMemDC;
	HBITMAP OldBit;
	static int n = 0;
	static int m = 0;
	GetClientRect(hWndMain, &crt);
	hDC = GetDC(hWndMain);

	hBit = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);

	hMemDC = CreateCompatibleDC(hDC);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	for (int i = 0; i < 17; i++)//отрисовка карты
	{
		for (int j = 0; j < 17; j++)
		{
			if (tile[i][j].draw_type == WALL) {
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_wall);
			}
			else if (tile[i][j].draw_type == FOOD)
			{
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_eating);

			}
			else if (tile[i][j].draw_type == EMPTY)
			{
				DrawBitmap(hMemDC, tile[i][j].x, tile[i][j].y, bit_empty);
			}
		}
	}

	DrawBitmap(hMemDC, player.x, player.y, n, bit_player);//игрок
	DrawBitmap(hMemDC, enemy[0].x, enemy[0].y, m, bit_enemy[0]);// враг
	DrawBitmap(hMemDC, enemy[1].x, enemy[1].y, m, bit_enemy[1]);
	DrawBitmap(hMemDC, enemy[2].x, enemy[2].y, m, bit_enemy[2]);
	DrawBitmap(hMemDC, enemy[3].x, enemy[3].y, m, bit_enemy[3]);

	n += 40;	//смена картинок анимации персонажа
	if (n >= 200)
		n = 0;

	m += 40;
	if (m >= 80)
		m = 0;
	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWndMain, hDC);
	InvalidateRect(hWndMain, NULL, FALSE);
}
void PlayManager::DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit) //рисование обьектов
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;
	BitBlt(hdc, x - SIZE, y - SIZE, bx, by, MemDC, 0, 0, SRCCOPY);


	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
void PlayManager::DrawBitmap(HDC hdc, int x, int y, int n, HBITMAP hBit) //рисование персонажей
{
	HDC MemDC;
	HBITMAP OldBitmap;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	TransparentBlt(hdc, x - SIZE, y - SIZE, 40, 40, MemDC, n, 0, 40, 40, RGB(255, 0, 255));

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
void PlayManager::Eat()
{
	if (tile[player.Index_Y][player.Index_X].draw_type == FOOD) {
		tile[player.Index_Y][player.Index_X].draw_type = EMPTY;//Измените тип плитки  еду -> пустое место.
	}
}
bool PlayManager::Win_Check()
{
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (tile[i][j].draw_type == FOOD)
				return false;
		}
	}
	return true;//выйграл
}

bool PlayManager::Catch_Player() //сьеден ли пакман
{
	for (int i = 0; i < 4; i++)
	{
		if (LengthPts(player.x, player.y, enemy[i].x, enemy[i].y) < 30) // расстояние между ними меньше клетки
			return true;
	}
	return false;
}
//pizda