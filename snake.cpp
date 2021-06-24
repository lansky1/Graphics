#include <GL/glut.h>
#include <iostream>
using namespace std;

// the id of the displayed menu
int m_id = 0; 
float mx, my;

// string rendering
void renderBitmapString(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void background()
{
    glColor3f(0.1882, 0.098, 0.2039);
    glBegin(GL_POLYGON);
    glVertex2f(420, 422);
    glVertex2f(90, 422);
    glVertex2f(90, 90);
    glVertex2f(420, 90);
    glEnd();
    glColor3f(1.0, 0.0784, 0.5764);
    renderBitmapString(310, 430, GLUT_BITMAP_TIMES_ROMAN_24, "main menu");
    renderBitmapString(225, 350, GLUT_BITMAP_TIMES_ROMAN_24, "Snake");
}

void background2()
{
    glColor3f(0.1882, 0.098, 0.2039);
    glBegin(GL_POLYGON);
    glVertex2f(420, 422);
    glVertex2f(90, 422);
    glVertex2f(90, 90);
    glVertex2f(420, 90);
    glEnd();
    glColor3f(1.0, 0.0784, 0.5764);
    renderBitmapString(300, 430, GLUT_BITMAP_TIMES_ROMAN_24, "pause menu");
    renderBitmapString(180, 350, GLUT_BITMAP_TIMES_ROMAN_24, "game is paused");
}

void high(int i, int j)
{
    if (m_id == 0)
    {
        j = 512 - j;
        if (((190 < i) && (i < 320)) && ((255 < j) && (j < 295)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended start button
            glBegin(GL_QUADS);
            glVertex2f(190, 295);
            glVertex2f(190, 255);
            glVertex2f(320, 255);
            glVertex2f(320, 295);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(205, 270, GLUT_BITMAP_TIMES_ROMAN_24, "start game");
        }

        if (((190 < i) && (i < 320)) && ((195 < j) && (j < 235)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended exit button
            glBegin(GL_QUADS);
            glVertex2f(190, 235);
            glVertex2f(190, 195);
            glVertex2f(320, 195);
            glVertex2f(320, 235);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(207, 210, GLUT_BITMAP_TIMES_ROMAN_24, "quit game");
        }
    }

    if (m_id == 2)
    {
        j = 512 - j;
        if (((195 < i) && (i < 315)) && ((255 < j) && (j < 295)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended start button
            glBegin(GL_QUADS);
            glVertex2f(195, 295);
            glVertex2f(195, 255);
            glVertex2f(315, 255);
            glVertex2f(315, 295);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(220, 270, GLUT_BITMAP_TIMES_ROMAN_24, "resume");
        }

        if (((150 < i) && (i < 360)) && ((195 < j) && (j < 235)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended exit button
            glBegin(GL_QUADS);
            glVertex2f(150, 235);
            glVertex2f(150, 195);
            glVertex2f(360, 195);
            glVertex2f(360, 235);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(172, 210, GLUT_BITMAP_TIMES_ROMAN_24, "go to main menu");
        }
    }
}

// mainmenu display function
void mainmenu()
{
    m_id = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    background();
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(205, 270, GLUT_BITMAP_TIMES_ROMAN_24, "start game");
    renderBitmapString(207, 210, GLUT_BITMAP_TIMES_ROMAN_24, "quit game");
    high(mx, my);
    glutPostRedisplay();
    glutSwapBuffers();
}

// gamescreen display function
void gamescreen()
{
    m_id = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1);
    glColor3f(0, 0, 0);
    renderBitmapString(287.5, 150, GLUT_BITMAP_TIMES_ROMAN_24, "1");
    glutPostRedisplay();
    glutSwapBuffers();
}

// pausemenu display function
void pausemenu()
{
    m_id = 2;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    background2();
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(220, 270, GLUT_BITMAP_TIMES_ROMAN_24, "resume");
    renderBitmapString(172, 210, GLUT_BITMAP_TIMES_ROMAN_24, "go to main menu");
    high(mx, my);
    glutPostRedisplay();
    glutSwapBuffers();
}

// display functions container
void display()
{
    if (m_id == 0)
        mainmenu();
    else if (m_id == 1)
        gamescreen();
    else if (m_id == 2)
        pausemenu();
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 511.0, 0.0, 511.0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27 && m_id == 0)
        exit(0);

    if (key == 27 && m_id == 1)
        glutDisplayFunc(pausemenu);

    if (key == 27 && m_id == 2)
        glutDisplayFunc(gamescreen);
}

void mouse(int x, int y)
{
    mx = x; my = y;
    glutPostRedisplay();
}

void mouse_keybind(int btn, int state, int x, int y)
{
    // main menu
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && m_id == 0)
    {
        y = 512 - y;
        if (((190 < x) && (x < 320)) && ((255 < y) && (y < 295)))
            glutDisplayFunc(gamescreen);

        if (((190 < x) && (x < 320)) && ((195 < y) && (y < 235)))
            exit(0);
    }

    // pause menu
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && m_id == 2)
    {
        y = 512 - y;
        if (((195 < x) && (x < 315)) && ((255 < y) && (y < 295)))
        {
            glutDisplayFunc(gamescreen);
        }

        if (((150 < x) && (x < 360)) && ((195 < y) && (y < 235)))
            // ADD A RESPAWN MECHANISM HERE
            glutDisplayFunc(mainmenu);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Snake");
    glutSwapBuffers();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse_keybind);
    glutPassiveMotionFunc(mouse);
    init();
    glutMainLoop();
}
