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

Challenges:

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

README has an overview of what the goal of the project is
10	README has a description of key challenges and how they were addressed
10	README describes how to install and run the code (assuming the user has docker installed)
10	README describes how to run and/or use the project
5	README acknowedges all sources of information or code used
