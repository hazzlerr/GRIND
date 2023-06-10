/*
  Time:
  Num of Submissions: 
  Analysis: I first thought about dp on masks, then I understood that we don't care about particular elements. Also, minimum number of queries hints bfs
  Rating: 2300
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("avx2")

using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define all(m) (m).begin(), (m).end()
#define rall(m) (m).rbegin(), (m).rend()
#define vec vector
#define sz(a) (int) (a).size()
#define mpp make_pair
#define mtt make_tuple

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      bool dbg = 0;
      int n, k;
      cin >> n >> k;
      vec <int> a(n);
      if (dbg) for (auto &i: a) cin >> i;
      vec <int> us(n + 1), p(n + 1);
      vec <int> bfs = {0};
      us[0] = 0;
      for (int pt = 0; pt < sz(bfs); ++pt){
            int u = bfs[pt];
            for (int i = max(0, k + u - n); i <= min(k, u); ++i){
                  int v = u + (k - i) - i;
                  if (0 <= v && v <= n && !us[v]){
                        us[v] = 1, p[v] = i;
                        bfs.push_back(v);
                  }
            }
      }
      if (!us[n]){
            cout << "-1\n";
            fflush(stdout);
            return 0;
      }
      int res = 0;
      auto ask = [&](vec <int> &v){
            assert(sz(v) == k);
            if (dbg){
                  for (auto &i: v) res ^= a[i - 1];
                  return;
            }
            cout << "? ";
            for (auto &i: v){
                  cout << i << " ";
            }
            cout << "\n";
            fflush(stdout);
            int x; cin >> x;
            res ^= x;
      };
      int cur = n;
      vec <pii> lol;
      while(cur != 0){
            int f = p[cur], s = k - p[cur];
            lol.push_back({f, s});
            cur -= k - 2 * p[cur];
      }
      vec <int> have, other(n);
      iota(all(other), 1);
      reverse(all(lol));
      for (auto [f, s]: lol){
            assert(sz(have) >= f);
            assert(sz(other) >= s);
            vec <int> t1, t2, qq;
            while(f--){
                  qq.push_back(have.back());
                  t1.push_back(have.back());
                  have.pop_back();
            }
            while(s--){
                  qq.push_back(other.back());
                  t2.push_back(other.back());
                  other.pop_back();
            }
            other.insert(other.end(), all(t1));
            have.insert(have.end(), all(t2));
            ask(qq);
      }
      cout << "! " << res << "\n";
      fflush(stdout);
      return 0;
}

inline void precalc(){}

signed main(){
//      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
