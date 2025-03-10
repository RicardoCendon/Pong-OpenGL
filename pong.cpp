#include <GL/glut.h>
#include <stdio.h>

// Dimensiones de la ventana
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Pelota
float ballX = 0.0f, ballY = 0.0f;
const float BALL_SIZE = 10.0f;
float ballSpeedX = 4.0f;
float ballSpeedY = 4.0f;

// Paletas
float paddleLeftY = 0.0f, paddleRightY = 0.0f;
const float PADDLE_WIDTH = 10.0f, PADDLE_HEIGHT = 80.0f;

// Puntuación
int scoreLeft = 0, scoreRight = 0;

// Función para mostrar puntaje en la pantalla
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar la pelota
    glBegin(GL_QUADS);
        glVertex2f(ballX - BALL_SIZE, ballY - BALL_SIZE);
        glVertex2f(ballX + BALL_SIZE, ballY - BALL_SIZE);
        glVertex2f(ballX + BALL_SIZE, ballY + BALL_SIZE);
        glVertex2f(ballX - BALL_SIZE, ballY + BALL_SIZE);
    glEnd();

    // Dibujar paleta izquierda
    glBegin(GL_QUADS);
        glVertex2f(-WINDOW_WIDTH / 2 + 20, paddleLeftY - PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH, paddleLeftY - PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH, paddleLeftY + PADDLE_HEIGHT / 2);
        glVertex2f(-WINDOW_WIDTH / 2 + 20, paddleLeftY + PADDLE_HEIGHT / 2);
    glEnd();

    // Dibujar paleta derecha
    glBegin(GL_QUADS);
        glVertex2f(WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH, paddleRightY - PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20, paddleRightY - PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20, paddleRightY + PADDLE_HEIGHT / 2);
        glVertex2f(WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH, paddleRightY + PADDLE_HEIGHT / 2);
    glEnd();

    // Dibujar puntuación en la parte superior
    char scoreText[20];
    sprintf(scoreText, "%d  -  %d", scoreLeft, scoreRight);
    drawText(scoreText, -30, 260);

    glFlush();
}

void updateBall(int value) {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Rebote en los bordes superior e inferior
    if (ballY + BALL_SIZE > WINDOW_HEIGHT / 2 || ballY - BALL_SIZE < -WINDOW_HEIGHT / 2) {
        ballSpeedY = -ballSpeedY;
    }

    // Colisión con la paleta derecha
    if (ballX + BALL_SIZE >= (WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH) &&
        ballY >= paddleRightY - PADDLE_HEIGHT / 2 &&
        ballY <= paddleRightY + PADDLE_HEIGHT / 2) {
        ballSpeedX = -ballSpeedX;
        ballX = (WINDOW_WIDTH / 2 - 20 - PADDLE_WIDTH) - BALL_SIZE - 1;
    }

    // Colisión con la paleta izquierda
    if (ballX - BALL_SIZE <= (-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH) &&
        ballY >= paddleLeftY - PADDLE_HEIGHT / 2 &&
        ballY <= paddleLeftY + PADDLE_HEIGHT / 2) {
        ballSpeedX = -ballSpeedX;
        ballX = (-WINDOW_WIDTH / 2 + 20 + PADDLE_WIDTH) + BALL_SIZE + 1;
    }

    // Si la pelota sale por el lado derecho, punto para el jugador izquierdo
    if (ballX > WINDOW_WIDTH / 2) {
        scoreLeft++;
        printf("Jugador izquierdo: %d\n", scoreLeft);
        ballX = 0;
        ballY = 0;
        ballSpeedX = -ballSpeedX;  
        glutPostRedisplay(); 
    }

    // Si la pelota sale por el lado izquierdo, punto para el jugador derecho
    if (ballX < -WINDOW_WIDTH / 2) {
        scoreRight++;
        printf("Jugador derecho: %d\n", scoreRight);
        ballX = 0;
        ballY = 0;
        ballSpeedX = -ballSpeedX;  
        glutPostRedisplay();
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateBall, 0);
}

// Player 1
void keyPressed(int key, int x, int y) {
    const float SPEED = 20.0f;

    if (key == GLUT_KEY_UP) {  
        if (paddleRightY + PADDLE_HEIGHT / 2 < WINDOW_HEIGHT / 2) {
            paddleRightY += SPEED;
        }
    } else if (key == GLUT_KEY_DOWN) { 
        if (paddleRightY - PADDLE_HEIGHT / 2 > -WINDOW_HEIGHT / 2) {
            paddleRightY -= SPEED;
        }
    }

    glutPostRedisplay();
}

// Player 2
void keyPressed2(unsigned char key, int x, int y) {
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

// Inicializar OpenGL
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
    glutKeyboardFunc(keyPressed2);
    glutTimerFunc(16, updateBall, 0); 
    glutMainLoop();

    return 0;
}
