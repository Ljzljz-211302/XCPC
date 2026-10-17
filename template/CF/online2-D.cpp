#include <bits/stdc++.h>
struct dsu
{
    int n;
    std::vector<int> fa, siz;
    dsu() {}
    dsu(size_t n) : n(n) { fa.resize(n + 1);
        std::iota(fa.begin(), fa.end(), 0);
        siz.assign(n + 1, 1);
    }
    int find(int i)
    {
        if(i==fa[i])
            return i;
        return fa[i] = find(fa[i]);
    }
    bool merge(int x,int y)
    {

    }
};
int main()
{
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int T = 1;
    std::cin >> T;
    while(T--)
    {
        int n;
        std::cin >> n;
        std::vector<int> dfn(n + 1), low(n + 1), siz(n + 1), mx(n + 1);
        auto dfs = [&](this auto &&dfs, int i, int f) -> void {

        };
    }
}