/*****************************************************************//**
 * \file   Utils.h
 * \brief  
 * Some common samples.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<vector>
#include<set>
#include<unordered_set>
#define PII pair<int, int>
using namespace std;

struct edge {
	int node;
	int length;
	int cost;
	//If you want to use emplace or emplace_back, you need to rewrite the constructor. If you use push or push_back, you don't need to do this.
	edge(int n, int l, int c) :node(n), length(l), cost(c) {}
	bool operator<(const edge& b) const {
		return this->length != b.length ? this->length > b.length : this->cost > b.cost;
	}
};
struct cmp {
	bool operator()(const edge& a, const edge& b) const {
		return a.length != b.length ? a.length > b.length : a.cost > b.cost;
	}
};
/**
 * Dijkstra algorithm O(N2).
 */
void djks_N2(int n, int s, vector<vector<int>> G, vector<bool>& vis, vector<int>& d);

/**
 * Dijkstra algorithm O(ElogN).
 */
void djks_ElogN(int n, int s, vector<vector<PII>> E, vector<bool>& vis, vector<int>& d);

/**
 * A sample of priority_queue using struct.
 * The question can be found in http://poj.org/problem?id=1724. The template of priority_queue is as follows
 */
int pq_bfs_struct(int K, int src, int dst, vector<vector<edge>>& v);

/**
 * A sample of priority_queue using bit.
 */
int pq_bfs_bit(int K, int src, int dst, vector<vector<int>>& v);

/**
 * A sample of Binary Search.
 * The question can be found in https://leetcode.cn/problems/split-array-largest-sum/description/
 */
int split_array(vector<int>& nums, int k);

/**
 * A sample of MST (Prim Algorithm).
 */
bool Prim(int n, vector<vector<int>>& v);

/**
 * A sample of MST (Kruskal Algorithm).
 */
bool Kruskal(int n, vector<vector<PII>>& v);
