#include<bits/stdc++.h>
//#include <boost/multiprecision/cpp_int.hpp>
#include<random>
#include <execution>
#include <immintrin.h> 
#include <numbers>
#include <cassert>
#ifdef _MSC_VER
#include<boost/multiprecision/cpp_int.hpp>
using i128 = boost::multiprecision::int128_t;
using u128 = boost::multiprecision::uint128_t;
#else
using i128 = __int128_t;
using u128 = __uint128_t;
#endif
using ll  = long long;
using u64 = uint64_t;
using i64 = int64_t;
using u32 = unsigned; 
using ull = unsigned long long;
constexpr int mod = 998244353, gen = 3;
constexpr int M = 1e9 + 7;
constexpr int N = 2e5 + 1;
constexpr int INF = 1e9 + 1;
constexpr ll inf = (ll)1e18;
constexpr double eps = 1e-8;
constexpr auto PI = std::numbers::pi;
#define mid ((l+r)>>1)
#define ls i<<1
#define rs i<<1|1
template<class T>
auto& operator+=(std::vector<T>& _Val, T&& x) {
	_Val.emplace_back(std::forward<T>(x));
	return _Val;
}
template<class... T>
std::istream& operator>>(std::istream& in, std::tuple<T...>& a)
{
	std::apply([&in](auto&... x) { ((in >> x), ...); }, a);
	return in;
}
template<class T1, class T2>
std::ostream& operator<<(std::ostream& out, const std::pair<T1, T2>& a)
{
	static_assert(
		std::is_same_v<decltype(std::declval<std::ostream&>() << std::declval<T1>()), std::ostream&>,
		"T1 must support ostream output");
	static_assert(
		std::is_same_v<decltype(std::declval<std::ostream&>() << std::declval<T2>()), std::ostream&>,
		"T2 must support ostream output");
	out << a.first << " " << a.second << '\n';
	return out;
}
template<typename Stream, typename T>
concept InputStreamable = requires(Stream& s, T& t) {
	{ s >> t } -> std::same_as<Stream&>;
};
template<typename T1, typename T2>
	requires InputStreamable<std::istream, T1>&&
InputStreamable<std::istream, T2>
std::istream& operator>>(std::istream& in, std::pair<T1, T2>& a) {
	return in >> a.first >> a.second;
}
template<class T>
concept output_forward =
std::ranges::forward_range<T> and not std::is_convertible_v<T, const char*> and not std::is_convertible_v<T, char*> and not std::same_as<std::decay_t<T>, std::string>;
template<output_forward T>
std::ostream& operator<<(std::ostream& out, const T& a) {
	if (std::ranges::empty(a)) return out;
	for (const auto& x : a) out << x << " ";
	return out;
}
template <typename T>
concept input_forward = std::ranges::forward_range<T> and not std::same_as<std::decay_t<T>, std::string>;
template<input_forward T>
std::istream& operator>>(std::istream& in, T& a) {
	for (auto& x : a) in >> x;
	return in;
}
ll power(ll a, u64 b, int P = mod) {
	ll res = 1;
	for (; b != 0; b /= 2, a = ((a % P) * (a % P) % P)) {
		if (b & 1) res = (ll)((res % P) * (a % P)) % P;
	}
	return res % P;
}
ll inv(ll a, int P = mod) { return power(a, P - 2, P) % P; }
std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
int main()
{
	std::ios::sync_with_stdio(0); std::cin.tie(0);
	int T = 1;
	std::cin >> T;
	while (T--)
	{
        int n, q;
        std::cin >> n >> q;
        std::vector<int> a(n);
        std::cin >> a;
        std::array<int, 30> ans;
        int mx = std::ranges::max(a), mn = std::ranges::min(a);
        ans[0] = mx - mn;
        for (int i = 1; i < 30;i++)
        {
            std::priority_queue<int> q;
            for (int j = 0; j < n;j++){
                for (int k = j + 1; k < n;k++) {
                    if((int)q.size()<n)
                        q.emplace(a[j] ^ a[k]);
                    else if(q.top()>(a[j]^a[k]))
                        q.pop(), q.emplace(a[j] ^ a[k]);
                }
            }
            a.clear();
            while(!q.empty())
                a.emplace_back(q.top()), q.pop();
            assert(a.size() == n);
            ans[i] = std::ranges::max(a) - std::ranges::min(a);
        }
        while(q--)
        {
            int x;
            std::cin >> x;
            if(x>=30) {
                std::cout << 0 << '\n';
                continue;
            }
            std::cout << ans[x] << '\n';
        }
    }
}
//千里潇湘挼蓝浦，兰桡昔日曾经。月高风定露华清。微波澄不动，冷浸一天星。
//独倚危樯情悄悄，遥闻妃瑟泠泠。新声含尽古今情。曲终人不见，江上数峰青.  
//休将半路梅花岭，梦断相思玉茗堂
/*
　　　　　／＞　 フ
　　　　　| 　_　 _|
　 　　　／`ミ _x 彡
　　 　 /　　　 　 |
　　　 /　  ヽ　　 ?
　／￣|　　 |　|　|
　| (￣ヽ＿_ヽ_)_)
　＼二つ
 */

