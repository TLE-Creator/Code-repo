#include<iostream>
#include<vector>
using namespace std;
class DSU {
private:
	vector<int> parents;
	vector<int> rank;
	int count;
public:
	DSU(int n) {
		parents.resize(n + 1);
		rank.resize(n + 1, 1);
		for (int i = 1; i <= n; i++) {
			parents[i] = i;
		}
		count = n;
	}
	int find(int x) {
		if (parents[x] != x) {
			parents[x] = find(parents[x]);
		}
		return parents[x];
	}
	void UnionSets(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);
		if (rootX == rootY) {
			return;
		}
		if (rank[rootX] < rank[rootY]) {
			parents[rootX] = rootY;
		}
		else if (rank[rootX] > rank[rootY]) {
			parents[rootY] = rootX;
		}
		else {
			parents[rootY] = rootX;
			rank[rootX]++;
		}
		count--;
	}
	bool connected(int x, int y) {
		return find(x) == find(y);
	}
	int getCount() {
		return count;
	}
};
int n, m;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	DSU uf(n);
	while (m--) {
		int z, x, y;
		cin >> z >> x >> y;
		if (z == 1) uf.UnionSets(x, y);
		else {
			if (uf.connected(x, y)) {
				cout << "Y";
			}
			else {
				cout << "N";
			}
			cout << endl;
		}
	}
	return 0;
}