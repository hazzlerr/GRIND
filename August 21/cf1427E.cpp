/*
  Time: 30:13
  Num of Submissions: 2
  Analysis: + and ^ are not related, so if we pick random numbers their sum will probably contribute to basis
  Difficulty: 2500
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const ll N = 1LL << 39;
const int L = 40;

ll b[L];
set <ll> have;
vec <string> ans;

void op(ll x, ll y, bool tp){
      ll nw = tp ? (x ^ y) : (x + y);
      if (have.count(nw)) return;
      ans.push_back(to_string(x) + (tp ? " ^ " : " + ") + to_string(y));
      have.insert(nw);
}

bool can(ll x){
      for (int i = 0; i < L; ++i){
            if (~x >> i & 1) continue;
            if (!b[i]) return 0;
            x ^= b[i];
      }
      return 1;
}

void add(ll x){
      for (int i = 0; i < L; ++i){
            if (~x >> i & 1) continue;
            if (!b[i]) return void(b[i] = x);
            op(x, b[i], 1);
            x ^= b[i];
      }
}

bool check(){
      ll x = 1;
      vec <ll> lol;
      for (int i = 0; i < L; ++i){
            if (~x >> i & 1) continue;
            if (!b[i]) return 0;
            if (need) lol.push_back(b[i]);
            x ^= b[i];
      } 
      reverse(all(lol));
      ll cur = 0;
      for (auto &i: lol){
            if (cur) op(cur, i, 1);
            cur ^= i;
      }
      return 1;
}

mt19937 rng(40);

ll get(){
      ll x = 0;
      for (int i = 0; i < L; ++i){
            if (b[i] && rng() % 2){
                  if (x) op(x, b[i], 1);
                  x ^= b[i];
            }
      }
      return x;
}

inline int solve(){
      ll x; cin >> x;
      add(x);
      while(!check()){
            ll x = get(), y = get();
            if (x + y < N && !can(x + y)){
                  op(x, y, 0), add(x + y);
            }
      }
      cout << sz(ans) << "\n";
      for (auto &i: ans){
            cout << i << "\n";
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
