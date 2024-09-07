struct TarjanSCC {
    vvi G;  // Lista de adyacencia
    vi st, low, num; 
    vi comp; 
    int n, timer; 
    int num_comps;

    TarjanSCC(int n_) : n(n_), num_comps(0) {
        G.resize(n);
        comp.assign(n, -1);
        low.resize(n);
        num.assign(n, -1);
        st.clear();
        timer = num_comps = 0; 
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
    }

    void DFS(int u) {
        num[u] = low[u] = timer++; 
        st.push_back(u);
        for(int v : G[u]) {
            if(num[v] == -1) {
                DFS(v);
                low[u] = min(low[u], low[v]);
            }else if(comp[v] == -1) low[u] = min(low[u], low[v]);
        }

        if(num[u] == low[u]) {
            int y = st.back();
            do {
                y = st.back();
                comp[y] = num_comps; 
                st.pop_back();
            } while(y != u);
            num_comps++; 
        }

    }

    void build_SCC() {
        for(int i = 0; i < n; i++) {
            if(num[i] == -1) DFS(i);
        }
    }

};
