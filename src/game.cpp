#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <iostream>

#include "sound.h"
#include "Sprite.h"
#include "PiskellSprite.h"
#include "SpriteFactory.h"
#include "Constants.h"

#include "scene.h"
#include <stdexcept>
#include "entity/Entity.hpp"
#include "entity/Character.hpp"
#include "entity/Equipment.hpp"
#include "entity/Action.hpp"
#include "entity/Factory.hpp"

#include "entity/turn.h"
#include <vector>
#include <thread>


// TODO: Fix game volume

// GLOBALS
int STEP = 0;
std::string current_scene = "start_scene";
std::string test = "";
std::string test2 = "";
std::string test3 = "";
std::string test4 = "";
std::string test5 = "";
std::string test6 = "this loser";
std::string monsterHealth = "";

std::string dmgeDone = "";
std::string testNum = "0123456789";
std::string menu = "run_attack";

bool playFx = true;
bool threadFx = true;

GLuint fontOffset;

std::string playerOneName = "";
std::string playerOneHP = "";

std::string playerTwoName = "";
std::string playerTwoHP = "";

std::string playerThreeName = "";
std::string playerThreeHP = "";

std::string playerFourName = "";
std::string playerFourHP = "";


std::vector<std::string> playerNames;

bool entityIsCharacter(Entity* entity) {

    for (unsigned int i=0; i < playerNames.size(); i++ ) {
        if (entity->GetName() == playerNames.at(i)) {
            return true;
        }
    }
    return false;
};

void makeRasterFont(void)
{
   GLuint i, j;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   fontOffset = glGenLists(128);
   for (i = 0,j = 'A'; i < 26; i++,j++) {
      glNewList(fontOffset + j, GL_COMPILE);
      glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
      glEndList();
   }

   glNewList(fontOffset + ' ', GL_COMPILE);
   glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
   glEndList();
}

GLuint fontNumOffset;
void makeRasterNumbers(void) {
    GLuint i, j;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    fontNumOffset = glGenLists(128);

    for (i=0, j='0'; i < 10; i++, j++) {
        glNewList(fontNumOffset + j, GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, numbers[i]);
        glEndList();
    };

}

void printString(const char *s, int length)
{
   glPushAttrib(GL_LIST_BIT);
   glListBase(fontOffset);
   glCallLists((GLsizei) length, GL_UNSIGNED_BYTE, (GLubyte *) s);
   glPopAttrib();
}

void printNumber(const char *s, int length) {
    glPushAttrib(GL_LIST_BIT);
    glListBase(fontNumOffset);
    glCallLists((GLsizei) length, GL_UNSIGNED_BYTE, (GLubyte *) s);
    glPopAttrib();
}


class Text : public Sprite {

    public:
        std::string *text;
        float red;
        float green;
        float blue;

        Text(std::string *currentText) {
            this->text = currentText;
            this->red = 1.0;
            this->green = 1.0;
            this->blue = 1.0;
        };

        void make() {
           GLfloat white[3] = { this->red, this->green, this->blue };
           glColor3fv(white);
           glRasterPos2i(this->xPos, this->yPos);
           printString(this->text->c_str(), this->text->size());

        };

        void setText(std::string text) {
            *this->text = text;
        };

        std::string * getText() {
            return this->text;
        };

        void setRed(float red) {
            this->red = red;
        };

        void setGreen(float green) {
            this->green= green;
        };

        void setBlue(float blue) {
            this->blue = blue;
        };
};


class TextNumber : public Sprite {

    public:
    std::string *text;
    float red;
    float green;
    float blue;

    TextNumber(std::string *currentText) {
            this->text = currentText;
            this->red = 1.0;
            this->green = 1.0;
            this->blue = 1.0;
        };

    void make() {
        GLfloat white[3] = { this->red, this->green, this->blue };
        glColor3fv(white);
        glRasterPos2i(this->xPos, this->yPos);
        printNumber(this->text->c_str(), this->text->size());
    };

        void setText(std::string text) {
            *this->text = text;
        };


        std::string * getText() {
            return this->text;
        };

        void setRed(float red) {
            this->red = red;
        };

        void setGreen(float green) {
            this->green= green;
        };

        void setBlue(float blue) {
            this->blue = blue;
        };

};


SpriteFactory spriteFactory;

// Sprites Setup
Sprite *boxFactory = spriteFactory.makeByName("DIALOGUE_BOX");
Sprite *logoFactory = spriteFactory.makeByName("LOGO");

Sprite *startBGFactory = spriteFactory.makeByName("START_BG");
Sprite *tavernBGFactory = spriteFactory.makeByName("TAVERN_BG");
Sprite *battleBGFactory = spriteFactory.makeByName("BATTLE_BG");
Sprite *catacombsBGFactory = spriteFactory.makeByName("CATACOMBS_BG");

// Forest
Sprite *banditFactory = spriteFactory.makeByName("BANDIT");
Sprite *spiderFactory = spriteFactory.makeByName("SPIDER");
Sprite *batFactory = spriteFactory.makeByName("BAT");
Sprite *slimeFactory = spriteFactory.makeByName("SLIME");

// Catacomb
Sprite *skeletonFactory = spriteFactory.makeByName("SKELETON");
Sprite *coughbieFactory = spriteFactory.makeByName("COUGHBIE");


Text *textOneFactory = new Text(&test);
Text *textTwoFactory = new Text(&test2);
Text *textThreeFactory = new Text(&test3);
Text *textFourFactory = new Text(&test4);
Text *textFiveFactory = new Text(&test5);
Text *chosenIndicator = new Text(&test6);
TextNumber *monsterHPIndicator = new TextNumber(&monsterHealth);
TextNumber *dmgIndicator = new TextNumber(&dmgeDone);
TextNumber *textNumFactory = new TextNumber(&testNum);

GLubyte sprite[TAVERN_SCENE_FRAME_HEIGHT][TAVERN_SCENE_FRAME_WIDTH][4];


// Character information
CharacterFactory characterFactory;
EntityFactory entityFactory;
PowerGemFactory powerGemFactory;
ArmorFactory armorFactory;

Character *mainCharacter = characterFactory.MakeByID(8);

class StartScene : public Scene {

    public:

      StartScene() : Scene() {

          this->name = "start_scene";
          textOneFactory->setXPos(315);
          textOneFactory->setYPos(100);
          textOneFactory->setGreen(0.5);

          this->music = "sounds/title_1.mp3";

          this->sprites.push_back(startBGFactory);

          banditFactory->setXPos(BACKGROUND_BORDER+100+45);
          banditFactory->setYPos(250);

          this->sprites.push_back(banditFactory);

          spiderFactory->setXPos(BACKGROUND_BORDER+200+45);
          spiderFactory->setYPos(250);
          this->sprites.push_back(spiderFactory);

          skeletonFactory->setXPos(BACKGROUND_BORDER+350+45);
          skeletonFactory->setYPos(250);
          this->sprites.push_back(skeletonFactory);

          coughbieFactory->setXPos(BACKGROUND_BORDER+450+45);
          coughbieFactory->setYPos(250);
          this->sprites.push_back(coughbieFactory);

          this->sprites.push_back(logoFactory);
          this->sprites.push_back(boxFactory);
          this->sprites.push_back(textOneFactory);

      }

};


class TavernScene : public Scene {

    public:
        TavernScene() : Scene() {

            this->name = "tavern_scene";
            threadLife = false;
            // threadLife = true;

            this->music = "sounds/tavern_bgm.mp3";
            textOneFactory->setGreen(1.0);
            textOneFactory->setXPos(TEXT_BOX_BORDER);
            textOneFactory->setYPos(140);

            textTwoFactory->setXPos(TEXT_BOX_BORDER);
            textTwoFactory->setYPos(100);

            textThreeFactory->setXPos(TEXT_BOX_BORDER);
            textThreeFactory->setYPos(60);

            this->sprites.push_back(tavernBGFactory);
            this->sprites.push_back(boxFactory);
            this->sprites.push_back(textOneFactory);
            this->sprites.push_back(textTwoFactory);
            this->sprites.push_back(textThreeFactory);
        }

};


class BattleScene : public Scene {

    public:

        int numMonsters = 0;

        BattleScene() {

            threadLife = false;

            name = "battle_scene";
            // music = "sounds/start_music.mp3";
             music = "sounds/battle_theme_catacomb.mp3";

            std::string area = "Catacombs";
            Entity* monsterOne = entityFactory.MakeByArea(area);
            Entity* monsterTwo = entityFactory.MakeByArea(area);
            Entity* monsterThree = entityFactory.MakeByArea(area);
            Entity* monsterFour = entityFactory.MakeByArea(area);

            enemyTeam[0] = monsterOne;
            enemyTeam_size += 1;

            enemyTeam[1] = monsterTwo;
            enemyTeam_size += 1;

            enemyTeam[2] = monsterThree;
            enemyTeam_size += 1;

            enemyTeam[3] = monsterFour;
            enemyTeam_size += 1;

            this->monsters.push_back(monsterOne);
            this->monsters.push_back(monsterTwo);
            this->monsters.push_back(monsterThree);
            this->monsters.push_back(monsterFour);

            Sprite *monsterOneFac = spriteFactory.makeByName(monsterOne->GetName());
            Sprite *monsterTwoFac = spriteFactory.makeByName(monsterTwo->GetName());
            Sprite *monsterThreeFac = spriteFactory.makeByName(monsterThree->GetName());
            Sprite *monsterFourFac = spriteFactory.makeByName(monsterFour->GetName());

            this->sprites.push_back(catacombsBGFactory);
            monsterOneFac->setXPos(BACKGROUND_BORDER+50);
            monsterOneFac->setYPos(250);
            this->sprites.push_back(monsterOneFac);

            monsterTwoFac->setXPos(BACKGROUND_BORDER+200);
            monsterTwoFac->setYPos(300);
            this->sprites.push_back(monsterTwoFac);

            monsterThreeFac->setXPos(BACKGROUND_BORDER+350);
            monsterThreeFac->setYPos(250);
            this->sprites.push_back(monsterThreeFac);

            monsterFourFac->setXPos(BACKGROUND_BORDER+500);
            monsterFourFac->setYPos(350);
            this->sprites.push_back(monsterFourFac);

            this->sprites.push_back(boxFactory);

            std::string namesTogether;

            for (unsigned int i=0; i < enemyTeam_size; i++) {
                namesTogether = namesTogether + " " + enemyTeam[i]->GetName();
            };

            textOneFactory->setText("OH NO YOU ENCOUNTERED " + namesTogether);
            this->sprites.push_back(textOneFactory);

            textTwoFactory->setText("ATTACK");
            this->sprites.push_back(textTwoFactory);

            textThreeFactory->setText("RUN");
            this->sprites.push_back(textThreeFactory);

            textFourFactory->setText("");
            textFourFactory->setXPos(TEXT_BOX_BORDER+100);
            textFourFactory->setYPos(100);

            this->sprites.push_back(textFourFactory);

            textFiveFactory->setText("");
            textFiveFactory->setXPos(TEXT_BOX_BORDER+100);
            textFiveFactory->setYPos(60);
            this->sprites.push_back(textFiveFactory);

            // Who is chosen
            this->sprites.push_back(chosenIndicator);

            // Show hp of monsters on screen
            this->sprites.push_back(monsterHPIndicator);

            // Show damage on screen
            this->sprites.push_back(dmgIndicator);
        };
};

class VictoryScene : public Scene {


    public:
    VictoryScene() {

        Sprite *victoryText = spriteFactory.makeByName("VICTORY_TEXT");
        Sprite *dialogueBox = spriteFactory.makeByName("DIALOGUE_BOX");

        victoryText->setXPos(victoryText->getXPos() + 200);

        textOneFactory->setText("TADA YOU DEFEATED THEM");
        this->sprites.push_back(victoryText);
        this->sprites.push_back(dialogueBox);
        this->sprites.push_back(textOneFactory);

        // Resetting menu
        menu = "run_attack";

    };

};

class GameOverScene : public Scene {

    public:
        GameOverScene() {

            threadLife = false;
            name = "game_over_scene";

            music = "sounds/death.mp3";
            Sprite *gameOverText = spriteFactory.makeByName("GAME_OVER_TEXT");
            Sprite *dialogueBox = spriteFactory.makeByName("DIALOGUE_BOX");

            textOneFactory->setText("PRESS A TO QUIT");
            this->sprites.push_back(gameOverText);
            this->sprites.push_back(dialogueBox);
            this->sprites.push_back(textOneFactory);
        };

};


Scene *globalScene = new StartScene();

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glShadeModel (GL_FLAT);
   makeRasterFont();
   makeRasterNumbers();
}



void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0.0, w, 0.0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void startSceneChoices() {
    if (test == "") {
        test = "PRESS A TO START";
        test2 = "";
    } else {
        test = "";
    };
};


void tavernSceneChoices() {

    // Description of scene
    test =  "YOU GAIN CONSCIOUS AND SEE A BARTENDER WORKING AWAY";

    // Options
    test2 = " LOOK AROUND AND PONDER.";
    test3 = " YOU GIVE UP";

    if (USR_CHOICE == 0){

        test2 = "O" + test2;
        textTwoFactory->setGreen(0.5);
        textThreeFactory->setGreen(1.0);
    }
    else if (USR_CHOICE == 1) {
        
        test3 = "O" + test3;
        textTwoFactory->setGreen(1.0);
        textThreeFactory->setGreen(0.5);
    }
};


void battleSceneChoices() {

    if (menu.compare("run_attack") == 0) {
        if (USR_CHOICE == 0) {
            textTwoFactory->setGreen(0.5);
            textThreeFactory->setGreen(1.0);
        }
        else if (USR_CHOICE == 1) {
            textTwoFactory->setGreen(1.0);
            textThreeFactory->setGreen(0.5);
        };
    } else if (menu.compare("choose_attack") == 0) {

        isPlayer = entityIsCharacter(turnQueue.front());

        // ?? Check
        if (isPlayer == true) {

            textTwoFactory->setText(enemyTeam[0]->GetName());
            textThreeFactory->setText(enemyTeam[1]->GetName());
            textFourFactory->setText(enemyTeam[2]->GetName());
            textFiveFactory->setText(enemyTeam[3]->GetName());

            std::string descr = "WHO DO YOU WANT " + turnQueue.front()->GetName() + " TO ATTACK";

            textOneFactory->setText(descr);

           Entity *curMonster = globalScene->monsters.at(USR_CHOICE);

           int indXPos = globalScene->sprites.at(USR_CHOICE+1)->getXPos();
           int indYPos = globalScene->sprites.at(USR_CHOICE+1)->getYPos();

           // update chosen position
           chosenIndicator->setText(enemyTeam[USR_CHOICE]->GetName() + " HP");
           chosenIndicator->setXPos(indXPos);
           chosenIndicator->setYPos(indYPos - 50);
           chosenIndicator->setGreen(0);
           chosenIndicator->setRed(0);
           chosenIndicator->setBlue(0);

           monsterHPIndicator->setXPos(indXPos);
           monsterHPIndicator->setYPos(indYPos - 80);
           monsterHPIndicator->setGreen(0);
           monsterHPIndicator->setBlue(0);

           int monsterHP = curMonster->GetHP();

            if (monsterHP < 0) {
                monsterHP = 0;
            }

            monsterHPIndicator->setText(std::to_string(monsterHP));


        } else if (isPlayer == false) {

            // Mosnter accept dialogue
            menu = "monster_accept_dialogue";

            // Is taking their turn
            textOneFactory->setText(turnQueue.front()->GetName() + " IS TAKING THEIR TURN");

            chosenIndicator->setText("");
            monsterHPIndicator->setText("");

            textTwoFactory->setText("PRESS A TO CONTINUE");
            textThreeFactory->setText("");
            textFourFactory->setText("");
            textFiveFactory->setText("");
            turn_SM();
        }

        if (USR_CHOICE == 0) {

            textTwoFactory->setGreen(0.5);
            textThreeFactory->setGreen(1.0);
            textFourFactory->setGreen(1.0);
            textFiveFactory->setGreen(1.0);
        }
        else if (USR_CHOICE == 1) {
            textTwoFactory->setGreen(1.0);
            textThreeFactory->setGreen(0.5);
            textFourFactory->setGreen(1.0);
            textFiveFactory->setGreen(1.0);
        } else if (USR_CHOICE == 2) {
            textTwoFactory->setGreen(1.0);
            textThreeFactory->setGreen(1.0);
            textFourFactory->setGreen(0.5);
            textFiveFactory->setGreen(1.0);
        } else if (USR_CHOICE == 3) {
            textTwoFactory->setGreen(1.0);
            textThreeFactory->setGreen(1.0);
            textFourFactory->setGreen(1.0);
            textFiveFactory->setGreen(0.5);
        }

    } else if (menu == "monster_dmg_dialogue") {
        dmgIndicator->setXPos(textOneFactory->getXPos()+20);
        dmgIndicator->setYPos(textOneFactory->getYPos()-20);
        dmgIndicator->setText(std::to_string(globalDamage));
        dmgIndicator->setRed(1);
        dmgIndicator->setGreen(0);
        dmgIndicator->setBlue(0);

        textOneFactory->setText(
                   currEntity->GetName() + " ATTACKED " + playerTeam[target]->GetName()
                   + " FOR "
       );
    }

};


void renderFn() {

    if (STEP % 200000 == 0) {

        // Render scene
        if ((current_scene.compare("start_scene") == 0) && (current_scene.compare(globalScene->name) !=0)) {
            globalScene = new StartScene();
        }
        else if ((current_scene.compare("tavern_scene") == 0) && (current_scene.compare(globalScene->name) != 0)) {
            globalScene = new TavernScene();
        }

        else if ((current_scene.compare("battle_scene") == 0) && (current_scene.compare(globalScene->name) != 0)) {
            globalScene = new BattleScene();
        }

        else if ((current_scene.compare("game_over_scene") == 0) && (current_scene.compare(globalScene->name) != 0)) {
            globalScene = new GameOverScene();
        }

        else if ((current_scene.compare("victory_scene") == 0) && (current_scene.compare(globalScene->name) != 0)) {
            globalScene = new VictoryScene();
        }

        // TODO: Incorporate into a single variable called update
        // on start scene
        // Updates Screen based on listened variables
        if (current_scene.compare("start_scene") == 0) {
            startSceneChoices();

        } else if (current_scene.compare("tavern_scene") == 0) {
            tavernSceneChoices();
        }
        else if ((current_scene.compare("battle_scene") == 0)) {
            battleSceneChoices();
        }
        else if ((current_scene.compare("victory_scene")==0)) {
            std::cout << "victory scene" << std::endl;
        }
        else if ((current_scene.compare("game_over_scene") == 0)) {
            std::cout << "game_over_choices" << std::endl;
        }

        globalScene->make();
    }

    STEP += 1;
};


void handleStartSceneInput(int key) {
    if (key == 'a') {
       current_scene = "tavern_scene";
   }
};


void handleTavernSceneInput(int key) {

   if (key == 'a') {
       if (USR_CHOICE == 0) {
           current_scene = "battle_scene";
       }
       else if (USR_CHOICE == 1) {
           current_scene = "game_over_scene";
       };
   }
};


void handleBattleSceneInput(int key) {

   if (key == 'a') {

       if (menu == "run_attack") {
           if (USR_CHOICE == 0) {

               menu = "choose_attack";
               inBattle = true;

                
           } else if (USR_CHOICE == 1) {
               current_scene = "game_over_scene";
           }

       }
       else if (menu == "choose_attack") {

           Entity* currentMonster = globalScene->monsters.at(USR_CHOICE);
           turn_SM();

           if (isPlayer) {

               std::string descript = "YOU ATTACKED " + currentMonster->GetName();

               textOneFactory->setText(descript);

               // render attack here
               renderAttack = true;

               turn_SM(); // Turns the state machine
               playHit(); // this plays the adio

               menu = "player_attack_dialogue";

              textTwoFactory->setText("PRESS A TO CONTINUE");
              textThreeFactory->setText("");
              textFourFactory->setText("");
              textFiveFactory->setText("");
           }

           else if (!isPlayer) {

               // Note that currEntity is not accessible until
               // Turing machine has turned
               turn_SM();
               std::cout << "currEntity: " << currEntity->GetName() << std::endl;
               std::cout << "target: " << target << std::endl;
           }

           // check enemy or player status
           if (enemyDefeated()) {
               // do victory animation
               current_scene = "victory_scene";
               turn_SM();

           } else if (playerDefeated()) {
               // do defeat animation
               current_scene = "game_over_scene";
               turn_SM();
           }

       } else if (menu == "monster_accept_dialogue") {
           menu = "monster_dmg_dialogue";

       } else if (menu == "player_attack_dialogue") {
           menu = "choose_attack";
       } else if (menu == "monster_dmg_dialogue") {
           menu = "choose_attack";
           dmgIndicator->setText("");
       }
       if (currState != SM_BattleFinished) {
           turn_SM();
       }
   }

};

void keyboard(unsigned char key, int x, int y)
{

   if (current_scene.compare("start_scene") == 0) {
       handleStartSceneInput(key);
   }

   else if (current_scene.compare("tavern_scene") == 0) {
       handleTavernSceneInput(key);
    
   } else if (current_scene.compare("battle_scene") == 0) {
       handleBattleSceneInput(key);
   }
   else if (current_scene.compare("game_over_scene") == 0) {
       if (key == 'a') {
           exit(0);
       }
   }

}


void tavernSpecialKeyboard(int key) {
     if (key == GLUT_KEY_UP) {
            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();

            if (USR_CHOICE == 0) {
                USR_CHOICE = 1;
            }

            else if (USR_CHOICE == 1) {
                USR_CHOICE = 0;
            };
        }

        else if (key == GLUT_KEY_DOWN) {

            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();

            if (USR_CHOICE == 1) {
                menu = "choose_attack";
                USR_CHOICE = 0;
            }

            else if (USR_CHOICE == 0) {
                USR_CHOICE = 1;
            };
        }
}

void battleSpecialKeyboard(int key) {

    if (menu == "run_attack") {
        if (key == GLUT_KEY_UP) {
            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();

            if (USR_CHOICE == 0) {
                USR_CHOICE = 1;
            }

            else if (USR_CHOICE == 1) {
                USR_CHOICE = 0;
            };
        }

        else if (key == GLUT_KEY_DOWN) {

            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();

            if (USR_CHOICE == 1) {
                menu = "choose_attack";
                USR_CHOICE = 0;
            }

            else if (USR_CHOICE == 0) {
                USR_CHOICE = 1;
            };
        }

    } else if (menu == "choose_attack") {

        if(key == GLUT_KEY_UP) {

            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();
            if (USR_CHOICE != 0) {
                USR_CHOICE = (USR_CHOICE - 1) % 4;
            } else {
                USR_CHOICE = 3;
            }

        } else if (key == GLUT_KEY_DOWN) {

            sfxThreadTwo = std::thread(playClick);
            sfxThreadTwo.detach();
            USR_CHOICE = (USR_CHOICE + 1) % 4;
        }

    } else if (menu == "accept_dialogue") {
        USR_CHOICE = 0;
    }

};


void specialKeyboard(int key, int x, int y) {
    if (current_scene == "tavern_scene") {
        tavernSpecialKeyboard(key);
    } else if (current_scene == "battle_scene") {
        battleSpecialKeyboard(key);
    }
   
};


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{

    CharacterFactory characterFactory;
    EntityFactory entityFactory;
    PowerGemFactory powerGemFactory;
    ArmorFactory armorFactory;

    srand(time(0));

    currState = SM_NotInBattle;
    inBattle = true;

    playerTeam_size = 4;
    playerTeam[0] = characterFactory.MakeByID(1);
    playerTeam[1] = characterFactory.MakeByID(4);
    playerTeam[2] = characterFactory.MakeByID(2);
    playerTeam[3] = characterFactory.MakeByID(7);

    playerNames.push_back("BOB");
    playerNames.push_back("SAM");
    playerNames.push_back("SETH");
    playerNames.push_back("PYRA");
    playerNames.push_back("WILL");
    playerNames.push_back("RAWR");
    playerNames.push_back("JAZZ");
    playerNames.push_back("HAX");


    // Equips gem and armor
    for (int i = 0; i < playerTeam_size; i++) {
        playerTeam[i]->EquipPowerGem(powerGemFactory.MakeByArea("Forest"));
        playerTeam[i]->EquipArmor(armorFactory.MakeByArea("Forest"));
    }

    // Gets tier of armor and power gem
    /*
    for (int i = 0; i < playerTeam_size; i++) {
        cout << playerTeam[i]->powerGem->GetName() + " +" << playerTeam[i]->powerGem->GetTier() << endl;
        cout << playerTeam[i]->armor->GetName() + " +" << playerTeam[i]->armor->GetTier() << endl;
    }
    */

   srand(time(0));

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);

   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeyboard);

   glutDisplayFunc(renderFn);

   glutSetWindowTitle("Covid Fantasy XIX: Evolution");

   glutIdleFunc(renderFn);

   glutMainLoop();

   return 0;
}
