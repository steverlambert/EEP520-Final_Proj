#ifndef _GAME_CONTROLLER_H
#define _GAME_CONTROLLER_H 

#include "enviro.h"

using namespace enviro;

// Inivisible class that handles the initial creation of objects 

class GameStartController : public Process, public AgentInterface {

    public:
    GameStartController() : Process(), AgentInterface(), starting(true) {}

    // Spawns additional agents based on which button is clicked.
    // Button 1 - One Player Mode 1: player one (rectangular movement), goal, follower (the enemy)
    // Button 2 - One Player Mode 2: player one (omni movement), goal, follower (the enemy)
    // Button 3 - Two Player Mode: player one, player two, goal one, goal two, flag

    void init() {
        watch("button_click", [this](Event &e) {
            if(e.value()["value"] == "1") {
                if (starting) {
                    Agent& player1 = add_agent("PlayerOneRect", -400, 0, 0, P1_STYLE);
                    Agent& goal2 = add_agent("GoalTwo", -600, 0, 0, GOAL2_STYLE);
                    Agent& fol = add_agent("Follower", 600, 100, 0, FOL_STYLE);
                }
                starting = false;
            }

            if(e.value()["value"] == "1_1") {
                if (starting) {
                    Agent& player1o = add_agent("PlayerOneOmni", -400, 0, 0, P1_STYLE);
                    Agent& goal2 = add_agent("GoalTwo", -600, 0, 0, GOAL2_STYLE);
                    Agent& fol = add_agent("Follower", 600, 100, 0, FOL_STYLE);
                }
                starting = false;
            }

            if(e.value()["value"] == "2") {
                if (starting) {
                    Agent& goal2 = add_agent("GoalTwo", -600, 0, 0, GOAL2_STYLE);
                    Agent& goal1 = add_agent("Goal", 600, 0, 0, GOAL_STYLE);
                    Agent& flag = add_agent("Flag", 0, 0, 0, FLAG_STYLE);
                    Agent& player2 = add_agent("PlayerTwoRect", 400, 0, 3.14, P2_STYLE);
                    Agent& player1 = add_agent("PlayerOneRect", -400, 0, 0, P1_STYLE);
                }
                starting = false;
            }
        });
    }
    void start() {}
    void update() {
    }
    void stop() {}
    bool starting;

    const json GOAL2_STYLE = { 
                   {"fill", "lightgreen"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "1px"},
                   {"strokeOpacity", "0.25"}
               };
    const json GOAL_STYLE = { 
                   {"fill", "blue"}, 
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
    const json FOL_STYLE = { 
                    {"fill", "black"}, 
                    {"stroke", "#888"}, 
                    {"strokeWidth", "1px"},
                    {"strokeOpacity", "0.25"}
                };
    const json P1_STYLE = { 
                    {"fill", "lightgreen"}, 
                    {"stroke", "#888"}, 
                    {"strokeWidth", "1px"},
                    {"strokeOpacity", "0.25"}
                };
    const json P2_STYLE = { 
                    {"fill", "blue"}, 
                    {"stroke", "#888"}, 
                    {"strokeWidth", "1px"},
                    {"strokeOpacity", "0.25"}
                };

};

class GameController : public Agent {
    public:
    GameController(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    GameStartController c;
};

DECLARE_INTERFACE(GameController)

#endif