//red black tree
//2017-03-10 19:12:28
#include<iostream>
#include<vector>

using namespace std;

enum TreeColor { red, black };

struct BRTreeNode {
	int data;
	TreeColor color;
	BRTreeNode* parent;
	BRTreeNode* left_child;
	BRTreeNode* right_child;

	BRTreeNode(int d, BRTreeNode* p, TreeColor c) :data(d), parent(p), color(c), left_child(nullptr), right_child(nullptr) {};
};

BRTreeNode* nil = new BRTreeNode(-1, nil, black);

class BRTree {
private:
	BRTreeNode* root;

	void left_rotate(BRTreeNode* node) {
		BRTreeNode* gp_node = node->parent->parent;
		BRTreeNode* p_node = node->parent;
		if (node->parent == gp_node->left_child) {
			gp_node->left_child = node;
		}
		else {
			gp_node->right_child = node;
		}
		node->parent = gp_node;
		p_node->parent = node;

		p_node->right_child = node->left_child;
		p_node->right_child->parent = p_node;

		node->left_child = p_node;
	}

	void right_rotate(BRTreeNode* node) {
		BRTreeNode* gp_node = node->parent->parent;
		BRTreeNode* p_node = node->parent;
		if (node->parent == gp_node->left_child) {
			gp_node->left_child = node;
		}
		else {
			gp_node->right_child = node;
		}
		node->parent = gp_node;
		p_node->parent = node;

		p_node->left_child = node->right_child;
		p_node->left_child->parent = p_node;

		node->right_child = p_node;
	}

	void insert_fixup(BRTreeNode* node) {
		while (node->parent->color == red) {
			BRTreeNode* gp_node = node->parent->parent;
			BRTreeNode* u_node = node->parent == gp_node->left_child ? gp_node->right_child : gp_node->left_child;
			if (u_node->color == red) {
				node->parent->color = black;
				u_node->color = black;
				node = gp_node;
			}
			else {
				if (u_node == gp_node->right_child) {
					if (node == node->parent->right_child) {
						left_rotate(node);
						node = node->left_child;
					}
					right_rotate(node->parent);
					node->parent->color = black;
					node->parent->right_child->color = red;
				}
				else {
					if (node == node->parent->left_child) {
						right_rotate(node);
						node = node->right_child;
					}
					left_rotate(node->parent);
					node->parent->color = black;
					node->parent->left_child->color = black;
				}
			}
		}
		root->color = black;
	}

public:
	BRTree(vector<int> nums) {
		root = new BRTreeNode(nums[0], nil, black);
		root->left_child = nil;
		root->left_child = nil;
		nil->parent = root;
		nil->left_child = root;
		nil->right_child = root;

		for (int index = 1; index < nums.size(); index++) {
			insert(nums[index]);
		}
	}

	BRTreeNode* get_root() { return root; }

	void insert(int data) {
		BRTreeNode* node = root;
		BRTreeNode* new_node = new BRTreeNode(data, node->left_child, red);
		while (node != nil) {
			if (data < node->data) {
				if (node->left_child != nil) {
					node = node->left_child;
				}
				else {
					new_node = new BRTreeNode(data, node->left_child, red);
					break;
				}
			}
			else {
				if (node->right_child != nil) {
					node = node->right_child;
				}
				else {
					new_node = new BRTreeNode(data, node->right_child, red);
					break;
				}
			}
		}
		new_node->left_child = nil;
		new_node->right_child = nil;
		insert_fixup(new_node);
	}

	int erase(BRTreeNode* node) {
		TreeColor d_color = node->color;
		BRTreeNode* p_node = node->parent;
		BRTreeNode* suc_node = find_suc(node);
		BRTreeNode* key_node;
		if (node->left_child == nil) {
			if (node->right_child == nil) {
				if (node == p_node->left_child) {
					p_node->left_child = nil;
				}
				else {
					p_node->right_child = nil;
				}
			}
			else {
				if (node == p_node->left_child) {
					p_node->left_child = node->right_child;
				}
				else {
					p_node->right_child = node->right_child;
				}
			}
			key_node = node->right_child;
			delete node;
		}
		else {
			if (node->right_child == nil) {
				if (node == p_node->left_child) {
					p_node->left_child = node->left_child;
				}
				else {
					p_node->right_child = node->left_child;
				}
				key_node = node->left_child;
				delete node;
			}
			else {
				node->data = suc_node->data;
				d_color = suc_node->color;
				suc_node->parent->left_child = suc_node->right_child;
				key_node = suc_node->right_child;
				delete suc_node;
			}
		}
		if (d_color == black) {

		}
	}

	BRTreeNode* find(int data) {
		BRTreeNode* node = root;
		while (node != nil) {
			if (node->data < data) {
				node = node->left_child;
			}
			else if (node->data > data) {
				node = node->right_child;
			}
			else {
				return node;
			}
		}
		return node;
	}

	BRTreeNode* find_max(BRTreeNode* node) {
		while (node->right_child != nil) {
			node = node->right_child;
		}
		return node;
	}

	BRTreeNode* find_min(BRTreeNode* node) {
		while (node->left_child != nil) {
			node = node->left_child;
		}
		return node;
	}

	BRTreeNode* find_pre(BRTreeNode* node) {
		if (node->left_child != nil) {
			return find_max(node->left_child);
		}
		else {
			return nil;
		}
	}

	BRTreeNode* find_suc(BRTreeNode* node) {
		if (node->right_child != nil) {
			return find_min(node->right_child);
		}
		else {
			return nil;
		}
	}
};