#ifndef COMBAT_CPP_DUNGEON_MASTER_HPP_
#define COMBAT_CPP_DUNGEON_MASTER_HPP_

#include <memory>

#include <zmq.hpp>
#include <zmq_addon.hpp>

class DungeonMaster
{
 public:
    explicit DungeonMaster(std::shared_ptr<zmq::context_t> context);
 private:
     std::shared_ptr<zmq::context_t> context_;
};

#endif // !COMBAT_CPP_DUNGEON_MASTER_HPP_
