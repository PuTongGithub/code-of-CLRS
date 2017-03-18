//kruskal
//2017-03-18 08:55:46
#include<iostream>
#include<vector>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*(x+1)

typedef int value_type;

using namespace std;

struct Edge {
	value_type value;
	int node_x;
	int node_y;

	Edge(value_type v, int x, int y) :value(v), node_x(x), node_y(y) {};
};

class MinHeap {
private:
	vector<Edge> min_heap;
	int heap_size;

	void heapfy(int index) {
		int min = index;
		if (LEFT(index) < heap_size && (min_heap[min].value > min_heap[LEFT(index)].value)) {
			min = LEFT(index);
		}
		if (RIGHT(index) < heap_size && (min_heap[min].value > min_heap[RIGHT(index)].value)) {
			min = RIGHT(index);
		}

		if (min != index) {
			auto temp = min_heap[index];
			min_heap[index] = min_heap[min];
			min_heap[min] = temp;

			heapfy(min);
		}
	}

public:
	MinHeap() {
		heap_size = 0;
	}
	MinHeap(vector<Edge> edges) {
		build_heap(edges);
	}

	void build_heap(vector<Edge> edges) {
		min_heap = edges;
		heap_size = edges.size();
		for (int index = edges.size() / 2; index >= 0; index--) {
			heapfy(index);
		}
	}

	Edge extract_min() {
		Edge min = min_heap[0];
		heap_size--;

		auto temp = min_heap[0];
		min_heap[0] = min_heap[heap_size];
		min_heap[heap_size] = temp;

		min_heap.pop_back();
		heapfy(0);
		return min;
	}
};

struct Set;
struct SetNode {
	int node_key;
	Set* main_set;
	SetNode* next_node;

	SetNode(int key) :node_key(key), main_set(nullptr), next_node(nullptr) {};
};
struct Set {
	SetNode* head;
	SetNode* tail;

	Set(SetNode* node) :head(node), tail(node) {
		node->main_set = this;
	}
};

class DisjointSet {
private:
	vector<SetNode*> set_nodes;

public:
	void make_set(SetNode* node) {
		new Set(node);
	}

	void make_sets(int node_num) {
		for (int node_key = 0; node_key < node_num; node_key++) {
			SetNode* new_node = new SetNode(node_key);
			make_set(new_node);
			set_nodes.push_back(new_node);
		}
	}

	Set* find_set(int node_key) {
		return set_nodes[node_key]->main_set;
	}

	void union_sets(Set* set_x, Set* set_y) {
		set_x->tail->next_node = set_y->head;
		set_x->tail = set_y->tail;

		set_y->head->main_set = set_x;
		for (auto set_node = set_y->head; set_node != set_y->tail;) {
			set_node = set_node->next_node;
			set_node->main_set = set_x;
		}

		delete set_y;
	}
};

class Kruskal {
private:
	vector<vector<int> > gragh;
	vector<Edge> min_edges;
	MinHeap min_edges_heap;
	DisjointSet nodes_sets;
	int node_num;
	int edge_num;

public:
	Kruskal(vector<vector<int> > G) {
		gragh = G;
		node_num = G.size();

		vector<Edge> edges;
		edge_num = 0;
		for (int x_index = 0; x_index < node_num; x_index++) {
			for (int y_index = x_index; y_index < node_num; y_index++) {
				if (gragh[x_index][y_index] != 0) {
					edges.push_back(Edge(gragh[x_index][y_index], x_index, y_index));
					edge_num++;
				}
			}
		}
		min_edges_heap.build_heap(edges);
		nodes_sets.make_sets(node_num);

		for (int loop_tag = 0; loop_tag < edge_num; loop_tag++) {
			Edge min = min_edges_heap.extract_min();
			Set* set_x = nodes_sets.find_set(min.node_x);
			Set* set_y = nodes_sets.find_set(min.node_y);
			if (set_x != set_y) {
				min_edges.push_back(min);
				nodes_sets.union_sets(set_x, set_y);
			}
		}
	}

	void show_min_edges() {
		for (auto edge : min_edges) {
			cout << edge.node_x << '-' << edge.node_y << ':' << edge.value << endl;
		}
	}
};

int main() {
	vector<vector<int> > test_gragh;
	test_gragh.resize(9, vector<int>(9));
	test_gragh[0][1] = 4;
	test_gragh[0][7] = 8;
	test_gragh[1][7] = 11;
	test_gragh[1][2] = 8;
	test_gragh[7][8] = 7;
	test_gragh[2][8] = 2;
	test_gragh[6][8] = 6;
	test_gragh[6][7] = 1;
	test_gragh[2][5] = 4;
	test_gragh[5][6] = 2;
	test_gragh[2][3] = 7;
	test_gragh[3][5] = 14;
	test_gragh[3][4] = 9;
	test_gragh[4][5] = 10;

	Kruskal test_k(test_gragh);
	test_k.show_min_edges();
	return 0;
}