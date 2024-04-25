#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    string name;
    int attacking;
    int defending;
};

bool comparePlayers(const Player &a, const Player &b) {
    return a.name < b.name;
}

int maxAttackingSum = 0;
int maxDefendingSum = 0;
vector<string> bestAttackers;
vector<string> bestDefenders;

void findBestPositions(vector<Player> &players, int pos, int attackersCount, int defendersCount, vector<string> attackers, vector<string> defenders, int attackingSum, int defendingSum) {
    if (pos == players.size()) {
        if (attackersCount == 5 && defendersCount == 5) {
            if (attackingSum > maxAttackingSum) {
                maxAttackingSum = attackingSum;
                maxDefendingSum = defendingSum;
                bestAttackers = attackers;
                bestDefenders = defenders;
            } else if (attackingSum == maxAttackingSum && defendingSum > maxDefendingSum) {
                maxDefendingSum = defendingSum;
                bestAttackers = attackers;
                bestDefenders = defenders;
            }
        }
        return;
    }

    if (attackersCount < 5) {
        attackers.push_back(players[pos].name);
        findBestPositions(players, pos + 1, attackersCount + 1, defendersCount, attackers, defenders, attackingSum + players[pos].attacking, defendingSum);
        attackers.pop_back();
    }

    if (defendersCount < 5) {
        defenders.push_back(players[pos].name);
        findBestPositions(players, pos + 1, attackersCount, defendersCount + 1, attackers, defenders, attackingSum, defendingSum + players[pos].defending);
        defenders.pop_back();
    }
}

int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t) {
        int n = 10;
        vector<Player> players(n);

        for (int i = 0; i < n; ++i) {
            cin >> players[i].name >> players[i].attacking >> players[i].defending;
        }

        sort(players.begin(), players.end(), comparePlayers);

        maxAttackingSum = 0;
        maxDefendingSum = 0;
        bestAttackers.clear();
        bestDefenders.clear();

        vector<string> attackers, defenders;
        findBestPositions(players, 0, 0, 0, attackers, defenders, 0, 0);

        sort(bestAttackers.begin(), bestAttackers.end());
        sort(bestDefenders.begin(), bestDefenders.end());

        cout << "Case " << t << ":" << endl;
        cout << "(";
        for (int i = 0; i < 5; ++i) {
            if (i != 0) cout << ", ";
            cout << bestAttackers[i];
        }
        cout << ")" << endl;
        cout << "(";
        for (int i = 0; i < 5; ++i) {
            if (i != 0) cout << ", ";
            cout << bestDefenders[i];
        }
        cout << ")" << endl;
    }

    return 0;
}
