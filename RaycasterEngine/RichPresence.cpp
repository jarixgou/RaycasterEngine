#include "RichPresence.h"

void CreateRichPresence(int _clientID, char _states[], char _details[], char _gameName[], char _icon[])
{
	// Create our Discord Client
	auto client = std::make_shared<discordpp::Client>();

	// Set up logging callback
	client->AddLogCallback([](auto message, auto severity) {
		std::cout << "[" << EnumToString(severity) << "] " << message << std::endl;
		}, discordpp::LoggingSeverity::Info);
}