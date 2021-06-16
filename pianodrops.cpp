#include <GL/glut.h>
#include <iostream>
using namespace std;

constexpr auto PI = 3.14159265358979323846;
int game_state = 0;
int game_point = 0;
char buffer1[10] = { '\0' };
char buffer2[10] = { '\0' };
char buffer3[10] = { '\0' };
int lives = 9;
int correct_clicks = 0;
int total_clicks = 0;
float xc, yc;
float mx, my;

void screen_squares()
{
    for (int i = 1; i < 4; ++i)
        for (int j = 1; j < 4; ++j)
        {
            if ((i % 2 != 0) && (j % 2 != 0))
                glColor3f(0.862, 0.0784, 0.2352);
            else if (i == j)
                glColor3f(1.0, 1.0, 1.0);
            else
                glColor3f(0.9803, 0.9803, 0.8235);
            glBegin(GL_QUADS);
            glVertex2f((1024 / 3) * (j - 1), (900 / 3) * (i - 1));
            glVertex2f((1024 / 3) * (j - 1), (900 / 3) * (i));
            glVertex2f((1024 / 3) * (j), (900 / 3) * (i));
            glVertex2f((1024 / 3) * (j), (900 / 3) * (i - 1));
            glEnd();
        }
}

void renderBitmapString(float x, float y, void* font, const char* string)
{
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void text_blocks()
{
    glColor3f(1.0, 0.0784, 0.5764);
    renderBitmapString(440, 730, GLUT_BITMAP_TIMES_ROMAN_24, "\"Piano Drops\"");

    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(480, 680, GLUT_BITMAP_TIMES_ROMAN_24, "lansky");
}

void game_options()
{
    glColor3f(0.0, 0.5, 0.0);

    // the intended start button
    glBegin(GL_QUADS);
    glVertex2f(396.995, 555.0);
    glVertex2f(396.995, 465.0);
    glVertex2f(636.995, 465.0);
    glVertex2f(636.995, 555.0);
    glEnd();

    // the intended exit button
    glBegin(GL_QUADS);
    glVertex2f(396.995, 445.0);
    glVertex2f(396.995, 355.0);
    glVertex2f(636.995, 355.0);
    glVertex2f(636.995, 445.0);
    glEnd();
}

void decor()
{
    glColor3f(0.3725, 0.6196, 0.6274);
    glBegin(GL_POLYGON);
    glVertex2f(50 + 0.0, 350 + 25.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(50 + 25.0 * 4, 350 + 50.0 * 4);
    glVertex2f(50 + 50.0 * 4, 350 + 25.0 * 4);
    glVertex2f(50 + 25.0 * 4, 350 + 0.0);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(50 + 37.5 * 4, 350 + 50.0 * 4);
    glVertex2f(50 + 25.0 * 4, 350 + 50.0 * 4);
    glVertex2f(50 + 50.0 * 4, 350 + 25.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(50 + 62.5 * 4, 350 + 25.0 * 4);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(50 + 62.5 * 4, 350 + 25.0 * 4);
    glVertex2f(50 + 50.0 * 4, 350 + 25.0 * 4);
    glVertex2f(50 + 25.0 * 4, 350 + 0.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(50 + 37.5 * 4, 350 + 0.0 * 4);
    glEnd();

    glColor3f(0.3725, 0.6196, 0.6274);
    glBegin(GL_POLYGON);
    glVertex2f(725 + 0.0, 350 + 25.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(725 + 25.0 * 4, 350 + 50.0 * 4);
    glVertex2f(725 + 50.0 * 4, 350 + 25.0 * 4);
    glVertex2f(725 + 25.0 * 4, 350 + 0.0);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(725 + 37.5 * 4, 350 + 50.0 * 4);
    glVertex2f(725 + 25.0 * 4, 350 + 50.0 * 4);
    glVertex2f(725 + 50.0 * 4, 350 + 25.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(725 + 62.5 * 4, 350 + 25.0 * 4);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(725 + 62.5 * 4, 350 + 25.0 * 4);
    glVertex2f(725 + 50.0 * 4, 350 + 25.0 * 4);
    glVertex2f(725 + 25.0 * 4, 350 + 0.0 * 4);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(725 + 37.5 * 4, 350 + 0.0 * 4);
    glEnd();
}

void background()
{
    glColor3f(0.1882, 0.098, 0.2039);
    glBegin(GL_POLYGON);
    glVertex2f(874, 700);
    glVertex2f(190, 800);
    glVertex2f(150, 600);
    glVertex2f(150, 100);
    glVertex2f(874, 200);
    glEnd();
    glColor3f(1.0, 0.0784, 0.5764);
    renderBitmapString(800, 800, GLUT_BITMAP_TIMES_ROMAN_24, "main menu");
    renderBitmapString(445, 600, GLUT_BITMAP_TIMES_ROMAN_24, "Piano Drops");    
}

void background2()
{
    glColor3f(0.1882, 0.098, 0.2039);
    glBegin(GL_POLYGON);
    glVertex2f(874, 800);
    glVertex2f(150, 700);
    glVertex2f(150, 200);
    glVertex2f(874, 100);
    glEnd();
    glColor3f(1.0, 0.0784, 0.5764);
    renderBitmapString(850, 820, GLUT_BITMAP_TIMES_ROMAN_24, "levels");
    renderBitmapString(445, 600, GLUT_BITMAP_TIMES_ROMAN_24, "choose level");
}

void high(int i, int j)
{
    if (game_state == 0)
    {
        j = 900 - j;
        if (((396.995 < i) && (i < 636.995)) && ((465 < j) && (j < 555)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended start button
            glBegin(GL_QUADS);
            glVertex2f(396.995, 555.0);
            glVertex2f(396.995, 465.0);
            glVertex2f(606.995, 465.0);
            glVertex2f(606.995, 555.0);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(455, 500, GLUT_BITMAP_TIMES_ROMAN_24, "start game");
        }

        if (((396.995 < i) && (i < 636.995)) && ((355 < j) && (j < 445)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended exit button
            glBegin(GL_QUADS);
            glVertex2f(396.995, 445.0);
            glVertex2f(396.995, 355.0);
            glVertex2f(606.995, 355.0);
            glVertex2f(606.995, 445.0);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(456, 390, GLUT_BITMAP_TIMES_ROMAN_24, "quit game");
        }
    }

    if (game_state == 1)
    {
        j = 900 - j;
        if (((396.995 < i) && (i < 636.995)) && ((465 < j) && (j < 555)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended start button
            glBegin(GL_QUADS);
            glVertex2f(416.995, 555.0);
            glVertex2f(416.995, 465.0);
            glVertex2f(606.995, 465.0);
            glVertex2f(606.995, 555.0);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(480, 505, GLUT_BITMAP_TIMES_ROMAN_24, "level 1");
        }

        if (((396.995 < i) && (i < 636.995)) && ((355 < j) && (j < 445)))
        {
            glColor3f(0.0, 0.5, 0.0);
            // the intended exit button
            glBegin(GL_QUADS);
            glVertex2f(416.995, 445.0);
            glVertex2f(416.995, 355.0);
            glVertex2f(606.995, 355.0);
            glVertex2f(606.995, 445.0);
            glEnd();
            glColor3f(1.0, 1.0, 1.0);
            renderBitmapString(480, 395, GLUT_BITMAP_TIMES_ROMAN_24, "level 2");
        }
    }
}

void mainmenu()
{
    game_state = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);
    background();
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(455, 500, GLUT_BITMAP_TIMES_ROMAN_24, "start game");
    renderBitmapString(456, 390, GLUT_BITMAP_TIMES_ROMAN_24, "quit game");
    high(mx, my);
    //screen_squares();
    //text_blocks();
    //game_options();
    //decor();
    glutPostRedisplay();
    glutSwapBuffers();
}

void level_options()
{
    glColor3f(0.862, 0.0784, 0.2352);

    // the intended level 1 button
    glBegin(GL_QUADS);
    glVertex2f(376.995, 555.0);
    glVertex2f(376.995, 465.0);
    glVertex2f(646.995, 465.0);
    glVertex2f(646.995, 555.0);
    glEnd();

    // the intended level 2 button
    glBegin(GL_QUADS);
    glVertex2f(376.995, 445.0);
    glVertex2f(376.995, 355.0);
    glVertex2f(646.995, 355.0);
    glVertex2f(646.995, 445.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(480, 505, GLUT_BITMAP_TIMES_ROMAN_24, "level 1");
    renderBitmapString(480, 395, GLUT_BITMAP_TIMES_ROMAN_24, "level 2");
}

void level_screen()
{
    game_state = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    background2();
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(480, 505, GLUT_BITMAP_TIMES_ROMAN_24, "level 1");
    renderBitmapString(480, 395, GLUT_BITMAP_TIMES_ROMAN_24, "level 2");
    high(mx, my);
    //level_options();
    glutPostRedisplay();
    glutSwapBuffers();
}

void sample()
{
    glColor3f(0.3725, 0.6196, 0.6274);
    glBegin(GL_POLYGON);
    glVertex2f(xc + 0.0, yc + 25.0);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(xc + 25.0, yc + 50.0);
    glVertex2f(xc + 50.0, yc + 25.0);
    glVertex2f(xc + 25.0, yc + 0.0);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(xc + 37.5, yc + 50.0);
    glVertex2f(xc + 25.0, yc + 50.0);
    glVertex2f(xc + 50.0, yc + 25.0);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(xc + 62.5, yc + 25.0);
    glEnd();

    glColor3f(0.1803, 0.5450, 0.3411);
    glBegin(GL_QUADS);
    glVertex2f(xc + 62.5, yc + 25.0);
    glVertex2f(xc + 50.0, yc + 25.0);
    glVertex2f(xc + 25.0, yc + 0.0);
    glColor3f(0.4, 0.8039, 0.6667);
    glVertex2f(xc + 37.5, yc + 0.0);
    glEnd();
}

void level_start()
{
    yc = 850;
    switch (rand() % 4)
    {
    case 0:
        xc = 267.5;
        break;
    case 1:
        xc = 392.5;
        break;
    case 2:
        xc = 517.5;
        break;
    case 3:
        xc = 642.5;
        break;
    }
}

void sample_start()
{
    yc = 850;
    switch (rand() % 4)
    {
    case 0:
        xc = 363;
        break;
    case 1:
        xc = 423;
        break;
    case 2:
        xc = 603;
        break;
    case 3:
        xc = 543;
        break;
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                    // reset to identity
    gluOrtho2D(0.0, 1023.0, 0.0, 899.0); // l, r, b, t
}

void lines(int X)
{
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(5, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glVertex2f(X, 900);
    glVertex2f(X, 0);
    glEnd();
    glPopAttrib();
}

void points()
{
    glBegin(GL_POINTS);
    glVertex2f(392, 360);
    glVertex2f(632, 240);
    glVertex2f(572, 420);
    glVertex2f(452, 180);
    glEnd();
}

void base_triangle()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(512, 300);
    glVertex2f(392, 540);
    glVertex2f(272, 180);
    glEnd();
    glColor3f(0.862, 0.0784, 0.2352);
    glBegin(GL_TRIANGLES);
    glVertex2f(512, 300);
    glVertex2f(392, 540);
    glVertex2f(752, 420);
    glEnd();
    glColor3f(0.862, 0.0784, 0.2352);
    glBegin(GL_TRIANGLES);
    glVertex2f(512, 300);
    glVertex2f(272, 180);
    glVertex2f(632, 60);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(512, 300);
    glVertex2f(632, 60);
    glVertex2f(752, 420);
    glEnd();
}

void base_rectangle()
{
    glColor3f(1, 0.2705, 0);
    glBegin(GL_QUADS);
    glVertex2f(230, 900);
    glVertex2f(230, 0);
    glVertex2f(355, 0);
    glVertex2f(355, 900);
    glEnd();
    glColor3f(0.4862, 0.9882, 0);
    glBegin(GL_QUADS);
    glVertex2f(355, 900);
    glVertex2f(355, 0);
    glVertex2f(480, 0);
    glVertex2f(480, 900);
    glEnd();
    glColor3f(0.1176, 0.5647, 1);
    glBegin(GL_QUADS);
    glVertex2f(480, 900);
    glVertex2f(480, 0);
    glVertex2f(605, 0);
    glVertex2f(605, 900);
    glEnd();
    glColor3f(1, 0.4117, 0.7058);
    glBegin(GL_QUADS);
    glVertex2f(605, 900);
    glVertex2f(605, 0);
    glVertex2f(730, 0);
    glVertex2f(730, 900);
    glEnd();
}

void detect(int s)
{
    if (s == 1)
    {
        game_point = 1;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(512, 300);
        glVertex2f(392, 540);
        glVertex2f(272, 180);
        glEnd();
    }
    else if (s == 2)
    {
        game_point = 2;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(512, 300);
        glVertex2f(272, 180);
        glVertex2f(632, 60);
        glEnd();
    }
    else if (s == 3)
    {
        game_point = 3;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(512, 300);
        glVertex2f(632, 60);
        glVertex2f(752, 420);
        glEnd();
    }
    else if (s == 4)
    {
        game_point = 4;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(512, 300);
        glVertex2f(392, 540);
        glVertex2f(752, 420);
        glEnd();
    }
    else if (s == 5)
    {
        game_point = 5;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(230, 300);
        glVertex2f(230, 0);
        glVertex2f(355, 0);
        glVertex2f(355, 300);
        glEnd();
    }
    else if (s == 6)
    {
        game_point = 6;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(355, 300);
        glVertex2f(355, 0);
        glVertex2f(480, 0);
        glVertex2f(480, 300);
        glEnd();
    }
    else if (s == 7)
    {
        game_point = 7;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(480, 300);
        glVertex2f(480, 0);
        glVertex2f(605, 0);
        glVertex2f(605, 300);
        glEnd();
    }
    else if (s == 8)
    {
        game_point = 8;
        //sprintf_s(buffer, "%d", game_point);
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(605, 300);
        glVertex2f(605, 0);
        glVertex2f(730, 0);
        glVertex2f(730, 300);
        glEnd();
    }
    else
    {
        game_point = 0;
        //sprintf_s(buffer, "%d", game_point);
    }
}

void click1()
{
    if (game_point != 0)
    {
        total_clicks += 1;
        if (game_point == 1 || game_point == 5)
            correct_clicks += 1;
        else
            lives -= 1;
        sprintf_s(buffer1, "%d", correct_clicks * 100 / total_clicks);
        sprintf_s(buffer2, "%d", total_clicks);
    }
}

void click2()
{
    if (game_point != 0)
    {
        total_clicks += 1;
        if (game_point == 2 || game_point == 6)
            correct_clicks += 1;
        else
            lives -= 1;
        sprintf_s(buffer1, "%d", correct_clicks * 100 / total_clicks);
        sprintf_s(buffer2, "%d", total_clicks);
    }
}

void click3()
{
    if (game_point != 0)
    {
        total_clicks += 1;
        if (game_point == 3 || game_point == 7)
            correct_clicks += 1;
        else
            lives -= 1;
        sprintf_s(buffer1, "%d", correct_clicks * 100 / total_clicks);
        sprintf_s(buffer2, "%d", total_clicks);
    }
}

void click4()
{
    if (game_point != 0)
    {
        total_clicks += 1;
        if (game_point == 4 || game_point == 8)
            correct_clicks += 1;
        else
            lives -= 1;
        sprintf_s(buffer1, "%d", correct_clicks * 100 / total_clicks);
        sprintf_s(buffer2, "%d", total_clicks);
    }
}

void a_sphere(float r, float g, float b, int rd)
{
    float theta;

    GLfloat angle;
    glLineWidth(1.5);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        theta = i * PI * i / 180;
        glVertex2f(150 + rd * cos(theta) / 2, 800 + rd * sin(theta) / 2);
    }
    glEnd();
}

void respawn()
{
    glutDisplayFunc(mainmenu);
    game_point = 0;
    lives = 9;
    correct_clicks = 0;
    total_clicks = 0;
    yc = 850;
    sprintf_s(buffer1, "%d", 0);
    sprintf_s(buffer2, "%d", 0);
}

void display()
{
    game_state = 2;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1);
    base_triangle();
    a_sphere(1, 0.2, 0, 100);
    a_sphere(0.862, 0.0784, 0.2352, 80);
    glColor3f(1.0, 0.8431, 0.0);
    renderBitmapString(392, 350, GLUT_BITMAP_TIMES_ROMAN_24, "1");
    renderBitmapString(622, 245, GLUT_BITMAP_TIMES_ROMAN_24, "3");
    renderBitmapString(532, 410, GLUT_BITMAP_TIMES_ROMAN_24, "4");
    renderBitmapString(462, 190, GLUT_BITMAP_TIMES_ROMAN_24, "2");
    glPointSize(4.0);
    points();
    glColor3f(0.0, 0.3921, 0.0);
    lines(392);
    lines(632);
    lines(572);
    lines(452);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(770, 870);
    glVertex2f(910, 870);
    glVertex2f(910, 740);
    glVertex2f(770, 740);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(770, 720);
    glVertex2f(910, 720);
    glVertex2f(910, 590);
    glVertex2f(770, 590);
    glEnd();
    renderBitmapString(795, 820, GLUT_BITMAP_TIMES_ROMAN_24, "Accuracy");
    renderBitmapString(865, 770, GLUT_BITMAP_TIMES_ROMAN_24, "%");
    renderBitmapString(835, 770, GLUT_BITMAP_TIMES_ROMAN_24, buffer1);
    renderBitmapString(815, 675, GLUT_BITMAP_TIMES_ROMAN_24, "Total");
    renderBitmapString(830, 625, GLUT_BITMAP_TIMES_ROMAN_24, buffer2);
    sprintf_s(buffer3, "%d", lives);
    renderBitmapString(145, 790, GLUT_BITMAP_TIMES_ROMAN_24, buffer3);
    if (yc < 50)
        sample_start();
    sample();
    yc -= 0.3;
    if (((900 - yc < 240) || (900 - yc > 540)) && xc == 363)
        detect(0);
    if (((900 - yc < 660) || (900 - yc > 770.333)) && xc == 423)
        detect(0);
    if (((900 - yc < 554.5) || (900 - yc > 840)) && xc == 603)
        detect(0);
    if (((900 - yc < 410.333) || (900 - yc > 554.5)) && xc == 543)
        detect(0);
    if ((900 - yc > 340) && (900 - yc < 660) && xc == 363)
        detect(1);
    if ((900 - yc > 660) && (900 - yc < 770.333) && xc == 423)
        detect(2);
    if ((900 - yc > 554.5) && (900 - yc < 840) && xc == 603)
        detect(3);
    if ((900 - yc > 410.333) && (900 - yc < 554.5) && xc == 543)
        detect(4);
    if (lives == 0)
    {
        respawn();
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

void level2()
{
    game_state = 3;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1);
    base_rectangle();
    a_sphere(1, 0.2, 0, 100);
    a_sphere(0.862, 0.0784, 0.2352, 80);
    glColor3f(0,0,0);
    renderBitmapString(287.5, 150, GLUT_BITMAP_TIMES_ROMAN_24, "1");
    renderBitmapString(412.5, 150, GLUT_BITMAP_TIMES_ROMAN_24, "2");
    renderBitmapString(537.5, 150, GLUT_BITMAP_TIMES_ROMAN_24, "3");
    renderBitmapString(662.5, 150, GLUT_BITMAP_TIMES_ROMAN_24, "4");
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(770, 870);
    glVertex2f(910, 870);
    glVertex2f(910, 740);
    glVertex2f(770, 740);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(770, 720);
    glVertex2f(910, 720);
    glVertex2f(910, 590);
    glVertex2f(770, 590);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(230, 900);
    glVertex2f(230, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(730, 900);
    glVertex2f(730, 0);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(230, 300);
    glVertex2f(730, 300);
    glEnd();
    renderBitmapString(795, 520, GLUT_BITMAP_TIMES_ROMAN_24, "Piece of Advise");
    renderBitmapString(745, 490, GLUT_BITMAP_TIMES_ROMAN_24, "Let the block cross the line.");
    renderBitmapString(795, 820, GLUT_BITMAP_TIMES_ROMAN_24, "Accuracy");
    renderBitmapString(865, 770, GLUT_BITMAP_TIMES_ROMAN_24, "%");
    renderBitmapString(835, 770, GLUT_BITMAP_TIMES_ROMAN_24, buffer1);
    renderBitmapString(815, 675, GLUT_BITMAP_TIMES_ROMAN_24, "Total");
    renderBitmapString(830, 625, GLUT_BITMAP_TIMES_ROMAN_24, buffer2);
    sprintf_s(buffer3, "%d", lives);
    renderBitmapString(145, 790, GLUT_BITMAP_TIMES_ROMAN_24, buffer3);
    if (yc < 0)
        level_start();
    sample();
    yc -= 1;
    if ((yc > 300) && xc == 267.5)
        detect(0);
    if ((yc > 300) && xc == 392.5)
        detect(0);
    if ((yc > 300) && xc == 517.5)
        detect(0);
    if ((yc > 300) && xc == 642.5)
        detect(0);
    if ((yc < 300) && xc == 267.5)
        detect(5);
    if ((yc < 300) && xc == 392.5)
        detect(6);
    if ((yc < 300) && xc == 517.5)
        detect(7);
    if ((yc < 300) && xc == 642.5)
        detect(8);
    if (lives == 0)
    {
        respawn();
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && game_state == 0)
    {
        y = 900 - y;
        if (((376.995 < x) && (x < 606.995)) && ((465 < y) && (y < 555)))
            glutDisplayFunc(level_screen);

        if (((376.995 < x) && (x < 606.995)) && ((355 < y) && (y < 445)))
            exit(0);
    }

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && game_state == 1)
    {
        y = 900 - y;
        if (((376.995 < x) && (x < 606.995)) && ((465 < y) && (y < 555)))
            glutDisplayFunc(display);

        if (((376.995 < x) && (x < 606.995)) && ((355 < y) && (y < 445)))
            glutDisplayFunc(level2);
    }
}

void mouse2(int x, int y)
{
    mx = x; my = y;
    glutPostRedisplay();
}

void game()
{
    if (game_state == 0)
        mainmenu();

    else if (game_state == 1)
        level_screen();

    else if (game_state == 2)
        display();

    else if (game_state == 3)
        level2();
}

void keypress(unsigned char key, int x, int y)
{
    //if (key == ' ' && game_state == 0)
        //glutDisplayFunc(level_screen);

    if (key == 27 && game_state == 0)
        exit(0);

    if (key == 49 && game_state == 1)
        glutDisplayFunc(display);

    if (key == 50 && game_state == 1)
        glutDisplayFunc(level2);

    if (key == 27 && game_state == 1)
        glutDisplayFunc(mainmenu);

    if (key == 27 && game_state == 2)
        glutDisplayFunc(level_screen);

    if (key == 27 && game_state == 3)
        glutDisplayFunc(level_screen);

    if (key == 49 && game_state == 2)
        click1();

    else if (key == 50 && game_state == 2)
        click2();

    else if (key == 51 && game_state == 2)
        click3();

    else if (key == 52 && game_state == 2)
        click4();

    if (key == 49 && game_state == 3)
        click1();

    else if (key == 50 && game_state == 3)
        click2();

    else if (key == 51 && game_state == 3)
        click3();

    else if (key == 52 && game_state == 3)
        click4();
}

int main(int argc, char** argv)
{
    cout << "*******************************************************************";
    cout << "\n\t\t\tPIANO TILES GAME\n\n";
    cout << "******************************************************************";
    cout << "\n\tHow to Play.. ? \n\n <1>The objective of the game is to press the tile of contact.\n\t To select tile use the keyboard keys 1, 2, 3, 4.\n";
    cout << "\n <2> TO start the game, press space or \n\tClick Left mouse button to click 'Start'.\n";
    cout << "\n <3> To Quit manually, press key 'Esc' or \n\t Click Left mouse button to click 'Exit'.\n";
    cout << "\n\nThe Game Ends as your 9 lives extinguish.\n";
    cout << "\n\nThe Game will exit when your lives end.\n";
    cout << "\n\nBEST OF LUCK\n";
    cout << "lansky\n";

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Piano Drops");
    glutSwapBuffers();
    glutDisplayFunc(game);
    glutKeyboardFunc(keypress);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouse2);
    init();
    glutMainLoop();
}
