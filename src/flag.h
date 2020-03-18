#ifndef _FLAG_AGENT_H
#define _FLAG_AGENT_H 

#include "enviro.h"
using namespace enviro;

// Flag (or ball) class. Spawns and is moved by other robots.
// Collisions with flag detected by goals.

class FlagController : public Process, public AgentInterface {

    public:
    FlagController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}
};

class Flag : public Agent {

    public:
    Flag(json spec, World& world) : Agent(spec, world) {
        add_process(lc);
    }
    private:
    FlagController lc;

};

DECLARE_INTERFACE(Flag);


#endif