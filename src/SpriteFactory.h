
#ifndef __SPRITE_FACTORY_H__
#define __SPRITE_FACTORY_H__

#include "PiskellSprite.h"

class SpriteFactory {

    public:
        SpriteFactory(){};

        Sprite *makeByName(std::string name) {

            if (name == "BANDIT") {
                return new Bandit();
            }
            else if (name == "SPIDER") {
                return new Spider();
            }
            else if (name == "SLIME") {
                return new Slime();
            }
            else if (name == "BAT") {
                return new Bat();
            }
            else if (name == "COUGHBIE") {
                return new Coughbie();
            }
            else if (name == "SKELETON") {
                return new Skeleton();
            }
	    else if (name == "RAT") {
		    return new Rat();
	    }
	    else if (name == "HAUNTED COFFIN") {
		    return new HauntedCoffin();
	    }
	    else if (name == "GRAVE ROBBER") {
		    return new GraveRobber();
	    }
            else if (name == "START_BG") {
                return new StartBackground();
            }
            else if (name == "TAVERN_BG") {
                return new TavernBackground();
            }
            else if (name == "BATTLE_BG") {
                return new BattleBackground();
            }
	    else if (name == "CATACOMBS_BG") {
		    return new CatacombsBackground();
	    }
            else if (name == "DIALOGUE_BOX") {
                return new DialogueBox();
            }
            else if (name == "LOGO") {
                return new Logo();
            } 
            else if (name == "VICTORY_TEXT") {
                return new VictoryText();
            }
            else if (name == "GAME_OVER_TEXT") {
                return new GameOverText();
            }
            else {
                throw std::invalid_argument("Received invalid sprite name.");
            }
        }
};


#endif
