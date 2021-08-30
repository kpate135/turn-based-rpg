#ifndef __SCENE_H__
#define __SCENE_H__

#include "sprite.h"
#include "entity/Entity.hpp"
#include "sound.h"
#include <vector>

class Scene {

    public:

        std::vector<Sprite*> sprites;
        std::vector<Entity*> monsters;

        std::string music;
        std::string name;

        Scene(){
        };

        ~Scene() {

            for (unsigned int i=0; i < this->sprites.size(); i++) {
                delete sprites.at(i);
            }

        };

        void make() {

            if (threadLife == false) {
                // threadLife = true;
            }

           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (unsigned int i=0; i < this->sprites.size(); i++) {
                this->sprites.at(i)->make();
            };

           glFlush();

           if (loopSong == false) {
               sfxThread = std::thread(playSfx, music, &loopSong, &threadLife);
               sfxThread.detach();
           }

        };

        const std::vector<Sprite*> getSprites() {
            return this->sprites;
        };

};

#endif
