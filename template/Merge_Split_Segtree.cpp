#include <bits/stdc++.h>
struct MergeSplitSegtree
{
	int n;
	int free = 0;
	std::vector<std::array<int, 3>> tr;
	MergeSplitSegtree(int n, int e) : n(n)
	{
		int lg = 0;
		while ((1 << lg) < n) lg++;
		tr.reserve(1ULL * e * (lg + 1) + 5);
		tr.emplace_back();
	}
	int newnode()
	{
		if (free)
		{
			int i = free;
			free = tr[i][0];
			tr[i] = {};
			return i;
		}
		tr.emplace_back();
		return (int)tr.size() - 1;
	}
	void recycle(int i)
	{
		if (!i) return;
		tr[i][0] = free;
		tr[i][1] = 0;
		tr[i][2] = 0;
		free = i;
	}
	int size(int i) const{
		return i ? tr[i][2] : 0;
	}
	void pull(int i){
		tr[i][2] = size(tr[i][1]) + size(tr[i][0]);
	}
	void insert(int& i, int l, int r, int x)
	{
		if (!i) i = newnode();
		tr[i][2]++;
		if (l == r) return;
		int m = (l + r) >> 1;
		if (x <= m) insert(tr[i][0], l, m, x);
		else insert(tr[i][1], m + 1, r, x);
	}
	void insert(int& i, int x){
		insert(i, 1, n, x);
	}
	int merge(int x, int y, int l, int r)
	{
		if (!x or !y) return x | y;
		if (l == r)
		{
			tr[x][2] += tr[y][2];
			recycle(y);
			return x;
		}
		int m = (l + r) >> 1;
		int yl = tr[y][0];
		int yr = tr[y][1];
		tr[x][0] = merge(tr[x][0], yl, l, m);
		tr[x][1] = merge(tr[x][1], yr, m + 1, r);
		pull(x);
		recycle(y);
		return x;
	}
	int merge(int x, int y){
		return merge(x, y, 1, n);
	}
	void split(int p, int k, int& a, int& b, int l, int r)
	{
		if (!p) { a = b = 0;return; }
		if (k <= 0) { a = 0, b = p;return; }
		if (k >= tr[p][2]) { a = p, b = 0;return; }
		if (l == r)
		{
			a = newnode();
			tr[a][2] = k;
			b = p;
			tr[b][2] -= k;
			return;
		}
		int m = (l + r) >> 1;
		int sz = size(tr[p][0]);
		int q = newnode();
		if (k <= sz)
		{
			int al, bl;
			split(tr[p][0], k, al, bl, l, m);
			a = q;
			tr[a][0] = al;
			tr[a][1] = 0;
			b = p;
			tr[b][0] = bl;
			pull(a);
			pull(b);
		}
		else
		{
			int ar, br;
			split(tr[p][1], k - sz, ar, br, m + 1, r);
			a = p;
			tr[a][1] = ar;
			b = q;
			tr[b][0] = 0;
			tr[b][1] = br;
			pull(a);
			pull(b);
		}
	}
	void split(int p, int k, int& a, int& b){
		split(p, k, a, b, 1, n);
	}
	int kth(int i, int k, int l, int r) const
	{
		if (l == r) return l;
		int m = (l + r) >> 1;
		int sz = size(tr[i][0]);
		if (k <= sz) return kth(tr[i][0], k, l, m);
		return kth(tr[i][1], k - sz, m + 1, r);
	}
	int kth(int i, int k) const{
		return kth(i, k, 1, n);
	}
};