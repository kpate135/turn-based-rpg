#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <iostream>
#include "sprite/Tavern_Scene.c"
#include "sprite/dialogue_box.c"
#include "sound.h"
#include "sprite/logo.c"
#include "sprite/BANDIT.c"
#include "sprite/start_bg.c"
#include "sprite/SPIDER.c"
#include "sprite/SKELETON.c"
#include "sprite/COUGHBIE.c"

#include <thread>

int STEP = 0;
std::string current_scene = "start";
std::string test = "";
std::string test2 = "";
std::string test3 = "";
int USR_CHOICE = 0;

GLubyte space[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

GLubyte letters[][13] = {
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, // A
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, // B
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, // C
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
   // glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, choice);
   glEndList();
}



void printString(const char *s, int length)
{
   glPushAttrib(GL_LIST_BIT);
   glListBase(fontOffset);
   glCallLists((GLsizei) length, GL_UNSIGNED_BYTE, (GLubyte *) s);
   glPopAttrib();
}


int BACKGROUND_BORDER = 20; // X pos
int TEXT_BOX_BORDER = 25+40; // X pos
bool loopSong = false;

bool threadLife = true;

std::thread sfxThread;


class Scene {
    public:
        Scene(){};
        virtual void make();
};

class DialogueBox {

    static const int frameCount = DIALOGUE_BOX_FRAME_COUNT;
    static const int frameWidth = DIALOGUE_BOX_FRAME_WIDTH;
    static const int frameHeight = DIALOGUE_BOX_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];


    std::string text;

    const uint32_t *data;

    public:


        DialogueBox() {
            
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


class Logo {

    static const int frameCount = LOGO_FRAME_COUNT;
    static const int frameWidth = LOGO_FRAME_WIDTH;
    static const int frameHeight = LOGO_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    std::string text;

    const uint32_t *data;

    public:


        Logo() {
            
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

                // Row and on this column = pixel
                sprite[row][col][0] = img_red; // 0-255
                sprite[row][col][1] = img_green;
                sprite[row][col][2] = img_blue;
                sprite[row][col][3] = img_alpha; // Transparency
                // sprite[row][col][3] = 255; // Transparency

                std::cout << "logo img_alpha: " << img_alpha << std::endl;
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


class Bandit {

    static const int frameCount = BANDIT_FRAME_COUNT;
    static const int frameWidth = BANDIT_FRAME_WIDTH;
    static const int frameHeight = BANDIT_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Bandit() {
            
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
            glRasterPos2i(BACKGROUND_BORDER+100, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Spider {

    static const int frameCount = SPIDER_FRAME_COUNT;
    static const int frameWidth = SPIDER_FRAME_WIDTH;
    static const int frameHeight = SPIDER_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Spider() {
            
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
            glRasterPos2i(BACKGROUND_BORDER+200, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Skeleton {

    static const int frameCount = SKELETON_FRAME_COUNT;
    static const int frameWidth = SKELETON_FRAME_WIDTH;
    static const int frameHeight = SKELETON_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Skeleton() {
            
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
            glRasterPos2i(BACKGROUND_BORDER+350, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };

};

class Coughbie {

    static const int frameCount = COUGHBIE_FRAME_COUNT;
    static const int frameWidth = COUGHBIE_FRAME_WIDTH;
    static const int frameHeight = COUGHBIE_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        Coughbie() {
            
            uint32_t red_mask = 0x000000ff;
            int row = frameHeight;

            this->data = &coughbie_data[0][0];
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
            glRasterPos2i(BACKGROUND_BORDER+450, 250);
            glDrawPixels(this->frameWidth,
                        this->frameHeight, GL_RGBA,
                        GL_UNSIGNED_BYTE, this->sprite);

        };


};

class StartBackground {

    static const int frameCount = START_BG_FRAME_COUNT;
    static const int frameWidth = START_BG_FRAME_WIDTH;
    static const int frameHeight = START_BG_FRAME_HEIGHT;

    GLubyte sprite[frameHeight][frameWidth][4];

    const uint32_t *data;

    public:

        StartBackground() {
            
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


DialogueBox boxFactory = DialogueBox();
Logo logoFactory = Logo();
Bandit banditFactory = Bandit();
StartBackground startBGFactory = StartBackground();
Spider spiderFactory = Spider();
Skeleton skeletonFactory = Skeleton();
Coughbie coughbieFactory = Coughbie();

GLubyte sprite[TAVERN_SCENE_FRAME_HEIGHT][TAVERN_SCENE_FRAME_WIDTH][4];


class StartScene : public Scene {

    public:
        void make() override {
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           startBGFactory.make();
           banditFactory.make();
           spiderFactory.make();
           skeletonFactory.make();
           coughbieFactory.make();
           logoFactory.make();
           boxFactory.make();

           GLfloat white[3] = { 1.0, 0.5, 1.0 };
           glColor3fv(white);

           glRasterPos2i(315, 100);

           printString(test.c_str(), test.size());

           glFlush();

           std::string soundName = "sounds/title_1.mp3";

           if (loopSong == false) {
               sfxThread = std::thread(playSfx, soundName, &loopSong, &threadLife);
               sfxThread.detach();
               loopSong = false;
           }

        }

};


void generateSprite(void)
{
    uint32_t red_mask = 0x000000ff;

    int row = TAVERN_SCENE_FRAME_HEIGHT;

    for (int i=0; i < TAVERN_SCENE_FRAME_WIDTH*TAVERN_SCENE_FRAME_HEIGHT; i++) {
        unsigned int img_red = red_mask & tavern_scene_data[0][i];

        // Bit shifting for 2 slots on hexadecimal
        // per color each position on hexidecimal is 4 bits.
        // Apply the red mask to get back decimal value
        // to obtain 0-255 rgb format
        unsigned int img_green = red_mask & (tavern_scene_data[0][i] >> 4*2);
        unsigned int img_blue = red_mask & (tavern_scene_data[0][i] >> 4*4);
        unsigned int img_alpha = red_mask & (tavern_scene_data[0][i] >> 4*6);

        int col = i % (TAVERN_SCENE_FRAME_WIDTH);


        if (i % TAVERN_SCENE_FRAME_WIDTH == 0) {
            row -= 1;
        }

        // Row and on this column = pixel
        sprite[row][col][0] = img_red; // 0-255
        sprite[row][col][1] = img_green;
        sprite[row][col][2] = img_blue;
        sprite[row][col][3] = img_alpha; // Transparency
    };
}




void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   generateSprite();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glShadeModel (GL_FLAT);
   makeRasterFont();
}


/* Everything above this line could be in a library 
 * that defines a font.  To make it work, you've got 
 * to call makeRasterFont() before you start making 
 * calls to printString().
 */
void display(void)
{
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           startBGFactory.make();
           banditFactory.make();
           spiderFactory.make();
           skeletonFactory.make();
           coughbieFactory.make();
           logoFactory.make();
           boxFactory.make();

           GLfloat white[3] = { 1.0, 0.5, 1.0 };
           glColor3fv(white);

           glRasterPos2i(315, 100);

           printString(test.c_str(), test.size());

           glFlush();

           std::string soundName = "sounds/title_1.mp3";

           if (loopSong == false) {
               sfxThread = std::thread(playSfx, soundName, &loopSong, &threadLife);
               sfxThread.detach();
               loopSong = false;
           }


}

void display2(void)
{
    threadLife = false;

   // Set scene here
   /*
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 300-100);
   glDrawPixels(TAVERN_SCENE_FRAME_WIDTH,
                TAVERN_SCENE_FRAME_HEIGHT, GL_RGBA,
                GL_UNSIGNED_BYTE, sprite);
   glFlush();
   */

   loopSong = false;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(BACKGROUND_BORDER, 300-120);
   glDrawPixels(TAVERN_SCENE_FRAME_WIDTH,
                TAVERN_SCENE_FRAME_HEIGHT, GL_RGBA,
                GL_UNSIGNED_BYTE, sprite);

   boxFactory.make();

   GLfloat white[3] = { 1.0, 1.0, 1.0 };
   glColor3fv(white);


   glRasterPos2i(TEXT_BOX_BORDER, 140);
   printString(test.c_str(), test.size());

   if (USR_CHOICE == 0) {
       GLfloat purp[3] = { 1.0, 0.5, 1.0 };
       glColor3fv(purp);

       glRasterPos2i(TEXT_BOX_BORDER, 100);
       printString(test2.c_str(), test.size());

       GLfloat white[3] = { 1.0, 1.0, 1.0 };
       glColor3fv(white);

       glRasterPos2i(TEXT_BOX_BORDER, 60);
       printString(test3.c_str(), test.size());
   }

   else if (USR_CHOICE == 1) {

       GLfloat white[3] = { 1.0, 1.0, 1.0 };
       glColor3fv(white);

       glRasterPos2i(TEXT_BOX_BORDER, 100);
       printString(test2.c_str(), test.size());


       GLfloat purp[3] = { 1.0, 0.5, 1.0 };
       glColor3fv(purp);

       glRasterPos2i(TEXT_BOX_BORDER, 60);
       printString(test3.c_str(), test.size());
   }

   glFlush();

};

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0.0, w, 0.0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void renderFn() {

    // Scene displayedScene;

    if (STEP % 200000 == 0) {
        if (current_scene == "start") {

            if (test == "") {
                test = "PRESS A TO START";
                test2 = "";
            } else {
                test = "";
            };

            // displayedScene = StartScene();
            display();
        };

        if (current_scene == "yes") {

            // Description of scene
            test =  "YOU ARE IN AN EMPTY ROOM.";

            // Options
            test2 = " LOOK AROUND AND PONDER.";
            test3 = " YOU GIVE UP";

            if (USR_CHOICE == 0){
                test2 = "O" + test2;
            }
            else if (USR_CHOICE == 1) {
                test3 = "O" + test3;
            };

            display2();
        };
    }


    // displayedScene.make();
    STEP += 1;
};


void keyboard(unsigned char key, int x, int y)
{

   std::cout << "key: " << key << std::endl;

   if (key == 'a') {
       std::cout << "switching scene" << std::endl;
       current_scene = "yes";
   }

}

void specialKeyboard(int key, int x, int y) {

    if (key == GLUT_KEY_UP) {
        if (USR_CHOICE == 0) {
            USR_CHOICE = 1;
        }

        else if (USR_CHOICE == 1) {
            USR_CHOICE = 0;
        };
    }

    else if (key == GLUT_KEY_DOWN) {

        if (USR_CHOICE == 1) {
            USR_CHOICE = 0;
        }

        else if (USR_CHOICE == 0) {
            USR_CHOICE = 1;
        };
    }
};


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{

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
