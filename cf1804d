// just some greedy idk

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
      int n, m;
      cin >> n >> m;
      int mn = 0, mx = 0;
      while(n--){
            string s; cin >> s;
            {
                  vec <bool> mrk(m);
                  int k = m / 4;
                  for (int i = 0; i + 1 < m && k; ++i){
                        if (mrk[i] || mrk[i + 1]) continue;
                        if (s[i] == '1' && s[i + 1] == '1'){
                              mrk[i] = mrk[i + 1] = 1;
                              ++mn, --k;
                        }
                  }
                  for (int i = 0; i + 1 < m && k; ++i){
                        if (mrk[i] || mrk[i + 1]) continue;
                        if (s[i] == '1' || s[i + 1] == '1'){
                              mrk[i] = mrk[i + 1] = 1;
                              ++mn, --k;
                        }
                  }
                  for (int i = 0; i + 1 < m && k; ++i){
                        if (mrk[i] || mrk[i + 1]) continue;
                        mrk[i] = mrk[i + 1] = 1;
                        mn += s[i] == '1' || s[i + 1] == '1';
                        --k;
                  }
                  for (int i = 0; i < m; ++i){
                        mn += s[i] == '1' && !mrk[i];
                  }
            }

            {
                  vec <bool> mrk(m);
                  int k = m / 4;
                  for (int i = 0; i + 1 < m && k; ++i){
                        if (mrk[i] || mrk[i + 1]) continue;
                        if (s[i] == '0' || s[i + 1] == '0'){
                              mrk[i] = mrk[i + 1] = 1;
                              mx += s[i] == '1' || s[i + 1] == '1';
                              --k;
                        }
                  }
                  for (int i = 0; i + 1 < m && k; ++i){
                        if (mrk[i] || mrk[i + 1]) continue;
                        mrk[i] = mrk[i + 1] = 1;
                        mx += s[i] == '1' || s[i + 1] == '1';
                        --k;
                  }
                  for (int i = 0; i < m; ++i){
                        mx += s[i] == '1' && !mrk[i];
                  }
            }
      }
      cout << mn << " " << mx << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
