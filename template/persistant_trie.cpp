#include <bits/stdc++.h>
struct Trie
{
    std::vector<std::array<int, 3>> g;//左右儿子和大小
    std::vector<int> rt;
    int n, cnt;
    Trie() {}
    Trie(size_t n) : n(n), cnt(0) { 
        g.resize((n + 1) * 30);
        rt.resize(n + 1);
    }
    void insert(int &i, int pre, int x, int d)
    {
        i = ++cnt;
        g[i] = g[pre];
        g[i][2]++;
        if(d < 0) return;
        int b = x >> d & 1;
        insert(g[i][b], g[pre][b], x, d - 1);
    }
    int query(int u, int k, int x)
    {
        int p = u, ans = 0;
        for (int i = 30; ~i;i--)
        {
            int b = x >> i & 1;
            int siz = g[p][2];
            if(k <= siz) p = g[p][b];
            else k -= siz, p = g[p][b ^ 1], ans |= 1 << i;
        }
        return ans;
    }
};