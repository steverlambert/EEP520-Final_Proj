#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"
#include <iostream>

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0), hit_leader(false) {}

    void init() {
        
        notice_collisions_with("PlayerOneRect", [&](Event &e) {
            remove_agent(id());
        });

        notice_collisions_with("PlayerTwoRect", [&](Event &e) {
            remove_agent(id());
        });

        notice_collisions_with("Follower", [&](Event &e) {
            remove_agent(id());
        });

        notice_collisions_with("StaticObject", [&](Event &e) {
            remove_agent(id());
        });     

    }
    void start() {}
    void update() {

        if ( counter++ > 30 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;
    bool hit_leader;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif