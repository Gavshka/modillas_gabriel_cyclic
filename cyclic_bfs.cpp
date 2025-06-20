#include <iostream>
#include <limits>

using namespace std;

const int MAX = 100;
int graph[MAX][MAX];
int in_degree[MAX];
int queue[MAX];
int front = 0, rear = 0;
int n;

void enqueue(int val) {
    queue[rear++] = val;
}

int dequeue() {
    return queue[front++];
}

bool isEmpty() {
    return front == rear;
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

    cout << "Enter adjacency matrix (only 0 or 1 and numbers separated by space or line):\n";
    for (int i = 0; i < n; ++i) {
        in_degree[i] = 0;
        for (int j = 0; j < n; ++j) {
            int val = safeInput();
            while (val != 0 && val != 1) {
                cout << "Only 0 or 1 allowed. Try again: ";
                val = safeInput();
            }

            graph[i][j] = val;
            if (val)
                in_degree[j]++;
        }
    }

    for (int i = 0; i < n; ++i)
        if (in_degree[i] == 0)
            enqueue(i);

    int count = 0;

    while (!isEmpty()) {
        int curr = dequeue();
        count++;

        for (int i = 0; i < n; ++i) {
            if (graph[curr][i]) {
                in_degree[i]--;
                if (in_degree[i] == 0)
                    enqueue(i);
            }
        }
    }

    if (count != n)
        cout << "Graph is cyclic.\n";
    else
        cout << "Graph is acyclic.\n";

    return 0;
}
