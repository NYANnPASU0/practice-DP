#include <cmath>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
#include "glut.h"

// желтый квадрат начало пути
/*
    2 ХОДА
    -красный квадрат - конь
    -зеленый квадрат - король
*/

// розовая линия конь
// бирюзовая линия король 


using ll = long long;
using ld = long double;

int n, m;
int index_X, index_Y;

//конь
std::set<std::pair<int, int>> first_positions_h;
std::set<std::pair<int, int>> second_positions_h;
//король
std::set<std::pair<int, int>> first_positions;
std::set<std::pair<int, int>> second_positions;

int ANS_2_1[int(1e4)];
int ANS_2_2[int(1e4)];

std::deque<int> BFS_path_king;
std::deque<int> BFS_path_horse;


int ind_dg(int i, int j, int m) //преобразует двумерный массив в одномерные координаты
{
    return i * m + j;
}


bool in(std::set<std::pair<int, int>>& A, int i, int j)
{
    return A.find(std::make_pair(i, j)) != A.end();
}


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
    int Shag[16] = {-2, 1,   -2, 3,    -1,-1,    -1, 3,    1, -3,    1, 1,    2, -3,    2,-1};
    // Первый ход
    for (int k = 0; k < 8; k++)
    {
        int new_row_h = ind_row + Shag[2 * k];
        int new_column_h = ind_column + Shag[2 * k + 1];
        if (check_correctness(n, m, new_row_h, new_column_h))
        {
            first_positions_h.insert({ new_row_h , new_column_h });
        }
    }
    for (std::set<std::pair<int, int>>::iterator it = first_positions_h.begin(); it != first_positions_h.end(); it++)
    {
        for (int j = 0; j < 16; j++)
        {
            int new_row_ = it->first + Shag[2 * j];
            int new_column_ = it->second + Shag[2 * j + 1];
            if (check_correctness(n, m, new_row_, new_column_))
            {
                second_positions_h.insert({ new_row_, new_column_ });
            }
        }
    }
    for (std::set<std::pair<int, int>>::iterator it = second_positions_h.begin(); it != second_positions_h.end(); it++)
    {
        std::cout << "Row: " << it->first + 1 << ", Column: " << it->second + 1 << std::endl;
    }


   std::cout << "KING" << std::endl;
   // Ходы короля
   int Shag_k[8] = {0, 1,   0, -1,     1, -1,    -1, 1};

   for (int k = 0; k < 4; k++)
   {
       int new_row = ind_row + Shag_k[2 * k];
       int new_column = ind_column + Shag_k[2 * k + 1];
       if (check_correctness(n, m, new_row, new_column))
       {
           first_positions.insert({ new_row, new_column});
       }
   }
   for (std::set<std::pair<int, int>>::iterator it = first_positions.begin(); it != first_positions.end(); it++)
   {
       for (int j = 0; j < 4; j++)
       {
           int new_row1 = it->first + Shag_k[2 * j];
           int new_column1 = it->second + Shag_k[2 * j + 1];
           if (check_correctness(n, m, new_row1, new_column1))
           {
               second_positions.insert({ new_row1, new_column1 });
           }
       }
   }
   for (std::set<std::pair<int, int>>::iterator it = second_positions.begin(); it != second_positions.end(); it++)
   {
       std::cout << "Row: " << it->first + 1 << ", Column: " << it->second + 1 << std::endl;
   }
    std::cout << std::endl;
}


//функция вывода пути
void path_output(int n, int m, int* path, int i) 
{
    if (path[i] != -1) {
        i = path[i];
        path_output(n, m, path, i);
        std::cout << i << ' ';
    }
}

void BFS_short_horse(int n, int m)
{
    int s, f;
    std::cout << std::endl;
    int start_row, start_column, finish_row, finish_column;

    std::cout << "HORSE" << std::endl;
    std::cout << "Input N(row), N(column) of start: ";
    std::cin >> start_row >> start_column;
    std::cout << std::endl;
    std::cout << "Input N(row), N(column) of finish: ";
    std::cin >> finish_row >> finish_column;

    start_row--;
    start_column--;
    finish_row--;
    finish_column--;

    if (!check_correctness(n, m, start_row, start_column))
    {
        std::cout << "Wrong input" << std::endl;
        return;
    }
    if (!check_correctness(n, m, finish_row, finish_column))
    {
        std::cout << "Wrong input" << std::endl;
        return;
    }

    int Shag[16] = { -2, 1,   -2, 3,    -1,-1,    -1, 3,    1, -3,    1, 1,    2, -3,    2,-1 };

    int* G = new int[n * n * m * m];
    for (int i = 0; i < n * n * m * m; i++)
    {
        G[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (check_correctness(n, m, i + Shag[2 * k], j + Shag[2 * k + 1]))
                {
                    G[ind_dg(ind_dg(i, j, m), ind_dg(i + Shag[2 * k], j + Shag[2 * k + 1], m), m * n)] = 1;
                }
            }
        }
    }

    s = ind_dg(start_row, start_column, m);
    f = ind_dg(finish_row, finish_column, m);
    int res = 0;

    int* Mark = new int[n * m];
    int* Len = new int[n * m];
    int* path = new int[n * m];

    for (int i = 0; i < n * m; i++)
    {
        Mark[i] = 0;
        Len[i] = -1;
        path[i] = -1;
    }
    Mark[s] = 1;
    Len[s] = 0;

    std::queue<int>q;
    q.push(s);

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();

        int row = tmp / m;
        int col = tmp % m;

        for (int i = 0; i < 8; i++)
        {
            int new_row = row + Shag[2 * i];
            int new_col = col + Shag[2 * i + 1];

            if (check_correctness(n, m, new_row, new_col))
            {
                int new_index = ind_dg(new_row, new_col, m);
                if (Mark[new_index] == 0)
                {
                    Mark[new_index] = 1;
                    Len[new_index] = Len[tmp] + 1;
                    path[new_index] = tmp; // Запоминаем путь
                    q.push(new_index);
                }
            }
        }
    }

    if (Len[f] != -1)
    {
        // Восстанавливаем путь
        BFS_path_horse.clear();
        for (int v = f; v != -1; v = path[v])
        {
            BFS_path_horse.push_back(v);
        }
    }
    std::cout << std::endl;
    for (auto it = BFS_path_horse.rbegin(); it != BFS_path_horse.rend(); ++it)
    {
        int a = *it;
        a++;
        std::cout << a << " ";
    }

    std::cout << std::endl;

    delete[] Mark;
    delete[] Len;
    delete[] path;
    delete[] G;
}

void BFS_short_king(int n, int m)
{
    int s, f;
    std::cout << std::endl;
    int start_row, start_column, finish_row, finish_column;

    std::cout << "KING" << std::endl;
    std::cout << "Input N(row), N(column) of start: ";
    std::cin >> start_row >> start_column;
    std::cout << std::endl;
    std::cout << "Input N(row), N(column) of finish: ";
    std::cin >> finish_row >> finish_column;

    start_row--;
    start_column--;
    finish_row--;
    finish_column--;

    if (!check_correctness(n, m, start_row, start_column))
    {
        std::cout << "Wrong input" << std::endl;
        return;
    }
    if (!check_correctness(n, m, finish_row, finish_column))
    {
        std::cout << "Wrong input" << std::endl;
        return;
    }

    int Shag_k[8] = { 0, 1,   0, -1,     1, -1,    -1, 1 };

    int* G = new int[n * n * m * m];
    for (int i = 0; i < n * n * m * m; i++)
    {
        G[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (check_correctness(n, m, i + Shag_k[2 * k], j + Shag_k[2 * k + 1]))
                {
                    G[ind_dg(ind_dg(i, j, m), ind_dg(i + Shag_k[2 * k], j + Shag_k[2 * k + 1], m), m * n)] = 1;
                }
            }
        }
    }

    s = ind_dg(start_row, start_column, m);
    f = ind_dg(finish_row, finish_column, m);
    int res = 0;

    int* Mark = new int[n * m];
    int* Len = new int[n * m];
    int* path = new int[n * m];

    for (int i = 0; i < n * m; i++)
    {
        Mark[i] = 0;
        Len[i] = -1;
        path[i] = -1;
    }
    Mark[s] = 1;
    Len[s] = 0;

    std::queue<int>q;
    q.push(s);

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();

        int row = tmp / m;
        int col = tmp % m;

        for (int i = 0; i < 8; i++)
        {
            int new_row = row + Shag_k[2 * i];
            int new_col = col + Shag_k[2 * i + 1];

            if (check_correctness(n, m, new_row, new_col))
            {
                int new_index = ind_dg(new_row, new_col, m);
                if (Mark[new_index] == 0)
                {
                    Mark[new_index] = 1;
                    Len[new_index] = Len[tmp] + 1;
                    path[new_index] = tmp; // Запоминаем путь
                    q.push(new_index);
                }
            }
        }
    }

    if (Len[f] != -1)
    {
        // Восстанавливаем путь
        BFS_path_king.clear();
        for (int v = f; v != -1; v = path[v])
        {
            BFS_path_king.push_back(v);
        }
    }
    std::cout << std::endl;
    for (auto it = BFS_path_king.rbegin(); it != BFS_path_king.rend(); ++it)
    {
        int a = *it;
        a++;
        std::cout << a << " ";
    }

    std::cout << std::endl;

    delete[] Mark;
    delete[] Len;
    delete[] path;
    delete[] G;
}



void display() // Функция для рисования сетки
{
    glClear(GL_COLOR_BUFFER_BIT);
    double sizes = 0.1; // Размер клетки

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double x = -(sizes * m) + sizes * j + (i + 1) * sizes;
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
            if (in(second_positions_h, i, j))
            {
                glColor3f(1.0, 0.0, 0.0);
                glVertex2f(x + 0.03, y + 0.03);
                glVertex2f(x + 0.03, y + sizes - 0.03);
                //
                glVertex2f(x + 0.03, y + sizes - 0.03);
                glVertex2f(x + sizes - 0.03, y + sizes - 0.03);
                //
                glVertex2f(x + sizes - 0.03, y + sizes - 0.03);
                glVertex2f(x + sizes - 0.03, y + 0.03);
                //
                glVertex2f(x + 0.03, y + 0.03);
                glVertex2f(x + sizes - 0.03, y + 0.03);
            }
            if (in(second_positions, i, j))
            {
                glColor3f(0.0, 1.0, 0.0);
                glVertex2f(x + 0.02, y + 0.02);
                glVertex2f(x + 0.02, y + sizes - 0.02);
                //
                glVertex2f(x + 0.02, y + sizes - 0.02);
                glVertex2f(x + sizes - 0.02, y + sizes - 0.02);
                //
                glVertex2f(x + sizes - 0.02, y + sizes - 0.02);
                glVertex2f(x + sizes - 0.02, y + 0.02);
                //
                glVertex2f(x + 0.02, y + 0.02);
                glVertex2f(x + sizes - 0.02, y + 0.02);
            }
            glColor3f(0.0, 1.0, 1.0);
            int ind = 0;
            while (ind + 1 < BFS_path_king.size() && BFS_path_king[ind + 1] != -1) { // Проверка на выход за границы
                glBegin(GL_LINES);
                glVertex2f(-(sizes * m * 0.7) + sizes * (BFS_path_king[ind] % m) + ((BFS_path_king[ind] / m) + 1) * 0.55 * sizes + 0.8 * sizes, // Используем одинаковое смещение по X
                    (sizes * n * 0.5) - sizes * (BFS_path_king[ind] / m) + 0.6 * sizes);
                glVertex2f(-(sizes * m * 0.7) + sizes * (BFS_path_king[ind + 1] % m) + ((BFS_path_king[ind + 1] / m) + 1) * 0.55 * sizes + 0.8 * sizes, // Используем одинаковое смещение по X
                    (sizes * n * 0.5) - sizes * (BFS_path_king[ind + 1] / m) + 0.6 * sizes);

                ind++;
            }

            glColor3f(1.0, 0.0, 1.0);
            ind = 0;
            while (ind + 1 < BFS_path_horse.size() && BFS_path_horse[ind + 1] != -1) { // Проверка на выход за границы
                glBegin(GL_LINES);
                glVertex2f(-(sizes * m * 0.4) + sizes * (BFS_path_horse[ind] % m) + ((BFS_path_horse[ind] / m) + 1) * 0.5 * sizes + 0.7 * sizes,
                    (sizes * n * 0.5) - sizes * (BFS_path_horse[ind] / m) + 0.6 * sizes);
                glVertex2f(-(sizes * m * 0.7) + sizes * (BFS_path_horse[ind + 1] % m) + ((BFS_path_horse[ind + 1] / m) + 1) * 0.5 * sizes + 0.5 * sizes,
                    (sizes * n * 0.5) - sizes * (BFS_path_horse[ind + 1] / m) + 0.6 * sizes);

                ind++;
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
    BFS_short_horse(n, m);
    BFS_short_king(n, m);
    glutMainLoop();

    return 0;
}
