# Turn-Based RPG Game

 > Authors: [Krishaan Patel](https://github.com/kpate135), [Rany Tith](https://github.com/ranyishere), [Gabriel Ruelas](https://github.com/FeistierMage-Gabe)

## Project Description
* Why is it important or interesting to you?
  * Because games are fun
  * Turnased RPG's are fun
* What languages/tools/technologies do you plan to use?
  * OpenGL - graphics tool (GLUT library) - (GLUT is event driven)
  * C++11 - Language
* What will be the input/output of your project?
  * GLUT library will handle keyboard and mouse input events
  * GLUT will display changes to the user graphically
* What are the design patterns you will be using? 
   * Abstract Factory:
     * This chooses what kind of monster to spawn and the quantity. For example, if a user is within a specific region of the map then choose a monster that represents that region. This design pattern will allow us to keep track of how regions of the map interact with the quantity and type of monsters without producing redundant code.
  * Composite:
    * This will handle our basic class system in the game for both allies and enemies. We chose composite because it makes it easier to structure and maintain our ally and enemy class systems. Composite allows us to alter and handle various groups of characteristics shared between certain characters.
 
## Class Diagram
![uml1](FactoryUML.jpg "FactoryUML")

![uml2](Scenes.jpg "Scenes")
The Abstract Scene acts as your abstract factory. There are four concrete factories: Battle Scene, Dialogue Scene, Victory Scene and Game Over Scene.
Each factory creates a Background, Character Sprite, and On-Screen text objects. In the UML diagram you can see how the factory is implemented on
the top right.


 > ## Phase III
 > You will need to schedule a check-in with the TA (during lab hours or office hours). Your entire team must be present. 
 > * Before the meeting you should perform a sprint plan like you did in Phase II
 > * In the meeting with your TA you will discuss: 
 >   - How effective your last sprint was (each member should talk about what they did)
 >   - Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 >   - Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 >   - What tasks you are planning for this next sprint.

 > ## Final deliverable
 > All group members will give a demo to the TA during lab time. The TA will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Kanban board. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
