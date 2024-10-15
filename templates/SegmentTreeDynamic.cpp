template<class T>
class SegmentTree {
private:
    T val, lazy, l, r;
    SegmentTree *L, *R;

    void update() {
        T lo = this->L ? this->L->val : 0;
        T hi = this->R ? this->R->val : 0;
        val = lo + hi;
    }

    void push_down() {
        if (!lazy) return;
        if (L) {
            L->val += (L->r - L->l) * lazy;
            L->lazy += lazy;
        }
        if (R) {
            R->val += (R->r - R->l) * lazy;
            R->lazy += lazy;
        }
        lazy = 0;
    }

public:
    SegmentTree(T val = 0, T l = 0, T r = 1) : val(val), l(l), r(r) {
        lazy = 0;
        L = R = nullptr;
    }

    SegmentTree *add(T cl, T cr, T delta) {
        if (cl <= l and r <= cr) {
            val += (r - l) * delta;
            lazy += delta;
            return this;
        }
        T mid = l + r >> 1;
        if (!L) L = new SegmentTree(0, l, mid);
        if (!R) R = new SegmentTree(0, mid, r);
        push_down();
        if (cl < mid) L = L->add(cl, cr, delta);
        if (cr > mid) R = R->add(cl, cr, delta);
        update();
        return this;
    }

    T ask(T l, T r) {
        if (r < this->l or this->r < l) return 0;
        if (l <= this->l and this->r <= r) return val;
        push_down();
        T lo = this->L ? this->L->ask(l, r) : 0;
        T hi = this->R ? this->R->ask(l, r) : 0;
        return lo + hi;
    }

    void del() {
        if (L) L->del();
        if (R) R->del();
        delete this;
    }
};