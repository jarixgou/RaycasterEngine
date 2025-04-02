#include "GameState.h"

GameState gameState = START;

void LoadGameState(void);
void CleanupGameState(void);

void SetGameState(GameState _gameState)
{
	CleanupGameState();
	gameState = _gameState;
	LoadGameState();
}

GameState GetGameState(void)
{
	return gameState;
}

void LoadGameState()
{
	switch (gameState)
	{
	case MENU:
		LoadMenu();
		break;
	case GAME:
		LoadGame();
		break;
	case GAME_OVER:
		LoadGameOver();
		break;
	default:
		break;
	}
}

void CleanupGameState()
{
	switch (gameState)
	{
	case MENU:
		CleanupMenu();
		break;
	case GAME:
		CleanupGame();
		break;
	case GAME_OVER:
		CleanupGameOver();
		break;
	default:
		break;
	}
}
