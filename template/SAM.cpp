#include <bits/stdc++.h>
using ll = long long;
struct SAM 
{
	static constexpr int ALPHABET_SIZE = 26;
	static constexpr int rt = 1;
	struct Node {
		int len;
		int link;
		std::array<int, ALPHABET_SIZE> next;
		Node() : len{}, link{}, next{} {}
	};
	std::vector<Node> t;
	SAM() { init(); }
	void init() {
		t.assign(2, Node());
		t[0].next.fill(1);
		t[0].len = -1;
	}
	int newNode() {
		t.emplace_back();
		return t.size() - 1;
	}
	int extend(int p, int c) 
	{
		if (t[p].next[c]) 
		{
			int q = t[p].next[c];
			if (t[q].len == t[p].len + 1) return q;
			int r = newNode();
			t[r].len = t[p].len + 1;
			t[r].link = t[q].link;
			t[r].next = t[q].next;
			t[q].link = r;
			while (t[p].next[c] == q) t[p].next[c] = r, p = t[p].link;
			return r;
		}
		int cur = newNode();
		t[cur].len = t[p].len + 1;
		while (!t[p].next[c]) t[p].next[c] = cur, p = t[p].link;
		t[cur].link = extend(p, c);
		return cur;
	}
	int extend(int p, char c, char offset = 'a') {
		return extend(p, c - offset);
	}

	int next(int p, int x) {
		return t[p].next[x];
	}

	int next(int p, char c, char offset = 'a') {
		return next(p, c - offset);
	}

	int link(int p) {
		return t[p].link;
	}

	int len(int p) {
		return t[p].len;
	}

	int size() {
		return t.size();
	}
};//自动机中，每个点表示一个endpos等价类，其link为第一个包含该点的超集
int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T = 1;
    //std::cin >> T;
    while(T--)
    {
        int n;
        std::string s;
        std::cin >> n >> s;
        SAM sam;
        int p = SAM::rt;
        for(auto& c:s)
            p = sam.extend(p, c);
        ll ans = 0;
        for (int i = 2; i < sam.size();i++)
            ans += sam.len(i) - sam.len(sam.link(i));
        std::cout << ans << '\n';
    }
}