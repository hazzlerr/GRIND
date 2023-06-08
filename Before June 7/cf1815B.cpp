// Graph other than straight line are not easy to use
// If we make a line, it's easy to find one end of a diameter and after that recover whole permutation

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

inline int solve(){
      int n; cin >> n;

      auto WHY = [&]{
            fflush(stdout);
            int why; cin >> why;
            if (why == -2) exit(0);
            return why;
      };
      auto ask = [&](int i, int j){
            cout << "? " << i << " " << j << "\n";
            return WHY();
      };

      if (n == 2){
            cout << "! 1 2 2 1\n"; WHY();
            return 0;
      }
      cout << "+ " << n + 1 << "\n"; WHY();
      cout << "+ " << n + 2 << "\n"; WHY();
      vec <int> ord(n);
      int l = 1, r = n;
      for (int i = 0; i < n; ++i){
            ord[i] = (i % 2 ? r-- : l++);
      }
      int mx = 0, en = 1;
      for (int i = 2; i <= n; ++i){
            if (umax(mx, ask(1, i))) en = i;
      }
      vec <int> p(n), q(n);
      p[en - 1] = ord[0];
      q[en - 1] = ord[n - 1];
      for (int i = 1; i <= n; ++i){
            if (i != en){
                  int ds = ask(en, i);
                  p[i - 1] = ord[ds];
                  q[i - 1] = ord[n - 1 - ds];
            }
      }
      cout << "! ";
      for (auto &i: p){
            cout << i << " ";
      }
      for (auto &i: q){
            cout << i << " ";
      }
      cout << "\n";
      WHY();
      return 0;
}

signed main(){
//      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      while(tst--) solve();
      return 0;
}
