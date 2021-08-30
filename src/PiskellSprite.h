#ifndef __PISKELL_SPRITE_H__
#define __PISKELL_SPRITE_H__

#include "sprite/Tavern_Scene.c"
#include "sprite/dialogue_box.c"
#include "sprite/logo.c"
#include "sprite/BANDIT.c"
#include "sprite/start_bg.c"
#include "sprite/SPIDER.c"
#include "sprite/SKELETON.c"
#include "sprite/COUGHBIE.c"
#include "sprite/SLIME.c"
#include "sprite/BAT.c"
#include "sprite/game_over_text.c"
#include "sprite/Battle_Scene.c"
#include "sprite/Catacombs_Scene.c"
#include "sprite/HAUNTED_COFFIN.c"
#include "sprite/Haunted_Armor.c"
#include "sprite/HAUNTED_HAMMER.c"
#include "sprite/COVID_ILL_MAN.c"
#include "sprite/GRAVE_ROBBER.c"
#include "sprite/RAT.c"
#include "sprite/victory_text.c"
#include "sprite/Forest_Scene.c"
#include "sprite/Tower_Scene.c"



int BACKGROUND_BORDER = 20; // X pos
int TEXT_BOX_BORDER = 25+40; // X pos

class TavernBackground : public Sprite {

    static const int frameCount = TAVERN_SCENE_FRAME_COUNT;
    static const int frameWidth = TAVERN_SCENE_FRAME_WIDTH;
    static const int frameHeight = TAVERN_SCENE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data = &tavern_scene_data[0][0];

    public:

        TavernBackground() {
            
            name = "TavernBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class DialogueBox : public Sprite {

    static const int frameCount = DIALOGUE_BOX_FRAME_COUNT;
    static const int frameWidth = DIALOGUE_BOX_FRAME_WIDTH;
    static const int frameHeight = DIALOGUE_BOX_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    std::string text;


    const uint32_t *data;

    public:

        DialogueBox() {
            
            name = "DialogueBox";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &dialogue_box_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 0);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class GameOverText : public Sprite {

    static const int frameCount = GAME_OVER_TEXT_FRAME_COUNT;
    static const int frameWidth = GAME_OVER_TEXT_FRAME_WIDTH;
    static const int frameHeight = GAME_OVER_TEXT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    std::string text;

    const uint32_t *data;

    public:


        GameOverText() {
            
            name = "GameOverText";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &game_over_text_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                sprite[row][col][0] = img_red;
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha;
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER+80, 450);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Bandit : public Sprite {

    static const int frameCount = BANDIT_FRAME_COUNT;
    static const int frameWidth = BANDIT_FRAME_WIDTH;
    static const int frameHeight = BANDIT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;


    public:

        Bandit() {
            
            name = "Bandit";
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &bandit_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            //glRasterPos2i(BACKGROUND_BORDER+100, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class StartBackground : public Sprite {

    static const int frameCount = START_BG_FRAME_COUNT;
    static const int frameWidth = START_BG_FRAME_WIDTH;
    static const int frameHeight = START_BG_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        StartBackground() {
            
            name = "StartBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &start_bg_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class Spider : public Sprite {

    static const int frameCount = SPIDER_FRAME_COUNT;
    static const int frameWidth = SPIDER_FRAME_WIDTH;
    static const int frameHeight = SPIDER_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Spider() {
            
            name = "Spider";
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &spider_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            //glRasterPos2i(BACKGROUND_BORDER+200, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Skeleton : public Sprite {

    static const int frameCount = SKELETON_FRAME_COUNT;
    static const int frameWidth = SKELETON_FRAME_WIDTH;
    static const int frameHeight = SKELETON_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        Skeleton() {
            
            name = "Skeleton";
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &skeleton_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            // glRasterPos2i(BACKGROUND_BORDER+350, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};


class Coughbie : public Sprite {

    static const int frameCount = COUGHBIE_FRAME_COUNT;
    static const int frameWidth = COUGHBIE_FRAME_WIDTH;
    static const int frameHeight = COUGHBIE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        Coughbie() {

            name = "Coughbie";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &coughbie_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            // glRasterPos2i(BACKGROUND_BORDER+450, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class Slime : public Sprite {

    static const int frameCount = SLIME_FRAME_COUNT;
    static const int frameWidth = SLIME_FRAME_WIDTH;
    static const int frameHeight = SLIME_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Slime() {
            
            name = "Slime";
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &slime_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {

            glRasterPos2i(this->xPos, this->yPos);
            // glRasterPos2i(BACKGROUND_BORDER+200, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};


class Bat : public Sprite {

    public:
    static const int frameCount = BAT_FRAME_COUNT;
    static const int frameWidth = BAT_FRAME_WIDTH;
    static const int frameHeight = BAT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    Bat() {
            
        name = "Bat";
        uint32_t red_mask = 0x000000ff;
        int row = frameHeight;

        this->data = &bat_data[0][0];

        for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            // glRasterPos2i(BACKGROUND_BORDER+200, 250);
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};


class BattleBackground : public  Sprite {
    static const int frameCount = BATTLE_SCENE_FRAME_COUNT;
    static const int frameWidth = BATTLE_SCENE_FRAME_WIDTH;
    static const int frameHeight = BATTLE_SCENE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data = &battle_scene_data[0][0];

    public:

        BattleBackground() {
            
            name = "BattleBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};


class VictoryText : public Sprite {


    static const int frameCount = VICTORY_TEXT_FRAME_COUNT;
    static const int frameWidth = VICTORY_TEXT_FRAME_WIDTH;
    static const int frameHeight = VICTORY_TEXT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    std::string text;

    const uint32_t *data;

    public:


        VictoryText() {
            
            name = "VictoryText";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &victory_text_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                sprite[row][col][0] = img_red;
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha;
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER+80, 450);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Logo : public Sprite {

    static const int frameCount = LOGO_FRAME_COUNT;
    static const int frameWidth = LOGO_FRAME_WIDTH;
    static const int frameHeight = LOGO_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    std::string text;


    const uint32_t *data;

    public:


        Logo() {
            
            name = "Logo";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &logo_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                sprite[row][col][0] = img_red;
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha;
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER+80, 450);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Rat : public Sprite {

    static const int frameCount = RAT_FRAME_COUNT;
    static const int frameWidth = RAT_FRAME_WIDTH;
    static const int frameHeight = RAT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Rat() {

            name = "Rat";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &rat_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};


class HauntedCoffin : public Sprite {

    static const int frameCount = HAUNTED_COFFIN_FRAME_COUNT;
    static const int frameWidth = HAUNTED_COFFIN_FRAME_WIDTH;
    static const int frameHeight = HAUNTED_COFFIN_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        HauntedCoffin() {

            name = "Haunted Coffin";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &haunted_coffin_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class HauntedArmor : public Sprite {

    static const int frameCount = HAUNTED_ARMOR_FRAME_COUNT;
    static const int frameWidth = HAUNTED_ARMOR_FRAME_WIDTH;
    static const int frameHeight = HAUNTED_ARMOR_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        HauntedArmor() {

            name = "Haunted Armor";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &haunted_armor_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class HauntedHammer : public Sprite {

    static const int frameCount = HAUNTED_HAMMER_FRAME_COUNT;
    static const int frameWidth = HAUNTED_HAMMER_FRAME_WIDTH;
    static const int frameHeight = HAUNTED_HAMMER_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        HauntedHammer() {

            name = "Haunted Hammer";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &haunted_hammer_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};


class CovidIllMan : public Sprite {

    static const int frameCount = COVID_ILL_MAN_FRAME_COUNT;
    static const int frameWidth = COVID_ILL_MAN_FRAME_WIDTH;
    static const int frameHeight = COVID_ILL_MAN_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        CovidIllMan() {

            name = "CovidIllMan";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &covid_ill_man_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};


class GraveRobber : public Sprite {

    static const int frameCount = GRAVE_ROBBER_FRAME_COUNT;
    static const int frameWidth = GRAVE_ROBBER_FRAME_WIDTH;
    static const int frameHeight = GRAVE_ROBBER_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        GraveRobber() {

            name = "Grave Robber";
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &grave_robber_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(this->xPos, this->yPos);
            // glRasterPos2i(BACKGROUND_BORDER+450, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class CatacombsBackground : public Sprite {

    static const int frameCount = CATACOMBS_SCENE_FRAME_COUNT;
    static const int frameWidth = CATACOMBS_SCENE_FRAME_WIDTH;
    static const int frameHeight = CATACOMBS_SCENE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        CatacombsBackground() {
            
            name = "CatacombsBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &catacombs_scene_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class ForestBackground : public Sprite {

    static const int frameCount = FOREST_SCENE_FRAME_COUNT;
    static const int frameWidth = FOREST_SCENE_FRAME_WIDTH;
    static const int frameHeight = FOREST_SCENE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        ForestBackground() {
            
            name = "ForestBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &forest_scene_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};

class TowerBackground : public Sprite {

    static const int frameCount = TOWER_SCENE_FRAME_COUNT;
    static const int frameWidth = TOWER_SCENE_FRAME_WIDTH;
    static const int frameHeight = TOWER_SCENE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    const uint32_t *data;

    public:

        TowerBackground() {
            
            name = "TowerBackground";

            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &tower_scene_data[0][0];
            for (unsigned int i=0; i < this->frameWidth*this->frameHeight; i++) {

                unsigned int img_red = red_mask & *(this->data + i);

                // Bit shifting for 2 slots on hexadecimal
                // per color each position on hexidecimal is 4 bits.
                // Apply the red mask to get back decimal value
                // to obtain 0-255 rgb format
                unsigned int img_green = red_mask & (*(this->data + i) >> 4*2);
                unsigned int img_blue = red_mask & (*(this->data + i) >> 4*4);
                unsigned int img_alpha = red_mask & (*(this->data + i) >> 4*6);

                int col = i % (this->frameWidth);

                if (i % this->frameWidth == 0) {
                    row -= 1;
                }

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
            };
        };

        // Make should return sprite, frameHeight, frameWidth
        void make() {
            glRasterPos2i(BACKGROUND_BORDER, 300-120);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };
};


#endif
