#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 2e4 + 5;
pair<int, int> w[maxn];
int n, k;
LL m;

bool cmp_first_inv(const pair<int, int> &x, const pair<int, int> &y) {
	return x > y;
}

LL solve(int C) {
	LL ans = 0;
	set<pair<int, int>, decltype(&cmp_first_inv)> in(&cmp_first_inv), in_max_delta(&cmp_first_inv);
	set<pair<int, int>> notin;
	for (int i = 1; i <= C; i++) {
		ans += w[i].first;
		in.emplace(w[i].first, i);
		in_max_delta.emplace(w[i].first - w[i].second, i);
	}
	for (int i = C + 1; i <= n; i++) {
		notin.emplace(w[i].second, i);
	}
	for (int i = 1; i <= k; i++) {
		int mx1 = -1;
		if (!in.empty() && !notin.empty()) {
			mx1 = in.begin()->first - notin.begin()->first;
		}
		int mx2 = -1;
		if (!in_max_delta.empty()) {
			mx2 = in_max_delta.begin()->first;
		}
		if (max(mx1, mx2) < 0)
			break;
		if (mx1 > mx2) {
			// replace
			ans -= mx1;

			auto in_it = in.begin();
			auto notin_it = notin.begin();
			int notin_id = notin_it->second;
			int in_id = in_it->second;

			notin.emplace(w[in_id].second, in_id);
			in.erase(in_it);
			notin.erase(notin_it);
		} else {
			// inplace
			ans -= mx2;

			auto in_max_delta_it = in_max_delta.begin();
			int id = in_max_delta_it->second;
			in.erase(make_pair(w[id].first, id));
			in_max_delta.erase(in_max_delta_it);
		}
	}
	return ans;
}

int main() {
	// freopen("test.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		cin >> w[i].first >> w[i].second;
	sort(w + 1, w + 1 + n);
	int ans = -1;
	int l = 0, r = n;
	while (l <= r) {
		int mid = (l + r) / 2;
		LL need = solve(mid);
		if (need <= m) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	cout << ans;

	return 0;
}
