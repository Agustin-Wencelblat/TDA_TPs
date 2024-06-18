#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <climits>  

using namespace std;

struct Arista {
    int origen, destino, costo;
    bool operator>(const Arista& otro) const {
        return costo > otro.costo;
    }
};

int calcular_distancia(const string& a, const string& b) {
    int distancia = 0;
    for (int i = 0; i < 4; ++i) {
        int d1 = abs(a[i] - b[i]);
        int d2 = 10 - d1;
        distancia += min(d1, d2);
    }
    return distancia;
}

int encontrar(int nodo, vector<int>& padre) {
    if (padre[nodo] != nodo) {
        padre[nodo] = encontrar(padre[nodo], padre);
    }
    return padre[nodo];
}

void unir(int nodo1, int nodo2, vector<int>& padre, vector<int>& rango) {
    int raiz1 = encontrar(nodo1, padre);
    int raiz2 = encontrar(nodo2, padre);
    if (raiz1 != raiz2) {
        if (rango[raiz1] > rango[raiz2]) {
            padre[raiz2] = raiz1;
        } else if (rango[raiz1] < rango[raiz2]) {
            padre[raiz1] = raiz2;
        } else {
            padre[raiz2] = raiz1;
            rango[raiz1]++;
        }
    }
}

int resolver_caso(const vector<string>& claves) {
    int n = claves.size();
    vector<Arista> aristas;
    
    // Calcular las distancias entre todas las claves
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int costo = calcular_distancia(claves[i], claves[j]);
            aristas.push_back({i, j, costo});
        }
    }
    
    // Ordenar las aristas por costo
    sort(aristas.begin(), aristas.end(), [](const Arista& a, const Arista& b) {
        return a.costo < b.costo;
    });
    
    // Inicializar el padre y rango para Union-Find
    vector<int> padre(n);
    vector<int> rango(n, 0);
    for (int i = 0; i < n; ++i) {
        padre[i] = i;
    }
    
    // Algoritmo de Kruskal para encontrar el MST
    int costo_total = 0;
    for (const auto& arista : aristas) {
        int raiz1 = encontrar(arista.origen, padre);
        int raiz2 = encontrar(arista.destino, padre);
        if (raiz1 != raiz2) {
            unir(raiz1, raiz2, padre, rango);
            costo_total += arista.costo;
        }
    }
    
    // Encontrar el costo mínimo para ir de "0000" a una de las claves
    int costo_inicial = INT_MAX;
    string inicial = "0000";
    for (const auto& clave : claves) {
        costo_inicial = min(costo_inicial, calcular_distancia(inicial, clave));
    }
    
    return costo_total + costo_inicial;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<string> claves(N);
        for (int i = 0; i < N; ++i) {
            cin >> claves[i];
        }
        cout << resolver_caso(claves) << endl;
    }
    return 0;
}
