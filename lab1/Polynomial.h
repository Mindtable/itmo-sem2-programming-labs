#pragma once

#include <initializer_list>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

class Polynomial
{
private:
	double *m_Coefficients = nullptr;
	long long m_MaxDegree;
    long long m_MinDegree;

public:
	Polynomial();
    Polynomial(double number);
	Polynomial(std::initializer_list<double> Coefficients, long long minDegree = 0);

	explicit Polynomial(const std::string &PolynomialString, long long maxDegree, long long minDegree = 0);

    Polynomial(const Polynomial &other);

    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    Polynomial& operator/=(int coef);
    Polynomial operator-() const;
    double operator[](int index);
    double operator[](int index) const;
    double operator()(double argument);

	~Polynomial();

    Polynomial &operator=(const Polynomial& polynomial);

    friend std::ostream& operator<<(std::ostream &out, const Polynomial &polynomial);
    friend std::istream& operator>> (std::istream &in, Polynomial &point);
    friend Polynomial operator+(Polynomial arg1, const Polynomial &arg2);
    friend Polynomial operator-(Polynomial arg1, const Polynomial &arg2);
    friend Polynomial operator*(Polynomial arg1, const Polynomial &arg2);
    friend Polynomial operator/(Polynomial arg1, double coef);
};

