// SegTree Persistente
//
// SegTree de soma, update de somar numa posicao
//
// query(a, b, t) retorna a query de [a, b] depois de
// t updates
// update(a, x, t) faz um update v[a]+=x a partir de
// como era depois de t updates
//
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = 3e4+10, UPD = 2e5+10, LOG = 20;
const int MAXS = 4*MAX+UPD*LOG;

namespace perseg {
	ll seg[MAXS], lazy[MAXS];
	int T[UPD], L[MAXS], R[MAXS], cnt, t;
	int n, *v;

	ll build(int p, int l, int r) {
		if (l == r) return seg[p] = v[l];
		L[p] = cnt++, R[p] = cnt++;
		int m = (l+r)/2;
		return seg[p] = build(L[p], l, m) + build(R[p], m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		T[0] = cnt++;
		build(0, 0, n-1);
	}
	ll query(int a, int b, int p, int l, int r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		int m = (l+r)/2;
		return query(a, b, L[p], l, m) + query(a, b, R[p], m+1, r);
	}
	ll query(int a, int b, int tt) {
		return query(a, b, T[tt], 0, n-1);
	}
	ll update(int a, int x, int lp, int p, int l, int r) {
		if (l == r) return seg[p] = seg[lp]+x;

		int m = (l+r)/2;
		if (a <= m)
			return seg[p] = update(a, x, L[lp], L[p]=cnt++, l, m) + seg[R[p]=R[lp]];
		return seg[p] = seg[L[p]=L[lp]] + update(a, x, R[lp], R[p]=cnt++, m+1, r);
	}
	void update(int a, int x, int tt=t) {
		update(a, x, T[tt], T[++t]=cnt++, 0, n-1);
	}
};
