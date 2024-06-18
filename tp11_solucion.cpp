#include <iostream>
#include <vector>
#include <limits>
#include <cstring>
#include <cstdio>

using namespace std;

// Estructura para representar una arista en el grafo
struct Arista {
    int origen, destino, peso;
};

vector<Arista> aristas; // Vector para almacenar todas las aristas del grafo
int D[1024], n, m; // Arreglo de distancias y variables para el número de nodos y restricciones

// Función para agregar una arista al grafo
void agregarArista(int origen, int destino, int peso) {
    aristas.push_back({origen, destino, peso});
}

// Función que implementa el algoritmo de Bellman-Ford para detectar ciclos negativos
bool bellmanFord(int vertices) {
    // Inicializa las distancias con el valor máximo posible excepto el nodo origen (0)
    fill(D, D + vertices + 1, numeric_limits<int>::max());
    D[0] = 0;

    // Relajamos todas las aristas vertices-1 veces
    for (int i = 0; i < vertices; ++i) {
        bool cambiado = false;
        for (const auto& arista : aristas) {
            if (D[arista.origen] != numeric_limits<int>::max() &&
                D[arista.origen] + arista.peso < D[arista.destino]) {
                D[arista.destino] = D[arista.origen] + arista.peso;
                cambiado = true;
            }
        }
        // Si en una iteración no se realizan cambios, terminamos antes
        if (!cambiado) break;
    }

    // Verificamos si existe un ciclo negativo
    for (const auto& arista : aristas) {
        if (D[arista.origen] != numeric_limits<int>::max() &&
            D[arista.origen] + arista.peso < D[arista.destino]) {
            return true; // Ciclo negativo encontrado
        }
    }

    return false; // No se encontró ningún ciclo negativo
}

int main() {
    // Leer los valores de n (longitud de la secuencia) y m (número de restricciones)
    while (scanf("%d %d", &n, &m) == 2 && n > 0) {
        aristas.clear(); // Limpiar el vector de aristas para el nuevo conjunto de datos
        n += 2; // Aumentar n en 2 para incluir el vértice 0 y el vértice n+1

        // Leer cada restricción
        for (int i = 0; i < m; ++i) {
            int si, ni, ki;
            char op[3];
            scanf("%d %d %s %d", &si, &ni, op, &ki);

            // Convertir la restricción a una arista del grafo
            if (strcmp(op, "gt") == 0) {
                // si + ni > ki -> a[si + ni + 1] - a[si] > -ki - 1
                agregarArista(si + ni + 1, si, -ki - 1);
            } else if (strcmp(op, "lt") == 0) {
                // si + ni < ki -> a[si] - a[si + ni + 1] < ki - 1
                agregarArista(si, si + ni + 1, ki - 1);
            }
        }

        // Añadir aristas de peso 0 desde el vértice 0 a todos los otros vértices
        for (int i = 1; i < n; ++i) {
            agregarArista(0, i, 0);
        }

        // Ejecutar el algoritmo de Bellman-Ford para detectar ciclos negativos
        if (bellmanFord(n)) {
            printf("successful conspiracy\n");
        } else {
            printf("lamentable kingdom\n");
        }
    }

    return 0;
}
