#include <iostream>
#include <limits>

using namespace std;

const int MAX = 100;

int graph[MAX][MAX];
bool visited[MAX];
bool recStack[MAX];
int parent[MAX];
int n;

bool dfs(int node, int& cycleStart, int& cycleEnd) {
    visited[node] = true;
    recStack[node] = true;

    for (int i = 0; i < n; ++i) {
        if (graph[node][i]) {
            if (!visited[i]) {
                parent[i] = node;
                if (dfs(i, cycleStart, cycleEnd))
                    return true;
            } else if (recStack[i]) {
                cycleStart = i;
                cycleEnd = node;
                return true;
            }
        }
    }

    recStack[node] = false;
    return false;
}

void printCycle(int start, int end) {
    int cycle[MAX];
    int idx = 0;

    cycle[idx++] = start;
    for (int v = end; v != start; v = parent[v])
        cycle[idx++] = v;
    cycle[idx++] = start;

    cout << "Cycle found: ";
    for (int i = idx - 1; i >= 0; --i)
        cout << cycle[i] << (i != 0 ? " -> " : "\n");
}

int safeInput() {
    int val;
    while (!(cin >> val)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Enter 0 or 1: ";
    }
    return val;
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;

    while (cin.fail() || n <= 0 || n > MAX) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid size. Enter a number between 1 and " << MAX << ": ";
        cin >> n;
    }

    cout << "Enter adjacency matrix (only 0 or 1 and numbers separated ):\n";
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
        recStack[i] = false;
        parent[i] = -1;

        for (int j = 0; j < n; ++j) {
            int val = safeInput();
            while (val != 0 && val != 1) {
                cout << "Only 0 or 1 allowed. Try again: ";
                val = safeInput();
            }
            graph[i][j] = val;
        }
    }

    int cycleStart = -1, cycleEnd = -1;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (dfs(i, cycleStart, cycleEnd)) {
                cout << "Graph is cyclic.\n";
                printCycle(cycleStart, cycleEnd);
                return 0;
            }
        }
    }

    cout << "Graph is acyclic.\n";
    return 0;
}
