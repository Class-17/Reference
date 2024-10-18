template<class T, auto op, auto e>
class SegmentTree {
private:
    int n;
    struct Node {
        int l, r;
        T dat;
    };
    std::vector<Node> t;

    void update(int k) {t[k].dat = op(t[k * 2].dat, t[k * 2 + 1].dat);}

    void change(int p, int x, T v) {
        if (t[p].r - t[p].l == 1) {t[p].dat = v; return;}
        int mid = t[p].l + t[p].r >> 1;
        if (x < mid) change(p * 2, x, v);
        else         change(p * 2 + 1, x, v);
        update(p);
    };

    T ask(int p, int l, int r) const {
        if (l <= t[p].l and r >= t[p].r) return t[p].dat;
        int mid = t[p].l + t[p].r >> 1;
        T res = e();
        if (l < mid) res = op(res, ask(p * 2, l, r));
        if (r > mid) res = op(res, ask(p * 2 + 1, l, r));
        return res;
    }
public:
    SegmentTree() : SegmentTree(0) {}

    SegmentTree(int n) : SegmentTree(std::vector<T>(n, e())) {}

    SegmentTree(const std::vector<T> &v) : n(v.size()) {
        t = std::vector<Node>(n * 4);
        auto build = [&](auto &self, int p, int l, int r)->void {
            t[p].l = l, t[p].r = r;
            if (r - l == 1) {t[p].dat = v[l]; return;}
            int mid = l + r >> 1;
            self(self, p * 2, l, mid);
            self(self, p * 2 + 1, mid, r);
            update(p);
        };
        build(build, 1, 0, n);
    }

    void set(int p, T v) {
        assert(0 <= p and p < n);
        change(1, p, v);
    }

    T get(int p) const {
        assert(0 <= p and p < n);
        return ask(1, p, p + 1);
    }

    T prod(int l, int r) const { // prod of [l, r)
        assert(0 <= l and l <= r and r <= n);
        return ask(1, l, r);
    }

    T all_prod() const {return t[1].dat;}
};