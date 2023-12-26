#include"utils.h"
#include<queue>
constexpr int INF = 1e9;

void djks_N2(int n, int s, vector<vector<int>> G, vector<bool>& vis, vector<int>& d) {
	fill(vis.begin(), vis.end(), false);
	fill(d.begin(), d.end(), INF);
	d[s] = 0;
	for (int i = 0; i < n; ++i) {
		int mn = INF;
		int u = -1;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && mn > d[j]) {
				mn = d[j];
				u = j;
			}
		}
		if (u == -1)return;
		vis[u] = true;
		for (int j = 0; j < n; ++j) {
			if (!vis[j] && d[u] + G[u][j] < d[j]) {
				d[j] = d[u] + G[u][j];
			}
		}
	}
}

//The pair of edge (E) is <destination, edge_weight>, the pair of pq is <distance, destination> for sort.
//Note that priority queue defaults to Max-Heap. 
void djks_ElogN(int n, int s, vector<vector<PII>> E, vector<bool>& vis, vector<int>& d) {
	fill(vis.begin(), vis.end(), false);
	fill(d.begin(), d.end(), INF);
	d[s] = 0;
	priority_queue <PII, vector<PII>, greater<PII>> pq;
	pq.push({ 0,s });
	while (!pq.empty()) {
		auto tmp = pq.top();
		if (vis[tmp.second])continue;
		vis[tmp.second] = true;
		pq.pop();
		for (auto i : E[tmp.second]) {
			if (!vis[i.first] && d[tmp.second] + i.second < d[i.first]) {
				d[i.first] = d[tmp.second] + i.second;
				pq.push({ d[i.first],i.first });
			}
		}
	}
}

int pq_bfs_struct(int K, int src, int dst, vector<vector<edge>>& v) {
	priority_queue<edge> pq;
	//If you don't overload the comparison operator, write the comparison function cmp.
	//priority_queue<edge, vector<edge>, cmp> pq;
	pq.emplace(src, 0, 0);
	while (!pq.empty()) {
		auto tmp = pq.top();
		pq.pop();
		if (tmp.node == dst)return tmp.length;
		for (auto it : v[tmp.node]) {
			int tCost = tmp.cost + it.cost;
			if (tCost <= K) {
				pq.emplace(it.node, tmp.length + it.length, tCost);
			}
		}
	}
	return -1;
}

int pq_bfs_bit(int K, int src, int dst, vector<vector<int>>& v) {
	priority_queue<int> pq;
	pq.emplace(-src);
	while (!pq.empty()) {
		int tmp = -pq.top();
		pq.pop();
		int node = (int)(tmp & 0x7f);
		if (node == dst)return tmp >> 19 & 0xfff;
		for (auto it : v[node]) {
			int tCost = (tmp >> 7 & 0xfff) + (it >> 7 & 0xfff);
			int tLength = (tmp >> 19 & 0xfff) + (it >> 19 & 0xfff);
			if (tCost <= K) {
				pq.emplace(-(tLength << 19 | tCost << 7 | (it & 0x7f)));
			}
		}
	}
	return -1;
}

static int check(vector<int>& nums, int mid, int k) {
	int cnt = 1, tsum = 0;
	for (int i : nums) {
		if (tsum + i > mid) {
			cnt++;
			tsum = i;
		}
		else {
			tsum += i;
		}
	}
	return cnt <= k;
}

int split_array(vector<int>& nums, int k) {
	int l = 0, r = 0;
	for (int i : nums) {
		l = l < i ? i : l;
		r += i;
	}

	//Note the border of Binary Search, you can also choose to use ( r = mid - 1, and while (l <= r)) here.
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(nums, mid, k)) {
			r = mid;
		}
		else {
			l = mid + 1;
		}
	}
	return l;
}
