#ifndef __SPRITE_H__
#define __SPRITE_H__

class Sprite {
    public:
        std::string name;
        int xPos;
        int yPos;

        int getXPos() {
            return this->xPos;
        };

        int getYPos() {
            return this->yPos;
        };

        void setXPos(int x) {
            this->xPos = x;
        }

        void setYPos(int y) {
            this->yPos = y;
        }

        virtual void make() {
        };
};

#endif
