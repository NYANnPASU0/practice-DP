#include <cmath>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include "glut.h"

// розовая линия конь
// бирюзовая линия король
// желтый квадрат начало пути 
// зеленый квадрат король, красный конь, задание про два хода 

using ll = long long;
using ld = long double;

int n, m;
int index_X, index_Y;


bool check_correctness(int n, int m, int ind_n, int ind_m) //проверка корректности введенных координат
{
    if (ind_n >= n || ind_n < 0 || ind_m >= m || ind_m < 0)
    {
        return false;
    }
    return true;
}

void two_steps(int n, int m) //функция находит номера всех клеток, куда фигура может попасть за два хода.
{
    int ind_row, ind_column;
    std::cout << std::endl << "2 steps:" << std::endl;
    std::cout << "Input N(row), M(column) of start: ";
    std::cin >> ind_row >> ind_column;
    ind_row--;
    ind_column--;
    index_X = ind_row;
    index_Y = ind_column;

    if (!check_correctness(n, m, ind_row, ind_column))
    {
        std::cout << "WRONG INPUT" << std::endl;
        return;
    }

    std::cout << "Possible positions after two moves:" << std::endl;
    std::cout << " HORSE " << std::endl;
    //ходы коня
    std::vector<std::pair<int, int>> Shag = { {-2, 1}, { -2, 3 }, { -1,-1 }, { -1, 3 }, { 1, -3 }, { 1, 1 }, { 2, -3 }, { 2,-1 } };

    std::vector<std::pair<int, int>> first_positions_h;
    std::set<std::pair<int, int>> second_positions_h;
    // Первый ход
    for (int k = 0; k < 8; k++)
    {
        int new_row_h = ind_row + Shag[k].first;
        int new_column_h = ind_column + Shag[k].second;
        if (check_correctness(n, m, new_row_h, new_column_h))
        {
            first_positions_h.push_back({ new_row_h , new_column_h });
        }
    }
    for (int i = 0; i < first_positions_h.size(); i++)
    {
        for (int j = 0; j < Shag.size(); j++)
        {
            int new_row_ = first_positions_h[i].first + Shag[j].first;
            int new_column_ = first_positions_h[i].second + Shag[j].second;
            if (check_correctness(n, m, new_row_, new_column_))
            {
                second_positions_h.insert({ new_row_ + 1, new_column_ + 1 });
            }
        }
    }
    for (std::set<std::pair<int, int>>::iterator it = second_positions_h.begin(); it != second_positions_h.end(); it++)
    {
        std::cout << "Row: " << it->first << ", Column: " << it->second << std::endl;
    }

   std::cout << "KING" << std::endl;
   // Ходы короля
   std::vector<std::pair<int, int>> Shag_k = {{0, 1}, {0, -1}, {1, -1}, {-1, 1}};
   std::vector<std::pair<int, int>> first_positions;
   std::set<std::pair<int, int>> second_positions;

   for (int k = 0; k < 4; k++)
   {
       int new_row = ind_row + Shag_k[k].first;
       int new_column = ind_column + Shag_k[k].second;
       if (check_correctness(n, m, new_row, new_column))
       {
           first_positions.push_back({ new_row, new_column});
       }
   }
   for (int i = 0; i < first_positions.size(); i++)
   {
       for (int j = 0; j < Shag_k.size(); j++)
       {
           int new_row = first_positions[i].first + Shag_k[j].first; 
           int new_column = first_positions[i].second + Shag_k[j].second;
           if (check_correctness(n, m, new_row, new_column))
           {
               second_positions.insert({ new_row + 1, new_column + 1 });
           }
       }
   }
   for (std::set<std::pair<int, int>>::iterator it = second_positions.begin(); it != second_positions.end(); it++)
   {
       std::cout << "Row: " << it->first << ", Column: " << it->second << std::endl;
   }
}


void display() // Функция для рисования сетки
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double sizes = 0.1;

            double x = - (sizes * m) + sizes * j + (i + 1) * sizes;
            double y = (sizes * n * 0.5) - sizes * i;

            glBegin(GL_LINES);

            glColor3f(1.0, 1.0, 1.0);

            glVertex2f(x, y);
            glVertex2f(x, y + sizes);
            //
            glVertex2f(x, y + sizes);
            glVertex2f(x + sizes, y + sizes);
            //
            glVertex2f(x + sizes, y + sizes);
            glVertex2f(x + sizes, y);
            //
            glVertex2f(x, y);
            glVertex2f(x + sizes, y);

            if (i == index_X && j == index_Y)
            {
                glColor3f(1.0, 1.0, 0.0);
                
                glVertex2f(x + 0.04, y + 0.04);
                glVertex2f(x + 0.04, y + sizes - 0.04);
                //
                glVertex2f(x + 0.04, y + sizes - 0.04);
                glVertex2f(x + sizes - 0.04, y + sizes - 0.04);
                //
                glVertex2f(x + sizes - 0.04, y + sizes - 0.04);
                glVertex2f(x + sizes - 0.04, y + 0.04);
                //
                glVertex2f(x + 0.04, y + 0.04);
                glVertex2f(x + sizes - 0.04, y + 0.04);
            }

            glEnd();
            glFlush();
        }
    }
}

int main(int argc, char** argv) {
    std::cout << "Input rows and columns counts: ";
    std::cin >> n >> m;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("LABA 7 n5");

    glClearColor(0.045, 0.045, 0.045, 1.0);
    glLoadIdentity();
    glutDisplayFunc(display);
    two_steps(n, m);
    glutMainLoop();

    return 0;
}
