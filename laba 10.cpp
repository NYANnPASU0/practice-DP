#include<iostream>
#include"сlasses_lab_10.h"
#include<vector>
#include<cmath>
#include<algorithm>
#include<typeinfo>
#include <type_traits>
#include "glut.h"

static int menu_id;
static int submenu_id;
static int submenu_lines;
static int submenu_info;
static int value = 0;

std::vector<Point> ALL_POINTS;
std::vector<Line> ALL_LINES;
std::vector<std::unique_ptr<Shape>> ALL_SHAPES;

void edit_menu()
{
    std::cout << "Выберите, что вы хотите сделать с фигурами: " << std::endl;
    std::cout << "1. Поворот" << std::endl;
    std::cout << "2. Масштаб" << std::endl;
}

void print_all_shapes(int a = 1)
{
    Polygon pol();
    if (ALL_POINTS.size() != 0)
    {
        for (int i = 0; i < ALL_POINTS.size(); i++)
        {
            std::cout << "  " << a + i << ") Точка" << ")\n";
        }
        a += ALL_POINTS.size();
    }
    if (ALL_LINES.size() != 0)
    {
        for (int i = 0; i < ALL_LINES.size(); i++)
        {
            std::cout << "  " << a + i << ") Линия" << '\n';
        }
        a += ALL_LINES.size();
    }
    if (ALL_SHAPES.size() != 0)
    {
        for (int i = 0; i < ALL_SHAPES.size(); i++)
        {
            std::cout << "" << a + i << ") ";
            if (nullptr != dynamic_cast<Circle*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Круг ";
            }
            else if (nullptr != dynamic_cast<Ellipse*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Эллипс ";
            }
            else if (nullptr != dynamic_cast<Square*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Квадрат ";
            }
            else if (nullptr != dynamic_cast<Rectangle*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Прямоугольник ";
            }
            else if (nullptr != dynamic_cast<Triangle*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Треугольник ";
            }
            else if (nullptr != dynamic_cast<Polygon*>(ALL_SHAPES[i].get()))
            {
                std::cout << "Многоугольник ";
            }
            else
            {
                std::cout << "ФИГУР НЕТ <3";
            }
            std::cout << std::endl;
        }
    }
}

void menu(int num)
{
    if (num == 1)
    {
        ALL_POINTS.clear();
        ALL_LINES.clear();
        ALL_SHAPES.clear();
    }
    else if (num == 2)
    {
        std::cout << "координаты точки (x, y): ";
        double x, y;
        std::cin >> x >> y;
        std::cout << std::endl;
        ALL_POINTS.push_back(Point(x, y));
    }
    else if (num == 3)
    {
        std::cout << "Количество вершин: ";
        int count;
        std::cin >> count;
        double x, y;
        std::vector<Point> mnogoug;
        for (int i = 0; i < count; i++)
        {
            std::cout << "Вершина " << i + 1 << "(x, y): ";
            std::cin >> x >> y;
            std::cout << std::endl;
            mnogoug.push_back(Point(x, y));
        }
        ALL_SHAPES.push_back(std::make_unique<Polygon>(mnogoug));
    }
    else if (num == 4)
    {
        double x, y, distancia;
        std::cout << "F1 (x, y): ";
        std::cin >> x >> y;
        Point F1(x, y);
        std::cout << "F2 (x, y): ";
        std::cin >> x >> y;
        Point F2(x, y);
        std::cout << "cумма растояний от фокусов F1, F1 до эллипса: ";
        std::cin >> distancia;
        std::cout << std::endl;
        ALL_SHAPES.push_back(std::make_unique<Ellipse>(F1, F2, distancia));
    }
    else if (num == 5)
    {
        std::cout << "Центр круга O(x, y): ";
        double x, y, radius;
        std::cin >> x >> y;
        std::cout << "Радиус: ";
        std::cin >> radius;
        std::cout << std::endl;
        ALL_SHAPES.push_back(std::make_unique<Circle>(Point(x, y), radius));
    }
    else if (num == 6)
    {
        double x, y, otn;
        std::cout << "Вершина 1 (нижняя левая (х, у)): ";
        std::cin >> x >> y;
        Point P1(x, y);
        std::cout << "Вершина 2 (верхняя правая (х, у)): ";
        std::cin >> x >> y;
        Point P2(x, y);
        std::cout << "Отношение(1/x) (введите x): ";
        std::cin >> otn;
        std::cout << std::endl;
        ALL_SHAPES.push_back(std::make_unique<Rectangle>(P1, P2, otn));
    }
    else if (num == 7)
    {
        double x, y;
        std::cout << "Вершина 1 (нижняя левая (х, у)): ";
        std::cin >> x >> y;
        Point P1(x, y);
        std::cout << "Вершина 2 (верхняя правая (х, у)): ";
        std::cin >> x >> y;
        std::cout << std::endl;
        Point P2(x, y);
        ALL_SHAPES.push_back(std::make_unique<Square>(P1, P2));

    }
    else if (num == 8)
    {
        int count_versh = 3;
        double x, y;
        std::vector<Point> trianglee;
        for (int i = 0; i < count_versh; i++)
        {
            std::cout << "Вершина " << i + 1 << "(x, y): ";
            std::cin >> x >> y;
            trianglee.push_back(Point(x, y));
        }
        ALL_SHAPES.push_back(std::make_unique<Triangle>(trianglee));
        std::cout << std::endl;
    }
    else if (num == 9)
    {
        double x, y;
        std::cout << "Введите 1 точку(x, y): ";
        std::cin >> x >> y;
        Point P1(x, y);
        std::cout << "Введите 2 точку(x, y): ";
        std::cin >> x >> y;
        std::cout << std::endl;
        Point P2(x, y);
        ALL_LINES.push_back(Line(P1, P2));
    }
    else if (num == 10)
    {
        double k, b;
        std::cout << "Введите k (коэффицент наклона): ";
        std::cin >> k;
        std::cout << "Введите b (сдвиг по оси х): ";
        std::cin >> b;
        std::cout << std::endl;
        ALL_LINES.push_back(Line(k, b));
    }
    else if (num == 12)
    {
        int ind, a;
        a = 1;
        std::cout << "Можно изменить:" << std::endl << std::endl;
        print_all_shapes();
        std::cin >> ind;
        if (ind > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size())
        {
            std::cout << "Число введено неверно.";
        }
        else
        {
            //изменение фигуры
            if (ind > ALL_POINTS.size() + ALL_LINES.size())
            {
                ind -= ALL_POINTS.size() + ALL_LINES.size() + 1;
                int p;
                edit_menu();
                std::cin >> p;
                switch (p)
                {
                case 1:
                    double x_, y, deg;
                    std::cout << "Введите центр вращения (x, y): ";
                    std::cin >> x_ >> y;
                    std::cout << "Градусы: ";
                    std::cin >> deg;
                    ALL_SHAPES[ind]->rotate(Point(x_, y), deg);
                    break;
                case 2:
                    std::cout << "Введите центр вращения (x, y): ";
                    std::cin >> x_ >> y;
                    std::cout << "Коэффицент масштабирования: ";
                    std::cin >> deg;
                    ALL_SHAPES[ind]->scale(Point(x_, y), deg);
                    break;
                }
            }
            else
            {
                std::cout << "Нельзя изменить" << std::endl;
            }
        }
    }
    else if (num == 13) {
        int a ,ind;
        a = 1;
        std::cout << "Можно удалить: " << std::endl;
        print_all_shapes();
        std::cin >> ind;
        if (ind > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size())
        {
            std::cout << "Введено неверно" << std::endl;
        }
        //фигуры(вычисление индекса)
        else if (ind >= ALL_POINTS.size() + ALL_LINES.size())
        {
            ind += -1 - ALL_POINTS.size() - ALL_LINES.size();
            std::vector< std::unique_ptr<Shape>>::iterator pos = ALL_SHAPES.begin() + ind;
            ALL_SHAPES.erase(pos);
        }
        //линии
        else if (ind >= ALL_POINTS.size())
        {
            ind += -1 - ALL_POINTS.size();
            std::vector<Line> ::iterator pos = ALL_LINES.begin() + ind;
            ALL_LINES.erase(pos);
        }
        else
        {
            std::vector<Point> ::iterator pos = ALL_POINTS.begin() + ind - 1;
            ALL_POINTS.erase(pos);
        }

    }
    else if (num == 14)
    {
        int a, x;
        a = 1;
        std::cout << "Периметр какой фигуры получить? ";
        print_all_shapes();
        std::cin >> x;
        if (x > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size())
        {
            std::cout << "Введено неверно." << std::endl;
        }
        //индекс фигуры
        else if (x > ALL_POINTS.size() + ALL_LINES.size())
        {
            x -= ALL_POINTS.size() + ALL_LINES.size() + 1;
            std::cout << "P = " << ALL_SHAPES[x]->perimetr() << std::endl << std::endl;
        }
        else
        {
            std::cout << "P = " << 0 << std::endl;
        }
    }
    else if (num == 15)
    {
        int a = 1, x;
        std::cout << "Площадь какой фигуры получить??";
        print_all_shapes();
        std::cin >> x;
        if (x > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size())
        {
            std::cout << "Введено невернo." << std::endl;
        }
        else if (x > ALL_POINTS.size() + ALL_LINES.size())
        {
            x -= 1 + ALL_POINTS.size() + ALL_LINES.size();
            std::cout << "S = " << ALL_SHAPES[x]->area() << std::endl << std::endl;
        }
        else
        {
            std::cout << "S = " << 0 << std::endl;
        }
    }

    else if (num == 16)
    {
        int a = 1;
        int i, j;
        std::cout << "Какие фигуры проверить на равенство? " << std::endl;
        print_all_shapes();
        std::cout << "Введите номера: ";
        std::cin >> i >> j;
        i--;
        j--;
        if (i != j)
        {
            if ((*ALL_SHAPES[i]) == (*ALL_SHAPES[j]))
            {
                std::cout << "Равны" << std::endl;
            }
            else
            {
                std::cout << "Не равны" << std::endl;
            }
        }
        else
        {
            std::cout << "нельзя вводить одну и ту же фигуру" << std::endl;
        }
    }
    else if (num == 17)
    {
        int a = 1;
        std::cout << "Какие фигуры сравнить?" << std::endl;
        print_all_shapes();
        int i, j;
        std::cout << "Введите номера: ";
        std::cin >> i >> j;
        i--;
        j--;
        if (i != j)
        {
            if (i > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size() || j > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size() ||
                i <= ALL_POINTS.size() + ALL_LINES.size() || j <= ALL_POINTS.size() + ALL_LINES.size())
            {
                std::cout << "Неверное число" << std::endl;
            }
            else
            {
                i -= 1 + ALL_POINTS.size() + ALL_LINES.size();
                j -= 1 + ALL_POINTS.size() + ALL_LINES.size();
                if (ALL_SHAPES[i]->isCongruentTo(*ALL_SHAPES[j]))
                {
                    std::cout << "Фигуры подобны" << std::endl;
                }
                else
                {
                    std::cout << "Фигуры не подобны" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "нельзя вводить одну и ту же фигуру" << std::endl ;
        }
    }
    else if (num == 18)
    {
        int a = 1;
        std::cout << "У каких фигур узнать подобие?" << std::endl;
        print_all_shapes();
        int i, j;
        std::cout << "Введите номера: ";
        std::cin >> i >> j;
        if (i != j)
        {
            if (i > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size() || j > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size() ||
                i <= ALL_POINTS.size() + ALL_LINES.size() || j <= ALL_POINTS.size() + ALL_LINES.size())
            {
                std::cout << "Неверный ввод!\n";
            }
            else
            {
                i -= 1 + ALL_POINTS.size() + ALL_LINES.size();
                j -= 1 + ALL_POINTS.size() + ALL_LINES.size();
                if (ALL_SHAPES[i]->isSimilarTo(*ALL_SHAPES[j]))
                {
                    std::cout << "Подобны" << std::endl;
                }
                else
                {
                    std::cout << "Не подобны" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "нельзя вводить одну и ту же фигуру" << std::endl;
        }
    }
    else if (num == 19)
    {
        int a, x;
        a = 1;
        std::cout << "Выбрать фигуру?" << std::endl;
        print_all_shapes();
        std::cin >> x;
        x--;
        double i, j;
        std::cout << "Введите координаты точки (x, y): ";
        std::cin >> i >> j;
        Point P(i, j);
        if (x > ALL_POINTS.size() + ALL_LINES.size() + ALL_SHAPES.size())
        {
            std::cout << "Введено неверно!\n";
        }
        else if (x > ALL_POINTS.size() + ALL_LINES.size())
        {
            x -= 1 + ALL_POINTS.size() + ALL_LINES.size();
            if (ALL_SHAPES[x].get()->containsPoint(P))
            {
                std::cout << "True" << std::endl;
            }
            else
            {
                std::cout << "False" << std::endl;
            }

        }
        else if (x > ALL_POINTS.size())
        {
            x -= 1 + ALL_POINTS.size();
            if (P.y == ALL_LINES[x].k * P.x + ALL_LINES[x].b)
            {
                std::cout << "True" << std::endl;
            }
            else
            {
                std::cout << "False" << std::endl;
            }

        }
        else
        {
            if (ALL_POINTS[x - 1] == P)
            {
                std::cout << "True" << std::endl;
            }
            else
            {
                std::cout << "False" << std::endl;
            }
        }
    }
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(199.0f / 255.0f, 189.0f / 255.0f, 189.0f / 255.0f);

    for (double x = -1.0f; x <= 1.0f; x += 0.01f)
    {
        for (double y = -1.0f; y <= 1.0f; y += 0.01f)
        {
            glBegin(GL_LINE_LOOP);
            glVertex2f(x - 0.1f, y - 0.1f);
            glVertex2f(x + 0.1f, y - 0.1f);
            glVertex2f(x + 0.1f, y + 0.1f);
            glVertex2f(x - 0.1f, y + 0.1f);
            glEnd();
        }
    }
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    glFlush();

    for (int i = 0; i < ALL_POINTS.size(); i++)
    {
        glPointSize(3.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
        glVertex2f((double)(ALL_POINTS[i].x / 100.0), (double)(ALL_POINTS[i].y / 100.0));
        glEnd();
        glFlush();
    }
    for (int i = 0; i < ALL_LINES.size(); i++)
    {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glColor3f(0.0f / 255.0f, 103.0f / 255.0f, 199.0f / 255.0f);
        glVertex2f(-1, ALL_LINES[i].k * -1.0 + ALL_LINES[i].b / 100.0);
        glVertex2f(1, ALL_LINES[i].k * 1.0 + ALL_LINES[i].b / 100.0);
        glEnd();
        glFlush();
    }
    for (int i = 0; i < ALL_SHAPES.size(); i++)
    {
        ALL_SHAPES[i]->glutDraw();
        glEnd();
        glFlush();
    }
}

void createMenu()
{
    submenu_lines = glutCreateMenu(menu);
    glutAddMenuEntry("по 2-ум точкам", 9);
    glutAddMenuEntry("kx + b", 10);

    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Точка", 2);
    glutAddSubMenu("Линия", submenu_lines);
    glutAddMenuEntry("Многоугольник", 3);
    glutAddMenuEntry("Эллипс", 4);
    glutAddMenuEntry("Круг", 5);
    glutAddMenuEntry("Прямоугольник", 6);
    glutAddMenuEntry("Квадрат", 7);
    glutAddMenuEntry("Треугольник", 8);

    submenu_info = glutCreateMenu(menu);
    glutAddMenuEntry("Периметр", 14);
    glutAddMenuEntry("Площадь", 15);
    glutAddMenuEntry("Равенство", 16);
    glutAddMenuEntry("Подобие", 18);

    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Очистить всё", 1);
    glutAddSubMenu("Добавить фигуру", submenu_id);
    glutAddMenuEntry("Изменить фигуру", 12);
    glutAddMenuEntry("Удалить фигуру", 13);
    glutAddSubMenu("Доп. функции", submenu_info);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "RU");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(1250, 900);
    glutInitWindowPosition(300, 10);
    glutCreateWindow("laba 10");
    createMenu();
    glClearColor(1, 1, 1, 1.0);
    gluOrtho2D(-1.0, 1.0, -0.7, 0.7);
    glutDisplayFunc(display);
    glutMainLoop();
}

