#include <iostream>
#include <vector>
#include <algorithm>

// ��������� ��� ������������� ����
struct Edge {
    int start, end, weight;

    Edge(int s, int e, int w = 0)
    {
        start = s;
        end = e;
        weight = w;
    }
};

// ������� ��� �������������� ��� �� ��������� �������
void sortEdgesByStart(std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.start < b.start;
        });
}

// ������� ��� ������ ������ ����
void printEdges(const std::vector<Edge>& edges) {
    for (const auto& edge : edges) {
        std::cout << "Start: " << edge.start << ", End: " << edge.end;
        if (edge.weight != 0)
            std::cout << ", Weight: " << edge.weight;
        std::cout << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    // ������
    std::vector<Edge> edges = {
        Edge(3, 4, 5),
        Edge(1, 2, 2),
        Edge(2, 4, 3),
        Edge(1, 3, 6),
        Edge(2, 3, 6)
    };

    std::cout << "�� ����������:\n";
    printEdges(edges);

    sortEdgesByStart(edges);

    std::cout << "\n����� ����������:\n";
    printEdges(edges);

    return 0;
}
