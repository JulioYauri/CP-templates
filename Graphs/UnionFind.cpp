struct DSU{
	int n;
    vi par, sz; 
    DSU (int n_) : n(n_) {
        par.resize(n); sz.assign(n, 1);
        for(int i = 0; i < n; i++) par[i] = i; 
    }

    int get(int a) { return par[a] == a ? a : par[a] = get(par[a]); }
    void unite(int a, int b) {
        a = get(a), b = get(b);
        if(a == b) return; 
        sz[a] += b; 
        par[b] = a; 
    }

};