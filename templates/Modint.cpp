template <int m>
class Modint {
private:
    unsigned int _v;
    static constexpr unsigned int umod() {return m;}
public:
    static constexpr int mod() {return m;}
    static Modint raw(int v) {
        Modint x;
        x._v = v;
        return x;
    }

    Modint() : _v(0) {}
    template <class T>
    Modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    Modint(bool v) {_v = ((unsigned int)(v) % umod());}

    unsigned int val() const {return _v;}

    Modint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    Modint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    Modint operator++(int) {
        Modint result = *this;
        ++*this;
        return result;
    }
    Modint operator--(int) {
        Modint result = *this;
        --*this;
        return result;
    }

    Modint& operator+=(const Modint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    Modint& operator-=(const Modint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    Modint& operator*=(const Modint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    Modint& operator/=(const Modint& rhs) {return *this = *this * rhs.inv();}

    Modint operator+() const {return *this;}
    Modint operator-() const {return Modint() - *this;}

    Modint pow(long long n) const {
        assert(0 <= n);
        Modint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    Modint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend Modint operator+(const Modint& lhs, const Modint& rhs) {
        return Modint(lhs) += rhs;
    }
    friend Modint operator-(const Modint& lhs, const Modint& rhs) {
        return Modint(lhs) -= rhs;
    }
    friend Modint operator*(const Modint& lhs, const Modint& rhs) {
        return Modint(lhs) *= rhs;
    }
    friend Modint operator/(const Modint& lhs, const Modint& rhs) {
        return Modint(lhs) /= rhs;
    }
    friend bool operator==(const Modint& lhs, const Modint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const Modint& lhs, const Modint& rhs) {
        return lhs._v != rhs._v;
    }
};