// Since I have working mcf, I decided to ac this problem too
// BUT, I didn't know that without eps it can tl, so next time I will be more careful

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

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

struct edge{
      int u, v, f, c;
      double w;
      edge() {}
      edge(int u, int v, int f, int c, double w): u(u), v(v), f(f), c(c), w(w) {}
};

const int N = 2010, inf = 1e9 + 42;

vec <int> g[N];
vec <edge> e;

void add(int u, int v, int c, double w){
      g[u].push_back(sz(e));
      e.push_back(edge(u, v, 0, c, w));
      g[v].push_back(sz(e));
      e.push_back(edge(v, u, 0, 0, -w));
}

const double eps = 1e-9;

pair <int, double> mcf(int n, int maxf, int s, int t){
      int flow = 0;
      double cost = 0;
      while(flow < maxf){
            vec <int> id(n, 2), p(n);
            vec <double> d(n, inf);
            deque <int> q;
            q.push_back(s);
            d[s] = 0;
            while(!q.empty()){
                  int u = q.front();
                  q.pop_front();
                  id[u] = 0;
                  for (auto &i: g[u]){
                        auto [u, v, f, c, w] = e[i];
                        if (f < c && d[v] > d[u] + w + eps){
                              d[v] = d[u] + w;
                              p[v] = i;
                              if (id[v] == 2){
                                    q.push_back(v);
                              }
                              if (id[v] == 0){
                                    q.push_front(v);
                              }
                              id[v] = 1;
                        }
                  }
            }
            if (d[t] == inf) break;
            int f = maxf - flow;
            int u = t;
            while(u != s){
                  int i = p[u];
                  umin(f, e[i].c - e[i].f);
                  u = e[i].u;
            }
            flow += f, cost += f * d[t];
            u = t;
            while(u != s){
                  int i = p[u];
                  e[i].f += f, e[i ^ 1].f -= f;
                  u = e[i].u;
            }
      }
      return {flow, cost};
}

inline int solve(){
      int n, a, b;
      cin >> n >> a >> b;
      vec <double> p(n), u(n);
      for (auto &i: p) cin >> i;
      for (auto &i: u) cin >> i;
      int s = n, s1 = n + 1, s2 = n + 2, t = n + 3;
      add(s, s1, a, 0);
      add(s, s2, b, 0);
      for (int i = 0; i < n; ++i){
            add(s1, i, 1, -p[i]);
            add(s2, i, 1, -u[i]);
            add(i, t, 1, 0);
            add(i, t, 1, p[i] * u[i]);
      }
      auto [flow, cost] = mcf(n + 4, a + b, s, t);
      cout << fixed << setprecision(4) << -cost;
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
