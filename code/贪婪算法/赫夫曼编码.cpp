//Huffman
//2017-03-13 18:56:43
/*
Letter		a	b	c	d	e	f
Frequency	45	13	12	16	9	5
*/
#include<iostream>
#include<vector>
#include<string>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*(x+1)
#define PARENT(x) (x-1)/2


using namespace std;

struct Letter {
	string letter;
	int frequency;
	Letter(string l, int f) :letter(l), frequency(f) {};
};

struct TreeNode {
	Letter data;
	TreeNode* parent;
	TreeNode* left_child;
	TreeNode* right_child;
	TreeNode(Letter letter) :data(letter), parent(nullptr), left_child(nullptr), right_child(nullptr) {};
};

class MinHeap {
private:
	vector<TreeNode*> datas;
	int heap_size;

	void min_heapify(int index) {
		int min = index;
		if (LEFT(index) < heap_size) {
			if (datas[LEFT(index)]->data.frequency < datas[min]->data.frequency) {
				min = LEFT(index);
			}
		}
		if (RIGHT(index) < heap_size) {
			if (datas[RIGHT(index)]->data.frequency < datas[min]->data.frequency) {
				min = RIGHT(index);
			}
		}

		if (min != index) {
			TreeNode* temp = datas[min];
			datas[min] = datas[index];
			datas[index] = temp;

			min_heapify(min);
		}
	}

	void add_heapify(int index) {
		if (datas[PARENT(index)]->data.frequency > datas[index]->data.frequency) {
			TreeNode* temp = datas[index];
			datas[PARENT(index)] = datas[index];
			datas[index] = temp;

			add_heapify(PARENT(index));
		}
	}

public:
	MinHeap(vector<TreeNode*> d): datas(d), heap_size(d.size()) {
		for (int index = heap_size / 2; index >= 0; index--) {
			min_heapify(index);
		}
	}

	TreeNode* extract_min() {
		TreeNode* temp = datas[0];
		datas[0] = datas[heap_size - 1];
		datas[heap_size - 1] = temp;
		heap_size--;
		min_heapify(0);
		return temp;
	}

	void add_data(TreeNode* data) {
		datas.insert(datas.begin() + heap_size, data);
		add_heapify(heap_size);
		heap_size++;
	}
};

class Huffman {
private:
	vector<Letter> original_datas;
	TreeNode* root;

	TreeNode* build_huffman(MinHeap datas, int datas_size) {
		for (int loop_tag = 0; loop_tag < datas_size - 1; loop_tag++) {
			TreeNode* new_node = new TreeNode(Letter("Null", 0));
			new_node->left_child = datas.extract_min();
			new_node->right_child = datas.extract_min();
			new_node->data.frequency = new_node->left_child->data.frequency + new_node->right_child->data.frequency;
			datas.add_data(new_node);
		}
		return datas.extract_min();
	}

	void show_tree(TreeNode* node) {
		if (node == nullptr) return;
		show_tree(node->left_child);
		cout << ' ' << node->data.letter << ' ' << node->data.frequency << ' ';
		show_tree(node->right_child);
	}

public:
	Huffman(vector<Letter> datas) :original_datas(datas) {
		vector<TreeNode*> temp_datas;
		for (auto data : datas) {
			temp_datas.push_back(new TreeNode(data));
		}
		MinHeap datas_min_heap(temp_datas);
		root = build_huffman(datas_min_heap, datas.size());
	}

	void show_huffman() {
		show_tree(root);
	}
};

int main() {
	vector<Letter> test_letters;
	test_letters.push_back(Letter("a", 45));
	test_letters.push_back(Letter("b", 13));
	test_letters.push_back(Letter("c", 12));
	test_letters.push_back(Letter("d", 16));
	test_letters.push_back(Letter("f", 9));
	test_letters.push_back(Letter("e", 5));

	Huffman test_h(test_letters);
	test_h.show_huffman();
	cout << endl;
}

