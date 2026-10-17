#include <bits/stdc++.h>
using ll = long long;
#define mid ((l+r)>>1)
constexpr ll inf = 2e18;
struct Line {
	ll k, b;
	int p;
	ll operator()(ll x) { return k * x + b; }
};
struct LiChaoSegtree
{
	std::vector<Line> s;
	std::vector<std::array<int, 2>> g;
	int n, cnt = 0;
	LiChaoSegtree(size_t n) :n(n), cnt(0) { s.resize(n << 5 | 1);g.resize(n << 5 | 1); }
	void insert(int& i, int l, int r, Line& x)
	{
		if (!i) { i = ++cnt;s[i] = x;return; }
		if (x(mid) < s[i](mid)) std::swap(x, s[i]);
		if (x(l) < s[i](l)) insert(g[i][0], l, mid, x);
		if (x(r) < s[i](r)) insert(g[i][1], mid + 1, r, x);
	}
	std::pair<ll, int> query(int l, int r, int i, int x)
	{
		if (!i) return { inf,0 };
		std::pair<ll, int> ans = { s[i](x),s[i].p };
		if (x <= mid) ans = std::min(ans, query(l, mid, g[i][0], x));
		else ans = std::min(ans, query(mid + 1, r, g[i][1], x));
		return ans;
	}
};