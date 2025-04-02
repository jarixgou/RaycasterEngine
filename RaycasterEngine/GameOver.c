#include "GameOver.h"

void LoadGameOver(void)
{
	printf("Load Game Over\n");
}

void KeyPressedGameOver(sfKeyEvent _key)
{
	switch (_key.code)
	{
	case sfKeyEscape:
		SetGameState(MENU);
		break;
	case sfKeySpace:
		SetGameState(GAME);
		break;
	default:
		break;
	}
}

void UpdateGameOver(sfRenderWindow* const _renderWindow, float _dt)
{
}

void DrawGameOver(sfRenderWindow* const _renderWindow)
{
}

void CleanupGameOver(void)
{
	printf("Cleanup Game Over\n");
}
