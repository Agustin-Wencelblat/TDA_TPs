#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Calcular la longitud de la subsecuencia creciente más larga
int longestIncreasingSubsequence(const vector<int>& heights, const vector<int>& widths) {
    int n = heights.size();
    vector<int> dp(n, 0);

    for (int i = 0; i < n; ++i) {
        dp[i] = widths[i]; // Cada edificio es una subsecuencia de longitud igual a su ancho
        for (int j = 0; j < i; ++j) {
            if (heights[j] < heights[i]) {
                dp[i] = max(dp[i], dp[j] + widths[i]); // Actualizamos si encontramos una subsecuencia creciente más larga
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

// Calcular la longitud de la subsecuencia decreciente más larga
int longestDecreasingSubsequence(const vector<int>& heights, const vector<int>& widths) {
    int n = heights.size();
    vector<int> dp(n, 0);

    for (int i = 0; i < n; ++i) {
        dp[i] = widths[i]; // Cada edificio es una subsecuencia de longitud igual a su ancho
        for (int j = 0; j < i; ++j) {
            if (heights[j] > heights[i]) {
                dp[i] = max(dp[i], dp[j] + widths[i]); // Actualizamos si encontramos una subsecuencia decreciente más larga
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;

        vector<int> heights(N);
        vector<int> widths(N);

        for (int i = 0; i < N; ++i) {
            cin >> heights[i];
        }

        for (int i = 0; i < N; ++i) {
            cin >> widths[i];
        }

        int increasing = longestIncreasingSubsequence(heights, widths);
        int decreasing = longestDecreasingSubsequence(heights, widths);

        if (increasing >= decreasing) {
            cout << "Case " << t << ". Increasing (" << increasing << "). Decreasing (" << decreasing << ")." << endl;
        } else {
            cout << "Case " << t << ". Decreasing (" << decreasing << "). Increasing (" << increasing << ")." << endl;
        }
    }

    return 0;
}
