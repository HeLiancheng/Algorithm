/*****************************************************************//**
 * \file   BIT.h
 * \brief  
 * This is the sample of BIT(Fenwick Tree)/Fenwick Tree.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<cstring>
#define MAX_LEN 10000
class BIT {
public:
	int tree[MAX_LEN];
	int N;
	BIT(int inpt[], int n) {
		N = n;
		memset(tree, 0, sizeof(tree));
		for (int i = 1; i <= n; ++i) {
			update(i, inpt[i]);
		}
	}
	inline void update(int idx, int val) {
		for (int i = idx; i < MAX_LEN; i += lowBit(i)) {
			tree[i] += val;
		}
	}
	int query(int findL, int findR) {
		return preSum(findR) - preSum(findL - 1);
	}
private:
	inline int lowBit(int x) {
		return (x) & (-x);
	}
	inline int preSum(int idx) {
		int cnt = 0;
		for (int i = idx; i; i -= lowBit(i)) {
			cnt += tree[i];
		}
		return cnt;
	}
};