#ifndef __PLAYER_TWO_RECT__H
#define __PLAYER_TWO_RECT__H

#include "enviro.h"
#include <iostream>

using namespace enviro;

// Class for "player 1" robot. Moves in a single direction with the
// i,j,k,l keys and fires with /. Only needed for two player game.

class PlayerTwoRectController : public Process, public AgentInterface {

    public:
    PlayerTwoRectController() : Process(), AgentInterface(), 
                                f(0), tau(0), firing(false), 
                                player_one_hit(false), 
                                have_flag(false), 
                                flag_id(0),
                                frozen(false),
                                frozen_timer(0),
                                in_goal(false),
                                points(0) {}

    // Watches for events:
    //      flag_dropped2: flag dropped by self; flag respawned behind self
    //      score2: flag carried into opposite goal by self; points added, flag respawned in middle
    //      flag_in_goaltwo: flag in collision with goal
    //
    //      key_down and key_up: provides control (movement and firing)
    // Notices collisions with:
    //      bullet: drops flag (if holding)
    //      flag: attaches to flag
    
    void init() {
       
        watch("flag_dropped2", [this](Event e) {
            remove_agent(flag_id);
            // spawn flag slightly behind robot
            Agent& flag = add_agent("Flag", x()-45*cos(angle()), y()-45*sin(angle()), 0, FLAG_STYLE);
            frozen = true;
            frozen_timer = 50;
        });

        watch("score2", [this](Event e) {
            remove_agent(flag_id);
            points++;
            label(std::to_string(points), 0, -20);
            Agent& flag = add_agent("Flag", 0,0,0, FLAG_STYLE);
        });

        watch("flag_in_goaltwo", [this](Event e) {
            in_goal = true;
        });

        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "/" && !firing ) {
                Agent& bullet = add_agent("Bullet", 
                    x() + 32*cos(angle()), 
                    y() + 32*sin(angle()), 
                    angle(), 
                    BULLET_STYLE);    
                    bullet.apply_force(50,0);
                firing = true;
            } else if ( k == "i" ) {
                f = magnitude;              
            } else if ( k == "k" ) {
                f = -magnitude;  
            } else if ( k == "j" ) {
                tau = -magnitude;
            } else if ( k == "l" ) {
                tau = magnitude;
            } 
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "/" ) {
                firing = false;
            } else if ( k == "i" || k == "k" ) {
                f = 0;               
            } else if ( k == "j" ) {
                tau = 0;
            } else if ( k == "l" ) {
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

        // only move if not frozen
        if (frozen_timer <= 0)
            apply_force(f,tau);
        else 
            frozen_timer--;

        // drop flag if hit with bullet while holding flag
        if( player_one_hit && have_flag) {
            emit(Event("flag_dropped2"));
            have_flag = false;
        }

        // score if collide with goal while holding flag
        if(have_flag && in_goal) {
            emit(Event("score2"));
            have_flag = false;
        }

        in_goal = false;
        player_one_hit = false;
    }
    void stop() {}

    double f, tau;
    double const magnitude = 200;
    bool firing, player_one_hit, have_flag, frozen, in_goal;
    int flag_id, frozen_timer, points;
    const json BULLET_STYLE = { 
                   {"fill", "blue"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "1px"},
                   {"strokeOpacity", ".25"}
               };

    const json FLAG_STYLE = { 
                    {"fill", "green"}, 
                    {"stroke", "#888"}, 
                    {"strokeWidth", "1px"},
                    {"strokeOpacity", "0.25"}
                };

};

class PlayerTwoRect : public Agent {
    public:
    PlayerTwoRect(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlayerTwoRectController c;
    
};

DECLARE_INTERFACE(PlayerTwoRect);

#endif