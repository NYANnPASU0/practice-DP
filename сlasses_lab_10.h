#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>
#include "glut.h"

double Pi = 3.1415926535;

class Point
{
public:
    double x, y;

    Point()
    {
        x = 0;
        y = 0;
    }

    Point(double x_, double y_)
    {
        x = x_;
        y = y_;
    }

    void Display()
    {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    Point operator=(Point p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }

    friend bool operator ==(const Point& a, const Point& b)
    { 
        return a.x == b.x && a.y == b.y;
    }

    friend bool operator !=(const Point& a, const Point& b)
    {
        return !(a == b); 
    }

    Point& operator+=(const Point& P)
    {
        x += P.x;
        y += P.y;
        return *this;
    }

    Point& operator-=(const Point& P)
    {
        x -= P.x;
        y -= P.y;
        return *this;
    }

    Point operator/(const double k)  const
    {
        return Point(x / k, y / k);
    }

    Point operator*(const double k) const
    {
        return Point(x * k, y * k);
    }

    Point operator+(const Point& P2) const
    {
        Point tmp = *this;
        return (tmp += P2);
    }

    Point operator-() const
    {
        return Point(-x, -y);
    }

    Point operator-(const Point& P2) const
    {
        Point tmp = *this;
        return (tmp += -P2);
    }

    Point rotate(Point P, double angle) //P - точка вращения
    {
        double deg = angle * Pi / 180.0; //преобразование в радианы
        double x, y;
        x = P.x + (this->x - P.x) * cosf(deg) - (this->y - P.y) * sinf(deg);
        y = P.y + (this->x - P.x) * sinf(deg) + (this->y - P.y) * cosf(deg);
        return Point(x, y);
    }

};

long double dist2(Point X, Point Y) //расстояние между точками
{
    Point Z = X - Y;
    return Z.x * Z.x + Z.y * Z.y;
}

double cross(Point a, Point b)
{
    double rez;
    rez = a.x * b.y - a.y * b.x;
    return rez;
}

class Line
{
public:
    Point A;
    Point B;

    double k;
    double b;

    Line()
    {
        k = 0;
        b = 0;
    }

    Line(Point P1, Point P2)
    {
        A = P1, B = P2;
        k = ((P2.y - P1.y) / (P2.x - P1.x));
        b = -k * P1.x + P1.y;
    }

    Line(double k_, double b_)
    {
        k = k_;
        b = b_;
    }

    Line(Point P1, double coeffic)
    {
        A = P1;
        k = coeffic;
        b = -k * P1.x + P1.y;
        B = Point(P1.x + 1, k * (P1.x + 1) + b);
    }

    bool operator==(const Line other)
    {
        return ((other.k == this->k) && (other.b == this->b));
    }

    bool operator!=(const Line other)
    {
        return !(*this == other);
    }

    void Display()
    {
        std::cout << " y = " << k << " * x ";
        if (b > 0)
        { 
            std::cout << "+ " << b;
        }
        else
        {
            std::cout << b;
        }
        std::cout << std::endl;
    }
};

class Shape
{
public:
    Shape() {}

    const double eps = 0.0001;

    virtual bool operator==(const Shape& another) const = 0;
    virtual bool operator!=(const Shape& another) const = 0;

    virtual bool isCongruentTo(const Shape& another) const = 0; //равна ли фигура другой в геометрическом смысле

    virtual double size() const = 0;

    virtual bool isSimilarTo(const Shape& another) const = 0; //подобна ли фигура другой
    virtual bool containsPoint(const Point& point) const = 0; //находится ли точка внутри фигуры

    virtual void rotate(Point center, double deg) = 0; //роворот на угол(в градусах)
    virtual void reflex(Point center) = 0; //симметрия относительно точки
    virtual void reflex(Line axis) = 0; //симметрия относительно прямой
    virtual void scale(Point center, const double& coefficient) = 0; //подобие

    virtual double area() const = 0; //площадь
    virtual double perimetr() const = 0;

    virtual void glutDraw() = 0;
    virtual std::string getInfo() = 0;

    Point Scale(const Point center, const Point& P, const double& coeff) const
    {
        return center + (P - center) * coeff;
    }

    Point Reflex(const Point& P, const Point& center)
    {
        return center * 2 - P;
    }

    Point Reflex(const Point& P, const Line& L)
    {
        Line line = perpendicular(L, P);
        Point center = intersect(line, L);
        return Reflex(P, center);
    }

    Point Rotate(const Point& center, const Point& P, const double angle)
    {
        double x = P.x - center.x;
        double y = P.y - center.y;
        double radians = Pi * angle / 180;
        return center + Point(x * cos(radians) - y * sin(radians), x * sin(radians) + y * cos(radians));
    }

    Line perpendicular(const Line& L, const Point& P1)
    {
        Point P2 = Point(P1.x + L.k, P1.y + (-1));
        return Line(P1, P2);
    }

    Point intersect(const Line& L1, const Line& L2) const
    {
        double a = -L1.b * (-1) + L2.b * (-1);
        double b = -L1.k * L2.b + L2.k * L1.b;
        double det = Det(L1, L2);
        return Point(a / det, b / det);
    }

    double Det(const Line& L1, const Line& L2) const
    {
        return L1.k * (-1) - (-1) * L2.k;
    }

    double Det(double a, double a1, double b, double b1) const
    {
        return a * b1 - b * a1;
    }

    double cross_product(const Point P1, const Point P2) const
    { 
        return P2.y * P1.x - P2.x * P1.y;
    }

    double Sin(const Point P1, const Point P2) const
    {
        return (P2.y * P1.x - P2.x * P1.y) / (sqrt(P1.x * P1.x + P1.y * P1.y) * sqrt(P2.x * P2.x + P2.y * P2.y));
    }

    double Sin(const Line L1, const Line L2) const
    {
        return Sin(Point(-1, L1.k), Point(-1, L2.k));
    }

    double Cos(const Point P1, const Point P2) const
    {
        return (P1.x * P2.x + P1.y * P2.y) / (sqrt(P1.x * P1.x + P1.y * P1.y) * sqrt(P2.x * P2.x + P2.y * P2.y));
    }

    double Cos(const Line L1, const Line L2) const
    {
        return Cos(Point(-1, L1.k), Point(-1, L2.k));
    }

    double Sin2(const Line L1, const Line L2) const
    {
        return 2 * Sin(L1, L2) * Cos(L1, L2);
    }

    double dist(const Point& P1, const Point& P2) const
    {
        return sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));
    }

    bool on_the_line(const Line& L1, const Point& p) const
    {
        return (p.y == L1.k * p.x + L1.b);
    }

    int direction(const Point& a, const Point& b, const Point& c) const
    {
        int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if (val == 0)
        {
            return 0;
        }
        else if (val < 0)
        {
            return 2;
        }
        return 1;
    }

    bool isIntersect(const Line& l1, const Line& l2) const
    {
        if (on_the_line(l1, l2.A) || on_the_line(l1, l2.B) || on_the_line(l2, l1.A) || on_the_line(l2, l1.B))
        {
            return true;
        }
        int d1 = direction(l1.A, l1.B, l2.A);
        int d2 = direction(l1.A, l1.B, l2.B);
        int d3 = direction(l2.A, l2.B, l1.A);
        int d4 = direction(l2.A, l2.B, l1.B);
        if (d1 != d2 && d3 != d4)
        {
            return true;
        }
        return false;
    }

    bool equal(double& a, double& b) const
    {
        return abs(a - b) < eps;
    }

    ~Shape() {}
};

long double sin(Point a, Point b)
{
    long double rez;
    long double len1 = sqrt(dist2(Point(0, 0), a));
    long double len2 = sqrt(dist2(Point(0, 0), b));
    rez = cross(a, b) / (len1 * len2);
    return rez;
}

class Polygon : public Shape
{
public:
    int size_;
    std::vector<Point> points;

    Polygon()
    {
        size_ = 0;
    }

    Polygon(const std::vector<Point>& p_)
    {
        size_ = p_.size();
        points = p_;
    }

    Polygon& operator=(const Polygon& P)
    {
        size_ = P.size_;
        for (int i = 0; i < size_; i++)
        {
            points[i] = P.points[i];
        }
        return *this;
    }

    Point Next(int pos) const
    {
        return points[(pos + 1) % size_];
    }

    Point Prev(int pos) const
    {
        return  points[(pos - 1 + size_) % size_];
    }

    double perimetr() const
    {
        double Per = 0;
        for (int i = 0; i < size_; i++)
        {
            Per += dist(Prev(i), points[i]);
        }
        return Per;
    }

    double area() const
    {
        double S = 0;
        for (int i = 0; i < size_; i++)
        {
            S += Det(points[i].x, points[i].y, Next(i).x, Next(i).y);
        }
        return 0.5 * abs(S);
    }

    int verticesCount() const
    {
        return size_;
    }

    std::vector<Point> getVertices() const
    {
        return points;
    }

    Point centroid() const
    {
        double x = 0;
        double y = 0;
        for (int i = 0; i < size_; i++)
        {
            x += points[i].x;
            y += points[i].y;
        }
        return Point(x / size_, y / size_);
    }

    bool operator==(const Shape& other) const
    {
        if (dynamic_cast<const Polygon*>(&other) == NULL)
        {
            return false;
        }
        const Polygon& Other = dynamic_cast<const Polygon&>(other);
        if (size_ != Other.size_ || this->points != Other.points)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    bool operator!=(const Shape& other) const
    {
        return !(*this == other);
    }


    bool isSimilarTo(const Shape& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Polygon*>(&other) == NULL)
        {
            return false;
        }
        const Polygon& Other = dynamic_cast<const Polygon&>(other);
        if (size_ != Other.size_)
            return false;

        std::vector<long double> angels1;
        std::vector<long double> angels2;

        int n = other.size();

        for (int i = 1; i <= n; i++)
        {
            Point vec1(points[i - 1] - points[i % n]);
            Point vec2(points[(i + 1) % n] - points[i % n]);
            angels1.push_back(sin(vec1, vec2));
        }
        for (int i = 1; i <= n; i++)
        {
            Point vec1(Other.points[i - 1] - Other.points[i % n]);
            Point vec2(Other.points[(i + 1) % n] - Other.points[i % n]);
            angels2.push_back(sin(vec1, vec2));
        }
        for (int i = 0; i < n; i++)
        {
            angels1.push_back(angels1[i]);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n && abs(angels1[i + j] - angels2[j]) < 0.00001; j++)
            {
                if (j == n - 1)
                {
                    return true;
                }
            }
        }
        reverse(angels1.begin(), angels1.end());
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n && abs(angels1[i + j] - angels2[j]) < 0.00001; j++)
            {
                if (j == n - 1)
                {
                    return true;
                }
            }
        }
        return false;
    }


    bool isCongruentTo(const Shape& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Polygon*>(&other) == NULL)
        {
            return false;
        }
        const Polygon& Other = dynamic_cast<const Polygon&>(other);
        if (size_ != Other.size_)
        {
            return false;
        }
        if (!isSimilarTo(other))
        {
            return false;
        }
        bool flag = true;
        for (int i = 0; i < size_; i++)
        {
            for (int j = 0; j < size_; j++)
            {
                if (dist(points[i], Next(i)) != dist(Other.points[i], Other.Next(i)))
                {
                    flag = false;
                    break;
                }
            }
            if (flag == true)
            {
                break;
            }
        }
        return flag;
    }

    bool containsPoint(const Point& point) const
    {
        if (points.size() < 3)
        {
            return false;
        }
        Line big_horizontal_line = { point, { std::numeric_limits<double>::max(), point.y } };
        int count = 0;
        for (size_t i = 0; i < points.size(); i++)
        {
            Line side = { points[i], points[(i + 1) % points.size()] };
            if (isIntersect(side, big_horizontal_line) && direction(side.A, point, side.B) != 0)
            {
                count++;
            }
        }
        return count % 2 == 1;
    }

    bool isConvex()
    {
        double check = 0;
        for (int i = 0; i < size_; i++)
        {
            double check_2 = cross_product(Next(i) - points[i], Prev(i) - points[i]);
            if (check * check_2 < 0)
            {
                return false;
            }
            check = check_2;
        }
        return true;
    }

    void rotate(Point center, double deg)
    {
        for (int i = 0; i < size_; i++)
        {
            points[i] = Rotate(center, points[i], deg);
        }
    }

    void reflex(Point center)
    {
        for (int i = 0; i < size_; i++)
        {
            points[i] = Reflex(points[i], center);
        }
    }

    void reflex(Line axis)
    {
        for (int i = 0; i < size_; i++)
        {
            points[i] = Reflex(points[i], axis);
        }
    }

    void scale(Point center, const double& coefficient)
    {
        for (int i = 0; i < size_; i++)
        {
            points[i] = Scale(center, points[i], coefficient);
        }
    }

    void glutDraw()
    {
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.5f);
        for (int i = 1; i < points.size(); i++)
        {
            glVertex2f(points[i - 1].x / 100, points[i - 1].y / 100);
            glVertex2f(points[i].x / 100, points[i].y / 100);
        }
        glVertex2f(points[points.size() - 1].x / 100, points[points.size() - 1].y / 100);
        glVertex2f(points[0].x / 100, points[0].y / 100);
        glEnd();
        glFlush();
    }

    std::string getInfo()
    {
        std::string str = "";
        if (this->points.size() > 0)
        { 
            str += "" + std::to_string(points[0].x) + ", " + std::to_string(points[0].y) + "";
        }
        return str;
    }

    double size() const
    {
        return points.size();
    }

    void Display()
    {
        for (int i = 0; i < size_; i++)
        {
            points[i].Display();
        }
    }
};


class Ellipse : public Shape
{
public:
    Point A, B;
    double a, b, c, d;

    Ellipse()
    {
        A = Point(0, 0);
        B = Point(0, 0);
        a = 0;
        b = 0;
        c = 0;
        d = 0;
    }

    Ellipse(const Point P1, const Point P2, double D)
    {
        A = P1;
        B = P2;
        d = D;
        a = D / 2;
        c = dist(P1, P2) / 2;
        b = sqrtf(abs(a * a - c * c));
    }

    virtual ~Ellipse() = default;

    Ellipse& operator=(const Ellipse& E)
    {
        A = E.A;
        B = E.B;
        d = E.d;
        return *this;
    }
    double perimetr() const
    {
        return (4 * Pi * a * b + (a - b) * 2) / (a + b);
    }

    double area() const
    {
        return Pi * a * b;
    }

    Point center() const
    {
        return (A + B) / 2;
    }

    std::pair<Point, Point> focuses() const
    {
        return std::make_pair(A, B);
    }

    std::pair<Line, Line> directrices()
    {
        double distance = dist(A, B);
        double D = d / (2 * eccentricity());
        double a = B.x - A.x;
        double b = B.y - A.y;
        double x1 = A.x + a * (D + distance / 2) / distance;
        double y1 = A.y + b * (D + distance / 2) / distance;
        double x2 = B.x - a * (D + distance / 2) / distance;
        double y2 = B.y - b * (D + distance / 2) / distance;
        Point p1(x1, y1);
        Point p2(x2, y2);
        x1 = x1 - b;
        x2 = x2 - b;
        y1 = y1 + a;
        y2 = y2 + a;
        Point p3(x1, y1);
        Point p4(x2, y2);
        return std::make_pair(Line(p1, p3), Line(p2, p4));
    }

    double eccentricity()
    {
        return dist(A, B) / d;
    }

    bool containsPoint(const Point& P) const
    {
        if (dist(A, P) + dist(B, P) > eps + d)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void rotate(Point center, double deg)
    {
        A = Rotate(center, A, deg);
        B = Rotate(center, B, deg);
    }

    void reflex(Point center)
    {
        A = Reflex(A, center);
        B = Reflex(B, center);
    }

    void reflex(Line axis)
    {
        A = Reflex(A, axis);
        B = Reflex(B, axis);
    }
    void scale(Point c, const double& coe)
    {
        this->A = Scale(c, A, coe);
        this->B = Scale(c, B, coe);
        this->a *= coe;
        this->b *= coe;
        this->c *= coe;
        this->d *= coe;

    }

    std::string getInfo()
    {
        std::string str = "";
        str += "F1(x, y) : " + std::to_string(this->A.x) + ", " + std::to_string(this->A.y) + ",  F2(x, y) : " + std::to_string(this->B.x) + ", " + std::to_string(this->B.y) + "";
        return str;
    }

    bool operator==(const Shape& other) const
    {
        if (dynamic_cast<const Ellipse*>(&other) == NULL)
        {
            return false;
        }
        const Ellipse& Other = dynamic_cast<const Ellipse&>(other);
        if (abs(dist2(A, B) - dist2(Other.A, Other.B)) < 0.0001 && d == Other.d)
        {
            return true;
        }
        else
        { 
            return false;
        }
    }

    bool operator!=(const Shape& other) const 
    {
        return !(*this == other);
    }

    bool isCongruentTo(const Shape& other) const
    {
        if (dynamic_cast<const Ellipse*>(&other) == NULL)
        {
            return false;
        }
        const Ellipse& Other = dynamic_cast<const Ellipse&>(other);
        if (dist(A, B) == dist(Other.A, Other.B) && d == Other.d)
        { 
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isSimilarTo(const Shape& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Ellipse*>(&other) == NULL)return false;
        const Ellipse& otherEllipse = static_cast<const Ellipse&>(other);
        double ratio1 = a / otherEllipse.a;
        double ratio2 = b / otherEllipse.b;
        if (abs(ratio1 - ratio2) > eps)
        {
            return false;
        }
        if (A != otherEllipse.A)
        {
            return false;
        }
        return true;
    }

    bool operator==(const Ellipse& other) const
    {
        return abs(a - other.a) < eps && abs(b - other.b) < eps;
    }



    void glutDraw()
    {
        double pointCount = 50;
        float step = double(2 * Pi / pointCount);
        double deg;
        if (A != B)
        {
            deg = atan((B.y - A.y) / (B.x - A.x));
        }
        else
        {
            deg = 0;
        }
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.5f);
        double dx = a / 100 * cosf(-step);
        double dy = b / 100 * sinf(-step);
        Point Cen = (A + B) / 200;
        double xb, yb, x, y;
        for (double angle = 0; angle < double(2 * Pi); angle += step)
        {
            xb = dx + Cen.x;
            yb = dy + Cen.y;
            x = Cen.x + (xb - Cen.x) * cosf(deg) - (yb - Cen.y) * sinf(deg);
            y = Cen.y + (xb - Cen.x) * sinf(deg) + (yb - Cen.y) * cosf(deg);
            glVertex2f(x, y);
            dx = a / 100 * cosf(angle);
            dy = b / 100 * sinf(angle);
            xb = dx + Cen.x;
            yb = dy + Cen.y;
            x = Cen.x + (xb - Cen.x) * cosf(deg) - (yb - Cen.y) * sinf(deg);
            y = Cen.y + (xb - Cen.x) * sinf(deg) + (yb - Cen.y) * cosf(deg);
            glVertex2f(x, y);
        }
        glEnd();
        glFlush();
    }

    double size() const
    {
        return a;
    }
};


class Circle : public Ellipse
{
public:
    Circle() {}

    Circle(Point center, double rad)
    {
        A = center;
        B = center;
        a = rad;
        b = rad;
        d = 2 * rad;
        c = 0;
    }

    ~Circle() {}

    std::string getInfo()
    {
        std::string str = "";
        str += "F1,F2(x ,y) : " + std::to_string(this->A.x) + ", " + std::to_string(this->A.y) + ", radius: " + std::to_string(this->radius());
        return str;
    }

    double radius() const
    {
        return a;
    }

    bool isSimilarTo(const Shape& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Circle*>(&other) == NULL)
        {
            return false;
        }
        const Circle& otherCircle = static_cast<const Circle&>(other);
        if (radius() != otherCircle.radius())
        {
            return true;
        }
        return false;
    }

    double size() const
    {
        return 3, 14 * a * b;
    }
};


class Rectangle :public Polygon
{
public:
    Rectangle() {}

    Rectangle(Point& P1, Point& P3, double k)
    {
        if (k < 1) { k = 1 / k; }
        Point center = (P1 + P3) / 2;
        Point P2 = Rotate(center, P1, 2 * atan(1 / k) * 57.29578);
        Point P4 = Reflex(P2, center);
        points.push_back(P1);
        points.push_back(P2);
        points.push_back(P3);
        points.push_back(P4);
        size_ = 4;
    }

    bool operator==(const Rectangle& other) const
    {
        return area() == other.area();
    }

    Point center()
    {
        return (points[0] + points[2]) / 2;
    }

    std::pair<Line, Line>diagonals()
    { 
        return { Line(points[0], points[2]), Line(points[1], points[3]) };
    }

    ~Rectangle() = default;

    double size() {};
};



class Square : public Rectangle
{
public:
    Square() {}

    Square(Point& P1, Point& P3)
    {
        double tg = 2;
        Point center = (P1 + P3) / 2;
        Point P2 = Rotate(center, P1, 90);
        Point P4 = Reflex(P2, center);
        points.push_back(P1);
        points.push_back(P2);
        points.push_back(P3);
        points.push_back(P4);
        size_ = 4;
    }

    Circle circumscribedCircle() //описанный круг
    {
        Point p = Point((points[0] + points[2]) / 2);
        return Circle(p, dist(p, points[0]));
    }

    Circle inscribedCircle() //вписанный круг
    {
        Point p = Point((points[0] + points[2]) / 2);
        return Circle(p, dist(points[0], points[1]) / 2);
    }

    bool operator==(const Shape& other) const
    {
        const Square& otherSquare = static_cast<const Square&>(other);
        double diagonal1 = dist(points[0], points[2]);
        double diagonal2 = dist(otherSquare.points[0], otherSquare.points[2]);
        if (diagonal1 == diagonal2)
        {
            return true;
        }
        return false;
    }


    bool isSimilarTo(const Square& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Polygon*>(&other) == NULL)
        {
            return false;
        }
        const Square& Another = dynamic_cast<const Square&>(other);
        if (size_ != Another.size_)
        {
            return false;
        }
        const Square& otherSquare = static_cast<const Square&>(other);
        double diagonal1 = dist(points[0], points[2]);
        double diagonal2 = dist(otherSquare.points[0], otherSquare.points[2]);
        if (otherSquare == *this)
        {
            return false;
        }
        return true;
    }

    ~Square() {}

    double size() {};
};


class Triangle : public Polygon
{
public:
    Triangle(std::vector<Point>& g)
    {
        this->size_ = g.size();
        this->points = g;
    }

    Circle circumscribedCircle()
    {
        Point A = points[0];
        Point B = points[1];
        Point C = points[2];
        Line AB(A, B);
        Line BC(B, C); 
        Line CA(C, A);
        Point Circumcenter((A.x * Sin2(CA, AB) + B.x * Sin2(AB, BC) + C.x * Sin2(CA, BC) / (Sin2(CA, AB) + Sin2(AB, BC) +
            Sin2(CA, BC))), ((A.y * Sin2(CA, AB)) + B.y * Sin2(AB, BC) + C.y * Sin2(CA, BC)) / (Sin2(CA, AB) + Sin2(AB, BC) + Sin2(CA, BC)));
        return Circle(Circumcenter, dist(Circumcenter, A));
    }

    Circle inscribedCircle()
    {
        double rad = (2 * area()) / (dist(points[0], points[1]) + dist(points[1], points[2]) + dist(points[2], points[0]));
        Point Center = orthocenter();
        return Circle(Center, rad);
    }

    Point orthocenter()
    {
        Line FirstPerpendicular = perpendicular(Line(points[1], points[2]), points[0]);
        Line SecondPerpendicular = perpendicular(Line(points[2], points[0]), points[1]);
        return intersect(FirstPerpendicular, SecondPerpendicular);
    }

    Line EulerLine()
    {
        return Line(orthocenter(), centroid());
    }

    Circle ninePointsCircle()
    {
        Point EulerCenter((orthocenter() + circumscribedCircle().focuses().first) / 2);
        double EulerRadius = circumscribedCircle().radius() / 2;
        return Circle(EulerCenter, EulerRadius);
    }

    bool operator==(const Shape& other) const
    {
        const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
        if (otherTriangle == NULL)
        {
            return false;
        }
        // Проверка равенства сторон
        for (int i = 0; i < 3; i++)
        {
            if (abs(dist(points[i], points[(i + 1) % 3]) - dist(otherTriangle->points[i], otherTriangle->points[(i + 1) % 3])) > eps)
            {
                return false;
            }
        }
        return true;
    }


    bool isSimilarTo(const Shape& other) const
    {
        if (*this == other)
        {
            return true;
        }
        if (dynamic_cast<const Triangle*>(&other) == NULL)
        {
            return false;
        }
        const Polygon& Another = dynamic_cast<const Triangle&>(other);
        if (size_ != Another.size_)
        {
            return false;
        }
        const Triangle& otherTriangle = static_cast<const Triangle&>(other);

        double side1Ratio = dist(points[0], points[1]) / otherTriangle.dist(otherTriangle.points[0], otherTriangle.points[1]);
        double side2Ratio = dist(points[1], points[2]) / otherTriangle.dist(otherTriangle.points[1], otherTriangle.points[2]);
        double side3Ratio = dist(points[2], points[0]) / otherTriangle.dist(otherTriangle.points[2], otherTriangle.points[0]);

        if (abs(side1Ratio - side2Ratio) > eps || abs(side2Ratio - side3Ratio) > eps || abs(side3Ratio - side1Ratio) > eps)
        {
            return false;
        }
        double angle1 = acos(Shape::Cos(Line(points[0], points[1]), Line(points[0], points[2])));
        double angle2 = acos(Shape::Cos(Line(otherTriangle.points[0], otherTriangle.points[1]), Line(otherTriangle.points[0], otherTriangle.points[2])));
        if (abs(angle1 - angle2) > eps)
        {
            return false;
        }
        return true;
    }

    double size() {};
};



