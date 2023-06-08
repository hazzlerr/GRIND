/*
  Time: 35:04
  Num of Submissions: 1
  Learned: How to win Nim-game
  Analysis: I knew how to win Nim (or at least I thought that it was possible), 
            but I did not remember the "symmetry" strategy for l != r (even though I remember solving similiar problem)
  Rating: 2533
*/

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

inline int solve(){
      int n, L, R;
      cin >> n >> L >> R;

      auto say = [&](int i, int len){
            cout << i << " " << len << "\n";
            fflush(stdout);
      };
      auto get = [&](){
            int i, len;
            cin >> i >> len;
            if (i == len && (i == -1 || i == 0)){
                  exit(0);
            }
            return mpp(i, len);
      };

      if (L != R){
            int s = L + (L % 2 != n % 2);
            cout << "First\n";
            fflush(stdout);
            say(n / 2 + 1 - s / 2, s);
            while(true){
                  auto [i, len] = get();
                  say(n - i + 1 - len + 1, len);
            }
      }

      vec <int> dp(n + 1);
      for (int i = 1; i <= n; ++i){
            set <int> s;
            for (int j = 0; j + L <= i; ++j){
                  s.insert(dp[j] ^ dp[i - j - L]);
            }
            while(s.count(dp[i])) ++dp[i];
      }
      
      int cur = dp[n];
      set <pii> s;
      s.insert({n, 1});

      auto turn = [&](int i, int len){
            auto [r, l] = *s.lower_bound({i, 0});
            s.erase({r, l});
            cur ^= dp[r - l + 1];
            if (i - 1 >= l){
                  s.insert({i - 1, l});
                  cur ^= dp[i - l];
            }
            if (i + len <= r){
                  s.insert({r, i + len});
                  cur ^= dp[r - (i + len) + 1];
            }
      };

      auto bot = [&](){
            auto [i, len] = get();
            turn(i, len);
      };
      auto me = [&](){
            bool fl = 0;
            for (auto [r, l]: s){
                  int len = r - l + 1;
                  for (int j = 0; j + L <= len; ++j){
                        if (cur == (dp[len] ^ dp[j] ^ dp[len - j - L])){
                              say(l + j, L), turn(l + j, L);
                              fl = 1;
                              break;
                        }
                  }
                  if (fl) break;
            }
            if (!fl){
                  cout << "FUUU\n";
                  exit(0);
            }
      };

      if (cur){
            cout << "First\n";
            fflush(stdout);
            me();
      }
      else{
            cout << "Second\n";
            fflush(stdout);
      }
      while(true) bot(), me();
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
