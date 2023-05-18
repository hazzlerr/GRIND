// If you build suffix array, number of different substrings is equal to n * (n - 1) / 2 - (sum of lcp[i])
// I just support suffix array in online using lcp (to be more precise lcs, but idc)
// For some reason hashes with modulo tled, so I swapped them to ull and got ac..

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

const int mod = 1e9 + 7;

ull add(ull a, ull b){
      a += b;
      return a;
}

void inc(ull &a, ull b){
      a += b;
}

ull sub(ull a, ull b){
      a -= b;
      return a;
}

ull mul(ull a, ull b){
      return a * b;
}

const int N = 1e5 + 42, P = 73;

ull pp[N];

void precalc(){
      pp[0] = 1;
      for (int i = 1; i < N; ++i){
            pp[i] = mul(pp[i - 1], P);
      }
}

string cur;
ull ha[N];

int get(int l, int r){
      return mul(sub(ha[r], l ? ha[l - 1] : 0), pp[N - l - 1]);
}

int lcp(int i, int j){
      int rs = 0;
      for (int l = 16; ~l; --l){
            rs += 1 << l;
            if (min(i, j) + 1 < rs || get(i - rs + 1, i) != get(j - rs + 1, j)){
                  rs -= 1 << l;
            }
      }
      return rs;
}

struct comp{
      bool operator()(int i, int j) const {
            int le = lcp(i, j);
            if (min(i, j) + 1 == le) return i < j;
            return cur[i - le] < cur[j - le];
      }
};

inline int solve(){
      string q; cin >> q;
      set <int, comp> s;
      int pt = 0;
      ll ans = 0;
      for (char c: q){
            if (c == '-'){
                  auto it = s.lower_bound(pt - 1);
                  if (next(it) != s.end()){
                        ans += lcp(*it, *next(it));
                  }
                  if (it != s.begin()){
                        ans += lcp(*it, *prev(it));
                  }
                  it = s.erase(it);
                  if (it != s.end() && it != s.begin()){
                        ans -= lcp(*it, *prev(it));
                  }
                  ans -= pt;
                  --pt;
                  cur.pop_back();
            }
            else{
                  cur += c;
                  ha[pt] = mul((c - 'a' + 1), pp[pt]);
                  if (pt) inc(ha[pt], ha[pt - 1]);
                  auto it = s.lower_bound(pt);
                  if (it != s.end() && it != s.begin()){
                        ans += lcp(*it, *prev(it));
                  }
                  s.insert(pt);
                  it = s.find(pt);
                  if (it != s.begin()){
                        ans -= lcp(*it, *prev(it));
                  }
                  if (next(it) != s.end()){
                        ans -= lcp(*it, *next(it));
                  }
                  ++pt;
                  ans += pt;
            }
            cout << ans << "\n";
      }
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
