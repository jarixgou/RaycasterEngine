#ifndef RICH_PRESENCE_H
#define RICH_PRESENCE_H

#ifdef __cplusplus
#define DISCORDPP_IMPLEMENTATION
#include "Discord/discordpp.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <functional>
#include <csignal>

extern "C"
{

	void CreateRichPresence(int _clientID, char _states[], char _details[], char _gameName[], char _icon[]);
}

#endif // __cplusplus

#endif // !RICH_PRESENCE_H

