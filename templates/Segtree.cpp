#if __cplusplus >= 201703L
template<class T, auto op, auto e>
#else
template<class T, T (*op)(T, T), T (*e)()>
#endif
class Segtree {
private:
    int n, size, log;
    std::vector<T> d;
    void update(int k) {d[k] = op(d[k * 2], d[k * 2 + 1]);}
public:
    Segtree() : Segtree(0) {}
    explicit Segtree(int n) : Segtree(std::vector<T>(n, e())) {}
    explicit Segtree(const std::vector<T> &v) : n(v.size()) {
        size = 1; while (size < n) size *= 2;
        log = __builtin_ctz(size);
        d = std::vector<T>(size * 2, e());
        for (int i = 0; i < n; ++i) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; --i)
            update(i);
    }

    void set(int p, T x) {
        assert(0 <= p and p < n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; ++i) update(p >> i);
    }

    T get(int p) const {
        assert(0 <= p and p < n);
        return d[p + size];
    }

    T prod(int l, int r) const { // prod of [l, r)
        assert(0 <= l and l <= r and r <= n);
        T sml = e(), smr = e();
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    T all_prod() const {return d[1];}

	template<bool (*f)(T)>
	int max_right(int l) const {
		return max_right(l, [](T x) {return f(x);});
	}

	template<class F>
	int max_right(int l, F f) const {
		assert(0 <= l and l <= n);
		assert(f(e()));
		if (l == n) return n;
		l += size;
		T sm = e();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!f(op(sm, d[l]))) {
				while (l < size) {
					l = l * 2;
					if (f(op(sm, d[l]))) {
						sm = op(sm, d[l]);
						l += 1;
					}
				}
				return l - size;
			}
			sm = (sm, d[l]);
			l += 1;
		} while ((l & -l) != l);
		return n;
	}

	template<bool (*f)(T)>
	int min_left(int r) const {
		return min_left(r, [](T x) {return f(x);});
	}

	template<class F>
	int min_left(int r, F f) const {
		assert(0 <= r and r <= n);
		assert(f(e()));
		if (r == 0) return 0;
		r += size;
		T sm = e();
		do {
			r -= 1;
			while (r > 1 and (r & 1)) r >>= 1;
			if (!f(op(d[r], sm))) {
				while (r < size) {
					r = r * 2 + 1;
					if (f(op(d[r], sm))) {
						sm = op(d[r], sm);
						r -= 1;
					}
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while ((r & -r) != r);
		return 0;
	}
};