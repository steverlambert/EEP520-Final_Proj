#ifndef _GOALTWO_AGENT_H
#define _GOALTWO_AGENT_H 

#include "enviro.h"

using namespace enviro;

// Goal class #2. Static object. Emits an event when the flag
// collides with it.

class GoalTwoController : public Process, public AgentInterface {

    public:
    GoalTwoController() : Process(), AgentInterface(), goal(false) {}

    // notices collisions with flag
    void init() {
        notice_collisions_with("Flag", [&](Event &e) {
            goal = true;
        });
    }
    void start() {}

    // Emits flag_in_goaltwo event when collides with flag
    void update() {
        if (goal)
            emit(Event("flag_in_goaltwo"));

        goal = false;
    }
    void stop() {}

    bool goal;

};

class GoalTwo : public Agent {
    public:
    GoalTwo(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GoalTwoController c;
};

DECLARE_INTERFACE(GoalTwo)

#endif