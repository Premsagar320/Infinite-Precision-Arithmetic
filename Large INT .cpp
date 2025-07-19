#include <bits/stdc++.h>
using namespace std;

class LargeInt {
    vector<int> digits;
    void divide_by_2();

public:
    LargeInt(unsigned long long n = 0);
    LargeInt(const string& s);
    LargeInt(const char* s);
    LargeInt(const LargeInt& other);

    bool isNull() const;
    int length() const;
    int operator[](int index) const;

    LargeInt& operator=(const LargeInt& other);
    LargeInt& operator++();
    LargeInt operator++(int);
    LargeInt& operator--();
    LargeInt operator--(int);

    LargeInt& operator+=(const LargeInt& other);
    LargeInt& operator-=(const LargeInt& other);
    LargeInt& operator*=(const LargeInt& other);
    LargeInt& operator/=(const LargeInt& other);
    LargeInt& operator%=(const LargeInt& other);
    LargeInt& operator^=(const LargeInt& exponent);

    bool operator==(const LargeInt& other) const;
    bool operator!=(const LargeInt& other) const;
    bool operator<(const LargeInt& other) const;
    bool operator<=(const LargeInt& other) const;
    bool operator>(const LargeInt& other) const;
    bool operator>=(const LargeInt& other) const;

    LargeInt sqrt() const;
    static LargeInt factorial(int n);

    friend istream& operator>>(istream& in, LargeInt& a);
    friend ostream& operator<<(ostream& out, const LargeInt& a);
};

LargeInt::LargeInt(unsigned long long n) {
    do {
        digits.push_back(n % 10);
        n /= 10;
    } while (n);
}

LargeInt::LargeInt(const string& s) {
    for (int i = s.size() - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw invalid_argument("ERROR: Non-digit character in string");
        digits.push_back(s[i] - '0');
    }
}

LargeInt::LargeInt(const char* s) {
    for (int i = strlen(s) - 1; i >= 0; i--) {
        if (!isdigit(s[i]))
            throw invalid_argument("ERROR: Non-digit character in string");
        digits.push_back(s[i] - '0');
    }
}

LargeInt::LargeInt(const LargeInt& other) : digits(other.digits) {}

bool LargeInt::isNull() const {
    return digits.size() == 1 && digits[0] == 0;
}

int LargeInt::length() const {
    return digits.size();
}

int LargeInt::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(digits.size()))
        throw out_of_range("ERROR: Index out of range");
    return digits[index];
}

LargeInt& LargeInt::operator=(const LargeInt& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

LargeInt& LargeInt::operator++() {
    int i = 0;
    int n = digits.size();
    while (i < n && digits[i] == 9) {
        digits[i] = 0;
        i++;
    }
    if (i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}

LargeInt LargeInt::operator++(int) {
    LargeInt temp(*this);
    ++(*this);
    return temp;
}

LargeInt& LargeInt::operator--() {
    if (isNull())
        throw underflow_error("UNDERFLOW");
    int i = 0;
    int n = digits.size();
    while (i < n && digits[i] == 0) {
        digits[i] = 9;
        i++;
    }
    digits[i]--;
    if (n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}

LargeInt LargeInt::operator--(int) {
    LargeInt temp(*this);
    --(*this);
    return temp;
}

LargeInt& LargeInt::operator+=(const LargeInt& other) {
    int t = 0, s, i;
    int n = length(), m = other.length();
    if (m > n)
        digits.resize(m, 0);
    n = length();
    for (i = 0; i < n; i++) {
        if (i < m)
            s = digits[i] + other.digits[i] + t;
        else
            s = digits[i] + t;
        t = s / 10;
        digits[i] = s % 10;
    }
    if (t)
        digits.push_back(t);
    return *this;
}

LargeInt operator+(const LargeInt& a, const LargeInt& b) {
    LargeInt temp = a;
    temp += b;
    return temp;
}

LargeInt& LargeInt::operator-=(const LargeInt& other) {
    if (*this < other)
        throw underflow_error("UNDERFLOW");
    int n = length(), m = other.length();
    int i, t = 0, s;
    for (i = 0; i < n; i++) {
        if (i < m)
            s = digits[i] - other.digits[i] + t;
        else
            s = digits[i] + t;
        if (s < 0)
            s += 10, t = -1;
        else
            t = 0;
        digits[i] = s;
    }
    while (n > 1 && digits[n - 1] == 0)
        digits.pop_back(), n--;
    return *this;
}

LargeInt operator-(const LargeInt& a, const LargeInt& b) {
    LargeInt temp = a;
    temp -= b;
    return temp;
}

LargeInt& LargeInt::operator*=(const LargeInt& other) {
    if (isNull() || other.isNull()) {
        *this = LargeInt();
        return *this;
    }
    int n = length(), m = other.length();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            v[i + j] += digits[i] * other.digits[j];
    n += m;
    digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++) {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        digits.pop_back();
    return *this;
}

LargeInt operator*(const LargeInt& a, const LargeInt& b) {
    LargeInt temp = a;
    temp *= b;
    return temp;
}

LargeInt& LargeInt::operator/=(const LargeInt& other) {
    if (other.isNull())
        throw invalid_argument("Arithmetic Error: Division By 0");
    if (*this < other) {
        *this = LargeInt();
        return *this;
    }
    if (*this == other) {
        *this = LargeInt(1);
        return *this;
    }
    int i, lgcat = 0, cc;
    int n = length();
    vector<int> cat(n, 0);
    LargeInt t;
    for (i = n - 1; t * 10 + digits[i] < other; i--) {
        t *= 10;
        t += digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + digits[i];
        for (cc = 9; cc * other > t; cc--);
        t -= cc * other;
        cat[lgcat++] = cc;
    }
    digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        digits[i] = cat[lgcat - i - 1];
    digits.resize(lgcat);
    return *this;
}

LargeInt operator/(const LargeInt& a, const LargeInt& b) {
    LargeInt temp = a;
    temp /= b;
    return temp;
}

LargeInt& LargeInt::operator%=(const LargeInt& other) {
    if (other.isNull())
        throw invalid_argument("Arithmetic Error: Division By 0");
    if (*this < other)
        return *this;
    if (*this == other) {
        *this = LargeInt();
        return *this;
    }
    int i, lgcat = 0, cc;
    int n = length();
    vector<int> cat(n, 0);
    LargeInt t;
    for (i = n - 1; t * 10 + digits[i] < other; i--) {
        t *= 10;
        t += digits[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + digits[i];
        for (cc = 9; cc * other > t; cc--);
        t -= cc * other;
        cat[lgcat++] = cc;
    }
    *this = t;
    return *this;
}

LargeInt operator%(const LargeInt& a, const LargeInt& b) {
    LargeInt temp = a;
    temp %= b;
    return temp;
}

LargeInt& LargeInt::operator^=(const LargeInt& exponent) {
    LargeInt exp = exponent;
    LargeInt base(*this);
    *this = 1;
    while (!exp.isNull()) {
        if (exp[0] & 1)
            *this *= base;
        base *= base;
        exp.divide_by_2();
    }
    return *this;
}

LargeInt operator^(LargeInt a, const LargeInt& b) {
    a ^= b;
    return a;
}

void LargeInt::divide_by_2() {
    int add = 0;
    for (int i = digits.size() - 1; i >= 0; i--) {
        int digit = (digits[i] >> 1) + add;
        add = ((digits[i] & 1) * 5);
        digits[i] = digit;
    }
    while (digits.size() > 1 && !digits.back())
        digits.pop_back();
}

bool LargeInt::operator==(const LargeInt& other) const {
    return digits == other.digits;
}

bool LargeInt::operator!=(const LargeInt& other) const {
    return !(*this == other);
}

bool LargeInt::operator<(const LargeInt& other) const {
    int n = length(), m = other.length();
    if (n != m)
        return n < m;
    while (n--)
        if (digits[n] != other.digits[n])
            return digits[n] < other.digits[n];
    return false;
}

bool LargeInt::operator<=(const LargeInt& other) const {
    return !(*this > other);
}

bool LargeInt::operator>(const LargeInt& other) const {
    return other < *this;
}

bool LargeInt::operator>=(const LargeInt& other) const {
    return !(*this < other);
}

LargeInt LargeInt::sqrt() const {
    LargeInt left(1), right(*this), v(1), mid, prod;
    right.divide_by_2();
    while (left <= right) {
        mid += left;
        mid += right;
        mid.divide_by_2();
        prod = (mid * mid);
        if (prod <= *this) {
            v = mid;
            ++mid;
            left = mid;
        } else {
            --mid;
            right = mid;
        }
        mid = LargeInt();
    }
    return v;
}

LargeInt LargeInt::factorial(int n) {
    LargeInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

istream& operator>>(istream& in, LargeInt& a) {
    string s;
    in >> s;
    a = LargeInt(s);
    return in;
}

ostream& operator<<(ostream& out, const LargeInt& a) {
    for (int i = a.digits.size() - 1; i >= 0; i--)
        out << a.digits[i];
    return out;
}


