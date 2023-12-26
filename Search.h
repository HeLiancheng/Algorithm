/*****************************************************************//**
 * \file   Search.h
 * \brief  
 * This is the sample of DFS and BFS.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<vector>
#include<queue>
#define NODE_NUM 100
#define PII pair<int, int>
#define PII pair<int, int>

using namespace std;
class Search {
public:
	vector<int> edges[NODE_NUM];
	vector<int> visit;
	Search(vector<PII>& v) {
		visit.assign(NODE_NUM, 0);
		for (auto it : v) {
			edges[it.first].emplace_back(it.second);
			edges[it.second].emplace_back(it.first);
		}
	}

	int bfs(int source, int dst) {
		fill(visit.begin(), visit.end(), 0);
		queue<PII> q;
		visit[source] = 1;
		q.emplace(source, 0);
		while (!q.empty()) {
			PII tmp = q.front();
			q.pop();
			if (tmp.first == dst)return tmp.second;
			for (int node : edges[tmp.first]) {
				if (!visit[node]) {
					visit[node] = 1;
					q.emplace(node, tmp.second + 1);
				}
			}
		}
		return -1;
	}
	int mDfs(int source, int dst, int step) {
		if (source == dst)return step;
		int ret = INT_MAX;
		for (int node : edges[source]) {
			if (!visit[node]) {
				visit[node] = 1;
				ret = min(ret, mDfs(node, dst, step + 1));
				visit[node] = 0;
			}
		}
		return ret;
	}
	int dfs(int source, int dst) {
		fill(visit.begin(), visit.end(), 0);
		visit[source] = 1;
		return mDfs(source, dst, 0);
	}
};