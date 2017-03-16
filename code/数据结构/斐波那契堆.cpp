//fib heap
//2017-03-16 16:42:16
#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

struct FibNode {
	int key;
	int degree;		//the number of children
	bool is_children_lost;
	FibNode* parent;
	FibNode* children;
	FibNode* left;
	FibNode* right;

	FibNode(int data) :key(data), degree(0), is_children_lost(false),parent(nullptr), children(nullptr), left(nullptr), right(nullptr) {};
};

class FibHeap {
private:
	FibNode* heap_min;
	int node_num;
	int root_num;
	FibNode* search_result;

	void add_to_root(FibNode* node) {
		add_to_list(node, heap_min);
		root_num++;
	}

	void add_to_list(FibNode* node, FibNode* list_node) {
		node->left = list_node->left;
		list_node->left->right = node;

		node->right = list_node;
		list_node->left = node;
	}

	void remove_node(FibNode* node) {
		node->left->right = node->right;
		node->right->left = node->left;
	}

	void link_node(FibNode* c_node, FibNode* p_node) {
		remove_node(c_node);
		if (p_node->children != nullptr) {
			add_to_list(c_node, p_node->children);
		}
		else {
			c_node->left = c_node;
			c_node->right = c_node;
			p_node->children = c_node;
		}
		c_node->parent = p_node;
		p_node->degree++;
		c_node->is_children_lost = false;
	}

	void consolidate() {
		vector<FibNode*> record_nodes;
		record_nodes.resize(10, nullptr);

		vector<FibNode*> root_list;
		FibNode *node = heap_min, *end_node = node->left;
		root_list.push_back(node);
		while (node != end_node) {
			node = node->right;
			root_list.push_back(node);
		}

		for (auto node:root_list) {
			int degree = node->degree;
			while (record_nodes[degree] != nullptr) {
				FibNode* sd_node = record_nodes[degree];
				if (node->key > sd_node->key) {
					FibNode* temp = node;
					node = sd_node;
					sd_node = temp;
				}
				link_node(sd_node, node);
				root_num--;
				record_nodes[degree] = nullptr;
				degree++;
			}
			record_nodes[degree] = node;
		}

		heap_min = nullptr;

		for (auto node : record_nodes) {
			if (node != nullptr) {
				if (heap_min == nullptr) {
					node->left = node;
					node->right = node;
					heap_min = node;
				}
				else {
					add_to_list(node, heap_min);
					if (node->key < heap_min->key) {
						heap_min = node;
					}
				}
			}
		}
	}

	void cut(FibNode* c_node) {
		if (c_node->parent->degree == 1) {
			c_node->parent->degree = 0;
			c_node->parent->children = nullptr;
		}
		else {
			c_node->parent->children = c_node->left;
			remove_node(c_node);
		}
		c_node->parent->degree--;
		add_to_root(c_node);
		c_node->parent = nullptr;
		c_node->is_children_lost = false;
	}

	void cascading_cut(FibNode* node) {
		FibNode* parent = node->parent;
		if (parent != nullptr) {
			if (node->is_children_lost) {
				cut(node);
				cascading_cut(parent);
			}
			else {
				parent->is_children_lost = true;
			}
		}
	}

	bool search_list(int key, FibNode* node, FibNode* end_node) {
		if (node->key == key) {
			search_result = node;
			return true;
		}

		if (node->children != nullptr) {
			if (search_list(key, node->children, node->children->left)) {
				return true;
			}
		}

		if (node == end_node) {
			return false;
		}
		return search_list(key, node->right, end_node);
	}

	void traverse_list(FibNode* node, FibNode* end_node, bool is_traverse_end) {
		if (is_traverse_end) {
			if (node->children != nullptr) {
				cout << node->key << ':';
				traverse_list(node->children, node->children->left, false);
			}
			if (node != end_node) {
				traverse_list(node->right, end_node, true);
			}
		}
		else {
			cout << node->key << ' ';
			if (node == end_node) {
				cout << endl;
				traverse_list(node->right, end_node, true);
			}
			else {
				traverse_list(node->right, end_node, false);
			}
		}
	}

public:
	FibHeap() {
		heap_min = nullptr;
		node_num = 0;
		root_num = 0;
	}

	FibHeap(vector<int> datas) {
		FibHeap();
		for (auto data : datas) {
			insert(data);
		}
	}

	FibNode* find_min() { return heap_min; }
	int size() { return node_num; }

	void insert(int data) {
		FibNode* new_node = new FibNode(data);
		if (heap_min == nullptr) {
			heap_min = new_node;
			heap_min->left = heap_min;
			heap_min->right = heap_min;
			root_num++;
		}
		else {
			add_to_root(new_node);

			if (data < heap_min->key) {
				heap_min = new_node;
			}
		}
		node_num++;
	}

	int extract_min() {
		if (heap_min == nullptr) {
			return -1;
		}

		FibNode* node_min = heap_min;

		if (node_min->children != nullptr) {
			FibNode* children = node_min->children;
			FibNode* next_children = children->right;
			for (int loop_tag = 0; loop_tag < node_min->degree; loop_tag++) {
				add_to_root(children);
				children->parent = nullptr;
				children = next_children;
				next_children = next_children->right;
			}
		}

		remove_node(node_min);
		root_num--;

		if (node_min == node_min->right) {
			heap_min = nullptr;
		}
		else {
			heap_min = node_min->right;
			consolidate();
		}

		node_num--;
		int data = node_min->key;
		delete node_min;
		return data;
	}

	void decrease_key(FibNode* node, int new_key) {
		if (node->key < new_key) return;	//error:new key greater than current key

		FibNode* parent = node->parent;
		node->key = new_key;
		if (parent != nullptr && (node->key < parent->key)) {
			cut(node);
			cascading_cut(parent);
		}
		if (node->key < heap_min->key) {
			heap_min = node;
		}
	}

	void erase(FibNode* node) {
		decrease_key(node, INT_MIN);
		extract_min();
	}

	FibNode* find(int key) {
		search_result = nullptr;
		search_list(key, heap_min, heap_min->left);
		return search_result;
	}

	void show() {
		traverse_list(heap_min, heap_min->left, false);
	}

	static FibHeap merge(FibHeap heap_x, FibHeap heap_y) {
		if (heap_x.heap_min == nullptr) {
			return heap_y;
		}
		if (heap_y.heap_min == nullptr) {
			return heap_x;
		}

		FibHeap new_heap(heap_x);

		FibNode* temp_node_x = new_heap.heap_min->left;
		FibNode* temp_node_y = heap_y.heap_min->right;
		heap_y.heap_min->right = new_heap.heap_min;
		new_heap.heap_min->left = heap_y.heap_min;
		temp_node_x->right = temp_node_y;
		temp_node_y->left = temp_node_x;

		if (new_heap.heap_min->key > heap_y.heap_min->key) {
			new_heap.heap_min = heap_y.heap_min;
		}
		new_heap.node_num += heap_y.node_num;

		return new_heap;
	}
};

int main() {
	vector<int> test_nums = { 23,7,3,18,39,52,38,41,17,30,24,26,35 };

	FibHeap test_heap(test_nums);
	cout << "Create heap:" << endl;
	test_heap.show();
	cout << endl;
	
	cout << "Insert(46):" << endl;
	test_heap.insert(46);
	test_heap.show();
	cout << endl;

	cout << "Minimun:" << test_heap.find_min()->key << endl;
	cout << endl;

	cout << "Extract min:" << endl;
	test_heap.extract_min();
	test_heap.show();
	cout << endl;

	cout << "Search(52):" << test_heap.find(52)->key << endl;
	cout << endl;

	cout << "Decrease key(41 to 2):" << endl;
	test_heap.decrease_key(test_heap.find(41), 2);
	test_heap.show();
	cout << endl;

	cout << "Delete(17):" << endl;
	test_heap.erase(test_heap.find(17));
	test_heap.show();
	cout << endl;

	vector<int> test_nums_b = { 1,6,4,3 };
	FibHeap test_heap_b(test_nums_b);
	cout << "Another heap:" << endl;
	test_heap_b.show();
	cout << endl;

	cout << "Union:" << endl;
	FibHeap::merge(test_heap, test_heap_b).show();
	cout << endl;
}