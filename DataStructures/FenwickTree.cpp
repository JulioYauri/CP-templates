int lso(int n) {return (n & (-n));}

// las consultas están indexadas en 1
template<typename T> 
struct FenwickTree {
    vector<T> ft; 
    FenwickTree(int m) {ft.assign(m + 1, 0);};
    T rsq(int j) {
        T sum = 0;
        for(; j; j -= lso(j)) sum += ft[j];
        return sum;
    }
    void upd(int i, T v) {
        for(; i < ft.size(); i += lso(i)) ft[i] += v;
    }
};
