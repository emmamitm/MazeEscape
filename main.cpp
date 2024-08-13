
#include "string"
#include "vector"
#include "iostream"
#include "queue"
using namespace std;
int traverse(vector<string>& graph) {
    int graphSize = graph.size();
    int graphLength = graph[0].size();
    vector<vector<int>> dist(graphSize, vector<int>(graphLength, INT_MAX));
    dist[0][0] = 0;
    using node = pair<int, pair<int, int>>;
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({0, {0, 0}});
    while (!pq.empty()) {
        pair<int, pair<int, int>> current = pq.top();
        pq.pop();
        int distance = current.first;
        int first = current.second.first;
        int second = current.second.second;
        if (dist[first][second] < distance)
            continue;
        const vector<vector<int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (auto& dir : dirs) {
            int changeFirst = first + dir[0];
            int changeSecond = second + dir[1];
            if (changeFirst>=0 && changeSecond>=0 && changeFirst<graphSize && changeSecond<graphLength && graph[changeFirst][changeSecond] != '#' && (dist[changeFirst][changeSecond] > distance + 1)) {
                dist[changeFirst][changeSecond] = distance + 1;
                pq.push({dist[changeFirst][changeSecond], {changeFirst, changeSecond}});
            }
        }
    }
    int endDistance = dist[graphSize-1][graphLength-1];
    if (endDistance == INT_MAX) {
        return -1;
    } else {
        return endDistance;
    }
}

int main() {
    vector<string> graph = {"s#.#.", ".#...", "...#t"};
    int result = traverse(graph);
    cout << "The length of the shortest path is: " << result << endl;
    return 0;
}