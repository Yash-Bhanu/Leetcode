#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> assignEdgeWeights(std::vector<std::vector<int>>& edges, std::vector<std::vector<int>>& queries) {
        int n = edges.size() + 1;
        const int MOD = 1000000007;

        std::vector<int> head(n + 1, -1);
        std::vector<int> to(2 * (n - 1));
        std::vector<int> nxt(2 * (n - 1));
        int edge_cnt = 0;

        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            to[edge_cnt] = v;
            nxt[edge_cnt] = head[u];
            head[u] = edge_cnt++;
            to[edge_cnt] = u;
            nxt[edge_cnt] = head[v];
            head[v] = edge_cnt++;
        }

        std::vector<int> parent(n + 1, 0);
        std::vector<int> depth(n + 1, 0);
        std::vector<int> order(n);
        order[0] = 1;
        int ptr = 1;

        for (int i = 0; i < n; ++i) {
            int u = order[i];
            for (int e = head[u]; e != -1; e = nxt[e]) {
                int v = to[e];
                if (v != parent[u]) {
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    order[ptr++] = v;
                }
            }
        }

        std::vector<int> sz(n + 1, 1);
        sz[0] = 0;
        std::vector<int> heavy(n + 1, 0);

        for (int i = n - 1; i >= 1; --i) {
            int u = order[i];
            int p = parent[u];
            sz[p] += sz[u];
            if (sz[u] > sz[heavy[p]]) {
                heavy[p] = u;
            }
        }

        std::vector<int> top(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            int u = order[i];
            int p = parent[u];
            top[u] = (heavy[p] == u) ? top[p] : u;
        }

        std::vector<int> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        int q = queries.size();
        std::vector<int> ans(q);

        for (int i = 0; i < q; ++i) {
            int u = queries[i][0];
            int v = queries[i][1];
            if (u == v) {
                ans[i] = 0;
                continue;
            }
            int a = u, b = v;
            while (top[a] != top[b]) {
                if (depth[top[a]] < depth[top[b]]) {
                    std::swap(a, b);
                }
                a = parent[top[a]];
            }
            int lca = (depth[a] < depth[b]) ? a : b;
            int dist = depth[u] + depth[v] - 2 * depth[lca];
            ans[i] = pow2[dist - 1];
        }

        return ans;
    }
};