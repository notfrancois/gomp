#include <gomp/Gomp.hpp>
#include <gomp/api.hpp>

#include <StreamerComponent.hpp>

#ifdef __cplusplus
extern "C"
{
#endif

GOMPONENT_EXPORT int streamer_createDynamicObject(int modelid, const float x, const float y, const float z, const float rx, const float ry, const float rz, int worldid, int interiorid, int playerid)
{
    IOmpStreamerComponent* streamer = Gomp::Get()->getStreamer();

    if (const std::shared_ptr<streamer::IObject> object = streamer->createDynamicObject(modelid, Vector3(x, y, z), Vector3(rx, ry, rz), worldid, interiorid, playerid)) {
        return object->getID();
    }

    return 0;
}

GOMPONENT_EXPORT void streamer_destroyDynamicObject(int objectid)
{
    IOmpStreamerComponent* streamer = Gomp::Get()->getStreamer();
    streamer->destroyDynamicObject(objectid);
}

#ifdef __cplusplus
}
#endif
