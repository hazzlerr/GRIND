// If we denote B as highest set bit in array, we don't need to make more than 1 edge bettwen numbers with B'th bit set and numbers with B'th bit unset
// Then, we can do a recursion where we find minimum edge between two components using bit trie (it will be nlog^2A but smh it works really fast)

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

const int N = 2e5 + 42, L = 30;

int bo[N * L][2], cnt = 0;

void clean(){
      for (int i = 0; i <= cnt; ++i){
            bo[i][0] = bo[i][1] = 0;
      }
      cnt = 0;
}

void add(int x){
      int v = 0;
      for (int i = L; ~i; --i){
            int b = x >> i & 1;
            if (!bo[v][b]) bo[v][b] = ++cnt;
            v = bo[v][b];
      }
}

int get(int x){
      int res = 0, v = 0;
      for (int i = L; ~i; --i){
            int b = x >> i & 1;
            if (bo[v][b]){
                  v = bo[v][b];
            }
            else{
                  res += 1 << i;
                  v = bo[v][b ^ 1];
            }
      }
      return res;
}

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      sort(all(a));
      a.erase(unique(all(a)), a.end());
      auto rec = [&](auto &&rec, vec <int> &cur, int bt) -> ll{
            if (bt == -1) return 0LL;
            vec <vec <int>> c(2);
            for (auto &i: cur){
                  c[i >> bt & 1].push_back(i);
            }
            if (c[0].empty() || c[1].empty()){
                  return rec(rec, c[0].empty() ? c[1] : c[0], bt - 1);
            }
            int we = 1 << 30;
            clean();
            for (auto &i: c[0]) add(i);
            for (auto &i: c[1]) umin(we, get(i));
            return rec(rec, c[0], bt - 1) + rec(rec, c[1], bt - 1) + we;
      };
      cout << rec(rec, a, 30) << "\n";
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
