#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"

#define PLAYER_SPRITE_PATH "Assets/Sprites/Player.png"
#define PLAYER_VELOCITY 5
#define PLAYER_ROTATION_FACTOR 50.f

typedef struct PlayerData
{
	sfSprite* spr;
	sfTexture* tex;
	float angle;

	sfVector2f dir;
}PlayerData;

void LoadPlayer(void);
void UpdatePlayer(float _dt);
void DrawPlayer(sfRenderWindow* _renderWindow);
void CleanupPlayer(void);

sfVector2f GetPlayerPosition(void);
float GetPlayerAngle(void);

#endif // !PLAYER_H

