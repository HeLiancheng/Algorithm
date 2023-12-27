/*****************************************************************//**
 * \file   RedBlackTree.h
 * \brief  
 * This is the sample of Red Black Tree.
 * 
 * \author Liancheng He
 * \date   December 2023
 *********************************************************************/
#pragma once
#include<cstdio>
constexpr int RED = 1;
constexpr int BLACK = 2;

struct RBNode {
	int color;
	RBNode* left, * right, * parent;
	int value;
	RBNode(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

inline bool cmp(RBNode* a, RBNode* b) {
	return a->value < b->value;
}

class RBTree {
public:
	RBNode* tRoot, * tLeaf;
	RBTree() {
		tLeaf = new RBNode(0);
		tLeaf->color = BLACK;
		tRoot = tLeaf;
	}
	void MidOrderIter(RBNode* root) {
		if (root == tLeaf)
			return;
		MidOrderIter(root->left);
		printf("%d ", root->value);
		MidOrderIter(root->right);
	}

	void insert(int val) {
		RBNode* node = new RBNode(val);
		node->left = node->right = tLeaf;
		RBNode* parent = nullptr, * tmp = this->tRoot;
		while (tmp != tLeaf) {
			parent = tmp;
			tmp = cmp(node, tmp) ? tmp->left : tmp->right;
		}
		node->parent = parent;
		if (parent == nullptr) {
			node->color = BLACK;
			this->tRoot = node;
			return;
		}
		if (cmp(node, parent))
			parent->left = node;
		else parent->right = node;

		if (parent->parent == nullptr)
			return;
		balanceAfterInsert(node);
	}

	void erase(int val) {
		RBNode* node = findNode(val);
		if (node == tLeaf) {
			printf("can not find the value %d", val);
			return;
		}
		int oriColor = node->color;
		RBNode* tmp = node;
		if (node->left == tLeaf) {
			tmp = node->right;
			transplant(node, node->right);
		}
		else if (node->right == tLeaf) {
			tmp = node->left;
			transplant(node, node->left);
		}
		else {
			RBNode* rl = minimum(node->right);
			oriColor = rl->color;
			if (rl->parent == node) {
				node->right = rl->right;
				rl->right->parent = node;
			}
			else {
				transplant(rl, rl->right);
			}
			node->value = rl->value;
			delete rl;
			rl = nullptr;

		}
		if (oriColor == BLACK)
			balanceAfterDelete(tmp);
	}

private:
	RBNode* findNode(int val) {
		RBNode* node = this->tRoot;
		while (node != tLeaf) {
			if (val == node->value)return node;
			if (val < node->value)node = node->left;
			else if (val > node->value)node = node->right;
		}
		return node;
	}

	inline void transplant(RBNode* a, RBNode* b) {
		if (a->parent == nullptr)
			this->tRoot = b;
		else if (a == a->parent->left)
			a->parent->left = b;
		else a->parent->right = b;
		b->parent = a->parent;
	}

	RBNode* minimum(RBNode* node) {
		while (node->left != tLeaf) {
			node = node->left;
		}
		return node;
	}

	inline RBNode* search(int val, RBNode* node) {
		if (node == tLeaf || node->value == val)
			return node;
		if (val < node->value) {
			return search(val, node->left);
		}
		else {
			return search(val, node->right);
		}
	}

	inline void leftRotate(RBNode* node) {
		RBNode* r = node->right;
		node->right = r->left;
		if (r->left != tLeaf)
			r->left->parent = node;
		r->left = node;
		if (node->parent == nullptr) {
			this->tRoot = r;
		}
		else if (node->parent->left == node) {
			node->parent->left = r;
		}
		else {
			node->parent->right = r;
		}
		r->parent = node->parent;
		node->parent = r;
	}

	inline void rightRotate(RBNode* node) {
		RBNode* l = node->left;
		node->left = l->right;
		if (l->right != tLeaf)
			l->right->parent = node;
		l->right = node;
		if (node->parent == nullptr) {
			this->tRoot = l;
		}
		else if (node->parent->left == node) {
			node->parent->left = l;
		}
		else {
			node->parent->right = l;
		}
		l->parent = node->parent;
		node->parent = l;
	}

	void balanceAfterInsert(RBNode* node) {
		RBNode* uncle;
		while (node->parent->color == RED) {
			if (node->parent == node->parent->parent->right) {
				uncle = node->parent->parent->left;
				if (uncle->color == RED) {
					node->parent->color = BLACK;
					uncle->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						rightRotate(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					leftRotate(node->parent->parent);
				}

			}
			else {
				uncle = node->parent->parent->right;
				if (uncle->color == RED) {
					node->parent->color = BLACK;
					uncle->color = BLACK;
					node->parent->parent->color = RED;
					node = node->parent->parent;
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						leftRotate(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					rightRotate(node->parent->parent);
				}
			}
			if (node == tRoot)
				break;
		}
		tRoot->color = BLACK;
	}

	void balanceAfterDelete(RBNode* node) {
		RBNode* bro;
		while (node != tRoot && node->color == BLACK) {
			if (node == node->parent->left) {
				bro = node->parent->right;
				if (bro->color == RED) {
					bro->color = BLACK;
					bro->parent->color = RED;
					leftRotate(bro->parent);
					bro = node->parent->right;
				}
				if (bro->left->color == BLACK && bro->right->color == BLACK) {
					bro->color = RED;
					node = node->parent;
				}
				else {
					if (bro->right->color == BLACK) {
						bro->color = RED;
						bro->left->color = BLACK;
						rightRotate(bro);
						bro = node->parent->right;
					}
					bro->color = node->parent->color;
					node->parent->color = BLACK;
					bro->right->color = BLACK;
					leftRotate(node->parent);
					node = this->tRoot;
				}
			}
			else {
				bro = node->parent->left;
				if (bro->color == RED) {
					bro->color = BLACK;
					bro->parent->color = RED;
					rightRotate(bro->parent);
					bro = node->parent->left;
				}
				if (bro->left->color == BLACK && bro->right->color == BLACK) {
					bro->color = RED;
					node = node->parent;
				}
				else {
					if (bro->left->color == BLACK) {
						bro->color = RED;
						bro->right->color = BLACK;
						leftRotate(bro);
						bro = node->parent->left;
					}
					bro->color = node->parent->color;
					node->parent->color = BLACK;
					bro->left->color = BLACK;
					rightRotate(node->parent);
					node = this->tRoot;
				}
			}
		}
	}
};
