// You just basically simulate the process

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

const int mod = 998244353;

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

int sub(int a, int b){
      a -= b;
      return a < 0 ? a + mod : a;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

int bpw(int a, int b){
      int r = 1;
      for (; b; b >>= 1, a = mul(a, a)){
            if (b & 1) r = mul(r, a);
      }
      return r;
}

int inv(int a){
      return bpw(a, mod - 2);
}

const int N = 1 << 20;

int fa[N], pp[N];

inline int solve(){
      int k; cin >> k;
      vec <int> a(1 << k);
      for (auto &i: a){
            cin >> i, i -= !!~i;
      }
      int ans = 1;
      while(sz(a) > 1){
            --k;
            vec <int> na(1 << k);
            int both = 0, cnt = 1 << k;
            int cut = (1 << k);
            for (int i = 0; i < cut; ++i){
                  if (a[i * 2] > a[i * 2 + 1]){
                        swap(a[i * 2], a[i * 2 + 1]);
                  }
                  if (!~a[i * 2]){
                        if (!~a[i * 2 + 1]){
                              ++both;
                              na[i] = -1;
                        }
                        else if (a[i * 2 + 1] >= cut){
                              --cnt;
                              na[i] = -1;
                        }
                        else na[i] = a[i * 2 + 1];
                  }
                  else{
                        if (a[i * 2 + 1] < cut || a[i * 2] >= cut){
                              cout << "0\n";
                              return 0;
                        }
                        na[i] = a[i * 2];
                        --cnt;
                  }
            }
            ans = mul(ans, mul(pp[both], fa[cnt]));
            a = na;
      }
      cout << ans << "\n";
      return 0;
}

inline void precalc(){
      fa[0] = pp[0] = 1;
      for (int i = 1; i < N; ++i){
            fa[i] = mul(fa[i - 1], i);
            pp[i] = mul(pp[i - 1], 2);
      }
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
