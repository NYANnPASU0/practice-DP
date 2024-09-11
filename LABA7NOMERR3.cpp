#include <iostream>
#include <fstream>
#include <iomanip>
#include "glut.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstdlib>

void draw_coordinate()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2d(-3, 0);
    glVertex2d(3, 0);
    glVertex2d(0, -3);
    glVertex2d(0, 3);
    glutSwapBuffers();
    glEnd();
}

void draw_points()
{
    //отрисовка точек на графике
    glColor3f(0.0, 0.0, 0.0);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(-2.0, 0.0);
    glVertex2f(2.0, 0.0);
    glVertex2f(0.0, -2.0);
    glVertex2f(0.0, 2.0);
    //отрисовка точек пересечения
    glVertex2f(-2.0, 2.0);
    glVertex2f(1.0, 2.0);
    glVertex2f(-2.0, -1.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(-1.0, 0.0);
    glEnd();
}

void points_and_graphics()
{
    std::string limit_for_y1 = std::to_string(-2.0);
    std::string limit_for_y2 = std::to_string(2.0);
    std::string limit_for_x1 = std::to_string(-2.0);
    std::string limit_for_x2 = std::to_string(2.0);
    std::string zero = std::to_string(0.0);

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-2.2, -0.2);
    for (int i = 0; i < limit_for_y1.size() - 5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, limit_for_y1[i]);
    }
    glRasterPos2f(1.8, -0.2);
    for (int i = 0; i < limit_for_y2.size() - 5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, limit_for_y2[i]);
    }
    glRasterPos2f(-0.2, -0.2);
    for (int i = 0; i < zero.size() - 5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, zero[i]);
    }
    glRasterPos2f(-0.2, -2.2);
    for (int i = 0; i < limit_for_y1.size() - 5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, limit_for_y1[i]);
    }
    glRasterPos2f(-0.1, 2.1);
    for (int i = 0; i < limit_for_y2.size() - 5; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, limit_for_y2[i]);
    }

    glEnd();
}

void limit()
{
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.5f, 1.0f);
    //ограничения по x (2 < x < -2)
    glVertex2f(-2.0, -3.0);
    glVertex2f(-2.0, 3.0);
    glVertex2f(2.0, -3.0);
    glVertex2f(2.0, 3.0);
    //ограничения по y (2 < y < -2)
    glVertex2f(-3.0, 2.0);
    glVertex2f(3.0, 2.0);
    glVertex2f(-3.0, -2.0);
    glVertex2f(3.0, -2.0);
    glEnd();
    // y = x + 1
    glBegin(GL_LINES);
    glVertex2f(-3.0, -2.0);
    glVertex2f(3.0, 4.0);
    glEnd();
    // y^5 = x^5 + 2
    glLineStipple(4, 0xCCCC);
    glBegin(GL_LINES);
    for (float x = -2.0; x < 2.0; x += 0.2)
    {
        float y = std::pow(std::pow(x, 5) + 2, 1.0 / 5.0);
        glVertex2f(x, y);
        float x1 = x + 0.2;
        float y1 = std::pow(std::pow(x1, 5) + 2, 1.0 / 5.0);
        glVertex2f(x1, y1);
    }
    for (float x = 3.0; x >= -3.0; x -= 0.2)
    {
        float y = std::pow(std::pow(x, 5) + 2, 1.0 / 5.0);
        if (y >= -2.0 && y <= 2.0)
        {
            glVertex2f(-y, -x);
            float x1 = x - 0.2;
            float y1 = std::pow(std::pow(x1, 5) + 2, 1.0 / 5.0);
            if (y1 >= -2.0 && y1 <= 2.0)
            {
                glVertex2f(-y1, -x1);
            }
        }
    }
    glEnd();
}

double random_point(double min, double max) {
    return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}

bool point_inside_figure(double x, double y)
{
    if (x >= -2 && x <= 2 && y >= -2 && y <= 2)
    {
        if (pow(x, 5) - pow(y, 5) < -2 && x - y < -1) return true;
    }
    return false;
}

void S_Monte_Carlo(int N)
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_coordinate();
    limit();
    draw_points();
    points_and_graphics();
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor3d(1.0, 0.0, 1.0);
    int points_inside_k = 0;
    for (int i = 0; i < N; i++)
    {
        double x = random_point(-2.0, 2.0);
        double y = random_point(-2.0, 2.0);
        if (point_inside_figure(x, y))
        {
            points_inside_k++;
            glVertex2d(x, y);
            glFlush();
            glEnd();
            glBegin(GL_POINTS);
        }
    }
    double S0 = 4.0 * 4.0;
    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
    std::cout << "S: " << S << std::endl;
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_coordinate();
    limit();
    draw_points();
    points_and_graphics();
    S_Monte_Carlo(30000);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(550, 550);
    glutCreateWindow("Task 3: figure");

    glutDisplayFunc(display);
    glOrtho(-3, 3, -3, 3, -1, 1);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}

