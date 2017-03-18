//prim
//2017-03-18 11:16:17
#include<iostream>
#include<vector>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*(x+1)
#define PARENT(x) (x-1)/2

typedef int value_type;

using namespace std;

struct Edge {
	value_type value;
	int node_x;
	int node_y;
	Edge(value_type v, int x, int y) :value(v), node_x(x), node_y(y) {};

	bool operator==(const Edge &edge) {
		if ((edge.node_x == node_x)&&(edge.node_y == node_y)&&(edge.value == value)) {
			return true;
		}
		else {
			return false;
		}
	}
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

	void up_heapfy(int index) {
		int min = index;
		while (PARENT(min) >= 0 && (min_heap[PARENT(min)].value > min_heap[min].value)) {
			auto temp = min_heap[min];
			min_heap[min] = min_heap[PARENT(min)];
			min_heap[PARENT(min)] = temp;
			min = PARENT(min);
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

	void insert(Edge edge) {
		heap_size++;
		min_heap.push_back(edge);
		up_heapfy(heap_size - 1);
	}

	void reduce_val(int edge_index, int new_val) {
		if (new_val > min_heap[edge_index].value) {
			return;
		}
		min_heap[edge_index].value = new_val;
		up_heapfy(edge_index);
	}

	void erase(int edge_index) {
		reduce_val(edge_index, INT_MIN);
		extract_min();
	}

	Edge extract_min() {
		if (heap_size == 0) {
			return Edge(-1, -1, -1);
		}
		Edge min = min_heap[0];
		heap_size--;

		auto temp = min_heap[0];
		min_heap[0] = min_heap[heap_size];
		min_heap[heap_size] = temp;

		min_heap.pop_back();
		heapfy(0);
		return min;
	}

	void show_heap() {
		cout << "Min heap:" << endl;
		for (auto edge : min_heap) {
			cout << edge.node_x << '-' << edge.node_y << ':' << edge.value << endl;
		}
		cout << endl;
	}
};

class Prim {
private:
	vector<vector<int> > gragh;
	MinHeap min_edges_heap;
	vector<Edge> min_edges;
	int node_num;
	vector<int> nodes_state;

	void add_node_edges(int node_key) {
		for (int y_index = 0; y_index < node_num; y_index++) {
			if (gragh[node_key][y_index] != 0 && nodes_state[y_index] == 0) {
				min_edges_heap.insert(Edge(gragh[node_key][y_index], node_key, y_index));
			}
		}
	}

public:
	Prim(vector<vector<int> > G) :gragh(G) {
		node_num = gragh.size();
		nodes_state.resize(node_num, 0);

		int start_node = -1;
		for (int x_index = 0; x_index < node_num; x_index++) {
			for (int y_index = 0; y_index < node_num; y_index++) {
				if (gragh[x_index][y_index] != 0) {
					start_node = x_index;
				}
			}
			if (start_node != -1) {
				nodes_state[start_node] = 1;
				add_node_edges(start_node);
				break;
			}
		}

		for (int loop_tag = 1; loop_tag < node_num; loop_tag++) {
			Edge min = min_edges_heap.extract_min();
			while (nodes_state[min.node_y] != 0) {
				min = min_edges_heap.extract_min();
			}
			min_edges.push_back(min);
			nodes_state[min.node_y] = 1;
			add_node_edges(min.node_y);
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
	test_gragh[1][0] = 4;
	test_gragh[0][7] = 8;
	test_gragh[7][0] = 8;
	test_gragh[1][7] = 11;
	test_gragh[7][1] = 11;
	test_gragh[1][2] = 8;
	test_gragh[2][1] = 8;
	test_gragh[7][8] = 7;
	test_gragh[8][7] = 7;
	test_gragh[2][8] = 2;
	test_gragh[8][2] = 2;
	test_gragh[6][8] = 6;
	test_gragh[8][6] = 6;
	test_gragh[6][7] = 1;
	test_gragh[7][6] = 1;
	test_gragh[2][5] = 4;
	test_gragh[5][2] = 4;
	test_gragh[5][6] = 2;
	test_gragh[6][5] = 2;
	test_gragh[2][3] = 7;
	test_gragh[3][2] = 7;
	test_gragh[3][5] = 14;
	test_gragh[5][3] = 14;
	test_gragh[3][4] = 9;
	test_gragh[4][3] = 9;
	test_gragh[4][5] = 10;
	test_gragh[5][4] = 10;

	Prim test_p(test_gragh);
	test_p.show_min_edges();
	return 0;
}