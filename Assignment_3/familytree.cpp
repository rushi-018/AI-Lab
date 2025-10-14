#include <iostream>
#include <map>
#include <vector>
using namespace std;

map<char, vector<char>> parentOf; // child -> parents

// Add parent-child relationship
void addRelation(char parent, char child) {
    parentOf[child].push_back(parent);
}

// Check if X is parent of Y
bool isParent(char x, char y) {
    for (char p : parentOf[y]) {
        if (p == x) return true;
    }
    return false;
}

// Check if X is grandparent of Y
bool isGrandParent(char x, char y) {
    for (char p : parentOf[y]) {
        if (isParent(x, p)) return true;
    }
    return false;
}

// Check if X and Y are siblings
bool isSibling(char x, char y) {
    if (x == y) return false;
    for (char p1 : parentOf[x]) {
        for (char p2 : parentOf[y]) {
            if (p1 == p2) return true;
        }
    }
    return false;
}

// Check if X is uncle/aunt of Y
bool isUncleAunt(char x, char y) {
    for (char p : parentOf[y]) {
        if (isSibling(x, p)) return true;
    }
    return false;
}

int main() {
    int n;
    cout << "Enter number of parent-child relations: ";
    cin >> n;

    cout << "Enter relations in format <parent child> (use letters a,b,c,...):\n";
    for (int i = 0; i < n; i++) {
        char p, c;
        cin >> p >> c;
        addRelation(p, c);
    }

    cout << "\nKnowledge Base created. You can now query relationships.\n";
    cout << "Commands:\n";
    cout << "1 X Y  -> Is X parent of Y?\n";
    cout << "2 X Y  -> Is X grandparent of Y?\n";
    cout << "3 X Y  -> Are X and Y siblings?\n";
    cout << "4 X Y  -> Is X uncle/aunt of Y?\n";
    cout << "0 -> Exit\n";

    while (true) {
        int cmd;
        char x, y;
        cout << "\nEnter query: ";
        cin >> cmd;
        if (cmd == 0) break;
        cin >> x >> y;

        if (cmd == 1) {
            cout << (isParent(x, y) ? "Yes" : "No") << endl;
        } else if (cmd == 2) {
            cout << (isGrandParent(x, y) ? "Yes" : "No") << endl;
        } else if (cmd == 3) {
            cout << (isSibling(x, y) ? "Yes" : "No") << endl;
        } else if (cmd == 4) {
            cout << (isUncleAunt(x, y) ? "Yes" : "No") << endl;
        } else {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}
