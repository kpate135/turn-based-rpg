#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "sprite/standing.c"


#define imageHeight 32
#define imageWidth 32

GLubyte sprite[imageHeight][imageWidth][3];

void generateFigure() {
    // 1 image 32 x 32 = 1024 height

    GLuint row = 0;
    GLuint col = 0;

    GLuint i;

    for(i=0; i < 1024; i++) {

        row = i % 32;
        col = col;

        // glNewList();

        uint32_t cur_color = new_piskel_data[0][i];

        int color;
        if (cur_color == 0x00000000) {
            sprite[row][col][0] = 0;
        } else {
            sprite[row][col][0] = 255;
        }

        sprite[row][col][1] = 0;
        sprite[row][col][2] = 0;
	
    }

};

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f,  0.0f,
				0.0f, 1.0f,  0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0f,-2.0f, 0.0f);
		glVertex3f( 2.0f, 0.0f, 0.0);
		glVertex3f( 0.0f, 2.0f, 0.0);
	glEnd();

	angle+=0.1f;

	glutSwapBuffers();
}

void init()
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   generateFigure();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
};
