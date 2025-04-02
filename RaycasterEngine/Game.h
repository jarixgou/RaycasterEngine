#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "GameState.h"

#include "Map.h"
#include "Player.h"

void LoadGame(void);
void KeyPressedGame(sfKeyEvent _key);
void UpdateGame(sfRenderWindow* const _renderWindow, float _dt);
void DrawGame(sfRenderWindow* const _renderWindow);
void CleanupGame(void);

#endif // !GAME_H
