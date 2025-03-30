#pragma once

#include <sdk.hpp>
#include <Server/Components/Dialogs/dialogs.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class GompDialogEvents : public PlayerDialogEventHandler, public Singleton<GompDialogEvents>
{
public:
	GompDialogEvents()
	{
		gamemode_ = Gamemode::Get();
	}

	void onDialogResponse(IPlayer& player, int dialogId, DialogResponse response, int listItem, StringView inputText) override
	{
		String inputTextStr = { inputText.data(), inputText.length() };

		gamemode_->call<void>("onDialogResponse", static_cast<void*>(&player), dialogId, int(response), listItem, inputTextStr);
	}

private:
	Gamemode* gamemode_;
};
