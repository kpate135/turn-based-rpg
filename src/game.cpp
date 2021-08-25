#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <iostream>

#include "sound.h"
#include "sprite.h"
#include "scene.h"

#include "sprite/Tavern_Scene.c"
#include "sprite/dialogue_box.c"
#include "sprite/logo.c"
#include "sprite/BANDIT.c"
#include "sprite/start_bg.c"
#include "sprite/SPIDER.c"
#include "sprite/SKELETON.c"
#include "sprite/COUGHBIE.c"
#include "sprite/Haunted_Armor.c"
#include "sprite/SLIME.c"
#include "sprite/BAT.c"
#include "sprite/Battle_Scene.c"

#include <stdexcept>

#include "entity/Entity.hpp"
#include "entity/Character.hpp"
#include "entity/Equipment.hpp"
#include "entity/Action.hpp"
#include "entity/Factory.hpp"

#include "entity/turn.h"

#include <vector>

#include <thread>



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

GLubyte space[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GLubyte letters[][13] = {
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
	{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
	{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
	{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc}, 
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, 
	{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, 
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
	{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, 
	{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06}, 
	{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3}, 
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, 
	{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3}, 
	{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3}, 
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e}, 
	{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
	{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, 
	{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
	{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e}, 
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff}, 
	{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
	{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
	{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
	{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
	{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
	{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};

GLubyte numbers[10][13] = {
            {0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xc3, 0xc3, 0x66, 0x3c}, // 0
            {0x00, 0x00, 0xfe, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xf8, 0x78, 0x38}, // 1
            {0x00, 0x00, 0xfe, 0x60, 0x30, 0x18, 0x0C, 0x04, 0xc6, 0xc3, 0x63, 0x3e, 0x1c}, // 2
            {0x00, 0xff, 0x83, 0x83, 0x83, 0x3,  0xf,  0x83, 0x83, 0x83, 0x83, 0xff},// 3
            {0x00, 0x00, 0x06, 0x06, 0x06, 0xff, 0xc6, 0x66, 0x36, 0x1e, 0x0e, 0x06, 0x02}, // 4
            {0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0xff, 0xff, 0xc0, 0xc0, 0xff, 0xff}, // 5
            {0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0xe7, 0xfe, 0xc0, 0xc0, 0xc0, 0x7f, 0x3e}, // 6
            {0x00, 0x00, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0xff, 0xff}, // 7
            {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0x7e, 0x7e, 0x42, 0xc3, 0xe7, 0x7e}, // 8
            {0x00, 0x00, 0x7c, 0x06, 0x03, 0x03, 0x03, 0x3f, 0x63, 0xc3, 0xc3, 0xe7, 0x7e}  // 9
    };



GLuint fontOffset;

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

int BACKGROUND_BORDER = 20; // X pos
int TEXT_BOX_BORDER = 25+40; // X pos

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


// TODO: set color choice
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
            else if (name == "START_BG") {
                return new StartBackground();
            }
            else if (name == "TAVERN_BG") {
                return new TavernBackground();
            }
            else if (name == "BATTLE_BG") {
                return new BattleBackground();
            }
            else if (name == "DIALOGUE_BOX") {
                return new DialogueBox();
            }
            else if (name == "LOGO") {
                return new Logo();
            } else {
                throw std::invalid_argument("Received invalid sprite name.");
            }
        }
};

SpriteFactory spriteFactory;

// Sprites Setup

Sprite *boxFactory = spriteFactory.makeByName("DIALOGUE_BOX");
Sprite *logoFactory = spriteFactory.makeByName("LOGO");

Sprite *startBGFactory = spriteFactory.makeByName("START_BG");
Sprite *tavernBGFactory = spriteFactory.makeByName("TAVERN_BG");
Sprite *battleBGFactory = spriteFactory.makeByName("BATTLE_BG");

Sprite *banditFactory = spriteFactory.makeByName("BANDIT");
Sprite *spiderFactory = spriteFactory.makeByName("SPIDER");
Sprite *batFactory = spriteFactory.makeByName("BAT");
Sprite *slimeFactory = spriteFactory.makeByName("SLIME");

Sprite *skeletonFactory = spriteFactory.makeByName("SKELETON");
Sprite *coughbieFactory = spriteFactory.makeByName("COUGHBIE");


Text *textOneFactory = new Text(&test); // descript

Text *textTwoFactory = new Text(&test2);
Text *textThreeFactory = new Text(&test3);
Text *textFourFactory = new Text(&test4);
Text *textFiveFactory = new Text(&test5);

Text *chosenIndicator = new Text(&test6);
TextNumber *monsterHPIndicator = new TextNumber(&monsterHealth);
TextNumber *dmgIndicator = new TextNumber(&monsterHealth);

TextNumber *textNumFactory = new TextNumber(&testNum);

GLubyte sprite[TAVERN_SCENE_FRAME_HEIGHT][TAVERN_SCENE_FRAME_WIDTH][4];


// Character information
CharacterFactory characterFactory;
EntityFactory entityFactory;
PowerGemFactory powerGemFactory;
ArmorFactory armorFactory;

// srand(time(0));

// currState = SM_NotInBattle;
// inBattle = false

// playerTeamSize;

Character *mainCharacter = characterFactory.MakeByID(8);

class StartScene : public Scene {

    public:

      StartScene() : Scene() {

          this->name = "start_scene";
          textOneFactory->setXPos(315);
          textOneFactory->setYPos(100);
          textOneFactory->setGreen(0.5);

          this->music = "sounds/title_1.mp3";
          // this->music = "sounds/tavern_bgm.mp3";

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

          // textNumFactory->setXPos(315);
          // textNumFactory->setYPos(50);
          // this->sprites.push_back(textNumFactory);
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

        // std::vector<Entity*> monsters;
        int numMonsters = 0;

        BattleScene() {

            threadLife = false;

            name = "battle_scene";
            music = "sounds/start_music.mp3";

            std::string area = "Forest";
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

            // Adding sprites
            this->sprites.push_back(battleBGFactory);

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

        Sprite *fetchSprite(Entity* monster) {
            std::string monsterName = monster->GetName();

            if (monsterName.compare("SLIME") == 0) {
                return slimeFactory;
            }

            else if (monsterName.compare("SPIDER") == 0) {
                return spiderFactory;
            }

            else if (monsterName.compare("BANDIT") == 0) {
                return banditFactory;
            }

            else if (monsterName.compare("BAT") == 0) {
                return batFactory;
            };

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
            chosenIndicator->setXPos(indXPos + 50);
            chosenIndicator->setYPos(indYPos - 50);
            chosenIndicator->setGreen(0);
            chosenIndicator->setRed(0);
            chosenIndicator->setBlue(0);

           monsterHPIndicator->setXPos(indXPos + 50);
           monsterHPIndicator->setYPos(indYPos - 80);
           monsterHPIndicator->setGreen(0);
           monsterHPIndicator->setBlue(0);
           int monsterHP = curMonster->GetHP();
           if (monsterHP < 0) {
               monsterHP = 0;
           }
           monsterHPIndicator->setText(std::to_string(monsterHP));

           dmgIndicator->setXPos(indXPos);
           dmgIndicator->setXPos(indYPos);

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
        };

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

        globalScene->make();
    }


    // displayedScene.make();
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
               sfxThreadThree = std::thread(playEncounter);
               sfxThreadThree.detach();
               current_scene = "battle_scene";
           }
           else if (USR_CHOICE == 1) {
               current_scene = "game_over";
           };

       }

};

void handleBattleSceneInput(int key) {

   if (key == 'a') {

       if (menu == "run_attack") {
           if (USR_CHOICE == 0) {

               std::cout << "Switching menu" << std::endl;
               menu = "choose_attack";
               inBattle = true;

                
           }
       }

       else if (menu == "choose_attack") {

               Entity* currentMonster = globalScene->monsters.at(USR_CHOICE);

               std::string descript = "YOU ATTACKED " + currentMonster->GetName();

               textOneFactory->setText(descript);

               // render attack here
               renderAttack = true;
                              
           turn_SM();
       }
       turn_SM();
   }

};

void keyboard(unsigned char key, int x, int y)
{

   std::cout << "key: " << key << std::endl;
   std::cout << "current_scene: " << current_scene << std::endl;
   std::cout << "menu: " << menu << std::endl;

   if (current_scene.compare("start_scene") == 0) {
       handleStartSceneInput(key);
   }

   else if (current_scene.compare("tavern_scene") == 0) {
       handleTavernSceneInput(key);
    
   } else if (current_scene.compare("battle_scene") == 0) {
       handleBattleSceneInput(key);
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

    };

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

    // Equips gem and armor
    for (int i = 0; i < playerTeam_size; i++) {
        playerTeam[i]->EquipPowerGem(powerGemFactory.MakeByArea("Covid Tower"));
        playerTeam[i]->EquipArmor(armorFactory.MakeByArea("Covid Tower"));
    }

    // Gets tier of armor and power gem
    for (int i = 0; i < playerTeam_size; i++) {
        cout << playerTeam[i]->powerGem->GetName() + " +" << playerTeam[i]->powerGem->GetTier() << endl;
        cout << playerTeam[i]->armor->GetName() + " +" << playerTeam[i]->armor->GetTier() << endl;
    }

   srand(time(0));

    // int ref = &haunted_armor_data[0][0];
   // Sprite hauntedArmor = Sprite("HAUNTED ARMOR", ha_fc, ha_fw, ha_fh, &haunted_armor_data[0][0]);

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

