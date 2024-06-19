#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Función para procesar cada conjunto de datos
void procesarConjunto() {
    int numArboles, alturaMaxima, alturaPerdida;
    cin >> numArboles >> alturaMaxima >> alturaPerdida;

    // Matriz que almacena la cantidad de bellotas en cada altura de cada árbol
    vector<vector<int>> bellotasPorArbol(numArboles, vector<int>(alturaMaxima + 1, 0));
    
    // Leer las bellotas y llenar la matriz bellotasPorArbol
    for (int i = 0; i < numArboles; ++i) {
        int numBellotas;
        cin >> numBellotas;
        for (int j = 0; j < numBellotas; ++j) {
            int altura;
            cin >> altura;
            bellotasPorArbol[i][altura]++;
        }
    }

    // Matriz para almacenar el número máximo de bellotas que se pueden recoger desde cada árbol y altura
    vector<vector<int>> bellotasMaximas(numArboles, vector<int>(alturaMaxima + 1, 0));

    // Vector para almacenar la cantidad máxima de bellotas que se pueden recoger en cada altura considerando todos los árboles
    vector<int> bellotasAcumuladas(alturaMaxima + 1, 0);

    // Calcular la cantidad máxima de bellotas que se pueden recoger en cada árbol y altura
    for (int altura = 0; altura <= alturaMaxima; ++altura) {
        for (int i = 0; i < numArboles; ++i) {
            // Si estamos en la base del árbol, el valor es simplemente la cantidad de bellotas en esa altura
            if (altura == 0) {
                bellotasMaximas[i][altura] = bellotasPorArbol[i][altura];
            } else {
                // Si Jayjay se queda en el mismo árbol
                bellotasMaximas[i][altura] = bellotasMaximas[i][altura - 1] + bellotasPorArbol[i][altura];
                // Si Jayjay vuela a este árbol desde otro árbol
                if (altura >= alturaPerdida) {
                    bellotasMaximas[i][altura] = max(bellotasMaximas[i][altura], bellotasAcumuladas[altura - alturaPerdida] + bellotasPorArbol[i][altura]);
                }
            }
            // Actualizar el vector de máxima cantidad de bellotas
            bellotasAcumuladas[altura] = max(bellotasAcumuladas[altura], bellotasMaximas[i][altura]);
        }
    }

    // La cantidad máxima de bellotas que Jayjay puede recoger al bajar de los árboles es el valor máximo en bellotasAcumuladas[alturaMaxima]
    cout << bellotasAcumuladas[alturaMaxima] << endl;
}

int main() {
    ios::sync_with_stdio(0); // Desactiva la sincronización con stdio para mejorar la eficiencia
    cin.tie(0); // Desenlaza cin de cout para mejorar la eficiencia

    int numConjuntos;
    cin >> numConjuntos;
    while (numConjuntos--) {
        procesarConjunto();
    }

    return 0;
}
