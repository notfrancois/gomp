#pragma once

#include <sdk.hpp>

#include <gomp/Singleton.hpp>
#include <gomp/Gamemode.hpp>

class StreamerEvents : public Singleton<StreamerEvents>, public streamer::StreamerEventHandler
{
private:
    Gamemode* gamemode_;
public:
    StreamerEvents()
    {
        gamemode_ = Gamemode::Get();
    }    

    void onStreamerCreateDynamicObject(int objectid)
    {
        gamemode_->call<void>("onStreamerCreateDynamicObject", objectid);
    }
};