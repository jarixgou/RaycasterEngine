#include "Player.h"

PlayerData playerData;

void LoadPlayer(void)
{
	playerData.spr = sfSprite_create();
	playerData.tex = sfTexture_createFromFile(PLAYER_SPRITE_PATH, NULL);

	sfSprite_setTexture(playerData.spr, playerData.tex, sfTrue);

	sfFloatRect hitbox = sfSprite_getGlobalBounds(playerData.spr);
	sfSprite_setOrigin(playerData.spr, (sfVector2f) { hitbox.width / 2, hitbox.height / 2 });

	sfSprite_setScale(playerData.spr, (sfVector2f) { GAME_SCALE * 3, GAME_SCALE * 3 });

	sfSprite_setPosition(playerData.spr, (sfVector2f) { 128, 324 });
}

void UpdatePlayer(float _dt)
{
	playerData.angle = 0;
	if (sfKeyboard_isKeyPressed(sfKeyRight))
	{
		playerData.angle += PLAYER_ROTATION_FACTOR * _dt;
	}
	if (sfKeyboard_isKeyPressed(sfKeyLeft))
	{
		playerData.angle -= PLAYER_ROTATION_FACTOR * _dt;
	}

	float angle = sfSprite_getRotation(playerData.spr);
	playerData.dir.x = cosf((float)((angle - 90) * M_PI / 180));
	playerData.dir.y = sinf((float)((angle - 90) * M_PI / 180));
	printf("dir : %f %f\n", playerData.dir.x, playerData.dir.y);

	sfVector2f velocity = { 0 };


	if (sfKeyboard_isKeyPressed(sfKeyUp))
	{
		velocity = (sfVector2f){ playerData.dir.x * PLAYER_VELOCITY * _dt, playerData.dir.y * PLAYER_VELOCITY * _dt };
	}
	else if (sfKeyboard_isKeyPressed(sfKeyDown))
	{
		velocity = (sfVector2f){ playerData.dir.x * -PLAYER_VELOCITY * _dt, playerData.dir.y * -PLAYER_VELOCITY * _dt };
	}

	sfSprite_move(playerData.spr, velocity);
	sfSprite_rotate(playerData.spr, playerData.angle);
}

void DrawPlayer(sfRenderWindow* _renderWindow)
{
	sfRenderWindow_drawSprite(_renderWindow, playerData.spr, NULL);
}

void CleanupPlayer(void)
{
	sfTexture_destroy(playerData.tex);
	playerData.tex = NULL;

	sfSprite_destroy(playerData.spr);
	playerData.spr = NULL;
}

sfVector2f GetPlayerPosition(void)
{
	return sfSprite_getPosition(playerData.spr);
}

float GetPlayerAngle(void)
{
	return sfSprite_getRotation(playerData.spr) - 90;
}
