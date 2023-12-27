/*****************************************************************//**
 * \file   BlockSplit.h
 * \brief  
 * This is a sample that uses block for search.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<algorithm>

#define MAX_LEN 50000
#define BLOCK_LEN 100
using namespace std;

class BlockSplit {
public:
	BlockSplit(int inpt[][2], int n) {
		idx = 0;
		arr = new int[MAX_LEN];
		idxSet = new int[MAX_LEN];
		fill(block[0], block[0] + 40 * 40, -1);
		init(inpt, n);
	}
	~BlockSplit() {
		delete[]arr;
		delete[]idxSet;
	}
	inline void addDot(int x, int y) {
		arr[idx] = x << 12 | y;
		int blockX = x / BLOCK_LEN, blockY = y / BLOCK_LEN;
		int tmp = block[blockX][blockY];
		block[blockX][blockY] = idx;
		idxSet[idx] = tmp;
		++idx;
	}

	int findNeighbor(int x, int y, int dis) {//dis <= 100
		int cnt = 0;
		int cx = x / BLOCK_LEN, cy = y / BLOCK_LEN;
		int sx = max(0, cx - 1), sy = max(0, cy - 1), dx = min(cx + 1, MAX_LEN - 1), dy = min(cy + 1, MAX_LEN - 1);
		for (int i = sx; i <= dx; ++i) {
			for (int j = sy; j <= dy; ++j) {
				int tmp = block[i][j];
				while (tmp != -1) {
					if (calDistance(x, y, arr[tmp] >> 12 & 0xfff, arr[tmp] & 0xfff) <= dis)++cnt;
					tmp = idxSet[tmp];
				}
			}
		}
		return cnt;
	}
	
private:
	int* arr, * idxSet;
	int idx;
	int block[40][40];

	void init(int inpt[][2], int n) {
		while (idx < n) addDot(inpt[idx][0], inpt[idx][1]);
	}

	inline int calDistance(int ax, int ay, int bx, int by) {
		return abs(ax - bx) + abs(ay - by);
	}
};