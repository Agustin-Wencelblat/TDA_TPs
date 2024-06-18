#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm> 
#include <sstream>  

using namespace std;

const int INF = INT_MAX;
const int MAX_FLOORS = 100;
const int SWITCH_TIME = 60;

// Estructura para representar una arista en el grafo
struct Edge {
    int to, weight;
};

// Función principal para resolver el problema
int solve(int n, int k, vector<int>& times, vector<vector<int>>& floors) {
    // Grafo de 100 * n nodos (cada nodo representa un piso de un elevador específico)
    vector<vector<Edge>> graph(MAX_FLOORS * n);

    // Construcción del grafo
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < floors[i].size(); ++j) {
            if (j > 0) {
                int from = i * MAX_FLOORS + floors[i][j - 1];
                int to = i * MAX_FLOORS + floors[i][j];
                int weight = (floors[i][j] - floors[i][j - 1]) * times[i];
                graph[from].push_back({to, weight});
                graph[to].push_back({from, weight});
            }
        }
    }

    // Conexiones entre diferentes elevadores en el mismo piso
    for (int f = 0; f < MAX_FLOORS; ++f) {
        vector<int> nodes;
        for (int i = 0; i < n; ++i) {
            if (find(floors[i].begin(), floors[i].end(), f) != floors[i].end()) {
                nodes.push_back(i * MAX_FLOORS + f);
            }
        }
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                graph[nodes[i]].push_back({nodes[j], SWITCH_TIME});
                graph[nodes[j]].push_back({nodes[i], SWITCH_TIME});
            }
        }
    }

    // Algoritmo de Dijkstra
    vector<int> dist(MAX_FLOORS * n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Iniciando desde el piso 0 de todos los elevadores que pasan por ahí
    for (int i = 0; i < n; ++i) {
        if (find(floors[i].begin(), floors[i].end(), 0) != floors[i].end()) {
            int start = i * MAX_FLOORS;
            dist[start] = 0;
            pq.push({0, start});
        }
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Encontrar la distancia mínima al piso k
    int min_time = INF;
    for (int i = 0; i < n; ++i) {
        if (find(floors[i].begin(), floors[i].end(), k) != floors[i].end()) {
            min_time = min(min_time, dist[i * MAX_FLOORS + k]);
        }
    }

    return (min_time == INF) ? -1 : min_time;
}

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> times(n);
        for (int i = 0; i < n; ++i) {
            cin >> times[i];
        }

        vector<vector<int>> floors(n);
        cin.ignore(); // Ignorar el salto de línea después de los tiempos
        for (int i = 0; i < n; ++i) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            int num;
            while (iss >> num) {
                floors[i].push_back(num);
            }
        }

        int result = solve(n, k, times, floors);
        if (result == -1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << result << endl;
        }
    }

    return 0;
}
