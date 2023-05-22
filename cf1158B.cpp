// I just observed the pattern (but for some reason it took me 50 minutes..)

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

bool check(string s, int n, int k){
      for (int j = 1; j <= n; ++j){
            map <string, int> cnt;
            for (int i = 0; i + j <= n; ++i){
                  ++cnt[s.substr(i, j)];
            }
            for (auto [_, c]: cnt){
                  if (c == 1){
                        return j == k;
                  }
            }
      }
      return 0;
}

inline int solve(){
//      for (int n = 9; n <= 12; ++n){
//            vec <string> res(n + 1);
//            for (int msk = 0; msk < (1 << n); ++msk){
//                  string s;
//                  for (int i = 0; i < n; ++i){
//                        s += (msk >> i & 1) + '0';
//                  }

//            }
//            for (int k = 1; k <= n; ++k){
//                  if (!res[k].empty()){
//                        cout << n << " " << k << ": " << res[k] << "\n";
//                  }
//            }
//      }
      auto run = [&](int n, int k){
      string res(n, '0');
      if (n == k){
            res = string(n, '0');
      }
      else{
            int per = (n - k) / 2;
            for (int i = 0; i < n; i += per + 1){
                  int st = ~n & 1;
                  for (int j = i; j < min(n - st, i + per); ++j){
                        res[st + j] = '1';
                  }
            }
            //cout << res << "\n";
      }
      cout << res << "\n";
//      assert(check(res, n, k));
      };
      int n, k;
      cin >> n >> k;
      run(n, k);
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
