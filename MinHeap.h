/*****************************************************************//**
 * \file   MinHeap.h
 * \brief  
 * This is a sample of Min Heap.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#include<algorithm>
using namespace std;
class MinHeap {
public:
	int arr[10000];
	int size;
	MinHeap() {
		fill(arr, arr+10000, INT_MAX);
		size = 0;
	}
	void exchange(int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}
	void upToDown(int mnId) {
		while (mnId <= (size / 2)) {
			int mnChild;
			if (mnId * 2 + 1 <= size)
				mnChild = arr[mnId * 2] > arr[mnId * 2 + 1] ? mnId * 2 + 1 : mnId * 2;
			else
				mnChild = mnId * 2;
			if (arr[mnChild] >= arr[mnId])
				break;
			else
				exchange(mnId, mnChild);
			mnId = mnChild;
		}
	}
	void update(int child) {
		int father = child / 2;
		while (father) {
			int mnId;
			mnId = arr[father * 2] > arr[father * 2 + 1] ? father * 2 + 1 : father * 2;
			if (arr[mnId] < arr[father]) {
				exchange(father, mnId);
				upToDown(mnId);
			}
			child = father;
			father /= 2;
		}
	}

	void push(int value) {
		++size;
		arr[size] = value;
		exchange(1, size);
		update(size);
	}
	void pop() {
		exchange(1, size);
		size--;
		upToDown(1);
	}
	int top() {
		return arr[1];
	}
	bool empty() {
		return size == 0 ? true : false;
	}
};