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

 > ## Phase II
 > In addition to completing the "Class Diagram" section below, you will need to 
 > * Set up your GitHub project board as a Kanban board for the project. It should have columns that map roughly to 
 >   * Backlog, TODO, In progress, In testing, Done
 >   * You can change these or add more if you'd like, but we should be able to identify at least these.
 > * There is no requirement for automation in the project board but feel free to explore those options.
 > * Create an "Epic" (note) for each feature and each design pattern and assign them to the appropriate team member. Place these in the `Backlog` column
 > * Complete your first *sprint planning* meeting to plan out the next 7 days of work.
 >   * Create smaller development tasks as issues and assign them to team members. Place these in the `TODO` column.
 >   * These cards should represent roughly 7 days worth of development time for your team, taking you until your first meeting with the TA
## Class Diagram
 > Include a class diagram(s) for each design pattern and a description of the diagram(s). Your class diagram(s) should include all the main classes you plan for the project. This should be in sufficient detail that another group could pick up the project this point and successfully complete it. Use proper OMT notation (as discussed in the course slides). You may combine multiple design patterns into one diagram if you'd like, but it needs to be clear which portion of the diagram represents which design pattern (either in the diagram or in the description). 
 

![uml1](FactoryUML.jpg "FactoryUML")
![uml2](Scenes.jpg "Scenes")

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
 
