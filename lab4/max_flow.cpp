#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define INF INT_MAX >> 1

class MaxFlow {
private:
    struct edge {
        int u, v, cap, flow;
        edge(int u, int v, int cap, int flow) : u(u), v(v), cap(cap), flow(flow) {}
    };

    int vertex_num_, edge_num_;
    std::vector<edge> edges;

    std::unordered_map<int, std::vector<int>> relatedEdge;

public:
    MaxFlow(int vertex_num) : vertex_num_(vertex_num) {
        relatedEdge.clear();
        edges.clear();
    }

    void Reset() {
        relatedEdge.clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        edge_num_ = edges.size();
        relatedEdge[from].emplace_back(edge_num_ - 2);
        relatedEdge[to].emplace_back(edge_num_ - 1);
    }

    std::pair<int, std::pair<std::unordered_set<int>, std::unordered_set<int>>> Maxflow(int s, int t) {
        int max_flow = 0;

        // x -> BFS 过程中最近接近点 x 的边给它的最大流
        // x -> BFS 过程中最近接近点 x 的边
        std::vector<int> a(vertex_num_ + 1), p(vertex_num_ + 1);

        for (;;) {
            // reset a
            std::fill(a.begin(), a.end(), 0);

            // BFS
            std::queue<int> q;
            q.push(s);
            a[s] = INF;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                // process all edges related to x
                for (int i = 0; i < relatedEdge[x].size(); i++) {
                    edge& e = edges[relatedEdge[x][i]];
                    if (!a[e.v] && e.cap > e.flow) {
                        p[e.v] = relatedEdge[x][i];  // e is the most related Edge with e.v
                        a[e.v] = std::min(a[x], e.cap - e.flow);
                        q.push(e.v);
                    }
                }
                // if touch t, stop bfs
                if (a[t]) break;
            }

            if (!a[t]) break;

            // backtracing path s -> t
            for (int u = t; u != s; u = edges[p[u]].u) {
                // add flow in g
                edges[p[u]].flow += a[t];
                // shrink flow in g'
                edges[p[u] ^ 1].flow -= a[t];
            }
            max_flow += a[t];
        }

        // bfs g'
        std::unordered_set<int> S, T;
        std::queue<int> q;
        std::vector<bool> vis(vertex_num_, false);
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            S.insert(x);

            for (int i = 0; i < relatedEdge.size(); ++i) {
                edge& e = edges[relatedEdge[x][i]];
                if (!vis[e.v] && e.cap != 0 && e.cap > e.flow) {
                    vis[e.v] = true;
                    q.push(e.v);
                }
            }
        }

        for (int i = 0; i < vertex_num_; ++i) {
            if (S.find(i) == S.end()) {
                T.insert(i);
            }
        }

        return {
            max_flow, {S, T}
        };
    }
};

int main(int argc, char** argv) {
    MaxFlow ek(6);
    ek.AddEdge(0, 1, 16);
    ek.AddEdge(0, 2, 13);
    ek.AddEdge(1, 2, 10);
    ek.AddEdge(1, 3, 12);
    ek.AddEdge(2, 1, 4);
    ek.AddEdge(2, 4, 14);
    ek.AddEdge(3, 2, 9);
    ek.AddEdge(3, 5, 20);
    ek.AddEdge(4, 3, 7);
    ek.AddEdge(4, 5, 2);

    auto res = ek.Maxflow(0, 5);
    std::cout << "max flow: " << res.first << std::endl;

    std::cout << "source: 0\ttarget: 5" << std::endl;
    std::cout << "S: ";
    for (auto& u : res.second.first) {
        std::cout << u << " ";
    }
    std::cout << std::endl;

    std::cout << "T: ";
    for (auto& u : res.second.second) {
        std::cout << u << " ";
    }
    std::cout << std::endl;
}