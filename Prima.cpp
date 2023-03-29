#include <climits>
#include <iostream>

const int MAX_VERTICES = 10;
const int MIN_VERTICES = 1;

int graph[MAX_VERTICES][MAX_VERTICES];

int getNumberOfVetices() {
    int numVertices;
    std::cout << "Enter the number of vertices (1-" << MAX_VERTICES << "): ";
    std::cin >> numVertices;
    return numVertices;
}
bool isValidNumberOfVertices(const int &numVertices) {
    return numVertices > MIN_VERTICES && numVertices < MAX_VERTICES;
}
void inputMatrix(int &numVertices) {
    numVertices = getNumberOfVetices();

    if (!isValidNumberOfVertices(numVertices)) {
        std::cerr << "Error: Invalid number of vertices." << std::endl;
        exit(1);
    }
    std::cout << "Enter the adjacency matrix (" << numVertices << "x" << numVertices << "):" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            std::cin >> graph[i][j];
            if (graph[i][j] < 0) {
                std::cerr << "Error: Invalid edge weight." << std::endl;
                exit(1);
            }
        }
    }
}
int findMinDistanceVertex(int *minDistance, bool *visited, const int &numVertices) {
    int minIndex;
    int min = INT_MAX;

    for (size_t v {0}; v < numVertices; v++) {
        if (!visited[v] && minDistance[v] < min) {
            min = minDistance[v], minIndex = v;
        }
    }

    return minIndex;
}

void printResult(const int *parent, const int &numVertices) {
    std::cout << "Minimum spanning tree:" << std::endl;
    int minCost{};
    for (size_t i {1}; i < numVertices; i++) {
        std::cout << "(" << parent[i] << ", " << i << ", " << graph[i][parent[i]] << ")" << std::endl;
        minCost += graph[i][parent[i]];
    }
    std::cout << "Min cost = " << minCost << '\n';
}

void prim(const int &numVertices) {
    int parent[numVertices];
    int minDistance[numVertices];
    bool visited[numVertices];

    for (size_t i{0}; i < numVertices; i++) {
        minDistance[i] = INT_MAX;
    }

    minDistance[0] = 0; // root of the tree
    parent[0] = -1;

    for (size_t i {0}; i < numVertices - 1; i++) {
        int u = findMinDistanceVertex(minDistance, visited, numVertices);
        visited[u] = true;
            for (size_t v = 0; v < numVertices; v++) {
                if (graph[u][v] && !visited[v] && graph[u][v] < minDistance[v]) {
                    parent[v] = u, minDistance[v] = graph[u][v];
                }
            }
    }

    printResult(parent, numVertices);
}

int main() {
    int numVertices;
    inputMatrix(numVertices);
    prim(numVertices);

    return 0;
}

