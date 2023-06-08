/*
  Time: 13:06
  Num of Submissions: 3
  Analysis: I noticed small constraints on ai and bi => thought about covering pairs of ai and bj with edges representing students => mcf => AC
            First I just did mcf until there was an answer but it (unsuprisingly) tled. Then I just reworked mcf a little and got AC
  Rating: 2159
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
 
struct edge{
      int u, v, f, w, c;
      edge() {}
      edge(int u, int v, int f, int w, int c): u(u), v(v), f(f), w(w), c(c) {}
};
 
const int A = 151, N = 2 * A + 1;
const ll inf = 1e18;
 
vec <int> g[N];
vec <edge> e;
 
void add(int u, int v, int w, int c){
//      cout << u << " " << v << " " << w << "\n";
      g[u].push_back(sz(e));
      e.push_back({u, v, 0, w, c});
      g[v].push_back(sz(e));
      e.push_back({v, u, 0, -w, 0});
}
 
pair <bool, ll> mcf(int n, int maxf, int s, int t, vec <ll> &ans){
      int flow = 0;
      ll cost = 0;
      while(flow < maxf){
            vec <int> id(n, 1), p(n);
            vec <ll> d(n, inf);
            deque <int> q;
            q.push_back(s);
            d[s] = 0;
            while(!q.empty()){
                  int u = q.front();
                  q.pop_front();
                  id[u] = 0;
                  for (auto &i: g[u]){
                        auto [u, v, f, w, c] = e[i];
                        if (f < c && umin(d[v], d[u] + w)){
                              p[v] = i;
                              if (id[v]){
                                    q.push_back(v);
                              }
                              else{
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
            ans.push_back(cost);
            u = t;
            while(u != s){
                  int i = p[u];
                  e[i].f += f, e[i ^ 1].f -= f;
                  u = e[i].u;
            }
      }
      return {flow == maxf, cost};
}
 
inline int solve(){
      int n; cin >> n;
      for (int i = 0; i < n; ++i){
            int a, b, c;
            cin >> a >> b >> c;
            add(a, A + b, -c, 1);
      }
      for (int i = 1; i < A; ++i){
            add(0, i, 0, 1);
            add(A + i, N - 1, 0, 1);
      }
      int k = 1;
      vec <ll> ans;
      mcf(N, A, 0, N - 1, ans);
      cout << sz(ans) << "\n";
      for (auto &i: ans){
            cout << -i << "\n";
      }
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
