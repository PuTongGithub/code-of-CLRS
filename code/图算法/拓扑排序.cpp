//topological sort
//2017-03-17 20:41:23
#include<iostream>
#include<vector>
#include<string>

using namespace std;

enum NodeState {
	not_find,
	is_found,
	finished
};

struct GraghNode {
	string key;
	vector<GraghNode*> adj_node;
	int found_time;
	int finish_time;
	GraghNode* pre_node;
	NodeState state;

	GraghNode(string k) : key(k), found_time(-1), finish_time(-1), pre_node(nullptr), state(not_find) {};
};

class DFS {
private:
	int time;
	vector<GraghNode*> topo_sort;

	void DFS_visit(GraghNode* g_node) {
		time++;
		g_node->state = is_found;
		g_node->found_time = time;

		for (auto node : g_node->adj_node) {
			if (node->state == not_find) {
				node->pre_node = g_node;
				DFS_visit(node);
			}
		}
		g_node->state = finished;
		time++;
		g_node->finish_time = time;

		topo_sort.push_back(g_node);
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

	void show_sort() {
		for (auto node : topo_sort) {
			cout << node->key << endl;
		}
	}
};

int main() {
	vector<GraghNode*> nodes;
	nodes.push_back(new GraghNode("underwear"));
	nodes.push_back(new GraghNode("pants"));
	nodes.push_back(new GraghNode("belt"));
	nodes.push_back(new GraghNode("shirt"));
	nodes.push_back(new GraghNode("sock"));
	nodes.push_back(new GraghNode("shoes"));
	nodes.push_back(new GraghNode("whatch"));
	nodes.push_back(new GraghNode("jack"));
	nodes.push_back(new GraghNode("tie"));


	nodes[0]->adj_node.push_back(nodes[1]);
	nodes[0]->adj_node.push_back(nodes[5]);

	nodes[1]->adj_node.push_back(nodes[5]);
	nodes[4]->adj_node.push_back(nodes[5]);
	nodes[1]->adj_node.push_back(nodes[2]);

	nodes[3]->adj_node.push_back(nodes[8]);
	nodes[3]->adj_node.push_back(nodes[2]);
	nodes[8]->adj_node.push_back(nodes[7]);
	nodes[2]->adj_node.push_back(nodes[7]);

	DFS test_DFS(nodes);
	test_DFS.show_sort();

	return 0;
}