//BFS
//2017-03-17 18:53:05
#include<iostream>
#include<vector>

using namespace std;

struct GraghNode {
	int key;
	vector<GraghNode*> adj_node;
	int distance;
	GraghNode* pre_node;
	bool is_found;

	GraghNode(int k) : key(k), distance(0), pre_node(nullptr), is_found(false) {};
};

vector<GraghNode*> nodes;

void show_gragh() {
	for (auto node : nodes) {
		cout << node->key;
		if (node->is_found) {
			cout << '+';
		}
		else {
			cout << '-';
		}
		cout << ' ';
	}
}

class Queue {
private:
	vector<GraghNode*> datas;
public:
	void in(GraghNode* data) {
		if (datas.empty()) {
			datas.push_back(data);
		}
		else {
			datas.insert(datas.begin(), data);
		}
	}

	GraghNode* out() {
		if (datas.empty()) {
			return nullptr;
		}
		GraghNode* data = datas.back();
		datas.pop_back();
		return data;
	}

	bool is_empty() {
		return datas.empty();
	}
};

class BFS {
private:
	Queue BFS_queue;
public:
	BFS(GraghNode* g_node) {
		BFS_queue.in(g_node);
		g_node->is_found = true;
		while (!BFS_queue.is_empty()) {
			GraghNode* p_node = BFS_queue.out();
			for (auto node : p_node->adj_node) {
				if (!node->is_found) {
					node->is_found = true;
					node->distance = p_node->distance + 1;
					node->pre_node = p_node;
					BFS_queue.in(node);
					show_gragh();
					cout << endl;
				}
			}
		}
	}
};

int main() {
	for (int index = 0; index < 8; index++) {
		nodes.push_back(new GraghNode(index));
	}
	
	nodes[0]->adj_node.push_back(nodes[1]);
	nodes[1]->adj_node.push_back(nodes[0]);

	nodes[0]->adj_node.push_back(nodes[4]);
	nodes[4]->adj_node.push_back(nodes[0]);

	nodes[1]->adj_node.push_back(nodes[5]);
	nodes[5]->adj_node.push_back(nodes[1]);

	nodes[5]->adj_node.push_back(nodes[2]);
	nodes[2]->adj_node.push_back(nodes[5]);

	nodes[5]->adj_node.push_back(nodes[6]);
	nodes[6]->adj_node.push_back(nodes[5]);

	nodes[2]->adj_node.push_back(nodes[3]);
	nodes[3]->adj_node.push_back(nodes[2]);

	nodes[2]->adj_node.push_back(nodes[6]);
	nodes[6]->adj_node.push_back(nodes[2]);

	nodes[3]->adj_node.push_back(nodes[6]);
	nodes[6]->adj_node.push_back(nodes[3]);

	nodes[3]->adj_node.push_back(nodes[7]);
	nodes[7]->adj_node.push_back(nodes[3]);

	nodes[6]->adj_node.push_back(nodes[7]);
	nodes[7]->adj_node.push_back(nodes[6]);

	BFS test_BFS(nodes[1]);

	return 0;
}