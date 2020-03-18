#ifndef _GOAL_AGENT_H
#define _GOAL_AGENT_H 

#include "enviro.h"

using namespace enviro;

// Goal class. Static object. Emits an event when the flag
// collides with it.

class GoalController : public Process, public AgentInterface {

    public:
    GoalController() : Process(), AgentInterface(), goal(false) {}

    // Notices collisions with flag
    void init() {
        notice_collisions_with("Flag", [&](Event &e) {
            goal = true;
        });
    }
    void start() {}

    // Emits flag_in_goal event when collision with flag occurs
    void update() {
        if (goal)
            emit(Event("flag_in_goal"));

        goal = false;
    }
    void stop() {}

    bool goal;
};

class Goal : public Agent {
    public:
    Goal(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GoalController c;
};

DECLARE_INTERFACE(Goal)

#endif