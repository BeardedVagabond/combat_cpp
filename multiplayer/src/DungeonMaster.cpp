#include "DungeonMaster.hpp"

explicit DungeonMaster::DungeonMaster(std::shared_ptr<zmq::context_t> context)
    : context_(std::move(context))
{
}
