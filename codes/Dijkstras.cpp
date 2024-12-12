#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef pair<int, int> pii;
void dijkstra(int source, const vector<vector<pii>>& graph, vector<int>& distances) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    distances[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int curr_node = pq.top().second;
        pq.pop();
        if (curr_dist > distances[curr_node]) {
            continue;
        }
        for (const auto& neighbor : graph[curr_node]) {
            int next_node = neighbor.first;
            int weight = neighbor.second;
            if (distances[curr_node] + weight < distances[next_node]) {
                distances[next_node] = distances[curr_node] + weight;
                pq.push({distances[next_node], next_node});
            }
        }
    }
}
int main() {
    int nodes, edges;
    cout << "Enter the number of nodes and edges: ";
    cin >> nodes >> edges;
    vector<vector<pii>> graph(nodes);
    cout << "Enter edges (format: source destination weight):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w); 
    }
    int source;
    cout << "Enter the source node: ";
    cin >> source;
    vector<int> distances(nodes, INT_MAX);
    dijkstra(source, graph, distances);
    cout << "Shortest distances from source node " << source << ":\n";
    for (int i = 0; i < nodes; ++i) {
        cout << "Node " << i << " -> Distance: ";
        if (distances[i] == INT_MAX) {
            cout << "Infinity\n";
        } else {
            cout << distances[i] << "\n";
        }
    }
    return 0;
}
