#ifndef MAP_H
#define MAP_H

#include "Common.h"

#define CELL_SIZE 32 * GAME_SCALE
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

typedef enum WallID
{
	NOTHING,
	GREEN,
	BLUE,
	YELLOW,
	MAX_WALL_ID
}WallID;

typedef struct mapData
{
	sfRectangleShape** wall2D; // Array
	int nbWall2D;
	
	double planeX;
	double planeY;
}MapData;

void LoadMap(void);
void UpdateMap(float _dt, sfVector2f _playerPos, float _playerAngle);
void DrawMap(sfRenderWindow* _renderWindow);
void CleanupMap(void);

#endif // !MAP_H
