#pragma once

#include <sdk.hpp>
#include <Server/Components/Console/console.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>
#include <gomp/api.hpp>

class GompConsoleEvents : public ConsoleEventHandler, public Singleton<GompConsoleEvents>
{
public:
	GompConsoleEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	bool onConsoleText(StringView command, StringView parameters, const ConsoleCommandSenderData& sender) override
	{
		String commandStr = { command.data(), command.length() };
		String parametersStr = { parameters.data(), parameters.length() };

		return gamemode_->call<unsigned char>("onConsoleText", commandStr, parametersStr) != 0;
	}

	void onRconLoginAttempt(IPlayer& player, StringView password, bool success) override
	{
		String passwordStr = { password.data(), password.length() };

		gamemode_->call<void>("onRconLoginAttempt", static_cast<void*>(&player), passwordStr, (unsigned char)(success ? 1 : 0));
	}

	// void onConsoleCommandListRequest(FlatHashSet<StringView>& commands) { }

private:
	Gamemode* gamemode_;
};
