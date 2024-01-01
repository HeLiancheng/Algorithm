/*****************************************************************//**
 * \file   DisSetUnion.h
 * \brief  
 * This is a sample of DSU (Disjoint Set Union)
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<vector>
using namespace std;

class DSU{
public:
	DSU(int max_len) :parent(vector<int>(max_len)), rank(vector<int>(max_len, 0)) {
		for (int i = 0; i < max_len; ++i) parent[i] = i;
	}
	void merge(int x, int y) {
		parent[find(x)] = find(y);
	}
	void mergeUpgrade(int x, int y) {
		int rx = find(x), ry = find(y);
		if (rank[rx] < rank[ry]) parent[rx] = parent[ry];
		else{
			parent[ry] = parent[rx];
			if (rank[rx] > rank[ry])++rank[rx];
		}
	}

	void mergePathCompression(int x, int y) {
		if (isSame(x, y)) return;
		int xRoot = parent[x];
		for (int i = 0; i < parent.size(); ++i)
			if (parent[i] == y)parent[i] = xRoot;
	}
private:
	vector<int> parent, rank;
	inline int find(int x) {
		return parent[x] == x ? x : find(parent[x]);
	}

	inline int compressPath(int x) {
		return x == parent[x] ? x : parent[x] = compressPath(parent[x]);
	}

	bool isSame(int x, int y) {
		return find(x)==find(y);
	}
};
