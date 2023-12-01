const uint32_t mod = 1e9 + 7;
//const uint32_t mod = 998244353;

struct mint{
      inline uint32_t nrm(int a){
            if (a >= mod) a -= mod;
            return a;
      }

      uint32_t x;

      mint(): x(0) {}

      mint(ll a) {
            a %= mod;
            if (a < 0) a += mod;
            x = a;
      }

      mint& operator+=(const mint &b){
            x = nrm(x + b.x);
            return *this;
      }
      mint& operator-=(const mint &b){
            x = nrm(mod + x - b.x);
            return *this;
      }
      mint& operator*=(const mint &b){
            x = x * ll(b.x) % mod;
            return *this;
      }

      mint bpw(ll b) const {
            mint r = 1, a = *this;
            if (b < 0){
                  b = -b, a = a.inv();
            }
            for (; b; b >>= 1, a *= a){
                  if (b & 1) r *= a;
            }
            return r;
      }
      mint inv() const {
            uint32_t t = x, res = 1;
            while(t != 1){
                  uint32_t d = mod / t;
                  res = res * ll(mod - d) % mod;
                  t = mod - t * d;
            }
            return res;
      }

      mint& operator /=(const mint &b){
            return *this *= b.inv();
      }

      mint operator+(const mint &b) const {
            return mint(*this) += b;
      }
      mint operator-(const mint &b) const {
            return mint(*this) -= b;
      }
      mint operator*(const mint &b) const {
            return mint(*this) *= b;
      }
      mint operator/(const mint &b) const {
            return mint(*this) /= b;
      }

      bool operator==(const mint &b) const {
            return x == b.x;
      }
      bool operator!=(const mint &b) const {
            return x != b.x;
      }
      bool operator<(const mint &b) const {
            return x < b.x;
      }
      bool operator>(const mint &b) const {
            return x > b.x;
      }

      friend istream& operator>>(istream &in, mint &a) { in >> a.x; return in; }
      friend ostream& operator<<(ostream &out, const mint &a) { out << a.x; return out; }
};
