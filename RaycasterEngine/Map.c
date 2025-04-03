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
	mapData.nbWall2D = 0;
	mapData.nbWall3D = 0;

	mapData.planeX = 0;
	mapData.planeY = 0.66f;

	mapData.wall2D = calloc(0, sizeof(sfRectangleShape*));
	mapData.wall3D = calloc(0, sizeof(sfRectangleShape*));

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
				sfRectangleShape_setPosition(mapData.wall2D[mapData.nbWall2D], (sfVector2f) { x* (float)CELL_SIZE, y* (float)CELL_SIZE });

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
	for (int i = 0; i < mapData.nbWall3D; i++)
	{
		sfRectangleShape_destroy(mapData.wall3D[i]);
		mapData.wall3D[i] = NULL;
	}
	mapData.nbWall3D = 0;
	free(mapData.wall3D);
	mapData.wall3D = NULL;
	mapData.wall3D = calloc(0, sizeof(sfRectangleShape*));

	float radAngle = _playerAngle * M_PI / 180;

	mapData.planeX = cosf((float)(radAngle + M_PI / 2));
	mapData.planeY = sinf((float)(radAngle + M_PI / 2));

	// Transform 2D into 3D
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Calculate ray direction and positon
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // X cordinate in camera space
		double rayDirX = cosf(radAngle) + mapData.planeX * cameraX;
		double rayDirY = sinf(radAngle) + mapData.planeY * cameraX;

		// Calculate the player pos in the map
		int mapX = floorf(_playerPos.x);
		int mapY = floorf(_playerPos.y);

		// Lenght of ray
		double sideDistX = 0;
		double sideDistY = 0;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist = 0;

		int stepX = 0;
		int stepY = 0;

		int hit = 0;
		int side = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (_playerPos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.f - _playerPos.x) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (_playerPos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.f - _playerPos.y) * deltaDistY;
		}

		// Perform DDA
		while (hit == 0)
		{
			// Jump to next map square
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// Check if ray has hit a wall
			if (map[mapX][mapY] != 0)
			{
				hit = 1;
			}
		}

		if (side == 0)
		{
			perpWallDist = sideDistX - deltaDistX;
		}
		else
		{
			perpWallDist = sideDistY - deltaDistY;
		}

		// Calculate height of line to draw on screen
		int lineHeight = (int)SCREEN_HEIGHT / perpWallDist;

		// Calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
		{
			drawStart = 0;
		}

		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
		{
			drawEnd = SCREEN_HEIGHT - 1;
		}

		sfColor color = sfWhite;
		switch (map[mapX][mapY])
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

		if (side == 1)
		{
			color = sfColor_fromRGB(color.r / 2, color.g / 2, color.b / 2);
		}

		sfRectangleShape** allocWall3D = realloc(mapData.wall3D, ((size_t)mapData.nbWall3D + 1) * sizeof(sfRectangleShape*));
		if (!allocWall3D)
		{
			fprintf(stderr, "Re alloc wall 3D failed !");
			system("pause");
			exit(EXIT_FAILURE);
		}
		mapData.wall3D = allocWall3D;
		allocWall3D = NULL;

		mapData.wall3D[mapData.nbWall3D] = sfRectangleShape_create();
		sfRectangleShape_setPosition(mapData.wall3D[mapData.nbWall3D], (sfVector2f) { (float)x, (float)drawStart });
		sfRectangleShape_setSize(mapData.wall3D[mapData.nbWall3D], (sfVector2f) { 1.f, (float)(drawEnd - drawStart) });
		sfRectangleShape_setFillColor(mapData.wall3D[mapData.nbWall3D], color);

		mapData.nbWall3D++;
	}
}

void DrawMap(sfRenderWindow* _renderWindow)
{
	/*for (int i = 0; i < mapData.nbWall2D; i++)
	{
		sfRenderWindow_drawRectangleShape(_renderWindow, mapData.wall2D[i], NULL);
	}*/

	for (int i = 0; i < mapData.nbWall3D; i++)
	{
		sfRenderWindow_drawRectangleShape(_renderWindow, mapData.wall3D[i], NULL);
	}
}

void CleanupMap(void)
{
}
