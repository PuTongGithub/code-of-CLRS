//Dijstra
//2017-03-18 16:42:42
#include<iostream>
#include<vector>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*(x+1)
#define PARENT(x) (x-1)/2
#define P_I INT_MAX

typedef int value_type;

using namespace std;

struct GraphNode {
	int node_key;
	int distance;
	int pre_node_key;

	GraphNode(int key) :node_key(key), distance(P_I), pre_node_key(-1) {};
};

struct Edge {
	value_type value;
	int node_x;
	int node_y;
	Edge(value_type v, int x, int y) :value(v), node_x(x), node_y(y) {};

	/*
	bool operator==(const Edge &edge) {
		if ((edge.node_x == node_x) && (edge.node_y == node_y) && (edge.value == value)) {
			return true;
		}
		else {
			return false;
		}
	}
	*/
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

	bool empty() {
		return min_heap.empty();
	}

	void show_heap() {
		cout << "Min heap:" << endl;
		for (auto edge : min_heap) {
			cout << edge.node_x << '-' << edge.node_y << ':' << edge.value << endl;
		}
		cout << endl;
	}
};

class Dijstra {
private:
	vector<vector<int> > graph;
	MinHeap min_edge_heap;
	//vector<Edge> edges;
	vector<GraphNode> nodes;
	vector<int> nodes_state;
	int node_num;

	void relax(int x_key, int y_key) {
		if (nodes[x_key].distance == P_I) {
			return;
		}
		if (nodes[y_key].distance > nodes[x_key].distance + graph[x_key][y_key]) {
			nodes[y_key].distance = nodes[x_key].distance + graph[x_key][y_key];
			nodes[y_key].pre_node_key = x_key;
		}
	}

	void relax_edges(int node_key) {
		for (int index = 0; index < node_num; index++) {
			if (graph[node_key][index] != 0) {
				relax(node_key, index);
			}
		}
	}

	void add_edges(int node_key) {
		for (int index = 0; index < node_num; index++) {
			if (nodes_state[index] == 0 && graph[node_key][index] != 0) {
				min_edge_heap.insert(Edge(graph[node_key][index], node_key, index));
			}
		}
	}

public:
	Dijstra(vector<vector<int> > G) :graph(G), node_num(G.size()) {
		/*
		for (int x_index = 0; x_index < node_num; x_index++) {
			for (int y_index = 0; y_index < node_num; y_index++) {
				if (graph[x_index][y_index] != 0) {
					edges.push_back(Edge(graph[x_index][y_index], x_index, y_index));
				}
			}
		}
		min_edge_heap.build_heap(edges);
		*/
		for (int node_key = 0; node_key < node_num; node_key++) {
			nodes.push_back(GraphNode(node_key));
		}
		nodes_state.resize(node_num, 0);
		add_edges(0);
		nodes_state[0] = 1;
		nodes[0].distance = 0;
		relax_edges(0);
		while (!min_edge_heap.empty()) {
			Edge min = min_edge_heap.extract_min();
			while (nodes_state[min.node_y] != 0) {
				min = min_edge_heap.extract_min();
			}
			nodes_state[min.node_y] = 1;
			relax_edges(min.node_y);
		}
	}

	void show_distance() {
		for (auto node : nodes) {
			cout << node.distance << ' ';
		}
		cout << endl;
	}

	void show_path(int node_key) {
		cout << "Path to " << node_key << endl;
		while (node_key != 0) {
			node_key = nodes[node_key].pre_node_key;
			cout << node_key << ' ';
		}
		cout << endl;
	}
};

int main() {
	vector<vector<int> > G = {
		{ 0,10,0,0,5 },
		{ 0,0,1,0,2 },
		{ 0,0,0,4,0 },
		{ 7,0,6,0,0 },
		{ 0,3,9,2,0 }
	};

	Dijstra test_sp(G);
	test_sp.show_distance();
	for (int node_key = 0; node_key < G.size(); node_key++) {
		test_sp.show_path(node_key);
	}
	return 0;
}