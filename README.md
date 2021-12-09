# Terrene
Terrene is an AI simulation game which was created during my first year of study at Academy of Interactive Entertainment. It utilises a thid party software called Raylib which serves as a wrapper around OpenGL, abstracting away the API and lower level management.</br>
</br>
In terrene the user can place sheep and wolf AI agents. These agents will try to maintain their stat levels using binary AI decision trees and A* pathfinding. You can view these stats by selecting an agent. This will highlight the agent and display a small GUI box containing information about the agent's stats and current activity.</br>
You can also toggle the debugging overlay. It shows each agent's detection range, the nearest points of interest (i.e food and water), their current path and the generated navigation grid.</br>
</br>
Procedural generation was used to generate the terrain and other features of Terrene. Unfortunately, to change the seed you must change a define and recomplie the project. It was meant to be that way for testing purposes and consistency but definitely should have been changed upon validating generation consistency.
