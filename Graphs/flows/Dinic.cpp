// O (V^2 E) pero es veloz en práctica
// para obtener los valores de flujo: 
// revisar aristas con capacidad > 0 
// las aristas con capacidad = 0 son residuales 
struct Edge {
    int u, v; 
    ll cap, flow; 
    Edge() {}; 
    Edge(int u, int v, ll cap) : u(u), v(v), cap(cap), flow(0) {}
};
struct Dinic {
    int n; 
    vector<Edge> E; 
    vvi g; 
    vi d, pt; 
    Dinic(int n): n(n), E(0), g(n), d(n), pt(n) {}
 
    void add_edge(int u, int v, ll cap) {
        E.emplace_back(u, v, cap);
        g[u].emplace_back(int(E.size()) - 1);
        E.emplace_back(v, u, 0);
        g[v].emplace_back(int(E.size()) - 1);
    }
 
    bool BFS(int S, int T) {
        queue<int> q; q.push(S);
        fill(d.begin(), d.end(), n + 1);
        d[S] = 0; 
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(u == T) break;
            for(int k : g[u]) {
                Edge &e = E[k]; 
                if(e.flow < e.cap && d[e.v] > d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1; 
                    q.emplace(e.v);
                }
            }
        }
        return d[T] != n + 1; 
    }
 
    ll DFS(int u, int T, ll flow = -1) {
        if(u == T || flow == 0) return flow; 
        for(int &i = pt[u]; i < int(g[u].size()); i++) {
            Edge &e = E[g[u][i]]; 
            Edge &oe = E[g[u][i] ^ 1]; 
            if(d[e.v] == d[e.u] + 1) {
                ll amt = e.cap - e.flow; 
                if(flow != -1 && amt > flow) amt = flow; 
                if(ll pushed = DFS(e.v, T, amt)) {
                    e.flow += pushed; 
                    oe.flow -= pushed;
                    return pushed; 
                }
            }
        }
        return 0; 
    }
 
    ll max_flow(int S, int T) {
        ll total = 0; 
        while(BFS(S, T)) {
            fill(pt.begin(), pt.end(), 0);
            while(ll flow = DFS(S, T)) total += flow; 
        }
        return total; 
    }
 
};