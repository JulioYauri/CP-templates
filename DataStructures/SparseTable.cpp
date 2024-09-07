const int MX = 100000 + 5;
const int LG = 19; // 19 alcanza para 500000 
int spt[LG][MX];

void build(const vi &v) {
	int n = v.size();
	for (int i = 0; i < n; i++) spt[0][i] = v[i];
    for (int j = 0; j < LG-1; j++)
        for (int i = 0; i + (1 << (j + 1)) <= n; i++)
            spt[j + 1][i] = min(spt[j][i], spt[j][i + (1 << j)]);
}

int rmq(int i, int j) {
    int k = 31 - __builtin_clz(j - i + 1);
    return min(spt[k][i], spt[k][j - (1 << k) + 1]);
}