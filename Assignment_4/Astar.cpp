#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

struct Node {
    vector<vector<int>> state;
    int g, h;
    Node* parent;

    int f() const { return g + h; }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f() > b->f(); // min-heap
    }
};

pair<int,int> findPos(int value) {
    if (value == 0) return make_pair(2,2);
    value--;
    return make_pair(value/3, value%3);
}

// Manhattan Distance Heuristic
int heuristic(vector<vector<int>>& st) {
    int dist = 0;
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            if (st[i][j] != 0) {
                pair<int,int> goalPos = findPos(st[i][j]);
                int gx = goalPos.first;
                int gy = goalPos.second;
                dist += abs(i - gx) + abs(j - gy);
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
    if (node == nullptr) return;
    printPath(node->parent);
    printState(node->state);
}

void AStar(vector<vector<int>> start) {
    priority_queue<Node*, vector<Node*>, Compare> open;
    map<vector<vector<int>>, int> visited;

    Node* s = new Node{start, 0, heuristic(start), nullptr};
    open.push(s);

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!open.empty()) {
        Node* curr = open.top(); open.pop();

        if (isGoal(curr->state)) {
            cout << "Solution found with cost = " << curr->g << "\n";
            printPath(curr);
            return;
        }

        if (visited[curr->state] && visited[curr->state] <= curr->g) continue;
        visited[curr->state] = curr->g;

        int zx, zy;
        for (int i=0; i<3; i++) for (int j=0; j<3; j++)
            if (curr->state[i][j] == 0) { zx = i; zy = j; }

        for (int i=0; i<4; i++) {
            int nx = zx + dx[i];
            int ny = zy + dy[i];
            if (nx>=0 && nx<3 && ny>=0 && ny<3) {
                auto newState = curr->state;
                swap(newState[zx][zy], newState[nx][ny]);
                Node* child = new Node{newState, curr->g+1, heuristic(newState), curr};
                open.push(child);
            }
        }
    }
    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> start(3, vector<int>(3));
    cout << "Enter initial 8-puzzle state (use 0 for blank):\n";
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            cin >> start[i][j];
        }
    }

    AStar(start);
    return 0;
}
