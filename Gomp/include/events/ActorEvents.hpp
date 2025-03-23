#pragma once
#include <sdk.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class ActorEvents : public ActorEventHandler, public Singleton<ActorEvents>
{
public:
	ActorEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onPlayerGiveDamageActor(IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part) override
	{
		gamemode_->call<void>("onPlayerGiveDamageActor", static_cast<void*>(&player), static_cast<void*>(&actor), amount, weapon, int(part));
	}

	void onActorStreamOut(IActor& actor, IPlayer& forPlayer) override
	{
		gamemode_->call<void>("onActorStreamOut", static_cast<void*>(&actor), static_cast<void*>(&forPlayer));
	}

	void onActorStreamIn(IActor& actor, IPlayer& forPlayer) override
	{
		gamemode_->call<void>("onActorStreamIn", static_cast<void*>(&actor), static_cast<void*>(&forPlayer));
	}

private:
	Gamemode* gamemode_;
};
