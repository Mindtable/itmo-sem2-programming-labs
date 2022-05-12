#include <iostream>
#include <cmath>
#include <vector>
#include <initializer_list>

struct Point {
public:
    double x, y;

    Point() {
        x = 0.0;
        y = 0.0;
    }

    Point(double x, double y = 0) : x(x), y(y) {

    }

    Point(const Point &other) {
        this->x = other.x;
        this->y = other.y;
    }

    Point &operator=(const Point &other) {
        this->x = other.x;
        this->y = other.y;

        return *this;
    }

    Point &operator-=(const Point &other) {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    Point &operator+=(const Point &other) {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Point &operator-() {
        this->x = -this->x;
        this->y = -this->y;

        return *this;
    }

    Point &operator*=(double number) {
        this->x *= number;
        this->y *= number;

        return *this;
    }

    [[nodiscard]] double dot(const Point &other) const {
        return this->x * other.x + this->y * other.y;
    }

    double cos(const Point &a, const Point &b) const {
        Point vecA = a - *this;
        Point vecB = b - *this;

        return vecA.dot(vecB) / vecA.dist() / vecB.dist();
    }

    double sin(const Point &a, const Point &b) const {
        double angleCos = cos(a, b);
        return sqrt(1 - angleCos * angleCos);
    }

    [[nodiscard]] double dist(const Point &other = Point()) const {
        return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
    }

    friend Point operator*(Point arg1, double number);

    friend Point operator+(Point arg1, const Point &other);

    friend Point operator-(Point arg1, const Point &other);

    friend std::istream &operator>>(std::istream &in, Point &polynomial);

    friend std::ostream &operator<<(std::ostream &out, const Point &polynomial);
};

Point operator*(Point arg1, double number) {
    return arg1 *= number;
}

Point operator+(Point arg1, const Point &other) {
    return arg1 += other;
}

Point operator-(Point arg1, const Point &other) {
    return arg1 -= other;
}

std::istream &operator>>(std::istream &in, Point &polynomial) {
    in >> polynomial.x;
    in >> polynomial.y;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Point &polynomial) {
    out << "(" << polynomial.x << ";" << polynomial.y << ")";

    return out;
}

class PerimeterInterface {
public:
    virtual double getPerimeter() const = 0;
};

class ShapeInterface : PerimeterInterface {
public:
    virtual double getArea() const = 0;
};

class Line : public PerimeterInterface {
protected:
    std::vector<Point> m_Points;
public:
    Line() {
    }

    Line(std::initializer_list<Point> points) {
        m_Points.reserve(points.size());

        for (const auto &elem: points) {
            m_Points.emplace_back(elem);
        }
    }

    Line(const Line &other) {
        this->m_Points = other.m_Points;
    }

    Line &operator=(const Line &other) {
        if (this == &other) {
            return *this;
        }
        this->m_Points = other.m_Points;
        return *this;
    }

    double getPerimeter() const override {
        auto first = m_Points.begin();
        double result = 0.0;

        for (auto i = m_Points.begin() + 1; i != m_Points.end(); ++i) {
            result += first->dist(*i);
            first = i;
        }

        return result;
    }
};

class ClosedLine : public Line {
public:
    ClosedLine() {

    }

    ClosedLine(std::initializer_list<Point> points) {
        m_Points.reserve(points.size());

        for (const auto &elem: points) {
            m_Points.emplace_back(elem);
        }
    }

    ClosedLine(const ClosedLine &other) {
        this->m_Points = other.m_Points;
    }

    ClosedLine &operator=(const ClosedLine &other) {
        if (this == &other) {
            return *this;
        }
        this->m_Points = other.m_Points;
        return *this;
    }

    double getPerimeter() const override {
        double result = Line::getPerimeter();
        if (m_Points.size() > 1) {
            result += m_Points.front().dist(m_Points.back());
        }
        return result;
    }
};

class Polygon : ShapeInterface {
private:
    std::vector<Point> m_Points;
public:
    Polygon() {

    }

    Polygon(std::initializer_list<Point> points) {
        m_Points.reserve(points.size());

        for (const auto &elem: points) {
            m_Points.emplace_back(elem);
        }
    }

    Polygon(const Polygon &other) {
        this->m_Points = other.m_Points;
    }

    Polygon &operator=(const Polygon &other) {
        if (this == &other) {
            return *this;
        }
        this->m_Points = other.m_Points;
        return *this;
    }

    double getPerimeter() const override {
        auto first = m_Points.begin();
        double result = 0.0;

        for (auto i = m_Points.begin() + 1; i != m_Points.end(); ++i) {
            result += first->dist(*i);
            first = i;
        }

        if (m_Points.size() > 1) {
            result += m_Points.front().dist(m_Points.back());
        }
        return result;
    }

    double getArea() const override {
        double res = 0;
        for (size_t i = 0; i != m_Points.size(); ++i) {
            auto
                    p1 = i ? m_Points[i - 1] : m_Points.back(),
                    p2 = m_Points[i];
            res += (p1.x - p2.x) * (p1.y + p2.y);
        }
        return fabs(res) / 2;
    }

};

class Triangle : public ShapeInterface {
private:
    Point m_pointA;
    Point m_pointB;
    Point m_pointC;

public:
    Triangle() : m_pointA(), m_pointB(), m_pointC() {

    }

    Triangle(const Point &A, const Point &B, const Point &C) : m_pointA(A), m_pointB(B), m_pointC(C) {

    }

    Triangle(const Triangle &other) {
        this->m_pointA = other.m_pointA;
        this->m_pointB = other.m_pointB;
        this->m_pointC = other.m_pointC;
    }

    Triangle &operator=(const Triangle &other) {
        if (this == &other) {
            return *this;
        }

        this->m_pointA = other.m_pointA;
        this->m_pointB = other.m_pointB;
        this->m_pointC = other.m_pointC;

        return *this;
    }

    double getPerimeter() const override {
        return m_pointA.dist(m_pointC) + m_pointA.dist(m_pointB) + m_pointB.dist(m_pointC);
    }

    double getArea() const override {
        double a = m_pointA.dist(m_pointC);
        double b = m_pointA.dist(m_pointB);

        return a * b * m_pointA.sin(m_pointB, m_pointC) / 2;
    }

};

class Trapezoid : ShapeInterface {
private:
    std::vector<Point> m_Points;
public:
    Trapezoid() {
        m_Points.resize(4);
    }

    Trapezoid(const Point &A, const Point &B, const Point &C, const Point &D) {
        m_Points.reserve(4);
        m_Points.push_back(A);
        m_Points.push_back(B);
        m_Points.push_back(C);
        m_Points.push_back(D);
    }

    Trapezoid(const Trapezoid &other) {
        this->m_Points = other.m_Points;
    }

    Trapezoid &operator=(const Trapezoid &other) {
        if (this == &other) {
            return *this;
        }

        this->m_Points = other.m_Points;

        return *this;
    }

    double getPerimeter() const override {
        auto first = m_Points.begin();
        double result = 0.0;

        for (auto i = m_Points.begin() + 1; i != m_Points.end(); ++i) {
            result += first->dist(*i);
            first = i;
        }

        if (m_Points.size() > 1) {
            result += m_Points.front().dist(m_Points.back());
        }
        return result;
    }

    double getArea() const override {
        return Triangle(m_Points[0], m_Points[1], m_Points[2]).getArea() +
               Triangle(m_Points[0], m_Points[2], m_Points[3]).getArea();
    }

    double getHeight() {
        return getArea() * 2 / (m_Points[0].dist(m_Points[3]) + m_Points[1].dist(m_Points[2]));
    }

};

class RightPolygon : ShapeInterface {
private:
    long long m_Sides;
    long long m_Radius;
    Point m_Center;
public:
    RightPolygon(long long sides, long long radius, const Point &center)
    : m_Sides(sides)
    , m_Radius(radius)
    , m_Center(center) {

    }

    RightPolygon(const RightPolygon &other) {
        this->m_Sides = other.m_Sides;
        this->m_Radius = other.m_Radius;
        this->m_Center = other.m_Center;
    }

    RightPolygon &operator=(const RightPolygon &other) {
        if (this == &other) {
            return *this;
        }

        this->m_Sides = other.m_Sides;
        this->m_Radius = other.m_Radius;
        this->m_Center = other.m_Center;

        return *this;
    }

    [[nodiscard]] double getPerimeter() const override {
        return m_Sides * 2 * m_Radius * sin(3.14 / m_Sides);
    }

    [[nodiscard]] double getArea() const override {
        return m_Radius * m_Radius * m_Sides * sin(6.28 / m_Sides) / 2;
    }
};

int main() {
    Point A(0, 0);
    Point B(3, 2);
    Point C(3, 4);
    Point D(0, 10);

    Line test({A});
    RightPolygon test2(4, 3, {0, 0});
    std::cout << test2.getArea() << std::endl;
    std::vector<int, std::allocator<int>> test3(4, 10);
    test3.push_back(20);
    for (const auto &elem: test3) {
        std::cout << elem << ' ';
    }
}
