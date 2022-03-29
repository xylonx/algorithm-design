#include <iostream>
#include <vector>

class ShortestPath {
private:
    struct edge {
        int u, v, w;
        edge(int u, int v, int w) : u(u), v(v), w(w){};
    };
    int vertex_num_;
    std::vector<edge> graph;

public:
    ShortestPath(int vertext_num) : vertex_num_(vertext_num) {}

    void AddEdge(int u, int v, int w) { graph.emplace_back(u, v, w); }

    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<std::vector<int>>>> GetFullSourceShortestPath() {
        std::vector<std::vector<int>> dis(vertex_num_ + 1, std::vector<int>(vertex_num_ + 1, INT_MAX >> 1));
        std::vector<std::vector<std::vector<int>>> path(vertex_num_ + 1,
                                                        std::vector<std::vector<int>>(vertex_num_ + 1));

        for (auto& e : graph) {
            path[e.u][e.v] = {e.u, e.v};
        }

        for (auto& e : graph) dis[e.u][e.v] = e.w;
        for (int k = 1; k <= vertex_num_; ++k) {
            for (int x = 1; x <= vertex_num_; ++x) {
                for (int y = 1; y <= vertex_num_; ++y) {
                    if (dis[x][k] + dis[k][y] < dis[x][y]) {
                        dis[x][y] = dis[x][k] + dis[k][y];
                        std::vector<int> tmp(path[x][k].begin(), path[x][k].end());
                        tmp.insert(tmp.end(), path[k][y].begin() + 1, path[k][y].end());
                        path[x][y] = tmp;
                    }
                }
            }
        }
        return {dis, path};
    }
};

int main(int argc, char** argv) {
    ShortestPath sp(5);

    sp.AddEdge(1, 2, 3);
    sp.AddEdge(1, 3, 8);
    sp.AddEdge(1, 5, -4);
    sp.AddEdge(2, 4, 1);
    sp.AddEdge(2, 5, 7);
    sp.AddEdge(3, 2, 4);
    sp.AddEdge(4, 1, 2);
    sp.AddEdge(4, 3, -5);
    sp.AddEdge(5, 4, 6);
    auto res = sp.GetFullSourceShortestPath();
    std::cout << "shortest path length: " << std::endl;
    for (int u = 1; u <= 5; ++u) {
        for (int v = 1; v <= 5; ++v) {
            if (u != v) {
                std::cout << u << " -> " << v << ": " << res.first[u][v] << "\tpath: ";
                for (auto& i : res.second[u][v]) {
                    std::cout << i << " ";
                }
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
}