#include <GL/glut.h>

// Ventana
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Posiciones iniciales
float ballX = 0.0f, ballY = 0.0f;
const float BALL_SIZE = 10.0f;
float paddleLeftY = 0.0f, paddleRightY = 0.0f;
const float PADDLE_WIDTH = 10.0f, PADDLE_HEIGHT = 80.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Pelota
    glBegin(GL_QUADS);
        glVertex2f(ballX - BALL_SIZE, ballY - BALL_SIZE); // Esquina inferior izquierda
        glVertex2f(ballX + BALL_SIZE, ballY - BALL_SIZE); // Esquina inferior derecha.
        glVertex2f(ballX + BALL_SIZE, ballY + BALL_SIZE); // Esquina superior derecha.
        glVertex2f(ballX - BALL_SIZE, ballY + BALL_SIZE); // Esquina superior izquierda.
    glEnd();

    // Paleta Izquierda 
    glBegin(GL_QUADS);
        glVertex2f(-WINDOW_WIDTH / 2 + 20, paddleLeftY - PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH, paddleLeftY - PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH, paddleLeftY + PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20, paddleLeftY + PADDLE_HEIGHT / 2);
    glEnd();

    // Paleta Derecha
    glBegin(GL_QUADS);
        glVertex2f(WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH, paddleRightY - PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20, paddleRightY - PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20, paddleRightY + PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH, paddleRightY + PADDLE_HEIGHT / 2);
    glEnd();

    glFlush();
}

void keyPressed(int key, int x, int y) {
    const float SPEED = 20.0f;  

    if (key == GLUT_KEY_UP) {  // Flecha arriba
        if (paddleRightY + PADDLE_HEIGHT / 2 < WINDOW_HEIGHT / 2) {
            paddleRightY += SPEED;
        }
    } else if (key == GLUT_KEY_DOWN) {  // Flecha abajo
        if (paddleRightY - PADDLE_HEIGHT / 2 > -WINDOW_HEIGHT / 2) {
            paddleRightY -= SPEED;
        }
    }

    glutPostRedisplay();  
}

void keyPressedPlayer2(unsigned char key, int x, int y) {
    const float SPEED = 20.0f;

    if (key == 'w' || key == 'W') {  
        if (paddleLeftY + PADDLE_HEIGHT / 2 < WINDOW_HEIGHT / 2) {
            paddleLeftY += SPEED;
        }
    } else if (key == 's' || key == 'S') {  
        if (paddleLeftY - PADDLE_HEIGHT / 2 > -WINDOW_HEIGHT / 2) {
            paddleLeftY -= SPEED;
        }
    }

    glutPostRedisplay();  
}


void initOpenGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pong OpenGL");
    initOpenGL();
    glutDisplayFunc(display);
    glutSpecialFunc(keyPressed);       
    glutKeyboardFunc(keyPressedPlayer2); 
    glutMainLoop();

    return 0;
}
