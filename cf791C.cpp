// I'll put it here as a remainder that I spent 30 minutes solving it...

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
      int n, k;
      cin >> n >> k;
      vec <string> names;
      for (char a = 'A'; a <= 'Z' && sz(names) < 2 * n; ++a){
            for (char b = 'a'; b <= 'z' && sz(names) < 2 * n; ++b){
                  names.push_back(string(1, a) + string(1, b));
            }
      }
      vec <int> bad(n - k + 1);
      for (int i = 0; i < sz(bad); ++i){
            string s; cin >> s;
            bad[i] = (s == "NO");
      }
      vec <string> res(names.begin(), names.begin() + n);
      int pt = n;
      for (int i = 0; i < sz(bad); ++i){
            if (bad[i]){
                  if (i - k + 1 >= 0 && bad[i - k + 1]){
                        res[i + k - 1] = res[i];
                  }
                  else{
                        res[i] = res[i + k - 1] = names[pt++];
                  }
            }
      }
      for (auto &i: res){
            cout << i << " ";
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
