#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

struct Edge {
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

bool compareEdges(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

int getLeader(int x, std::vector<int> &leader) {
    if (x < 0 || x >= leader.size()) return -1;  // check limits

    if (x == leader[x])
        return x;

    return leader[x] = getLeader(leader[x], leader);
}

bool unite(int x, int y, std::vector<int> &leader) {
    srand(time(NULL));
    if (x < 0 || x >= leader.size() || y < 0 || y >= leader.size()) return false;  // check limits

    x = getLeader(x, leader);
    y = getLeader(y, leader);

    if (x == y)
        return false;

    if (rand() % 2 == 0)
        std::swap(x, y);

    leader[x] = y;
    return true;
}

std::vector<Edge> kruskal(std::vector<Edge> &edges,const int &numVertices) {
    std::sort(edges.begin(), edges.end(), compareEdges);

    std::vector<int> leader(numVertices);
    for (int i = 0; i < numVertices; i++)
        leader[i] = i;

    std::vector<Edge> edges;
    for (const auto& edge : edges) {
        int from = edge.from, to = edge.to;

        if (unite(from, to, leader))
            edges.push_back(edge);
    }

    return edges;
}

int getTotalWeight(const std::vector<Edge> &edges) {
    int totalWeight = 0;
    for (const auto &edge : edges) {
        totalWeight += edge.weight;
    }
    return totalWeight;
}

void printEdges(const std::vector<Edge> &edges, const int &totalWeight) {
    for (const auto &edge : edges) {
        std::cout << "Edge: (" << edge.from + 1 << ", " << edge.to + 1 << "), weight: " << edge.weight << std::endl;
    }
    std::cout << "Total weight of the minimum spanning tree: " << totalWeight << std::endl;
}

void getNumVerticesAndEdges(int& numVertices, int& numEdges) {
    std::cout << "Number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Number of edges: ";
    std::cin >> numEdges;
}

int main() {
    int numVertices, numEdges;
    getNumVerticesAndEdges(numVertices, numEdges);

    std::vector<Edge> edges(numEdges);

    for (auto &edge : edges) {
        std::cin >> edge.from >> edge.to >> edge.weight;
        edge.from--;
        edge.to--;
    }
    std::vector<Edge> edges = kruskal(edges, numVertices);

    printEdges(edges, getTotalWeight(edges));

    return 0;
}
