#include <GL/glut.h>
#teste
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Pong OpenGL");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

