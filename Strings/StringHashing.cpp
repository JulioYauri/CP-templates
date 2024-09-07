
inline int add(int a, int b, const int &mod) { return a+b >= mod ? a+b-mod : a+b; }
inline int sbt(int a, int b, const int &mod) { return a-b < 0 ? a-b+mod : a-b; }
inline int mul(int a, int b, const int &mod) { return 1ll*a*b % mod; }

const int X[] = {257, 359}; // 31 43
const int MOD[] = {(int)1e9+7, (int)1e9+9};
const int N = 1e5 + 10;
int pows[N][2], ipows[N][2];
int h[2];

int binpow(int a, int exp, const int &mod) {
    int res = 1; 
    while(exp > 0) {
        if(exp % 2) res = mul(res, a, mod);
        a = mul(a, a, mod);
        exp >>= 1; 
    }
    return res; 
}

struct Hashing {
    string s;
    int n; 
    vvi ph; 

    Hashing(string &s) : s(s) { 
        n = s.size(); 
        ph.assign(n, vi(2));    
    }

    void build() {     
        for(int j = 0; j < 2; j++) {
            ph[0][j] = s[0];
            for(int i = 1; i < n; i++) {
                ph[i][j] = add(ph[i - 1][j], mul(pows[i][j], s[i], MOD[j]), MOD[j]);
            }
        }
    }

    pii substr_hash(int l, int r) {
        if(l == 0) return make_pair(ph[r][0], ph[r][1]);
        h[0] = mul(sbt(ph[r][0], ph[l - 1][0], MOD[0]), ipows[l][0], MOD[0]);
        h[1] = mul(sbt(ph[r][1], ph[l - 1][1], MOD[1]), ipows[l][1], MOD[1]);
        return make_pair(h[0], h[1]);
    }
};

void init() {
    for(int j = 0; j < 2; j++) {
        pows[0][j] = 1; 
        for(int i = 1; i < N; i++) pows[i][j] = mul(pows[i - 1][j], X[j], MOD[j]);
        ipows[N - 1][j] = binpow(pows[N - 1][j], MOD[j] - 2, MOD[j]);
        for(int i = N - 1; i > 0; i--) ipows[i - 1][j] = mul(ipows[i][j], X[j], MOD[j]);
    }
}
