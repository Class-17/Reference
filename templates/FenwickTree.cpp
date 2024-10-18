template<class T>
class FenwickTree {
private: // fenwickTree for interval [0, n)
    int n;
    std::vector<T> data;
public:
    FenwickTree() : FenwickTree(0) {}
    explicit FenwickTree(int n) : n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p and p < n);
        p += 1;
        while (p <= n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) {// return sum of [l, r)
        assert(0 <= l and l <= r and r <= n);
        return sum(r) - sum(l);
    }

    T sum(int r) {// return sum of [0, r)
        assert(0 <= r and r <= n);
        T s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};