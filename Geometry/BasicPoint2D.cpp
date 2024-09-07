
struct P{
    ll x, y; 
    P() : x(0), y(0) {}
    P(ll x_, ll y_) : x(x_), y(y_) {}
    void read() { cin >> x >> y; }


    P operator - (const P& b) const { 
        return P(x - b.x, y - b.y); 
    }
    void operator-=(const P& b) {
        x -= b.x; 
        y -= b.y; 
    }

    ll operator *(const P& b) const { 
        return 1LL * x * b.y - 1LL * y * b.x; 
    }
    // si miro a Pb, en que lado queda c
    // positivo = izquierda
    ll triangle(const P& b, const P& c) const {
        return (b - *this) * (c - *this);
    }

    friend ostream& operator<<(ostream& os, const P& p) {
        os << p.x << " " << p.y; return os; 
    }

};

bool intersects(P p1, P p2, P p3, P p4) {
    if((p2 - p1) * (p4 - p3) == 0) { // paralelos
        if(p1.triangle(p2, p3) != 0) return false; // no colineales
        // ahora son colineales
        // bounding boxes
        for(int it = 0; it < 2; it++) {
            if(max(p1.x, p2.x) < min(p3.x, p4.x) 
                || max(p1.y, p2.y) < min(p3.y, p4.y)) return false; 
            swap(p1, p3); 
            swap(p2, p4);
        }
        return true; 
    }

    for(int it = 0; it < 2; it++) {
        ll t1 = p1.triangle(p2, p3), t2 = p1.triangle(p2, p4);
        if((t1 < 0 && t2 < 0) || (t1 > 0 && t2 > 0)) return false; 
        swap(p1, p3);
        swap(p2, p4);
    }   
    return true; 
}

bool on_boundary(P p, P p1, P p2) { // p está en el segmento p1p2 ? 
    if(p.triangle(p1, p2) != 0) return false; // no son colineales
    return min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x)
        && min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y);
}

ll polygon_area(const vector<P>& poly) { // dividir entre dos al final 
    int n = poly.size();
    ll ans = 0;
    for(int i = 1; i + 1 < n; i++) ans += poly[0].triangle(poly[i], poly[i + 1]);
    return abs(ans);
}

ll points_inside(const vector<P>& poly) { // teorema de pick
    int n = poly.size();
    ll on_boundary = 0; 
    for(int i = 0; i < n; i++) {
        // segmento entre p[i] y p[i + 1]; 
        P p1 = poly[i], p2 = poly[(i + 1) % n]; 
        p2 -= p1; 
        on_boundary += gcd(abs(p2.x), abs(p2.y));
    }
    // pick: Area = Inside + Boundary / 2  - 1
    //          2 * Area = 2 * Inside + Boundary - 2
    //          Inside = (2 * Area - Boundary + 2) / 2
    return (polygon_area(poly) - on_boundary + 2) / 2;
} 

vector<P> convex_hull(vector<P> points) {
    int n = points.size();
    sort(points.begin(), points.end(), [](P p1, P p2){
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    vector<P> hull; 
    for(int rep = 0; rep < 2; rep++) { // la primera halla el hull superior
        int S = hull.size();
        for(int i = 0; i < n; i++) {
            while((int)hull.size() >= S + 2) {
                P A = hull.end()[-2]; 
                P B = hull.end()[-1]; 
                // el <= incluye puntos colineales 
                if(A.triangle(B, points[i]) <= 0) break; 
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        hull.pop_back(); // derecha e izquierda se repiten 
        reverse(points.begin(), points.end());
    }
    return hull; 
}