/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Include the component's definition.
#include <gomp/Gomp.hpp>
#include <gomp/Gamemode.hpp>
#include <events/ActorEvents.hpp>
#include <events/CheckpointEvents.hpp>
#include <events/ClassEvents.hpp>
#include <events/ConsoleEvents.hpp>
#include <events/DialogEvents.hpp>
#include <events/GangZoneEvents.hpp>
#include <events/MenuEvents.hpp>
#include <events/ObjectEvents.hpp>
#include <events/PickupEvents.hpp>
#include <events/PlayerEvents.hpp>
#include <events/TextDrawEvents.hpp>
#include <events/VehicleEvents.hpp>
#include <events/CustomModelEvents.hpp>

// Required component methods.
StringView Gomp::componentName() const {
	return "Go";
}

SemanticVersion Gomp::componentVersion() const
{
	return SemanticVersion(1, 0, 0, 0);
}

void Gomp::onLoad(ICore* c)
{
	// Cache core, listen to player events.

	core = c;
	config = &c->getConfig();
	players = &c->getPlayers();

	gamemode_ = Gamemode::Get();
}

void Gomp::onInit(IComponentList* components)
{
	actors = components->queryComponent<IActorsComponent>();
	checkpoints = components->queryComponent<ICheckpointsComponent>();
	classes = components->queryComponent<IClassesComponent>();
	console = components->queryComponent<IConsoleComponent>();
	dialogs = components->queryComponent<IDialogsComponent>();
	gangzones = components->queryComponent<IGangZonesComponent>();
	menus = components->queryComponent<IMenusComponent>();
	objects = components->queryComponent<IObjectsComponent>();
	pickups = components->queryComponent<IPickupsComponent>();
	textdraws = components->queryComponent<ITextDrawsComponent>();
	textlabels = components->queryComponent<ITextLabelsComponent>();
	vehicles = components->queryComponent<IVehiclesComponent>();
	models = components->queryComponent<ICustomModelsComponent>();
	streamer = components->queryComponent<IOmpStreamerComponent>();

	if (actors)
	{
		actors->getEventDispatcher().addEventHandler(ActorEvents::Get());
	}

	if (checkpoints)
	{
		checkpoints->getEventDispatcher().addEventHandler(CheckpointEvents::Get());
	}

	if (classes)
	{
		classes->getEventDispatcher().addEventHandler(ClassEvents::Get());
	}

	if (console)
	{
		console->getEventDispatcher().addEventHandler(ConsoleEvents::Get());
	}

	if (dialogs)
	{
		dialogs->getEventDispatcher().addEventHandler(DialogEvents::Get());
	}

	if (gangzones)
	{
		gangzones->getEventDispatcher().addEventHandler(GangZoneEvents::Get());
	}

	if (menus)
	{
		menus->getEventDispatcher().addEventHandler(MenuEvents::Get());
	}

	if (objects)
	{
		objects->getEventDispatcher().addEventHandler(ObjectEvents::Get());
	}

	if (pickups)
	{
		pickups->getEventDispatcher().addEventHandler(PickupEvents::Get());
	}

	if (players)
	{
		players->getPlayerSpawnDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerConnectDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerStreamDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerTextDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerShotDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerChangeDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerDamageDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerClickDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerCheckDispatcher().addEventHandler(PlayerEvents::Get());
		players->getPlayerUpdateDispatcher().addEventHandler(PlayerEvents::Get());
	}

	if (textdraws)
	{
		textdraws->getEventDispatcher().addEventHandler(TextDrawEvents::Get());
	}

	if (vehicles)
	{
		vehicles->getEventDispatcher().addEventHandler(VehicleEvents::Get());
	}

	if (models)
	{
		models->getEventDispatcher().addEventHandler(CustomModelEvents::Get());
	}
}

bool Gomp::loadGamemode() {
	StringView gamemodeName = config->getString("go.gamemode");
	if (gamemodeName.empty()) {
		core->logLn(LogLevel::Error, "go.gamemode config string is not set");
		return false;
	}

	try {
		gamemode_->load(gamemodeName.to_string());
		gamemode_->call<void>("onGameModeInit");
		return true;
	}
	catch (const std::runtime_error& error) {
		core->logLn(LogLevel::Error, "Failed to load gamemode: %s", error.what());
		return false;
	}
}

void Gomp::onReady() {
	if (!loadGamemode()) {
		return;
	}
}

void Gomp::onFree(IComponent* component)
{
#define COMPONENT_UNLOADED(var) \
	if (component == var)       \
		var = nullptr;

	COMPONENT_UNLOADED(actors)
	COMPONENT_UNLOADED(checkpoints)
	COMPONENT_UNLOADED(classes)
	COMPONENT_UNLOADED(console)
	COMPONENT_UNLOADED(dialogs)
	COMPONENT_UNLOADED(gangzones)
	COMPONENT_UNLOADED(menus)
	COMPONENT_UNLOADED(objects)
	COMPONENT_UNLOADED(pickups)
	COMPONENT_UNLOADED(textdraws)
	COMPONENT_UNLOADED(textlabels)
	COMPONENT_UNLOADED(vehicles)
	COMPONENT_UNLOADED(models)
	COMPONENT_UNLOADED(streamer)
}

void Gomp::free()
{
	// Deletes the component.
	delete this;
}

void Gomp::reset()
{
	// Resets data when the mode changes.
}

// When this component is destroyed we need to tell any linked components this it is gone.
Gomp::~Gomp()
{
	// unload gamemode
	gamemode_->call<void>("onGameModeExit");
	gamemode_->unload();
}

// Get the Streamer component (extending legacy support).
IOmpStreamerComponent* Gomp::getStreamer() {
	return streamer;
}
