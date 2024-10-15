class Trie {
private:
    array<Trie*, 26> child;
    int tail;
    int f(const char &ch) {return ch - 'a';}
public:
    Trie() : tail(0) {child.fill(nullptr);};

    void insert(const string &s) {
        Trie *t = this;
        for (auto &ch : s) {
            int x = f(ch);
            if (!t->child[x])
                t->child[x] = new Trie;
            t = t->child[x];
        }
        ++t->tail;
    }

    int search(const string &s) {
        Trie *t = this;
        for (auto &ch : s) {
            int x = f(ch);
            if (!t->child[x]) return 0;
            t = t->child[x];
        }
        return t->tail;
    }

    void del() {
        for (auto &x : child)
            if (x) x->del();
        delete this;
    }
};