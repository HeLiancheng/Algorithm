/*****************************************************************//**
 * \file   AVLTree.h
 * \brief  
 * This is a sample of AVL Tree.
 * \author Administrator
 * \date   December 2023
 *********************************************************************/
#pragma once
#include <cstdio>
#include <algorithm>
using namespace std;
struct AVLNode {
	int value;
	AVLNode* left;
	AVLNode* right;
	AVLNode* parent;
	int balanceFactor;
	AVLNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), balanceFactor(0) {}
};
class AVLTree {
public:
	AVLNode* tRoot;
	AVLTree() : tRoot(nullptr) {}
	void MidOrderIter(AVLNode* root) {
		if (root == nullptr)
			return;
		MidOrderIter(root->left);
		printf("%d ", root->value);
		MidOrderIter(root->right);
	}
	AVLNode* find(int val, AVLNode* nod) {
		AVLNode* res = nullptr, * node = nod;
		while (node) {
			res = node;
			if (node->value < val) {
				node = node->right;
			}
			else if (node->value > val) {
				node = node->left;
			}
			else
				break;
		}
		return res;
	}

	AVLNode* findUnbalance(AVLNode* node) {
		if (node == nullptr || abs(node->balanceFactor) > 1)
			return node;
		return findUnbalance(node->parent);
	}
	void updateAllBalance(AVLNode* node) {
		AVLNode* parent = node->parent;
		while (parent) {
			if (parent->left == node)
				parent->balanceFactor--;
			else
				parent->balanceFactor++;
			node = parent;
			parent = parent->parent;
		}
	}

	void RotateLeft(AVLNode* node) {
		AVLNode* pparent = node->parent;
		AVLNode* rt = node->right;
		AVLNode* rl = rt->left;
		node->right = rl;
		rt->left = node;
		if (pparent == nullptr) {
			tRoot = rt;
		}
		else {
			bool isL = pparent->left == node ? true : false;
			if (isL) {
				pparent->left = rt;
			}
			else {
				pparent->right = rt;
			}
		}
		rt->parent = pparent;
		node->parent = rt;
		if (rl)
			rl->parent = node;
		rt->balanceFactor = 0;
		node->balanceFactor = 0;
	}

	void RotateRight(AVLNode* node) {
		AVLNode* pparent = node->parent;
		AVLNode* lft = node->left;
		AVLNode* lr = lft->right;
		node->left = lr;
		lft->right = node;
		if (pparent == nullptr) {
			tRoot = lft;
		}
		else {
			bool isL = pparent->left == node ? true : false;
			if (isL) {
				pparent->left = lft;
			}
			else {
				pparent->right = lft;
			}
		}
		lft->parent = pparent;
		node->parent = lft;
		if (lr)
			lr->parent = node;
		lft->balanceFactor = 0;
		node->balanceFactor = 0;
	}
	void LeftRightRotate(AVLNode* parent) {
		AVLNode* lft = parent->left;
		AVLNode* lr = lft->right;
		int bf = lr->balanceFactor;
		RotateLeft(lft);
		RotateRight(parent);
		if (bf < 0) {
			parent->balanceFactor = 1;
		}
		else if (bf > 0) {
			lft->balanceFactor = -1;
		}
	}

	void RightLeftRotate(AVLNode* parent) {
		AVLNode* rt = parent->right;
		AVLNode* rl = rt->left;
		int bf = rl->balanceFactor;
		RotateRight(rt);
		RotateLeft(parent);
		if (bf < 0) {
			parent->balanceFactor = 1;
		}
		else if (bf > 0) {
			rt->balanceFactor = -1;
		}
	}

	void insert(int val) {
		AVLNode* node = new AVLNode(val);
		if (tRoot == nullptr) {
			tRoot = node;
			return;
		}
		AVLNode* parent = find(node->value, tRoot);
		if (parent->value < node->value) {
			parent->right = node;
		}
		else if (parent->value > node->value) {
			parent->left = node;
		}
		else {
			return;
		}
		node->parent = parent;
		while (parent) {
			if (parent->left == node)
				parent->balanceFactor--;
			else
				parent->balanceFactor++;
			if (parent->balanceFactor == 0)
				return;
			else if (parent->balanceFactor == 1 || parent->balanceFactor == -1) {
				node = parent;
				parent = parent->parent;
			}
			else {
				if (parent) {
					if (parent->balanceFactor > 1) {
						if (parent->right->balanceFactor > 0)
							RotateLeft(parent);
						else if (parent->right->balanceFactor < 0) {
							RightLeftRotate(parent);
						}
					}
					else if (parent->balanceFactor < -1) {
						if (parent->left->balanceFactor < 0)
							RotateRight(parent);
						else if (parent->left->balanceFactor > 0) {
							LeftRightRotate(parent);
						}
					}
				}
				return;
			}
		}
	}

	void erase(int val) {
		AVLNode* node = find(val, tRoot);
		if (node == nullptr || node->value != val) {
			printf("not found!");
			return;
		}
		AVLNode* p = node->parent, * q = nullptr, * r = node;
		if (node->left && node->right) {
			p = node;
			if (node->balanceFactor > 0) {
				q = node->right;
				while (q->left) {
					p = q;
					q = q->left;
				}
			}
			else {
				q = node->left;
				while (q->right) {
					p = q;
					q = q->right;
				}
			}
			node->value = q->value;
			node = q;
		}
		if (node->right)
			q = node->right;
		else
			q = node->left;
		bool isLeft = false;
		if (p == nullptr) {
			tRoot = q;
		}
		else {
			if (p->left == node) {
				p->left = q;
				isLeft = true;
			}
			else
				p->right = q;
		}
		delete node;
		node = nullptr;

		while (p) {
			if (isLeft)
				p->balanceFactor++;
			else
				p->balanceFactor--;
			if (p->balanceFactor == -1 || p->balanceFactor == 1)
				return;
			else if (p->balanceFactor == 0) {
				q = p;
				p = p->parent;
				if (p)
					isLeft = p->left == q ? true : false;
			}
			else {
				if (p) {
					if (p->balanceFactor > 1) {
						if (p->right->balanceFactor > 0)
							RotateLeft(p);
						else if (p->right->balanceFactor < 0) {
							RightLeftRotate(p);
						}
					}
					else if (p->balanceFactor < -1) {
						if (p->left->balanceFactor < 0)
							RotateRight(p);
						else if (p->left->balanceFactor > 0) {
							LeftRightRotate(p);
						}
					}
				}
				return;
			}
		}

	}
};