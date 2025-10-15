#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int h;   // heuristic value
    Node* parent;

    Node(vector<vector<int>> s, int hVal, Node* p) {
        state = s; h = hVal; parent = p;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->h > b->h; // min-heap based on heuristic only
    }
};

// Goal position for tiles
pair<int,int> goalPos(int value) {
    if (value == 0) return {2,2};
    value--;
    return {value/3, value%3};
}

// Manhattan Distance
int heuristic(vector<vector<int>>& st) {
    int dist = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (st[i][j] != 0) {
                pair<int,int> gp = goalPos(st[i][j]);
                dist += abs(i - gp.first) + abs(j - gp.second);
            }
        }
    }
    return dist;
}

bool isGoal(vector<vector<int>>& st) {
    vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};
    return st == goal;
}

void printState(vector<vector<int>>& st) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cout << st[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void printPath(Node* node) {
    if (!node) return;
    printPath(node->parent);
    printState(node->state);
}

string encode(vector<vector<int>>& st) {
    string s = "";
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            s += char(st[i][j] + '0');
    return s;
}

void GBFS(vector<vector<int>> start) {
    priority_queue<Node*, vector<Node*>, Compare> open;
    set<string> visited;

    Node* root = new Node(start, heuristic(start), nullptr);
    open.push(root);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!open.empty()) {
        Node* curr = open.top(); open.pop();

        if (isGoal(curr->state)) {
            cout << "Goal found using GBFS!\n";
            printPath(curr);
            return;
        }

        string enc = encode(curr->state);
        if (visited.count(enc)) continue;
        visited.insert(enc);

        int zx, zy;
        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (curr->state[i][j] == 0) {
                    zx = i; zy = j;
                }
            }
        }

        for (int k=0; k<4; k++) {
            int nx = zx + dx[k];
            int ny = zy + dy[k];
            if (nx>=0 && nx<3 && ny>=0 && ny<3) {
                auto newState = curr->state;
                swap(newState[zx][zy], newState[nx][ny]);
                if (!visited.count(encode(newState))) {
                    Node* child = new Node(newState, heuristic(newState), curr);
                    open.push(child);
                }
            }
        }
    }
    cout << "No solution found with GBFS.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter initial 8-puzzle state (use 0 for blank):\n";
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cin >> start[i][j];
        }
    }

    GBFS(start);
    return 0;
}
