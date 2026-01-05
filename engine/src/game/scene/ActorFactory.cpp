#include "game/scene/ActorFactory.h"

#include "game/object/ActorsSystem.h"

template <>
ActorsSystem& ActorFactory::GetSystem<ActorsSystem>() {
    return mActorsSystem;
}
