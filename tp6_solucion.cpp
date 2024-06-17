#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<int> a, b;
    for(int i = 0; i < n; i++) {
        if(s[i] != t[i]) {
            if(s[i] == 'a') {
                a.push_back(i+1);
            } else {
                b.push_back(i+1);
            }
        }
    }
    if((a.size() + b.size()) % 2 == 1) {
        cout << -1 << endl;
        return 0;
    }
    vector<pair<int, int>> ans;
    while(a.size() > 1) {
        int x = a.back();
        a.pop_back();
        int y = a.back();
        a.pop_back();
        ans.push_back({x, y});
    }
    while(b.size() > 1) {
        int x = b.back();
        b.pop_back();
        int y = b.back();
        b.pop_back();
        ans.push_back({x, y});
    }
    if(!a.empty() && !b.empty()) {
        ans.push_back({a.back(), a.back()});
        ans.push_back({a.back(), b.back()});
    }
    cout << ans.size() << endl;
    for(auto p : ans) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
