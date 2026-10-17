#include <bits/stdc++.h>
struct dsu
{
    std::vector<int> fa, siz;
    int n;
    void init(int n) {
        fa.resize(n + 1);
        std::iota(fa.begin(), fa.end(), 0);
        siz.assign(n + 1, 1);
    }
    dsu(size_t n) : n(n) { init(n); }
    int find(int i) {if(i==fa[i])
            return i;
        return fa[i] = find(fa[i]);
    }
    bool merge(int x,int y)
    {
        x = find(x), y = find(y);
        if(x==y)
            return 1;
        fa[x] = y;
        siz[y] += siz[x];
        return 0;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

struct DSU {
    std::vector<int> siz;
    std::vector<int> f;
    std::vector<std::array<int, 2>> his;
    
    DSU(int n) : siz(n + 1, 1), f(n + 1) {
        std::iota(f.begin(), f.end(), 0);
    }
    
    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int time() {
        return his.size();
    }
    
    void revert(int tm) {
        while (his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
        }
    }
};