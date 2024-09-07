const int INF = 2e6 + 1; 
const int N = 2e6 + 20;
int tree[N * 4 + 10];
int lazy[N * 4 + 10];
int arr[N + 10]; 
 // add on range, max on range 
void build(int v, int tl, int tr) {
	if(tl == tr) {
        tree[v] = arr[tl]; 
		return; 
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm + 1, tr);
	tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}
 
void push(int v) {
    tree[v * 2] += lazy[v]; 
    lazy[v * 2] += lazy[v]; 
    tree[v * 2 + 1] += lazy[v]; 
    lazy[v * 2 + 1] += lazy[v]; 
    lazy[v] = 0;
}	
 
void update(int v, int tl, int tr, int l, int r, int adding) {
	if(l > r) return; 
	if(l == tl && r == tr) {
		tree[v] += adding; 
		lazy[v] += adding; 
		return; 
	}
	push(v);
	int tm = (tl + tr) / 2;
	update(v * 2, tl, tm, l, min(r, tm), adding);
	update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, adding);
	tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
}
 
int query(int v, int tl, int tr, int l, int r) {
	if(l > r) return -1;
	if(l == tl && r == tr) return tree[v];
	push(v);
	int tm = (tl + tr) / 2;
	return max(query(v * 2, tl, tm, l, min(r, tm)) 
		 ,query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
}
 