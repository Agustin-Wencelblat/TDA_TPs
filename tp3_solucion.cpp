#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int c;
    cin >> c;

    while (c--) {
        int t, h, f;
        cin >> t >> h >> f;

        vector<vector<int>> acorns(t, vector<int>(h + 1, 0));

        // Leer alturas de las bellotas en cada árbol
        for (int i = 0; i < t; ++i) {
            int a;
            cin >> a;
            for (int j = 0; j < a; ++j) {
                int n;
                cin >> n;
                acorns[i][n]++;
            }
        }

        vector<int> dp(h + 1, 0);

        // Llenar dp para la altura más baja
        for (int i = 0; i < t; ++i) {
            dp[h] = max(dp[h], acorns[i][h]);
        }

        // Iterar desde la segunda altura más baja hasta la base
        for (int height = h - 1; height >= 0; --height) {
            for (int tree = 0; tree < t; ++tree) {
                int add = acorns[tree][height + 1];
                if (height + f <= h) {
                    add = max(add, dp[height + f]);
                }
                acorns[tree][height] += add;
                dp[height] = max(dp[height], acorns[tree][height]);
            }
        }

        cout << dp[0] << endl;
    }

    return 0;
}
