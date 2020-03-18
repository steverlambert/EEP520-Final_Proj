#ifndef _FOLLOW_AGENT_H
#define _FOLLOW_AGENT_H 

#include "enviro.h"

using namespace enviro;

// Class for "enemy". Tries to move toward goal.

class FollowController : public Process, public AgentInterface {

    public:
    FollowController() : Process(), AgentInterface(), counter(50), goalx(-600), goaly(0), speed(1) {}

    // Notices collisions with:
    //      GoalTwo: enemy wins, player loses
    //      Bullet: enemy "dies", new enemy "spawns", speed increments
    void init() {
        
        notice_collisions_with("GoalTwo", [&](Event &e) {
            label("YOU LOSE", 0, -100);
        });

        notice_collisions_with("Bullet", [&](Event &e) {
            emit(Event("killed_guy"));
            teleport(600,rand()%600 - 300,0);
            speed+=0.05; // increase attack speed each time
        });
    }
    void start() {}

    // Move robot after a delay so user has time to prepare
    // goalx and goaly are coordinates of the goal that the player is defending
    void update() {
        if (counter-- < 0)
            omni_move_toward(goalx, goaly, speed); 
    }

    void stop() {}
    float vx,vy, speed;
    int counter, goalx, goaly;
};

class Follower : public Agent {

    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(lc);
    }
    private:
    FollowController lc;

};

DECLARE_INTERFACE(Follower);


#endif