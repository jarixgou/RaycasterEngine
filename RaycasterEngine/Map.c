#include "Map.h"

MapData mapData;

int map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,2,0,0,0,0,0,0,0,1},
	{1,0,0,2,0,0,0,0,0,0,0,1},
	{1,0,0,2,2,2,0,0,0,0,0,1},
	{1,0,0,0,0,3,0,0,0,0,0,1},
	{1,0,0,0,0,3,0,0,0,0,0,1},
	{1,0,0,0,0,3,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

void LoadMap(void)
{
	mapData.planeX = 0;
	mapData.planeY = 0.66f;

	mapData.wall2D = calloc(0, sizeof(sfRectangleShape*));

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			if (map[y][x] != NOTHING)
			{
				sfRectangleShape** allocWall2D = realloc(mapData.wall2D, ((size_t)mapData.nbWall2D + 1) * sizeof(sfRectangleShape*));
				if (!allocWall2D)
				{
					fprintf(stderr, "Re alloc wall 2D failed");
					system("pause");
					exit(EXIT_FAILURE);
				}
				mapData.wall2D = allocWall2D;
				allocWall2D = NULL;

				mapData.wall2D[mapData.nbWall2D] = sfRectangleShape_create();

				sfRectangleShape_setSize(mapData.wall2D[mapData.nbWall2D], (sfVector2f) { CELL_SIZE, CELL_SIZE });
				sfRectangleShape_setPosition(mapData.wall2D[mapData.nbWall2D], (sfVector2f) { x* CELL_SIZE, y* CELL_SIZE });

				sfColor color = sfWhite;
				switch (map[y][x])
				{
				case GREEN:
					color = sfGreen;
					break;
				case BLUE:
					color = sfBlue;
					break;
				case YELLOW:
					color = sfYellow;
					break;
				default:
					break;
				}

				sfRectangleShape_setFillColor(mapData.wall2D[mapData.nbWall2D], color);

				mapData.nbWall2D++;
			}
		}

	}
}

void UpdateMap(float _dt, sfVector2f _playerPos, float _playerAngle)
{
	// Transform 2D into 3D
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Calculate ray direction and positon
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // X cordinate in camera space
		double rayDirX = cosf(_playerAngle) + mapData.planeX * cameraX;
		double rayDirY = sinf(_playerAngle) + mapData.planeY * cameraX;

		// Calculate the player pos in the map
		int mapX = floorf(_playerPos.x);
		int mapY = floorf(_playerPos.y);

		// Lenght of ray
		double sideDistX = 0;
		double sideDistY = 0;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
	}
}

void DrawMap(sfRenderWindow* _renderWindow)
{
	for (int i = 0; i < mapData.nbWall2D; i++)
	{
		sfRenderWindow_drawRectangleShape(_renderWindow, mapData.wall2D[i], NULL);
	}
}

void CleanupMap(void)
{
}
