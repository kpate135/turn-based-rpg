#include <GL/glut.h>
#include <iostream>


bool* keyStates = new bool[256]();

void keyOperations() {

    std::cout << "keyOps: " << std::endl;
    if (keyStates['a'] == true) {
        glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)
        glClearColor(0.0f, 1.0f, 0.0f, 0.0f); // Clear the background of our window to red
        glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
        glFlush(); // Flush the OpenGL buffers to the window
    } else {
        // exit(0);
    };

};

void drawString(float x, float y, float z, unsigned char *string) {
  glRasterPos3f(x, y, z);

  for (unsigned char* c = string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);  // Updates the position
  }
}

void keyPressed(unsigned char key, int x, int y) {
    std::cout <<"key was pressed: " << key << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    keyStates[key] = true;
    drawString(x, y, 0, &key);
    // RenderString(0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, key, RGB(1.0f, 0.0f, 0.0f));
};

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = false; // Set the state of the current key to not pressed
}

void reshape (int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
    glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
    glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

/*
void display(void)
{

    keyOperations();

    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);

    //draw white polygon (rectangle) with corners at
    // (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.75, 0.25, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glVertex3f(0.25, 0.75, 0.0);
    glEnd();

    // Don't wait start processing buffered OpenGL routines
    glFlush();
}
*/

void display (void) {  
    std::cout <<"display being called" << std::endl;
    keyOperations();  
      
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Clear the background of our window to red  
    glClear(GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)  
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
      
    glFlush(); // Flush the OpenGL buffers to the window  
} 

void init() {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

};

/**
 * Main
 */
int main(int argc, char** argv) {
    //Initialise GLUT with command-line parameters.
    glutInit(&argc, argv);

    //Set Display Mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //Set the window size
    glutInitWindowSize(250,250);

    //Set the window position
    glutInitWindowPosition(100,100);

    //Create the window
    glutCreateWindow("A Simple OpenGL Windows Application with GLUT");

    //Call init (initialise GLUT
    init();

    //Call "display" function
    glutDisplayFunc(display);

    glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
    glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events

    //Enter the GLUT event loop
    std::cout << "entering main loop" << std::endl;
    glutMainLoop();

    return 0;
};
