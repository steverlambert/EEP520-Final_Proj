#ifndef __PLAYER_ONE_RECT__H
#define __PLAYER_ONE_RECT__H

#include "enviro.h"
#include <iostream>

using namespace enviro;

// Class for "player 1" robot. Moves in a single direction with the
// w,a,s,d keys and fires with q. 

class PlayerOneRectController : public Process, public AgentInterface {

    public:
    PlayerOneRectController() : Process(), AgentInterface(), 
                                f(0), tau(0), firing(false), 
                                player_one_hit(false), 
                                have_flag(false), 
                                flag_id(0),
                                frozen(false),
                                frozen_timer(0),
                                in_goal(false),
                                points(0) {}

    
    // Watches for events:
    //      2-Player Mode:
    //      flag_dropped1: flag dropped by self; flag respawned behind self
    //      score1: flag carried into opposite goal by self; points added, flag respawned in middle
    //      flag_in_goal: flag in collision with goal
    //      1-Player Mode:
    //      killed_guy: hit enemy; points added
    //
    //      key_down and key_up: provides control (movement and firing)
    // Notices collisions with:
    //      bullet: drops flag (if holding)
    //      flag: attaches to flag

    void init() {
        
        watch("flag_dropped1", [this](Event e) {
            remove_agent(flag_id);
            Agent& flag = add_agent("Flag", x()-45*cos(angle()), y()-45*sin(angle()), 0, BULLET_STYLE);
            frozen = true;
            frozen_timer = 50;
        });

        watch("score1", [this](Event e) {
            remove_agent(flag_id);
            points++;
            label(std::to_string(points), 0, -20);
            Agent& flag = add_agent("Flag", 0,0,0, FLAG_STYLE);
        });

        watch("flag_in_goal", [this](Event e) {
            in_goal = true;
        });

        watch("killed_guy", [this](Event e) {
            points++;
            label(std::to_string(points), 0, -20);
        });
        
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "q" && !firing ) {
                Agent& bullet = add_agent("Bullet", 
                    x() + 32*cos(angle()), 
                    y() + 32*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                firing = true;
            } else if ( k == "w" ) {
                f = magnitude;              
            } else if ( k == "s" ) {
                f = -magnitude;  
            } else if ( k == "a" ) {
                tau = -magnitude;
            } else if ( k == "d" ) {
                tau = magnitude;
            } 
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "q" ) {
                firing = false;
            } else if ( k == "w" || k == "s" ) {
                f = 0;               
            } else if ( k == "a" ) {
                tau = 0;
            } else if ( k == "d" ) {
                tau = 0;
            } 
        });

        notice_collisions_with("Bullet", [&](Event &e) {
            player_one_hit = true;
        }); 

        notice_collisions_with("Flag", [&](Event &e) {
            flag_id = e.value()["id"];
            Agent& other_robot = find_agent(flag_id);
            attach_to(other_robot);
            have_flag = true;
        });

    }
    void start() {}

    // Moves robot and emits events as needed
    void update() {

        // robot can only move if it is not frozen 
        if (frozen_timer <= 0)
            apply_force(f,tau);
        else 
            frozen_timer--;

        // drop flag if hit with bullet while holding flag
        if( player_one_hit && have_flag) {
            emit(Event("flag_dropped1"));
            have_flag = false;
        }

        // score if collide with goal while holding flag
        if(have_flag && in_goal) {
            emit(Event("score1"));
            have_flag = false;
        }
        player_one_hit = false;
        in_goal = false;
    }

    void stop() {}

    double f, tau;
    double const magnitude = 200;
    bool firing, player_one_hit, have_flag, frozen, in_goal;
    int flag_id, frozen_timer, points;
    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "1px"},
                   {"strokeOpacity", "0.25"}
               };
    const json FLAG_STYLE = { 
                    {"fill", "green"}, 
                    {"stroke", "#888"}, 
                    {"strokeWidth", "1px"},
                    {"strokeOpacity", "0.25"}
                };

};

class PlayerOneRect : public Agent {
    public:
    PlayerOneRect(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlayerOneRectController c;
    
};

DECLARE_INTERFACE(PlayerOneRect);

#endif