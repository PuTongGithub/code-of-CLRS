//red black tree
//2017-03-10 19:12:28
#include<iostream>
#include<vector>

using namespace std;

enum TreeColor { red, black };

struct RBTreeNode {
	int data;
	TreeColor color;
	RBTreeNode* parent;
	RBTreeNode* left_child;
	RBTreeNode* right_child;

	RBTreeNode(int d, TreeColor c) :data(d), parent(nullptr), color(c), left_child(nullptr), right_child(nullptr) {};
};

RBTreeNode* nil = new RBTreeNode(-1, black);

class RBTree {
private:
	RBTreeNode* root;

	void left_rotate(RBTreeNode* node) {
		RBTreeNode* y_node = node->right_child;
		node->right_child = y_node->left_child;
		if (y_node->left_child != nil) {
			y_node->left_child->parent = node;
		}
		y_node->parent = node->parent;
		if (node->parent == nil) {
			root = y_node;
		}
		else if (node == node->parent->left_child) {
			node->parent->left_child = y_node;
		}
		else {
			node->parent->right_child = y_node;
		}
		y_node->left_child = node;
		node->parent = y_node;
	}

	void right_rotate(RBTreeNode* node) {
		RBTreeNode* y_node = node->left_child;
		node->left_child = y_node->right_child;
		if (y_node->right_child != nil) {
			y_node->right_child->parent = node;
		}
		y_node->parent = node->parent;
		if (node->parent == nil) {
			root = y_node;
		}
		else if (node == node->parent->right_child) {
			node->parent->right_child = y_node;
		}
		else {
			node->parent->left_child = y_node;
		}
		y_node->right_child = node;
		node->parent = y_node;
	}

	void insert_fixup(RBTreeNode* node) {
		while (node->parent->color == red) {
			RBTreeNode* gp_node = node->parent->parent;
			RBTreeNode* u_node = node->parent == gp_node->left_child ? gp_node->right_child : gp_node->left_child;
			if (u_node->color == red) {
				node->parent->color = black;
				u_node->color = black;
				gp_node->color = red;
				node = gp_node;
			}
			else {
				if (u_node == gp_node->right_child) {
					if (node == node->parent->right_child) {
						node = node->parent;
						left_rotate(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					right_rotate(node->parent->parent);
				}
				else {
					if (node == node->parent->left_child) {
						node = node->parent;
						right_rotate(node);
					}
					node->parent->color = black;
					node->parent->parent->color = red;
					left_rotate(node->parent->parent);
				}
			}
		}
		root->color = black;
	}

	void erase_fixup(RBTreeNode* node) {
		if (node == root || node->color == red) {
			node->color = black;
			return;
		}
		RBTreeNode* b_node;
		bool is_node_a_right_child;
		if (node == node->parent->left_child) {
			b_node = node->parent->right_child;
			is_node_a_right_child = false;
		}
		else {
			b_node = node->parent->left_child;
			is_node_a_right_child = true;
		}

		if (b_node->color == red) {
			b_node->color = black;
			node->parent->color = red;
			if (is_node_a_right_child) {
				right_rotate(node->parent);
			}
			else {
				left_rotate(node->parent);
			}
			erase_fixup(node);
		}
		else {
			if (b_node->right_child->color == black && b_node->left_child->color == black) {
				b_node->color = red;
				erase_fixup(node->parent);
			}
			else {
				if (is_node_a_right_child) {
					if (b_node->left_child->color == black) {
						b_node->color = red;
						b_node->right_child->color = black;
						left_rotate(b_node);
						b_node = node->parent->left_child;
					}
					b_node->color = node->parent->color;
					node->parent->color = black;
					b_node->right_child->color = black;
					right_rotate(node->parent);
				}
				else {
					if (b_node->right_child->color == black) {
						b_node->color = red;
						b_node->left_child->color = black;
						right_rotate(b_node);
						b_node = node->parent->right_child;
					}
					b_node->color = node->parent->color;
					node->parent->color = black;
					b_node->right_child->color = black;
					left_rotate(node->parent);
				}
			}
		}
		node->color = black;
	}

	void tansplant(RBTreeNode* d_node, RBTreeNode* t_node) {
		if (d_node == root) {
			root = t_node;
		}
		else {
			if (d_node->parent->left_child == d_node) {
				d_node->parent->left_child = t_node;
			}
			else {
				d_node->parent->right_child = t_node;
			}
		}
		t_node->parent = d_node->parent;
		delete d_node;
	}

	void print_tree(RBTreeNode* node) {
		if (node == nil) return;
		print_tree(node->left_child);
		cout << node->data << ' ';
		print_tree(node->right_child);
	}

public:
	RBTree(vector<int> nums) {
		root = new RBTreeNode(nums[0], black);
		root->parent = nil;
		root->left_child = nil;
		root->right_child = nil;
		root->color = black;
		nil->parent = root;
		nil->left_child = root;
		nil->right_child = root;

		for (int index = 1; index < nums.size(); index++) {
			insert(nums[index]);
		}
	}

	RBTreeNode* get_root() { return root; }

	void insert(int data) {
		RBTreeNode* node = root;
		RBTreeNode* new_node = new RBTreeNode(data, red);
		new_node->left_child = nil;
		new_node->right_child = nil;
		while (node != nil) {
			if (data < node->data) {
				if (node->left_child != nil) {
					node = node->left_child;
				}
				else {
					node->left_child = new_node;
					new_node->parent = node;
					break;
				}
			}
			else {
				if (node->right_child != nil) {
					node = node->right_child;
				}
				else {
					node->right_child = new_node;
					new_node->parent = node;
					break;
				}
			}
		}
		insert_fixup(new_node);
	}

	int erase(RBTreeNode* node) {
		if (node == nil) {
			return -1;
		}
		int data = node->data;
		TreeColor d_color = node->color;
		RBTreeNode* key_node;
		if (node->left_child == nil) {
			key_node = node->right_child;
			tansplant(node, node->right_child);
		}
		else {
			if (node->right_child == nil) {
				key_node = node->left_child;
				tansplant(node, node->left_child);
			}
			else {
				RBTreeNode* suc_node = find_suc(node);
				node->data = suc_node->data;
				d_color = suc_node->color;
				key_node = suc_node->right_child;
				if (suc_node->parent == node) {
					node->right_child = suc_node->right_child;
					suc_node->right_child->parent = node;
				}
				else {
					suc_node->parent->left_child = suc_node->right_child;
					suc_node->right_child->parent = suc_node->parent;
				}
				delete suc_node;
			}
		}
		if (d_color == black) {
			erase_fixup(key_node);
		}
		return data;
	}

	RBTreeNode* find(int data) {
		RBTreeNode* node = root;
		while (node != nil) {
			if (node->data == data) {
				return node;
			}
			if (node->data > data) {
				node = node->left_child;
			}
			else {
				node = node->right_child;
			}
		}
		return node;
	}

	RBTreeNode* find_max(RBTreeNode* node) {
		while (node->right_child != nil) {
			node = node->right_child;
		}
		return node;
	}

	RBTreeNode* find_min(RBTreeNode* node) {
		while (node->left_child != nil) {
			node = node->left_child;
		}
		return node;
	}

	RBTreeNode* find_pre(RBTreeNode* node) {
		if (node->left_child != nil) {
			return find_max(node->left_child);
		}
		else {
			return nil;
		}
	}

	RBTreeNode* find_suc(RBTreeNode* node) {
		if (node->right_child != nil) {
			return find_min(node->right_child);
		}
		else {
			return nil;
		}
	}

	void show_tree() {
		print_tree(root);
		cout << endl;
	}
};

int main() {
	vector<int> test_num = { 5,2,4,1,9,3,6,7,8,0 };

	cout << "Creat tree:" << endl;
	RBTree test_tree(test_num);
	test_tree.show_tree();
	cout << endl;

	cout << "Insert (8 and 2)" << endl;
	test_tree.insert(8);
	test_tree.show_tree();
	test_tree.insert(2);
	test_tree.show_tree();
	cout << endl;

	cout << "Search (6):";
	cout << test_tree.find(6)->data << endl;
	cout << endl;

	cout << "Minimum:";
	cout << test_tree.find_min(test_tree.get_root())->data << endl;
	cout << endl;

	cout << "Maximum:";
	cout << test_tree.find_max(test_tree.get_root())->data << endl;
	cout << endl;

	cout << "Find pre(3):";
	RBTreeNode* pre = test_tree.find_pre(test_tree.find(3));
	if (pre == nil) cout << "No pre!" << endl;
	else cout << pre->data << endl;
	cout << endl;

	cout << "Find suc(3):";
	RBTreeNode* suc = test_tree.find_suc(test_tree.find(3));
	if (suc == nil) cout << "No suc!" << endl;
	else cout << suc->data << endl;
	cout << endl;

	cout << "Delete (0,1,2,8,6):" << endl;
	test_tree.erase(test_tree.find(0));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(1));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(2));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(8));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(6));
	test_tree.show_tree();

	return 0;
}