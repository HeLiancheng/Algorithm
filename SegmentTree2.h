/*****************************************************************//**
 * \file   SegmentTree2.h
 * \brief  
 * This is the sample of SegmentTree with lazy label(update a piece of data).
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#define MAX_LEN 10000
#define kl k<<1
#define kr k<<1|1

class SegTree {
public:
	SegTree(int inpt[],int n) {
		arr = inpt;
		N = n;
		build(1, n, 1);
	}
	
	void updateSeq(int l, int r, int updateL, int updateR, int val, int k) {
		if (updateL <= l && updateR >= r) {
			tree[k].val += (r - l + 1) * val;
			tree[k].lazy = val;
			return;
		}
		pushDown(l, r, k);
		int mid = (l + r) >> 1;
		if (updateL <= mid) updateSeq(l, mid, updateL, updateR, val, kl);
		if (updateR > mid) updateSeq(mid + 1, r, updateL, updateR, val, kr);
		tree[k].val = tree[kl].val + tree[kr].val;
	}

	int query(int l, int r, int findL, int findR, int k) {
		if (findL <= l && findR >= r) return tree[k].val;
		pushDown(l, r, k);
		int mid = (l + r) >> 1;
		int cnt = 0;
		if (findL <= mid) cnt += query(l, mid, findL, findR, kl);
		if (findR > mid) cnt += query(mid + 1, r, findL, findR, kr);
		return cnt;
	}

private:
	struct Node {
		int val;
		int lazy;
	};
	int* arr;
	Node tree[MAX_LEN];
	int N;
	void build(int l, int r, int k) {
		if (l == r) tree[k].val = arr[l - 1];
		else {
			int mid = (l + r) >> 1;
			build(l, mid, kl);
			build(mid + 1, r, kr);
			tree[k].val = tree[kl].val + tree[kr].val;
		}
	}
	inline void f(int l, int r, int val, int k) {
		tree[k].val += (r - l + 1) * tree[k].lazy;
		tree[k].lazy = val;
	}
	inline void pushDown(int l, int r, int k) {
		if (tree[k].lazy) {
			int mid = (l + r) >> 1;
			f(kl, l, mid, tree[k].lazy);
			f(kr, mid + 1, r, tree[k].lazy);
			tree[k].lazy = 0;
		}
	}
};
