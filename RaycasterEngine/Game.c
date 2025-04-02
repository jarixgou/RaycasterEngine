#include "Game.h"

void LoadGame(void)
{
	printf("Load Game\n");
	LoadMap();
	LoadPlayer();
}

void KeyPressedGame(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
		break;
	case sfKeySpace:
		SetGameState(GAME_OVER);
		break;
	default:
		break;
	}
}

void UpdateGame(sfRenderWindow* const _renderWindow, float _dt)
{
	UpdatePlayer(_dt);
	UpdateMap(_dt, GetPlayerPosition(), GetPlayerAngle());
}

void DrawGame(sfRenderWindow* const _renderWindow)
{
	DrawMap(_renderWindow);
	DrawPlayer(_renderWindow);
}

void CleanupGame(void)
{
	printf("Cleanup Game\n");
}
