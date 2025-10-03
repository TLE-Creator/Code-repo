#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class DSU {
private:
	vector<int> parent;
	vector<int> rank;
	int count;
public:
	DSU(int n) {
		parent.resize(n + 1);
		rank.resize(n + 1, 1);
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
		}
		count = n;
	}
	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	void UnionSets(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);
		if (rootX == rootY) {
			return;
		}
		if (rank[rootX] < rank[rootY]) {
			parent[rootX] = rootY;
		}
		else if (rank[rootX] > rank[rootY]) {
			parent[rootY] = rootX;
		}
		else {
			parent[rootY] = rootX;
			rank[rootX]++;
		}
		count--;
	}
	int getCount() {
		return count;
	}
	bool isConnected(int x, int y) {
		return find(x) == find(y);
	}
};
struct Edge {
	int  u, v, weight;
	Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
	bool operator<(const Edge& other) {
		return weight < other.weight;
	}
};
class Graph {
private:
	vector<Edge> edges;
	int V;
public:
	Graph(int v) :V(v) {}
	void addEdge(int u, int v, int w) {
		edges.push_back({ u,v,w });
		edges.push_back({ v,u,w });
	}
	pair<int, bool> KruskalMST() {
		sort(edges.begin(), edges.end());
		DSU uf(V);
		int total = 0;
		int edgeCount = 0;
		for (Edge edge : edges) {
			if (edgeCount == V - 1) {
				break;
			}
			int rootU = uf.find(edge.u);
			int rootV = uf.find(edge.v);
			if (rootU != rootV) {
				uf.UnionSets(edge.u, edge.v);
				total += edge.weight;
				edgeCount++;
			}
		}
		bool isConnect = (uf.getCount() == 1);
		return { total,isConnect };
	}
};
int n, m;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	DSU dsu(n);
	Graph g(n);
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		dsu.UnionSets(x, y);
		g.addEdge(x, y, z);
	}
	if (g.KruskalMST().second) {
		cout << g.KruskalMST().first;
	}
	else {
		cout << "orz";
	}
	return 0;
}