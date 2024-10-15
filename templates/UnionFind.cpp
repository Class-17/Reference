class UnionFind {
private:
    int n;
    std::vector<int> dsu;
public:
    UnionFind(int n = 0) : n(n), dsu(n, -1) {}

    int find(int x) {
        if (dsu[x] < 0) return x;
        return dsu[x] = find(dsu[x]);
    }

    int unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return x;
        if (dsu[x] > dsu[y]) std::swap(x, y);
        dsu[x] += dsu[y];
        dsu[y] = x;
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return -dsu[find(x)];
    }
};