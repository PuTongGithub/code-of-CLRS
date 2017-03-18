//DAG shortest paths
//2017-03-18 15:54:20
#include<iostream>
#include<vector>
#define P_I INT_MAX

using namespace std;

struct GraghNode {
	int node_key;
	int distance;
	int pre_node_key;

	GraghNode(int key) :node_key(key), distance(P_I), pre_node_key(-1) {};
};

class TopoSort {
private:
	vector<int> sort_nodes;
	vector<int> nodes_state;
	vector<vector<int> > gragh;
	int node_num;

	void DFS_visit(int node_key) {
		if (nodes_state[node_key] == 1) {
			return;
		}
		nodes_state[node_key] = 1;

		for (int index = 0; index < node_num; index++) {
			if (gragh[node_key][index] != 0) {
				DFS_visit(index);
			}
		}

		sort_nodes.push_back(node_key);
	}

public:
	TopoSort(vector<vector<int> > G): gragh(G) {
		node_num = G.size();
		nodes_state.resize(node_num, 0);

		for (int node_key = 0; node_key < node_num; node_key++) {
			DFS_visit(node_key);
		}
	}

	vector<int> sorted_nodes_key() {
		vector<int> sorted;
		for (int index = sort_nodes.size() - 1; index >= 0; index--) {
			sorted.push_back(sort_nodes[index]);
		}
		return sorted;
	}
};

class DAGSP {
private:
	vector<vector<int> > gragh;
	int node_num;
	vector<GraghNode> nodes;
	vector<int> topo_sort_key;
	int start_node;

	void relax(int x_key, int y_key) {
		if (nodes[x_key].distance != P_I) {
			if (nodes[y_key].distance > nodes[x_key].distance + gragh[x_key][y_key]) {
				nodes[y_key].distance = nodes[x_key].distance + gragh[x_key][y_key];
				nodes[y_key].pre_node_key = x_key;
			}
		}
	}

public:
	DAGSP(vector<vector<int> > G) :gragh(G) {
		node_num = G.size();
		TopoSort sort(G);
		topo_sort_key = sort.sorted_nodes_key();
		for (int node_key = 0; node_key < node_num; node_key++) {
			nodes.push_back(GraghNode(node_key));
		}
		start_node = 1;
		nodes[start_node].distance = 0;

		for (auto node_key : topo_sort_key) {
			for (int index = 0; index < node_num; index++) {
				if (gragh[node_key][index] != 0) {
					relax(node_key, index);
				}
			}
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
		while (node_key != start_node && node_key != -1) {
			node_key = nodes[node_key].pre_node_key;
			cout << node_key << ' ';
		}
		cout << endl;
	}
};

int main() {
	vector<vector<int> > G = {
		{ 0,5,3,0,0,0 },
		{ 0,0,2,6,0,0 },
		{ 0,0,0,7,4,2 },
		{ 0,0,0,0,-1,1 },
		{ 0,0,0,0,0,-2 },
		{ 0,0,0,0,0,0 },
	};

	DAGSP test_sp(G);
	test_sp.show_distance();
	for (int node_key = 0; node_key < G.size(); node_key++) {
		test_sp.show_path(node_key);
	}
	return 0;
}