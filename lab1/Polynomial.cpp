#include "Polynomial.h"

Polynomial::Polynomial() {
    m_MaxDegree = 0;
    m_MinDegree = 0;
    m_Coefficients = new double[m_MaxDegree - m_MinDegree + 1];
    m_Coefficients[0] = 0;
}

Polynomial::Polynomial(double number) {
    m_MaxDegree = 0;
    m_MinDegree = 0;
    m_Coefficients = new double[m_MaxDegree - m_MinDegree + 1];
    m_Coefficients[0] = number;
}

Polynomial::Polynomial(std::initializer_list<double> Coefficients, long long minDegree) {
    m_MaxDegree = Coefficients.size() - 1 + minDegree;
    m_MinDegree = minDegree;
    m_Coefficients = new double[m_MaxDegree - m_MinDegree + 1];

    decltype(Coefficients.begin()) CoefIter = Coefficients.begin();

    for (long long i = m_MaxDegree - m_MinDegree; i != -1; --i, ++CoefIter) {
        m_Coefficients[i] = *CoefIter;
    }
}

Polynomial::Polynomial(const std::string &PolynomialString, long long maxDegree, long long minDegree) {
    //a_(n - i) x ^ i
    //Only sorted: first -- the highest degree
    //last -- the lowest degree

    m_MaxDegree = maxDegree;
    m_MinDegree = minDegree < 0 ? minDegree : 0;
    m_Coefficients = new double[m_MaxDegree - m_MinDegree + 1];

    for (size_t j = 0; j != m_MaxDegree - m_MinDegree + 1; ++j) {
        m_Coefficients[j] = 0;
    }


    std::string firstSign = "+ ";
    for (char j: PolynomialString) {
        if (std::isdigit(j)) {
            break;
        } else if (j == '+' || j == '-') {
            firstSign = "";
            break;
        }
    }

    std::string operand;
    std::string sign;
    std::stringstream input(firstSign + PolynomialString);
    while (input >> sign && input >> operand) {
        auto xPos = operand.find('x');
        long long degree;
        if (xPos == std::string::npos) {
            degree = 0;
        } else if (xPos + 1 == operand.size()) {
            degree = 1;
        } else {
            degree = std::stoll(operand.substr(xPos + 2));
        }

        if (xPos == 0) {
            m_Coefficients[degree - m_MinDegree] = (sign == "-" ? -1 : 1) * 1;
        } else {
            m_Coefficients[degree - m_MinDegree] = (sign == "-" ? -1 : 1) * std::stod(operand.substr(0, xPos));
        }
    }
}

Polynomial::~Polynomial() {
    delete[] m_Coefficients;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &polynomial) {
    bool isZero = true;
    for (long long j = polynomial.m_MaxDegree; j != polynomial.m_MinDegree - 1; --j) {
        int coef = polynomial.m_Coefficients[j - polynomial.m_MinDegree];

        if (coef != 0) {
            isZero = false;
            if (j != polynomial.m_MaxDegree) {
                out << (coef > 0.0 ? "+ " : "- ");
            } else if (coef < 0.0) {
                out << "- ";
            }

            if (j == 0 || abs(coef) != 1) {
                out << abs(coef);
            }
            if (j == 1) {
                out << "x ";
            } else if (j != 0) {
                out << "x^" << j << ' ';
            } else {
                out << ' ';
            }
        }
    }
    if (isZero) {
        out << 0;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Polynomial &polynomial) {
    std::string input;
    std::getline(in, input);

    auto dLPos = input.find('^') + 1;
    auto firstDegreeEnd = dLPos;
    while (input[firstDegreeEnd] != ' ') {
        firstDegreeEnd++;
    }
    auto maxDegree = std::stoll(input.substr(dLPos, firstDegreeEnd - dLPos));

    auto dRPos = input.rfind('^') + 1;
    auto qq = input.substr(dRPos);
    auto minDegree = std::stoll(input.substr(dRPos));
    polynomial = Polynomial(input, maxDegree, minDegree);
    return in;
}

Polynomial &Polynomial::operator=(const Polynomial &polynomial) {
    if (this == &polynomial) {
        return *this;
    }

    delete[] this->m_Coefficients;
    this->m_MaxDegree = polynomial.m_MaxDegree;
    this->m_MinDegree = polynomial.m_MinDegree;
    this->m_Coefficients = new double[this->m_MaxDegree - this->m_MinDegree + 1];

    for (size_t i = 0; i != m_MaxDegree - m_MinDegree + 1; ++i) {
        this->m_Coefficients[i] = polynomial.m_Coefficients[i];
    }
    return *this;
}

Polynomial::Polynomial(const Polynomial &other) {
    this->m_MaxDegree = other.m_MaxDegree;
    this->m_MinDegree = other.m_MinDegree;
    this->m_Coefficients = new double[m_MaxDegree - m_MinDegree + 1];

    for (size_t j = 0; j != m_MaxDegree - m_MinDegree + 1; ++j) {
        this->m_Coefficients[j] = other.m_Coefficients[j];
    }
}

bool Polynomial::operator==(const Polynomial &other) const {
    std::stringstream arg1;
    std::stringstream arg2;
    arg1 << *this;
    arg2 << other;
    return arg1.str() == arg2.str();
}

bool Polynomial::operator!=(const Polynomial &other) const {
    return !(*this == other);
}

Polynomial &Polynomial::operator+=(const Polynomial &other) {
    long long newMinDegree = std::min(this->m_MinDegree, other.m_MinDegree);
    long long newMaxDegree = std::max(this->m_MaxDegree, other.m_MaxDegree);

    double *result;

    if (newMinDegree != this->m_MinDegree || newMaxDegree != this->m_MaxDegree) {
        result = new double[newMaxDegree - newMinDegree + 1];
        for (size_t j = 0; j != newMaxDegree - newMinDegree + 1; ++j) {
            result[j] = 0;
        }

        for (size_t j = 0; j != this->m_MaxDegree - this->m_MinDegree + 1; ++j) {
            result[j + (this->m_MinDegree - newMinDegree)] += this->m_Coefficients[j];
        }
    } else {
        result = this->m_Coefficients;
    }

    for (size_t j = 0; j != other.m_MaxDegree - other.m_MinDegree + 1; ++j) {
        result[j + (other.m_MinDegree - newMinDegree)] += other.m_Coefficients[j];
    }

    if (newMinDegree != this->m_MinDegree || newMaxDegree != this->m_MaxDegree) {
        delete[] this->m_Coefficients;
        this->m_MaxDegree = newMaxDegree;
        this->m_MinDegree = newMinDegree;
        this->m_Coefficients = result;
    }
    return *this;
}

Polynomial operator+(Polynomial arg1, const Polynomial &arg2) {
    return arg1 += arg2;
}

Polynomial Polynomial::operator-() const {
    Polynomial other(*this);
    for (size_t j = 0; j != other.m_MaxDegree - other.m_MinDegree + 1; ++j) {
        other.m_Coefficients[j] *= -1;
    }
    return other;
}

Polynomial &Polynomial::operator-=(const Polynomial &other) {
    *this += -other;
    return *this;
}

Polynomial operator-(Polynomial arg1, const Polynomial &arg2) {
    return arg1 -= arg2;
}

double Polynomial::operator[](const int index) {
    if (index < m_MinDegree || index > m_MaxDegree) {
        return 0;
    }
    return m_Coefficients[index - m_MinDegree];
}

double Polynomial::operator[](const int index) const {
    if (index < m_MinDegree || index > m_MaxDegree) {
        return 0;
    }
    return m_Coefficients[index - m_MinDegree];
}

Polynomial &Polynomial::operator*=(const Polynomial &other) {
    long long newMaxDegree = this->m_MaxDegree + other.m_MaxDegree;
    long long newMinDegree = this->m_MinDegree + other.m_MinDegree;
    auto result = new double[newMaxDegree - newMinDegree + 1];

    for (size_t i = 0; i != newMaxDegree - newMinDegree + 1; ++i) {
        result[i] = 0;
    }

    for (size_t i = 0; i != this->m_MaxDegree - this->m_MinDegree + 1; ++i) {
        for (size_t j = 0; j != other.m_MaxDegree - other.m_MinDegree + 1; ++j) {
            result[i + j] += this->m_Coefficients[i] * other.m_Coefficients[j];
        }
    }

    delete[] this->m_Coefficients;
    this->m_MaxDegree = newMaxDegree;
    this->m_MinDegree = newMinDegree;
    this->m_Coefficients = result;
    return *this;
}

Polynomial operator*(Polynomial arg1, const Polynomial &arg2) {
    return arg1 *= arg2;
}

Polynomial &Polynomial::operator/=(int coef) {
    for (size_t i = 0; i != this->m_MaxDegree - this->m_MinDegree + 1; ++i) {
        this->m_Coefficients[i] /= coef;
    }
    return *this;
}

Polynomial operator/(Polynomial arg1, double coef) {
    return arg1 /= coef;
}

double Polynomial::operator()(double argument) {
    double result = 0;
    for (long long j = 0; j != m_MaxDegree - m_MinDegree + 1; ++j) {
        result += m_Coefficients[j] * pow(argument, j + m_MinDegree);
    }
    return result;
}
