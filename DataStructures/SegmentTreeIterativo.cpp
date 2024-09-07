// query = max [l, r)
// update = asignar en punto 
// indexa desde 0 
// 2 * n de memoria 
struct SegmentTree{
	vi tree; 
	int n;
	SegmentTree(int n) : n(n) , tree(2 * n + 5, 0) {}
	void upd(int p, int v){
		p += n; 
		for(tree[p] = v; p > 1; p>>=1) tree[p>>1] = max(tree[p],tree[p^1]);
	}
	int query(int l, int r){ // [l, r)
		int res = 0;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) res = max(res, tree[l++]);
			if(r & 1) res = max(res, tree[--r]);
		}
		return res;
	}
};