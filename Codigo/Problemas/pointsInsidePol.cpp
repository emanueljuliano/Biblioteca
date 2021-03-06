// Points Inside Polygon
//
// Encontra quais pontos estao
// dentro de um poligono simples nao convexo
// o poligono tem lados paralelos aos eixos
// Pontos na borda estao dentro
// Pontos podem estar em ordem horaria ou anti-horaria
//
// O(n log(n))

#define f first
#define s second
#define pb push_back

typedef long long ll;
typedef pair<int, int> ii;

const ll N = 1e9+10;
const int MAX = 1e5+10;
int ta[MAX];

namespace seg {
	unordered_map<ll, int> seg;
	int query(int a, int b, ll p, ll l, ll r) {
		if (b < l or r < a) return 0;
		if (a <= l and r <= b) return seg[p];
		ll m = (l+r)/2;
		return query(a, b, 2*p, l, m)+query(a, b, 2*p+1, m+1, r);
	}
	int query(ll p) {
		return query(0, p+N, 1, 0, 2*N);
	}
	int update(ll i, int x, ll p, ll l, ll r) {
		if (i < l or r < i) return seg[p];
		if (l == r) return seg[p] += x;
		ll m = (l+r)/2;
		return seg[p] = update(i, x, 2*p, l, m)+update(i, x, 2*p+1, m+1, r);
	}
	void update(ll a, ll b, int x) {
		if (a > b) return;
		update(a+N, x, 1, 0, 2*N);	
		update(b+N+1, -x, 1, 0, 2*N);
	}
};

void pointsInsidePol(vector<ii>& pol, vector<ii>& v) {
	vector<pair<int, pair<int, ii> > > ev; // {x, {tipo, {a, b}}}
	// -1: poe ; id: query ; 1e9: tira
	for (int i = 0; i < v.size(); i++)
		ev.pb({v[i].f, {i, {v[i].s, v[i].s}}});
	for (int i = 0; i < pol.size(); i++) {
		ii u = pol[i], v = pol[(i+1)%pol.size()];
		if (u.s == v.s) {
			ev.pb({min(u.f, v.f), {-1, {u.s, u.s}}});
			ev.pb({max(u.f, v.f), {N, {u.s, u.s}}});
			continue;
		}
		int t = N;
		if (u.s > v.s) t = -1;
		ev.pb({u.f, {t, {min(u.s, v.s)+1, max(u.s, v.s)}}});
	}

	sort(ev.begin(), ev.end());
	for (int i = 0; i < v.size(); i++) ta[i] = 0;
	for (auto i : ev) {
		pair<int, ii> j = i.s;
		if (j.f == -1) seg::update(j.s.f, j.s.s, 1);
		else if (j.f == N) seg::update(j.s.f, j.s.s, -1);
		else if (seg::query(j.s.f)) ta[j.f] = 1; // ta dentro
	}
}
