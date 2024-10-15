template<class T>
class SegmentTree {
private:
    vector<T> val, lazy;
    vector<int> L, R;

    void update(int p) {
        val[p] = val[p << 1] + val[p<<1|1];
    }

    void build(const vector<T> &arr, int p, int l, int r) {
        tie(L[p], R[p]) = pair{l, r};
        if (l == r) {val[p] = arr[l]; return;}
        int mid = l + r >> 1;
        build(arr, p << 1, l, mid);
        build(arr, p<<1|1, mid + 1, r);
        update(p);
    }

    void push_down(int p) {
        if (!lazy[p]) return;
        val[p << 1] += (R[p << 1] - L[p << 1] + 1) * lazy[p];
        val[p<<1|1] += (R[p<<1|1] - L[p<<1|1] + 1) * lazy[p];
        lazy[p << 1] += lazy[p];
        lazy[p<<1|1] += lazy[p];
        lazy[p] = 0;
    }

    void add(int p, int l, int r, T delta) {
        if (l <= L[p] and R[p] <= r) {
            val[p] += (R[p] - L[p] + 1) * delta;
            lazy[p] += delta;
            return;
        }
        push_down(p);
        int mid = L[p] + R[p] >> 1;
        if (l <= mid) add(p << 1, l, r, delta);
        if (r > mid)  add(p<<1|1, l, r, delta);
        update(p);
    }
    
    T ask(int p, int l, int r) {
        if (r < L[p] or R[p] < l) return 0;
        if (l <= L[p] and R[p] <= r) return val[p];
        push_down(p);
        return ask(p << 1, l, r) + ask(p<<1|1, l, r);
    }

public:
    SegmentTree(int n = 0) {
        val = lazy = vector<T>(n + 1 << 2);
        L = R = vector<int>(n + 1 << 2);
    }

    SegmentTree(const vector<T> &arr) {
        int n = size(arr);
        val = lazy = vector<T>(n << 2);
        L = R = vector<int>(n << 2);
        build(arr, 1, 1, n - 1);
    }

    void add(int l, int r, T delta) {
        add(1, l, r, delta);
    }

    T ask(int l, int r) {
        return ask(1, l, r);
    }
};