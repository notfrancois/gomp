#pragma once
#include <sdk.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class GompMenuEvents : public MenuEventHandler, public Singleton<GompMenuEvents>
{
public:
	GompMenuEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerSelectedMenuRow(IPlayer& player, MenuRow row) override
	{
		gamemode_->call<void>("onPlayerSelectedMenuRow", static_cast<void*>(&player), uint8_t(row));
	}
	
	void onPlayerExitedMenu(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerExitedMenu", static_cast<void*>(&player));
	}

private:
	Gamemode* gamemode_;
};
