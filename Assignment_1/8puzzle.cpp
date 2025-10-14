#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

string goal = "123456780";

// Directions: up, down, left, right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Row and column from index
int row(int idx) { return idx / 3; }
int col(int idx) { return idx % 3; }

string swapPos(const string &s, int i, int j)
{
    string newS = s;
    char temp = newS[i];
    newS[i] = newS[j];
    newS[j] = temp;
    return newS;
}

vector<string> getNeighbours(string s)
{
    vector<string> result;
    int z = s.find('0');
    int x = row(z);
    int y = col(z);

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3)
        {
            int newIndex = nx * 3 + ny;
            result.push_back(swapPos(s, z, newIndex));
        }
    }
    return result;
}

void bfs(string start)
{
    set<string> visited;
    queue<pair<string, int>> q;
    q.push(make_pair(start, 0));
    visited.insert(start);

    while (!q.empty())
    {
        pair<string, int> p = q.front();
        q.pop();
        string curr = p.first;
        int depth = p.second;

        if (curr == goal)
        {
            cout << "Goal reached in " << depth << " moves using BFS.\n";
            return;
        }

        vector<string> neighbors = getNeighbours(curr);
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (visited.find(neighbors[i]) == visited.end())
            {
                visited.insert(neighbors[i]);
                q.push(make_pair(neighbors[i], depth + 1));
            }
        }
    }
    cout << "Goal not reachable using BFS.\n";
}

void dfs(string start)
{
    set<string> visited;
    stack<pair<string, int>> st;
    st.push(make_pair(start, 0));
    visited.insert(start);

    while (!st.empty())
    {
        pair<string, int> p = st.top();
        st.pop();
        string curr = p.first;
        int depth = p.second;

        if (curr == goal)
        {
            cout << "Goal reached in " << depth << " moves using DFS.\n";
            return;
        }

        vector<string> neighbors = getNeighbours(curr);
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (visited.find(neighbors[i]) == visited.end())
            {
                visited.insert(neighbors[i]);
                st.push(make_pair(neighbors[i], depth + 1));
            }
        }
    }
    cout << "Goal not reachable using DFS.\n";
}

int main()
{
    string start = "";
    cout << "Enter 3x3 puzzle (use 0 for blank):\n";
    for (int i = 0; i < 9; i++)
    {
        int x;
        cin >> x;
        start += (x + '0');
    }

    bfs(start);
    dfs(start);

    return 0;
}
// The code implements BFS and DFS for solving the 8-puzzle problem.