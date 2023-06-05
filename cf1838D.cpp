/*
  Time: Didn't solve during contest
  Num Submissions: 10
  Learned: THINK SIMPLER
  Analysis: I almost instantly understood the idea with "((" and "))" but for some reason couldn't think everything through carefully. 
            I guess I need to sleep more
  Rating: ???
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
      int n, q;
      cin >> n >> q;
      string s; cin >> s;
      set <int> op, cl;
      auto upd = [&](int i){
            if (i >= 0 && i + 1 < n){
                  if (s[i] == s[i + 1]){
                        (s[i] == '(' ? op : cl).insert(i);
                  }
            }
      };
      auto del = [&](int i){
            if (i >= 0 && i + 1 < n){
                  if (s[i] == s[i + 1]){
                        (s[i] == '(' ? op : cl).erase(i);
                  }
            }
      };
      for (int i = 0; i < n; ++i) upd(i);
      while(q--){
            int i; cin >> i, --i;
            del(i), del(i - 1);
            s[i] = s[i] == '(' ? ')' : '(';
            upd(i), upd(i - 1);
            if (s[0] == ')' || s[n - 1] == '('){
                  cout << "NO\n";
                  continue;
            }
            if (n % 2){
                  cout << "NO\n";
                  continue;
            }
            if (op.empty() || cl.empty()){
                  cout << (op.empty() && cl.empty() ? "YES\n" : "NO\n");
                  continue;
            }
            int op1 = *op.begin(), op2 = *op.rbegin();
            int cl1 = *cl.begin(), cl2 = *cl.rbegin();
            cout << (op1 < cl1 && op2 < cl2 ? "YES\n" : "NO\n");
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
