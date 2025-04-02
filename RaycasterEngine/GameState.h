#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Common.h"
#include "Menu.h"
#include "Game.h"
#include "GameOver.h"

typedef enum GameState
{
	START,
	MENU,
	GAME,
	GAME_OVER,
}GameState;

void SetGameState(GameState _gameState);
GameState GetGameState(void);

#endif
