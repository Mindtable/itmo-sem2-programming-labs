#pragma once
#include <iostream>

template<int Number, int Pow>
class Power {
public:
    static const int value = Number * Power<Number, Pow - 1>::value;
};

template<int Number>
class Power<Number, 0> {
public:
    static const int value = 1;
};

template<int Point, int Coefficient, int ... Coefficients>
class Polynomial {
public:
    static const int degree = sizeof...(Coefficients);
    static const int value = Power<Point, degree>::value * Coefficient + Polynomial<Point, Coefficients...>::value;

    template<typename stream>
    friend stream& operator<<(stream& out, Polynomial<Point, Coefficient, Coefficients...> poly) {
        out << Coefficient << "x^" << degree << " + " << Polynomial<Point, Coefficients...>();
        return out;
    }
};

template<int Point, int Coefficient>
class Polynomial<Point, Coefficient> {
public:
    static const int value = Coefficient;
    static const int degree = 0;

    template<typename stream>
    friend stream& operator<<(stream& out, Polynomial<Point, Coefficient> poly) {
        out << Coefficient;
        return out;
    }
};

//int main() {
//    // 4x^2 + 3x + 10, point 20
//    std::cout << Polynomial<20, 4, 3, 10>::value << std::endl;
//    std::cout << Polynomial<20, 4, 3, 10>() << std::endl;
//}