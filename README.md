# EEP520-Final_Proj
A 1- or 2- player robot soccer game (with shooting).

The goal of this project was to create a game that could be played with one or two players - on a single computer - that used several of the latest enviro features, including: 
- omnidirectional agents
- dynamically adding/removing agents
- buttons
- keyboard front end events
- invisible agents
- collisions
- agent constraints, such as attaching

# Challenges
The most difficult and time-consuming aspect of creating this game was the dynamic addition and removal of agents. I encountered the errors "could not find agent id", "bad function call", and "can't add to process while updating" countless times while trying to add or remove agents. At first, I was handling much of the control of the system with the "player one" robot class. Once invisible agents were an option, I moved the control to an overall invisible controller, which made the code much cleaner and easier to debug. I also realized that you cannot add an agent inside a collision loop (this gives the "updating" error). Emitting events and setting flags became the best method. For the flag control in the two-player game, I left the control in the robot classes because the flag needed to respawn directly behind the robots and the flag class is unaware of the robots' positions. The teleport method would be perfect for this, but - because the flag is attached to the robot - it will remain attached after a teleport, which throws everything into chaos. A "detach" method would be useful here. 

Somewhat related to the above, I spent several hours trying to add a "reset" command so the game could be played multiple times and with different modes without the need to restart enviro. I was ultimately unsuccessful. By teleporting agents back to their starting position, resetting works if the user plays the same mode over and over, but once a new mode is selected the process breaks. My other method was to emit a "reset" event when the reset button is clicked. This produced two odd behaviors. First, it would reset and start a new game successfully once but would crash with a “could not find agent id” on the second reset. Second, when I reset, emitted the event, and deleted the relevant agents, a “ghost” agent was leftover. An invisible version of the robot that was deleted remained and would eventually crash the system. I only know this because it fired white bullets that were outlined in black when I pressed the fire key. So, the first addition to my game when I have more time is a reset button.

# Installation
Clone the EEP520-Final_Proj repository and make it your working directory.
Then, run 

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.5 bash
```
From there, compile with
```bash
make
```
Start the enviro server with 
```bash
esm start
enviro
```
Then, navigating to http://localhost in any web browser will bring up the project window.

# Running
The game features single player and two player modes. The mode is selected with the buttons in the top right of the screen.

Single Player:
For single player mode, you may select between two fighters. The first is a tank that moves forward or backward and turns like a typical car. The second is a spaceship that can move in any direction. Both fighters fire their weapons in the direction you are facing.

The objective is to protect the goal from the attacking enemy. Your player is moved with the w,s,a,d keys and can fire with the q key. Shoot the enemy to protect the goal. You will gain points for each enemy you kill! The game is lost when the enemy reaches the goal.

![two](single-player_1.png)
Single Player Mode: Fighter 1

![two](single-player_2.png)
Single Player Mode: Fighter 2

Two Player:
In two player mode, both players use the tank robot. Player 1 (green) moves with w,s,a,d and fires with q. Player 2 (blue) moves with i,j,k,l and fires with /. The objective is to score the ball in the other players goal. The ball will attach to the tank when they come in contact. If shot while holding the ball, a player will drop the ball and will be frozen for a couple seconds. First player to 3 wins!

![two](two-player.png)
Two Player Mode

Notes:
- to change modes, you must stop and rerun enviro
- my high score in single-player mode is 10

# Sources
- https://github.com/klavinslab/enviro

