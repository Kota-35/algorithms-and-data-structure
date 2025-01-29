#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 幅優先探索 (BFS)
void bfs(vector<vector<int> >& adj, int s) {
    // キューを宣言
    queue<int> q;

    // 訪問済みフラグを宣言
    vector<bool> visited(adj.size(), false);

    // 始点を訪問済みにする
    visited[s] = true;
    q.push(s);

    while (!q.empty()) {
        // キューの先頭を取り出す
        int u = q.front();
        q.pop();
        cout << u << " ";

        // 隣接する頂点を訪問済みにする
        for (int x: adj[u]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    } 
}

void add_edge(vector<vector<int> >& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main() {
    // Number of vertices in the graph
    int V = 5;

    // Adjacency list representation of the graph
    vector<vector<int> > adj(V);

    // Add edges to the graph
    add_edge(adj, 0, 1);
    add_edge(adj, 0, 2);
    add_edge(adj, 1, 3);
    add_edge(adj, 1, 4);
    add_edge(adj, 2, 4);

    // Perform BFS traversal starting from vertex 0
    cout << "BFS starting from 0 : \n";
    bfs(adj, 0);

    return 0;
}