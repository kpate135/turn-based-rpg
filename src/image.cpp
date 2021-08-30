#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "sprite/standing.c"
#include "sprite/Slime.c"
#include "sprite/Slime_clone.c"
#include "sprite/Dragon.c"
#include "sprite/Covizard.c"
#include "sprite/Tavern_Scene.c"

#define imageHeight 250
#define imageWidth 250

#define checkImageWidth 500
#define checkImageHeight 500



// Covid theme
// Vaccination in the beggining
// Beat up covid zerg
// Give the vaccine to the zerg so he dies

GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLdouble zoomFactor = 1.0;
static GLint height;

// glTexImage2D;

void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
	 c = 255;
         checkImage[i][j][0] = (GLubyte) c/3;
         checkImage[i][j][1] = (GLubyte) c/4;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 225/2;
      }
   }
}


// Description
// choices

GLubyte sprite[TAVERN_SCENE_FRAME_HEIGHT][TAVERN_SCENE_FRAME_WIDTH][4];

void generateFigure(void)
{
   int i, j, c;
    
   for (i = 0; i < imageHeight; i++) {
      for (j = 0; j < imageWidth; j++) {

         uint32_t alpha_mask = 0xff000000;
         uint32_t red_mask = 0x000000ff; //
         uint32_t green_mask = 0x0000ff00; //
         uint32_t blue_mask = 0x00ff0000; //

         // c = ((((i&0x1)==0)^((j&0x1))==0))*255;
         // c = 255;
         sprite[i][j][0] = (GLubyte) 255;
         sprite[i][j][1] = (GLubyte) 255;
         sprite[i][j][2] = (GLubyte) 0;
         sprite[i][j][3] = (GLubyte) 225;
      }
   }
}

void generateSprite(void)
{
    uint32_t red_mask = 0x000000ff;

    std::cout << "seg fault here: " << std::endl;
    int row = TAVERN_SCENE_FRAME_HEIGHT+1;

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

	std::cout << "row:" << row << std::endl;
	std::cout << "col:" << col << std::endl;

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
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);

   // glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, 
                // GL_UNSIGNED_BYTE, checkImage);
	
   glDrawPixels(TAVERN_SCENE_FRAME_WIDTH, TAVERN_SCENE_FRAME_HEIGHT, GL_RGBA,
                GL_UNSIGNED_BYTE, sprite);
   glFlush();

   // glClear(GL_COLOR_BUFFER_BIT);
   // glRasterPos2i(0, 0);
   // std::cout << "drawing pixels" << std::endl;
   // GL_UNSIGNED_BYTE, sprite);
   // glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void motion(int x, int y)
{
   static GLint screeny;
   
   screeny = height - (GLint) y;
   glRasterPos2i (x, screeny);
   glPixelZoom(zoomFactor, zoomFactor);
   glCopyPixels (0, 0, checkImageWidth, checkImageHeight,
                 GL_COLOR);
   glPixelZoom(1.0, 1.0);
   glFlush ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'r':
      case 'R':
         zoomFactor = 1.0;
         glutPostRedisplay();
         printf ("zoomFactor reset to 1.0\n");
         break;
      case 'z':
         zoomFactor += 0.5;
         if (zoomFactor >= 3.0) 
            zoomFactor = 3.0;
         printf ("zoomFactor is now %4.1f\n", zoomFactor);
         break;
      case 'Z':
         zoomFactor -= 0.5;
         if (zoomFactor <= 0.5) 
            zoomFactor = 0.5;
         printf ("zoomFactor is now %4.1f\n", zoomFactor);
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(800,600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   // glutMotionFunc(motion);
   glutMainLoop();
   return 0; 
}
