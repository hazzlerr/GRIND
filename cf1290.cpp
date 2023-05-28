// Forgot to upload yesterday :sob:

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
      string s; cin >> s;
      int n = sz(s);
      vec <vec <int>> pf(26, vec <int> (n));
      ++pf[s[0] - 'a'][0];
      for (int i = 1; i < n; ++i){
            pf[s[i] - 'a'][i] = 1;
            for (int j = 0; j < 26; ++j){
                  pf[j][i] += pf[j][i - 1];
            }
      }
      int q; cin >> q;
      while(q--){
            int l, r;
            cin >> l >> r, --l, --r;
            if (l == r){
                  cout << "Yes\n";
                  continue;
            }
            if (l + 1 == r){
                  cout << (s[l] == s[r] ? "No\n" : "Yes\n");
                  continue;
            }
            vec <int> cnt(26);
            int have = 0, big = 0;
            for (int i = 0; i < 26; ++i){
                  cnt[i] = pf[i][r] - (l ? pf[i][l - 1] : 0);
                  have += cnt[i] != 0;
                  big += cnt[i] > 1;
            }
            int small = have - big;
            if (s[l] != s[r]){
                  cout << "Yes\n";
                  continue;
            } 
            if (have > 2){
                  cout << "Yes\n";
                  continue;
            }
            cout << "No\n";
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
