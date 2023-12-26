#include "mySort.h"
#include<algorithm>

static void heapify(vector<int>& v, int idx, int end) {
	int cur = idx, child = idx << 1 | 1;
	while (child < end) {
		if (child + 1 < end && v[child] < v[child + 1]) ++child;
		if (v[cur] >= v[child]) break;
		swap(v[cur], v[child]);
		cur = child;
		child = cur << idx << 1 | 1;
	}
}

void heapSort(vector<int>& v)
{
	//build heap
	int halfLen = v.size() >> 1;
	for (int i = halfLen - 1; i >= 0; --i) {
		heapify(v, i, v.size());
	}
	//sort
	for (int i = v.size() - 1; i > 0; --i) {
		swap(v[0], v[i]);
		heapify(v, 0, i);
	}
}

static int part(vector<int>& v, int l, int r) {
	int tmp = v[l];
	while (l < r) {
		while (l < r && tmp <= v[r]) --r;
		if (l < r) swap(v[l++], v[r]);
		while (l < r && tmp >= v[l]) ++l;
		if (l < r) swap(v[l], v[r--]);
	}
	return l;
}

void quickSort(vector<int>& v, int l, int r)
{
	if (l < r) {
		int mid = part(v, l, r);
		quickSort(v, l, mid - 1);
		quickSort(v, mid + 1, r);
	}
}
static void mergeProcess(vector<int>& v, vector<int>& v2, int l, int mid, int r) {
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) v2[k++] = v[i] <= v[j] ? v[i++] : v[j++];
	while (i <= mid) v2[k++] = v[i++];
	while (j <= r) v2[k++] = v[j++];
	while (l <= r) {
		v[l] = v2[l];
		++l;
	}
}

void mergeSort(vector<int>& v, vector<int>& v2, int l, int r) {
	if (l < r) {
		int mid = (l + r) >> 1;
		mergeSort(v, v2, l, mid);
		mergeSort(v, v2, mid + 1, r);
		mergeProcess(v, v2, l, mid, r);
	}
}
