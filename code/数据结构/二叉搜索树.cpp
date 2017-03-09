//search tree
//2017-03-09 19:55:49
#include<iostream>
#include<vector>

using namespace std;

struct TreeNode{
	int data;
	TreeNode* parent;
	TreeNode* left_child;
	TreeNode* right_child;

	TreeNode(int d, TreeNode* p) :data(d), parent(p), left_child(nullptr), right_child(nullptr) {};
};

class Tree {
private:
	TreeNode* root;

	void print_tree(TreeNode* node) {
		if (node == nullptr) return;
		print_tree(node->left_child);
		cout << node->data << ' ';
		print_tree(node->right_child);
	}

public:
	Tree() { root = nullptr; }

	Tree(vector<int> nums) {
		root = new TreeNode(nums[0], nullptr);
		for (int index = 1; index < nums.size(); index++) {
			insert(nums[index], root);
		}
	}

	TreeNode* get_root() { return root; }

	void insert(int num, TreeNode* node) {
		if (num < node->data) {
			if (node->left_child == nullptr) {
				node->left_child = new TreeNode(num, node);
			}
			else {
				insert(num, node->left_child);
			}
		}
		else {
			if (node->right_child == nullptr) {
				node->right_child = new TreeNode(num, node);
			}
			else {
				insert(num, node->right_child);
			}
		}
	}

	TreeNode* find(int num, TreeNode* node) {
		if (num == node->data) {
			return node;
		}
		if (num < node->data) {
			if (node->left_child != nullptr) {
				return find(num, node->left_child);
			}
		}
		else {
			if (node->right_child != nullptr) {
				return find(num, node->right_child);
			}
		}
		return nullptr;
	}

	TreeNode* find_min(TreeNode* node) {
		while (node->left_child != nullptr) {
			node = node->left_child;
		}
		return node;
	}

	TreeNode* find_max(TreeNode* node) {
		while (node->right_child != nullptr) {
			node = node->right_child;
		}
		return node;
	}

	TreeNode* find_pre(TreeNode* node) {
		if (node->left_child != nullptr) {
			return find_max(node->left_child);
		}
		return nullptr;
	}

	TreeNode* find_suc(TreeNode* node) {
		if (node->right_child != nullptr) {
			return find_min(node->right_child);
		}
		return nullptr;
	}

	int erase(TreeNode* node) {
		int d = node->data;
		if (node->left_child == nullptr) {
			if (node->right_child == nullptr) {
				TreeNode* p = node->parent;
				if (p->left_child == node) {
					p->left_child = nullptr;
				}
				else {
					p->right_child = nullptr;
				}
			}
			else {
				TreeNode* p = node->parent;
				if (p->left_child == node) {
					p->left_child = node->right_child;
				}
				else {
					p->right_child = node->right_child;
				}
			}
			delete node;
		}
		else {
			if (node->right_child == nullptr) {
				TreeNode* p = node->parent;
				if (p->left_child == node) {
					p->left_child = node->left_child;
				}
				else {
					p->right_child = node->left_child;
				}
				delete node;
			}
			else {
				TreeNode* suc = find_suc(node);
				node->data = suc->data;
				suc->parent->left_child = suc->right_child;
				delete suc;
			}
		}
		return d;
	}

	void show_tree() {
		print_tree(root);
		cout << endl;
	}
};

int main() {
	vector<int> test_num = { 5,2,4,1,9,3,6,7,8,0 };

	cout << "Creat tree:" << endl;
	Tree test_tree(test_num);
	test_tree.show_tree();
	cout << endl;

	cout << "Insert (8 and 2)" << endl;
	test_tree.insert(8, test_tree.get_root());
	test_tree.show_tree();
	test_tree.insert(2, test_tree.get_root());
	test_tree.show_tree();
	cout << endl;

	cout << "Search (6):";
	cout << test_tree.find(6, test_tree.get_root())->data << endl;
	cout << endl;

	cout << "Minimum:";
	cout << test_tree.find_min(test_tree.get_root())->data << endl;
	cout << endl;

	cout << "Maximum:";
	cout << test_tree.find_max(test_tree.get_root())->data << endl;
	cout << endl;

	cout << "Find pre(3):";
	TreeNode* pre = test_tree.find_pre(test_tree.find(3, test_tree.get_root()));
	if (pre == nullptr) cout << "No pre!" << endl;
	else cout << pre->data << endl;
	cout << endl;

	cout << "Find suc(3):";
	TreeNode* suc = test_tree.find_suc(test_tree.find(3, test_tree.get_root()));
	if (suc == nullptr) cout << "No suc!" << endl;
	else cout << suc->data << endl;
	cout << endl;

	cout << "Delete (0,1,2,9):" << endl;
	test_tree.erase(test_tree.find(0, test_tree.get_root()));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(1, test_tree.get_root()));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(2, test_tree.get_root()));
	test_tree.show_tree();
	test_tree.erase(test_tree.find(9, test_tree.get_root()));
	test_tree.show_tree();

	return 0;
}