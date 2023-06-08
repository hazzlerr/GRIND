// A cool way to think about correct bracket sequence - represent it with a tree, where '(' creates new node, and ')' returns current pointer to the parent
// The number of correct bracket subsequences on [l, r] is the sum of C(number of u's children, 2) for all u that lie in this range

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

struct bit{
      int n;
      vec <ll> t;
      bit() {}
      bit(int z): n(z + 5), t(z + 5) {}

      void upd(int p, ll x){
            for (p += 5; p < n; p += p & -p){
                  t[p] += x;
            }
      }

      ll get(int r){
            ll res = 0;
            for (r += 5; r > 0; r -= r & -r){
                  res += t[r];
            }
            return res;
      }

      ll get(int l, int r){
            return get(r) - get(l - 1);
      }
};

ll foo(int x){
      return x * ll(x + 1) / 2;
}

inline int solve(){
      int n, q;
      cin >> n >> q;
      string s; cin >> s;
      vec <int> st, mrk(n);
      int z = 5;
      for (int i = 0; i < n; ++i){
            if (s[i] == '('){
                  st.push_back(i);
            }
            else if (!st.empty()){
                  mrk[st.back()] = mrk[i] = 1, ++z;
                  st.pop_back();
            }
      }
      vec <vec <int>> g(z);
      vec <int> id(n), par(z);
      int cur = 0, v = 1;
      for (int i = 0; i < n; ++i){
            if (mrk[i]){
                  if (s[i] == '('){
                        g[cur].push_back(v);
                        par[v] = cur, cur = v++;
                        id[i] = cur;
                  }
                  else{
                        id[i] = cur;
                        cur = par[cur];
                  }
            }
      }
      bit t(2 * z + 42);
      vec <bit> sub(z);
      vec <int> fi(z), fo(z), sid(z), ss(z);
      int tmr = 0;
      auto dfs = [&](auto &&dfs, int u) -> void {
            fi[u] = tmr++;
            for (auto &v: g[u]) dfs(dfs, v);
            fo[u] = tmr++;
            ss[u] = sz(g[u]);
            t.upd(fi[u], +foo(ss[u]));
            sub[u] = bit(ss[u]);
            for (int i = 0; i < ss[u]; ++i){
                  sid[g[u][i]] = i;
                  sub[u].upd(i, 1);
            }
      }; dfs(dfs, 0);

      while(q--){
            int tp, l, r;
            cin >> tp >> l >> r, --l, --r;
            if (tp == 1){
                  int u = id[l], pu = par[u];
                  sub[pu].upd(sid[u], -1);
                  t.upd(fi[pu], -foo(ss[pu]--));
                  t.upd(fi[pu], +foo(ss[pu]));
            }
            else{
                  int u = id[l], v = id[r];
                  int pu = par[u];
                  ll ans = t.get(fi[u], fo[v]);
                  ans += foo(sub[pu].get(sid[u], sid[v]));
                  cout << ans << "\n";
            }
      }
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
