#include <iostream>
#include  "glut.h"
#include <windows.h>
#include <algorithm>
#include <vector>

const double pi = 3.14159265358979;

struct point
{
    double x, y;

    point(int x = 0, int y = 0) : x(x), y(y) {};

    point operator+(point& p)
    {
        point rez;
        rez.x = x + p.x;
        rez.y = y + p.y;
        return rez;
    }

    point operator-(point& p)
    {
        point rez;
        rez.x = x - p.x;
        rez.y = y - p.y;
        return rez;
    }

    point operator*(double& t)
    {
        point rez;
        rez.x = t * x;
        rez.y = t * y;
        return rez;
    }
};

void draw_coordinate()
{
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    //отрисовка oси Ox
    glVertex2f(-25.0, 0.0);
    glVertex2f(25.0, 0.0);
    //отрисовка стрелочки 1
    glVertex2f(25.0, 0.0);
    glVertex2f(24.0, 0.5);
    glVertex2f(25.0, 0.0);
    glVertex2f(24.0, -0.5);
    //отрисовка oси Oy
    glVertex2f(0.0, 25.0);
    glVertex2f(0.0, -25.0);
    ////отрисовка стрелочки 2
    glVertex2f(0.0, 25.0);
    glVertex2f(0.5, 24.0);
    glVertex2f(0.0, 25.0);
    glVertex2f(-0.5, 24.0);
    glEnd();
}

int random_point(int N, int M)
{
    return /*(rand() % M) / floor(M / N);*/ rand() % N;
}

void paint(int N, std::vector<point>& points)
{
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 0.0);

    point curr;
    std::cout << "Input coord to start point: ";
    std::cin >> curr.x >> curr.y;
    glVertex2f(curr.x, curr.y);

    for (int i = 0; i < N; i++)
    {
        int num = random_point(6, 19);
        point buff = points[num];

        curr = curr + buff;
        curr = curr * 0.5;

        glVertex2f(curr.x, curr.y);
    }

    glEnd();
    //glFlush();

    return;
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_coordinate();
    std::cout << "Input washi points!" << '\n';
    std::vector<point> points;

    for (int i = 0; i < 6; i++)
    {
        point p;
        std::cout << "Input x, y for point " << i + 1 << ' ';
        std::cin >> p.x >> p.y;
        points.push_back(p);
    }

    paint(1000000, points);

    glutSwapBuffers();
    return;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(950, 700);
    glutCreateWindow("Task 2");

    glutDisplayFunc(display);
    glOrtho(-1000, 1000, -1000, 1000, -1, 1);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutMainLoop();

    return 0;
}