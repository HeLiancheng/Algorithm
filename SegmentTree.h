/*****************************************************************//**
 * \file   SegmentTree.h
 * \brief  
 * This is the sample of SegmentTree(update single data).
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#define MAX_LEN 10000
#define kl k<<1
#define kr k<<1|1

class SegmentTree {
public:
	SegmentTree(int inpt[], int n) {
		arr = inpt;
		build(1, n, 1);
	}

	void build(int l, int r, int k) {
		if (l == r) {
			tree[k] = arr[l - 1];
		}
		else {
			int mid = l + (r - l) >> 1;
			build(l, mid, kl);
			build(mid + 1, r, kr);
			tree[k] = tree[kl] + tree[kr];
		}
	}

	void updateSingle(int l, int r, int idx, int val, int k) {
		int mid = l + (r - l) >> 1;
		if (l == r) {
			tree[k] = val;
			arr[idx] = val;
			return;
		}
		if (mid >= idx) {
			updateSingle(l, mid, idx, val, kl);
		}
		else {
			updateSingle(mid + 1, r, idx, val, kr);
		}
		tree[k] = tree[kl] + tree[kr];
	}

	int query(int l, int r, int findl, int findr, int k) {
		if (findl <= l && findr >= r) {
			return tree[k];
		}
		int mid = (l + r) >> 1;
		int temp = 0;
		if (l <= mid)temp += query(l, mid, findl, findr, kl);
		if (r > mid)temp += query(mid + 1, r, findl, findr, kr);
		return temp;
	}

private:
	int* arr;
	int tree[MAX_LEN << 2];
};
