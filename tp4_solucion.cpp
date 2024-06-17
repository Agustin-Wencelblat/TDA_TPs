#include <iostream>
#include <string>
using namespace std;

bool areEquivalent(const string& a, const string& b, int a_start, int b_start, int length) {
    if (a.compare(a_start, length, b, b_start, length) == 0) {
        return true;
    }
    if (length % 2) {
        return false;
    }
    int mid = length / 2;
    return ((areEquivalent(a, b, a_start, b_start + mid, mid) && areEquivalent(a, b, a_start + mid, b_start, mid)) ||
            (areEquivalent(a, b, a_start, b_start, mid) && areEquivalent(a, b, a_start + mid, b_start + mid, mid)));
}

bool areEquivalent(const string& a, const string& b) {
    return areEquivalent(a, b, 0, 0, a.length());
}

int main() {
    string a, b;
    cin >> a >> b;
    printf("%s\n", areEquivalent(a, b) ? "YES" : "NO");
    return 0;
}
