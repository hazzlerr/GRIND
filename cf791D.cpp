// Could have done semi-smart dp, but I went braindead and wrote cd :skull:

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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

const int N = 2e5 + 42;

vec <int> g[N];
int ss[N], us[N];

void siz(int u, int p){
      ss[u] = 1;
      for (auto &v: g[u]){
            if (v != p && !us[v]){
                  siz(v, u), ss[u] += ss[v];
            }
      }
}

int cen(int u, int p, int n){
      for (auto &v: g[u]){
            if (v != p && !us[v] && ss[v] > n / 2){
                  return cen(v, u, n);
            }
      }
      return u;
}

int cen(int u){
      siz(u, u);
      return cen(u, u, ss[u]);
}

const int K = 5;

ll dp[K];
ll dst = 0;

void get(int u, int p, int h, vec <int> &d){
      d.push_back(h);
      for (auto &v: g[u]){
            if (v != p && !us[v]){
                  get(v, u, h + 1, d);
            }
      }
}

void dec(int u, int k){
      us[u] = 1;
      vec <int> cur(k);
      ll sum = 0, cnt = 1;
      cur[0] = 1;
      for (auto &v: g[u]) if (!us[v]){
            vec <int> d;
            get(v, u, 1, d);
            for (auto &x: d){
                  dst += sum + x * cnt;
                  int o = x % k;
                  for (int i = 0; i < k; ++i){
                        dp[(o + i) % k] += cur[i];
                  }
            }
            for (auto &x: d){
                  sum += x, ++cur[x % k], ++cnt;
            }
      }
      for (auto &v: g[u]){
            if (!us[v]) dec(cen(v), k);
      }
}

inline int solve(){
      int n, k;
      cin >> n >> k;
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      dec(cen(0), k);
      for (int i = 1; i < k; ++i){
            dst += (k - i) * dp[i];
      }
      cout << dst / k << "\n";
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
