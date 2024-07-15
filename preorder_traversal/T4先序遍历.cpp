#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, pn;
int L0[maxn], R0[maxn], fa0[maxn];
int L[maxn], R[maxn], fa[maxn];
int ls[maxn], pn_ls;
int last[maxn];
int sufmin[maxn];
inline bool is_dummy(int id) { return id > n; }
void recover() {
	memcpy(L, L0, sizeof(L[0]) * pn + 3);
	memcpy(R, R0, sizeof(R[0]) * pn + 3);
	memcpy(fa, fa0, sizeof(fa[0]) * pn + 3);
}
void dfs(int a) {
	ls[++pn_ls] = a;
	int i = pn_ls;
	if (L0[a] == 0 && !is_dummy(ls[pn_ls])) {
		L0[a] = ++pn;
		fa0[pn] = a;
	}
	if (L0[a])
		dfs(L0[a]);
	if (R0[a] == 0 && !is_dummy(ls[pn_ls])) {
		R0[a] = ++pn;
		fa0[pn] = a;
	}
	if (R0[a])
		dfs(R0[a]);
	last[i] = pn_ls;
}
void dfs_gen_ans(int a, vector<int> &ans) {
	ans.push_back(a);
	if (L[a] && !is_dummy(L[a])) {
		dfs_gen_ans(L[a], ans);
	}
	if (R[a] && !is_dummy(R[a])) {
		dfs_gen_ans(R[a], ans);
	}
}
void move(int tree_id, int pos_id) {
	int f = fa[tree_id];
	if (L[f] == tree_id)
		L[f] = 0;
	if (R[f] == tree_id)
		R[f] = 0;

	f = fa[pos_id];
	if (L[f] == pos_id)
		L[f] = tree_id;
	if (R[f] == pos_id)
		R[f] = tree_id;

	fa[tree_id] = fa[pos_id];
	fa[pos_id] = 0;
}
vector<int> solve1() {
	vector<int> ans;
	int target_tree = -1;
	int i, j;
	for (i = 1; i <= pn; i++) {
		if (is_dummy(ls[i]))
			continue;
		if (last[i] + 1 > pn)
			continue;
		j = last[i] + 1;
		if (is_dummy(ls[j])) {
			if (last[i] + 2 > n)
				continue;
			j = last[i] + 2;
		}
		if (ls[i] > ls[j]) {
			target_tree = i;
			break;
		}
	}
	if (target_tree == -1) {
		dfs_gen_ans(1, ans);
		return ans;
	}
	int target_pos = pn; // assert is_dummy(ls[target_pod])
	for (i = j + 1; i < pn; i++) {
		if (!is_dummy(ls[i]))
			continue;
		if (ls[i + 1] > ls[target_tree]) {
			target_pos = i;
			break;
		}
	}
	move(ls[target_tree], ls[target_pos]);
	dfs_gen_ans(1, ans);
	return ans;
}
vector<int> solve2() {
	sufmin[pn] = pn;
	for (int i = pn - 1; i >= 1; i--) {
		sufmin[i] = sufmin[i + 1];
		if (ls[i] < ls[sufmin[i]]) {
			sufmin[i] = i;
		}
	}
	for (int i = 1; i < pn; i++) {
		if (!is_dummy(ls[i]))
			continue;
		int j = i + 1; // assert is_dummy(ls[j])==false
		int sm = sufmin[i];
		if (ls[j] != ls[sm]) {
			move(ls[sm], ls[i]);
			break;
		}
	}
	vector<int> ans;
	dfs_gen_ans(1, ans);
	return ans;
}
int uset[maxn];
int find(int x) {
	if (x != uset[x])
		uset[x] = find(uset[x]);
	return uset[x];
}
bool mergeset(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return false;
	uset[a] = b;
	return true;
}
int main() {
	freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			uset[i] = i;
		pn = n;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &L0[i], &R0[i]);
			if (L0[i]) {
				fa0[L0[i]] = i;
				if (!mergeset(i, L0[i])) {
					assert(false);
					while (1)
						;
				}
			}
			if (R0[i]) {
				fa0[R0[i]] = i;
				if (!mergeset(i, R0[i])) {
					assert(false);
					while (1)
						;
				}
			}
		}
		pn_ls = 0;
		dfs(1);
		vector<int> ans[2];
		recover();
		ans[0] = solve1();
		assert(ans[0].size() == n);
		recover();
		ans[1] = solve2();
		assert(ans[1].size() == n);
		int p = 0;
		for (int i = 0; i < ans[0].size(); i++) {
			if (ans[0][i] < ans[1][i]) {
				p = 0;
				break;
			} else if (ans[0][i] > ans[1][i]) {
				p = 1;
				break;
			}
		}
		for (auto x : ans[p]) {
			printf("%d ", x);
		}
		putchar(10);

		memset(L, 0, sizeof(L[0]) * pn + 2);
		memset(L0, 0, sizeof(L[0]) * pn + 2);
		memset(R, 0, sizeof(L[0]) * pn + 2);
		memset(R0, 0, sizeof(L[0]) * pn + 2);
	}
	return 0;
}