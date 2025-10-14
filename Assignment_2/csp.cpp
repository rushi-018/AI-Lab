#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Check if current assignment is valid
bool isValid(string region, string color, map<string, string>& assignment,
             map<string, vector<string>>& adj) {
    for (string neighbor : adj[region]) {
        if (assignment[neighbor] == color) {
            return false; // adjacent region has same color
        }
    }
    return true;
}

// Backtracking CSP Solver
bool backtrack(map<string, string>& assignment,
               vector<string>& regions,
               map<string, vector<string>>& adj,
               vector<string>& colors,
               int index) {
    if (index == regions.size()) return true; // all regions assigned

    string region = regions[index];
    for (string color : colors) {
        if (isValid(region, color, assignment, adj)) {
            assignment[region] = color;
            if (backtrack(assignment, regions, adj, colors, index + 1))
                return true;
            assignment[region] = ""; // backtrack
        }
    }
    return false;
}

int main() {
    int n, m;
    cout << "Enter number of regions: ";
    cin >> n;

    vector<string> regions(n);
    cout << "Enter region names:\n";
    for (int i = 0; i < n; i++) {
        cin >> regions[i];
    }

    // adjacency list
    map<string, vector<string>> adj;
    cout << "Enter adjacency list (neighbors for each region):\n";
    for (int i = 0; i < n; i++) {
        cout << "Enter number of neighbors of " << regions[i] << ": ";
        int k;
        cin >> k;
        cout << "Enter neighbors: ";
        for (int j = 0; j < k; j++) {
            string neigh;
            cin >> neigh;
            adj[regions[i]].push_back(neigh);
        }
    }

    cout << "Enter number of colors: ";
    cin >> m;
    vector<string> colors(m);
    cout << "Enter colors:\n";
    for (int i = 0; i < m; i++) {
        cin >> colors[i];
    }

    map<string, string> assignment;
    for (string r : regions) assignment[r] = "";

    if (backtrack(assignment, regions, adj, colors, 0)) {
        cout << "\nSolution found:\n";
        for (string r : regions) {
            cout << r << " -> " << assignment[r] << endl;
        }
    } else {
        cout << "\nNo solution found.\n";
    }

    return 0;
}
// //
// Enter number of regions: 4
// Enter region names:
// A B C D
// Enter adjacency list (neighbors for each region):
// Enter number of neighbors of A: 2
// Enter neighbors: B C
// Enter number of neighbors of B: 2
// Enter neighbors: A D
// Enter number of neighbors of C: 2
// Enter neighbors: A D
// Enter number of neighbors of D: 2
// Enter neighbors: B C
// Enter number of colors: 3
// Enter colors:
// Red Green Blue
// //