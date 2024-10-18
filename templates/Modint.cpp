template <int m>
class Mint {
private:
    unsigned int _v;
    static constexpr unsigned int umod() {return m;}
public:
    static constexpr int mod() {return m;}
    static Mint raw(int v) {
        Mint x;
        x._v = v;
        return x;
    }

    Mint() : _v(0) {}
    template <class T>
    Mint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    Mint(bool v) {_v = ((unsigned int)(v) % umod());}

    unsigned int val() const {return _v;}

    Mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    Mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    Mint operator++(int) {
        Mint result = *this;
        ++*this;
        return result;
    }
    Mint operator--(int) {
        Mint result = *this;
        --*this;
        return result;
    }

    Mint& operator+=(const Mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    Mint& operator-=(const Mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    Mint& operator*=(const Mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    Mint& operator/=(const Mint& rhs) {return *this = *this * rhs.inv();}

    Mint operator+() const {return *this;}
    Mint operator-() const {return Mint() - *this;}

    Mint pow(long long n) const {
        assert(0 <= n);
        Mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    Mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend Mint operator+(const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) += rhs;
    }
    friend Mint operator-(const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) -= rhs;
    }
    friend Mint operator*(const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) *= rhs;
    }
    friend Mint operator/(const Mint& lhs, const Mint& rhs) {
        return Mint(lhs) /= rhs;
    }
    friend bool operator==(const Mint& lhs, const Mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const Mint& lhs, const Mint& rhs) {
        return lhs._v != rhs._v;
    }
};