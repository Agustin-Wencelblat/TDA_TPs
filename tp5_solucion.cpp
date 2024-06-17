#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long int minWork(vector<int>& demands) {
    int n = demands.size();
    int pos_start = 0, neg_start = 0;
    long long int total_work = 0;

    while (pos_start < n && neg_start < n) {
        // Encontrar la próxima casa con demanda positiva
        while (pos_start < n && demands[pos_start] <= 0) {
            pos_start++;
        }
        // Encontrar la próxima casa con demanda negativa
        while (neg_start < n && demands[neg_start] >= 0) {
            neg_start++;
        }
        
        if (pos_start < n && neg_start < n) {
            int min_wine = min(demands[pos_start], -demands[neg_start]);
            total_work += min_wine * abs(pos_start - neg_start);
            demands[pos_start] -= min_wine;
            demands[neg_start] += min_wine;
        }
    }

    return total_work;
}

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }

        vector<int> demands(n);
        for (int i = 0; i < n; ++i) {
            cin >> demands[i];
        }

        cout << minWork(demands) << endl;
    }

    return 0;
}
