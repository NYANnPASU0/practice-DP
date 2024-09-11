#include <iostream>
#include "glut.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>

const double PI = 3.1415926535;
const double EXP = 2.71;

void draw_coordinate()
{
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    //отрисовка oси Ox
    glVertex2f(-25.0, 0.0);
    glVertex2f(25.0, 0.0);
    //отрисовка oси Oy
    glVertex2f(0.0, 25.0);
    glVertex2f(0.0, -25.0);
    glEnd();
}

double random_point(double min, double max) {
    return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}

double res_integral_a(double x)
{
    return (x * x * std::pow(EXP, x)) / (x * x + 4 * x + 4);
}

double res_integral_b(double x)
{
    return cos(log(x));
}

double res_integral_c(double x)
{
    return (std::pow(x, 4)) / (std::sqrt(4 + std::powf(x, 5)));
}

double res_integral_d(double x)
{
    return 1 / ((std::pow(EXP, x)) + (1 / (std::pow(EXP, x))));
}

//double S_Monte_Carlo_for_a(int N)
//{
//    glPointSize(1.0);
//    glBegin(GL_POINTS);
//    glColor3f(0.0f, 0.5f, 1.0f);
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(0.0, 1.0);
//        double y = random_point(0.0, 1.0);
//        if (y <= res_integral_a(x))
//        {
//            points_inside_k++;
//            glVertex2f(x, y);
//        }
//    }
//    glEnd();
//    glFlush();
//    double S0 = 1.0 * 1.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//double S_Monte_Carlo_for_a_pogr(int N)
//{
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(0.0, 1.0);
//        double y = random_point(0.0, 1.0); points_inside_k++;
//    }
//    double S0 = 1.0 * 1.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//double S_Monte_Carlo_for_b(int N)
//{
//    glPointSize(1.0);
//    glBegin(GL_POINTS);
//    glColor3f(0.0f, 0.5f, 1.0f);
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(PI / 7, (3 * PI) / 7);
//        double y = random_point(0.0, 1.0);
//        if (y <= res_integral_b(x))
//        {
//            points_inside_k++;
//            glVertex2f(x, y);
//        }
//    }
//    glEnd();
//    glFlush();
//    double S0 = 1.0 * 1.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//double S_Monte_Carlo_for_b_pogr(int N)
//{
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(PI / 7, (3 * PI) / 7);
//        double y = random_point(0.0, 1.0);
//        if (y <= res_integral_b(x)) points_inside_k++;
//    }
//    double S0 = 1.0 * 1.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//double S_Monte_Carlo_for_c(int N)
//{
//    glPointSize(1.0);
//    glBegin(GL_POINTS);
//    glColor3f(0.0f, 0.5f, 1.0f);
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(1.0, 8.0);
//        double y = random_point(0.0, 23.0);
//        if (y <= res_integral_c(x))
//        {
//            points_inside_k++;
//            glVertex2f(x, y);
//
//        }
//    }
//    glEnd();
//    double S0 = 7.0 * 23.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    std::cout << "S: " << S << std::endl;
//    return S;
//}

//double S_Monte_Carlo_for_c_pogr(int N)
//{
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(1.0, 8.0);
//        double y = random_point(0.0, 23.0);
//        if (y <= res_integral_c(x)) points_inside_k++;
//    }
//    double S0 = 7.0 * 23.0;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//float S_Monte_Carlo_for_d(int N)
//{
//    glPointSize(1.0);
//    glBegin(GL_POINTS);
//    glColor3f(0.0f, 0.5f, 1.0f);
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(-10.0, -3.0);
//        double y = random_point(0, 0.5);
//        if (y <= res_integral_d(x))
//        {
//            points_inside_k++;
//            glVertex2f(x, y);
//
//        }
//    }
//    glEnd();
//    double S0 = 7.0 * 0.5;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

//float S_Monte_Carlo_for_d_pogr(int N)
//{
//    int points_inside_k = 0;
//    for (int i = 0; i < N; i++)
//    {
//        double x = random_point(-10.0, -3.0);
//        double y = random_point(0, 0.5);
//        if (y <= res_integral_d(x)) points_inside_k++;
//    }
//    double S0 = 7.0 * 0.5;
//    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
//    return S;
//}

double S_Monte_Carlo_for_all(int N, double (*res_integral)(double), double x_1, double x_2, double y_1, double y_2, double s0_1, double s0_2)
{
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.5f, 1.0f);
    int points_inside_k = 0;
    for (int i = 0; i < N; i++)
    {
        double x = random_point(x_1, x_2);
        double y = random_point(y_1, y_2);
        if (y <= res_integral(x))
        {
            points_inside_k++;
            glVertex2f(x, y);
        }
    }
    glEnd();
    glFlush();
    double S0 = s0_1 * s0_2;
    double S = (static_cast<double>(points_inside_k) / static_cast<double>(N)) * S0;
    return S;
}

double rounded_num(double num)
{
    return std::round(num * 100.0) / 100.0;
}


void display() {
    char n;
    std::vector<int> A = { 10, 100, 1000, 10000, 100000, 1000000 };
    std::vector<double> x_and_y = { 0.0, 1.0, 0.4, 1.4, 8.0, 23.0, -10.0, 1.6};
    std::vector<double> for_S0 = { 1.0, 8.0, 23.0 };
    std::vector<double> size = { -2.0, 2.0, -1.0, -23.0, 23.0, -10.0, 3.0, 1.0 };
    glClear(GL_COLOR_BUFFER_BIT);
    draw_coordinate();
    std::cout << "Which integral to derive? " << std::endl;
    std::string a = "\t1\na.\t/ (x^2 * e^x) / (x + 2)^2 dx\n\t0";
    std::string b = "\t3pi/7\nb.\t/ cos(ln(x)) dx\n\tpi/7";
    std::string c = "\t8\nc.\t/ x^4 dx / sqrt(4 + x^5)\n\t1";
    std::string d = "\t-3\nd.\t/ dx / (e^x + e^-x)\n\t-10";
    std::cout << a << '\n' << '\n' << b << '\n' << '\n' << c << '\n' << '\n' << d << '\n' << '\n' << "Enter the number: ";
    std::cin >> n;
    double s1, s2, s3, s4;
    std::cout << std::endl;
    switch (n) {
    case 'a':
        s1 = S_Monte_Carlo_for_all(100,res_integral_a, x_and_y[0], x_and_y[1], x_and_y[0], x_and_y[1], for_S0[0], for_S0[0]);
        std::cout << "S: " << s1 << std::endl;
        std::cout << std::endl;
        std::cout << "relative error: " << std::endl;
        for (int i = 0; i < A.size(); i++)
        {
            double pogr1 = S_Monte_Carlo_for_all(A[i], res_integral_a, x_and_y[0], x_and_y[1], x_and_y[0], x_and_y[1], for_S0[0], for_S0[0]);
            double rounded_s = rounded_num(pogr1);
            double absolutn_pogr = std::abs(pogr1 - rounded_s);
            double otnosit_pogr = std::abs(absolutn_pogr / rounded_s);
            std::cout << "N = " << A[i] << "    "<< "ROUNDED_S: " << rounded_s << "    ABSOLUTE ERROR: " << std::fixed << std::setprecision(4) << absolutn_pogr << "     RELATIVE ERROR: "  << std::fixed << std::setprecision(4) << otnosit_pogr << std::endl;
            std::cout << "S: " << pogr1 << std::endl;
            std::cout << std::endl;
        }
        glutSwapBuffers();
        break;
    case 'b':
        s2 = S_Monte_Carlo_for_all(100, res_integral_b, x_and_y[2], x_and_y[3], x_and_y[0], x_and_y[1], for_S0[0], for_S0[0]);
        std::cout << "S: " << s2 << std::endl;
        std::cout << "relative error: " << std::endl;
        for (int i = 0; i < A.size(); i++)
        {
            double pogr2 = S_Monte_Carlo_for_all(A[i], res_integral_b, x_and_y[2], x_and_y[3], x_and_y[0], x_and_y[1], for_S0[0], for_S0[0]);
            double rounded_s = rounded_num(pogr2);
            double absolutn_pogr = std::abs(pogr2 - rounded_s);
            double otnosit_pogr = std::abs(absolutn_pogr / rounded_s);
            std::cout << "N = " << A[i] << "    " << "ROUNDED_S: " << rounded_s << "    ABSOLUTE ERROR: " << std::fixed << std::setprecision(4) << absolutn_pogr << "     RELATIVE ERROR: " << std::fixed << std::setprecision(4) << otnosit_pogr << std::endl;
            std::cout << "S: " << pogr2 << std::endl;
            std::cout << std::endl;
        }
        glutSwapBuffers();
        break;
    case 'c':
        s3 = S_Monte_Carlo_for_all(100, res_integral_c, x_and_y[1], x_and_y[4], x_and_y[0], x_and_y[5], for_S0[1], for_S0[2]);
        std::cout << "S: " << s3 << std::endl;
        std::cout << "relative error: " << std::endl;
        for (int i = 0; i < A.size(); i++)
        {
            double pogr3 = S_Monte_Carlo_for_all(A[i], res_integral_c, x_and_y[1], x_and_y[4], x_and_y[0], x_and_y[5], for_S0[1], for_S0[2]);
            double rounded_s = rounded_num(pogr3);
            double absolutn_pogr = std::abs(pogr3 - rounded_s);
            double otnosit_pogr = std::abs(absolutn_pogr / rounded_s);
            std::cout << "N = " << A[i] << "    " << "ROUNDED_S: " << rounded_s << "    ABSOLUTE ERROR: " << std::fixed << std::setprecision(4) << absolutn_pogr << "     RELATIVE ERROR: " << std::fixed << std::setprecision(4) << otnosit_pogr << std::endl;
            std::cout << "S: " << pogr3 << std::endl;
            std::cout << std::endl;
        }
        glutSwapBuffers();
        break;
    case 'd':
        s4 = S_Monte_Carlo_for_all(100, res_integral_d, x_and_y[6], x_and_y[0], x_and_y[0], x_and_y[7], for_S0[0], for_S0[0]);
        std::cout << "S: " << s4 << std::endl;
        std::cout << "relative error: " << std::endl;
        for (int i = 0; i < A.size(); i++)
        {
            double pogr4 = S_Monte_Carlo_for_all(A[i], res_integral_d, x_and_y[6], x_and_y[0], x_and_y[0], x_and_y[7], for_S0[0], for_S0[0]);
            double rounded_s = rounded_num(pogr4);
            double absolutn_pogr = std::abs(pogr4 - rounded_s);
            double otnosit_pogr = std::abs(absolutn_pogr / rounded_s);
            std::cout << "N = " << A[i] << "    " << "ROUNDED_S: " << rounded_s << "    ABSOLUTE ERROR: " << std::fixed << std::setprecision(4) << absolutn_pogr << "     RELATIVE ERROR: " << std::fixed << std::setprecision(4) << otnosit_pogr << std::endl;
            std::cout << "S: " << pogr4 << std::endl;
            std::cout << std::endl;
        }
        glutSwapBuffers();
        break;
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(950, 700);
    glutCreateWindow("Task 4");

    glutDisplayFunc(display);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-2, 2, -1, 2);
    glutMainLoop();

    return 0;
}