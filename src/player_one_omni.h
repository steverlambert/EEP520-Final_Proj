#ifndef _PLAYER_ONE_OMNI
#define _PLAYER_ONE_OMNI

#include "enviro.h"

using namespace enviro;

// Class for "player 1" robot. Moves omnidirectionally with the
// w,a,s,d keys and fires with q. Used only for one-player game.

class PlayerOneOmniController : public Process, public AgentInterface {

    public:
    PlayerOneOmniController() : Process(), AgentInterface(), vx(0), vy(0), points(0), firing(false) {}
   
    // watches for events:
    //      killed_guy: hit enemy; points added
    //      key_down and key_up: provides control (movement and firing)
    void init() {

        watch("killed_guy", [this](Event e) {
            points++;
            label(std::to_string(points), 0, -20);
        });

        watch("keydown", [this](Event e) {
            if (e.value()["key"] == "w") {
                vy=-30;
            } else if ( e.value()["key"] == "s" ) {
                vy=30;
            } else if ( e.value()["key"] == "a" ) {
                vx=-30;
            } else if ( e.value()["key"] == "d" ) {
                vx=30;
            } else if (e.value()["key"] == "q" && !firing) {
                Agent& bullet = add_agent("Bullet", 
                    x() + 50*cos(angle()), 
                    y() + 50*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                firing = true;
            }
        });

        watch("keyup", [this](Event e) {
            if (e.value()["key"] == "q" ) {
                firing = false;
            } else if (e.value()["key"] == "w") {
                vy=0;
            } else if ( e.value()["key"] == "s" ) {
                vy=0;
            } else if ( e.value()["key"] == "a" ) {
                vx=0;
            } else if ( e.value()["key"] == "d" ) {
                vx=0;
            } 
        });
    }
    void start() {}

    // Move robot
    void update() {
        omni_track_velocity(vx,vy); 
    }

    void stop() {}

    double vx, vy;
    bool firing;
    int points;
    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"stroke-width", "5px"},
                   {"stroke-opacity", "0.25"}
               };        

};

class PlayerOneOmni : public Agent {

    public:
    PlayerOneOmni(json spec, World& world) : Agent(spec, world) {
        add_process(lc);
    }
    private:
    PlayerOneOmniController lc;

};

DECLARE_INTERFACE(PlayerOneOmni);


#endif