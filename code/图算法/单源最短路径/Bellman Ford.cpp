//Bellman Ford
//2017-03-18 14:56:47
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

class BellmanFord {
private:
	vector<vector<int> > gragh;
	vector<GraghNode> nodes;
	int node_num;
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
	bool is_path_viable;

	BellmanFord(vector<vector<int> > G) : gragh(G) {
		node_num = gragh.size();
		for (int node_key = 0; node_key < node_num; node_key++) {
			nodes.push_back(GraghNode(node_key));
		}
		start_node = 0;
		nodes[start_node].distance = 0;

		is_path_viable = true;

		for (int loop_tag = 0; loop_tag < node_num - 1; loop_tag++) {
			for (int x_index = 0; x_index < node_num; x_index++) {
				for (int y_index = 0; y_index < node_num; y_index++) {
					if (gragh[x_index][y_index] != 0) {
						relax(x_index, y_index);
					}
				}
			}
		}

		for (int x_index = 0; x_index < node_num; x_index++) {
			for (int y_index = 0; y_index < node_num; y_index++) {
				if (gragh[x_index][y_index] != 0) {
					if (nodes[y_index].distance > nodes[x_index].distance + gragh[x_index][y_index]) {
						is_path_viable = false;
						break;
					}
				}
			}
			if (!is_path_viable) {
				break;
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
		while (node_key != start_node) {
			node_key = nodes[node_key].pre_node_key;
			cout << node_key << ' ';
		}
		cout << endl;
	}
};

int main() {
	vector<vector<int> > G = {
		{ 0,6,0,0,7 },
		{ 0,0,5,-4,8 },
		{ 0,-2,0,0,0 },
		{ 2,0,7,0,0 },
		{ 0,0,-3,9,0 }
	};

	BellmanFord test_BF(G);
	test_BF.show_distance();
	cout << "Is path viable:" << test_BF.is_path_viable << endl;
	for (int node_key = 0; node_key < G.size(); node_key++) {
		test_BF.show_path(node_key);
	}
	return 0;
}