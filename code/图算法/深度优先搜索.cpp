//DFS
//2017-03-17 20:13:46
#include<iostream>
#include<vector>

using namespace std;

enum NodeState {
	not_find,
	is_found,
	finished
};

struct GraghNode {
	int key;
	vector<GraghNode*> adj_node;
	int found_time;
	int finish_time;
	GraghNode* pre_node;
	NodeState state;

	GraghNode(int k) : key(k), found_time(-1), finish_time(-1), pre_node(nullptr), state(not_find) {};
};

vector<GraghNode*> nodes;

void show_gragh() {
	for (auto node : nodes) {
		cout << node->key << ':';
		if (node->found_time > -1) {
			cout << node->found_time;
		} 
		else {
			cout << ' ';
		}
		cout << '/';
		if (node->finish_time > -1) {
			cout << node->finish_time;
		}
		else {
			cout << ' ';
		}
		cout << ' ';
	}
	cout << endl;
}

class DFS {
private:
	int time;

	void DFS_visit(GraghNode* g_node) {
		time++;
		g_node->state = is_found;
		g_node->found_time = time;

		show_gragh();

		for (auto node : g_node->adj_node) {
			if (node->state == not_find) {
				node->pre_node = g_node;
				DFS_visit(node);
			}
		}
		g_node->state = finished;
		time++;
		g_node->finish_time = time;

		show_gragh();
	}
public:
	DFS(vector<GraghNode*> &g_nodes) {
		time = 0;
		for (auto node : g_nodes) {
			if (node->state == not_find) {
				DFS_visit(node);
			}
		}
	}
};

int main() {
	for (int index = 0; index < 6; index++) {
		nodes.push_back(new GraghNode(index));
	}

	nodes[0]->adj_node.push_back(nodes[1]);
	nodes[0]->adj_node.push_back(nodes[3]);
	nodes[3]->adj_node.push_back(nodes[1]);
	nodes[1]->adj_node.push_back(nodes[4]);
	nodes[4]->adj_node.push_back(nodes[3]);
	nodes[5]->adj_node.push_back(nodes[5]);
	nodes[2]->adj_node.push_back(nodes[5]);
	nodes[2]->adj_node.push_back(nodes[4]);

	DFS test_DFS(nodes);

	return 0;
}