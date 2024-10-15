template<class T>
class ChthollyTree {
using Idx = unsigned long long;
private:
    struct Node {
        Idx l, r;
        mutable T v; 
        Node(const Idx &_l, const Idx &_r, const T &_v) : 
            l(_l), r(_r), v(_v) {}
        bool operator < (const Node &other) const {
            return l < other.l;
        }
    };
    std::set<Node> odt;
    Idx n;
public:
    ChthollyTree() {}

    ChthollyTree(const Idx &_l, const Idx &_r, const T &_v) {
        odt.emplace(_l, _r, _v);
        n = _r;
    }

    ChthollyTree(const std::vector<T> &a) {
        n = a.size();
        for (int i = 0; i < n; ++i)
            odt.emplace(i + 1, i + 1, a[i]);
    }

    auto split(Idx x) {
        if (x > n) return odt.end();
        auto it = std::prev(odt.upper_bound(Node{x, 0, T()}));
        if (it->l == x) return it;
        auto [l, r, v] = *it;
        odt.erase(it);
        odt.emplace(l, x - 1, v);
        return odt.emplace(x, r, v).first;
    }

    void assign(Idx l, Idx r, T v) {
        auto itR = split(r + 1), itL = split(l);
        odt.erase(itL, itR);
        odt.emplace(l, r, v);
    }

    void add(Idx l, Idx r, T v) {
        auto itR = split(r + 1), itL = split(l);
        for (auto it = itL; it != itR; ++it)
            it->v += v;
    }
    
    auto run(Idx l, Idx r) { // add argument at there
        auto itR = split(r + 1), itL = split(l);
        for (auto it = itL; it != itR; ++it) {
           const auto &[il, ir, iv] = *it;
           // action for interval [l, r]
        }
    }
};