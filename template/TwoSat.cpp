#include <bits/stdc++.h>
struct TwoSat 
{
    int n;
    // 对每个布尔变量 x_i 建立两个点：
    // 2 * i     表示字面量 (x_i = false)
    // 2 * i + 1 表示字面量 (x_i = true)
    // 因而一个字面量取反可以直接将其编号异或 1。
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}

    // 加入子句 (x_u = f) OR (x_v = g)。
    // 利用 A OR B 等价于 (!A -> B) AND (!B -> A)，连边为：
    // (x_u = !f) -> (x_v = g)
    // (x_v = !g) -> (x_u = f)
    //
    // 常见约束写法：
    // 强制 x_u = f：            addClause(u, f, u, f)
    // 至少一个为 true：         addClause(u, true,  v, true)
    // 至多一个为 true：         addClause(u, false, v, false)
    // x_u 与 x_v 至少一个为假： addClause(u, false, v, false)
    // (x_u = f) -> (x_v = g)：   addClause(u, !f, v, g)
    // x_u == x_v：
    //   addClause(u, false, v, true)
    //   addClause(u, true,  v, false)
    // x_u != x_v：
    //   addClause(u, true,  v, true)
    //   addClause(u, false, v, false)
    void addClause(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    bool satisfiable() {
        std::vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        for (int i = 0; i < n; ++i) {
            // x_i=true 和 x_i=false 位于同一个强连通分量时，
            // 两个相反字面量可以互相推出，公式无解。
            if (id[2 * i] == id[2 * i + 1]) return false;

            // Tarjan 按汇点 SCC 在先的顺序编号，据此构造一组可行赋值。
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};
