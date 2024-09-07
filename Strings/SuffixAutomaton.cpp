const int MAX_LEN = 500000 + 10;
struct state{
	int len = 0; 
	int link = 0; 
	map<char, int> nxt; 
};

state st[MAX_LEN * 2];
int sz = 0, last = 0;

void SA_init() {
	st[0].len = 0; 
	st[0].link = -1; 
	sz++; 
	last = 0;
}

void SA_extend(char c) {  
	int cur = sz++; 
	st[cur].len = st[last].len + 1; 
	int p = last; 
	while(p != -1 && !st[p].nxt.count(c)) {
		st[p].nxt[c] = cur; 
		p = st[p].link; 
	}

	if(p == -1) {
		st[cur].link = 0; 
	}else{
		int q = st[p].nxt[c]; 
		if(st[p].len + 1 == st[q].len) { 
			st[cur].link = q; 
		}else{
			int clone = sz++; 
			st[clone].len = st[p].len + 1; 
			st[clone].nxt = st[q].nxt; 
			st[clone].link = st[q].link; 
			while(p != -1 && st[p].nxt[c] == q) {
				st[p].nxt[c] = clone; 
				p = st[p].link; 
			}
			st[q].link = st[cur].link = clone; 
		}
	}
	last = cur; 
}