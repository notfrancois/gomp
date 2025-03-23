#pragma once
#include <sdk.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class CheckpointEvents : public PlayerCheckpointEventHandler, public Singleton<CheckpointEvents>
{
public:
	CheckpointEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerEnterCheckpoint(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerEnterCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerLeaveCheckpoint(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerLeaveCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerEnterRaceCheckpoint(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerEnterRaceCheckpoint", static_cast<void*>(&player));
	}

	void onPlayerLeaveRaceCheckpoint(IPlayer& player) override
	{
		gamemode_->call<void>("onPlayerLeaveRaceCheckpoint", static_cast<void*>(&player));
	}

private:
	Gamemode* gamemode_;
};
