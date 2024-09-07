const int MAXN = 200000 + 10;

vi tree[4 * MAXN];
vi arr;

void build(int v, int tl, int tr) {
	if(tl == tr) {
		tree[v] = vi(1, arr[tl]);
		return; 
	}

	int tm = (tl + tr) / 2;
	build(2 * v, tl, tm);
	build(2 * v + 1, tm + 1, tr);
	merge(tree[v * 2].begin(), tree[v * 2].end(), 
			tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(), 
			back_inserter(tree[v]));
	
}

int query(int v, int tl, int tr, int l, int r, int x) {
	if(l > r) return 0;
	if(l == tl && r == tr) {
		auto pos = upper_bound(tree[v].begin(), tree[v].end(), x);
		return tree[v].end() - pos; 
	}

	int tm = (tl + tr) / 2;
	return query(v * 2, tl, tm, l, min(r, tm), x) 
			+ query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
}