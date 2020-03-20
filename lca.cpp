struct Node {
    int finish;
    int weight;
};


class LCA {
 private:
    int quantity, logQuntity;
    int currTime = 0;
    vector<vector<Node>> tree;
    vector<int> depth;
    vector<int64_t> sumWeight;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																								vector<vector<int>> parents;
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																	
    vector<int> timeIn;
    vector<int> timeOut;

 private:
    void treeInput() {
       for (int i = 0; i < tree.size() - 1; ++i) {
            int st, fn, wei;
            cin >> st >> fn >> wei;

            tree[st].push_back({ fn, wei });
            tree[fn].push_back({ st, wei });
        }
    }

    void dfs(int ver = 0, int parent = 0, int64_t way = 0) {
        timeIn[ver] = ++currTime;
        parents[ver][0] = parent;
        sumWeight[ver] = way;
        for (int k = 1; k <= logQuntity; ++k) {
            parents[ver][k] = parents[parents[ver][k - 1]][k - 1];
        }
        for (auto v : tree[ver]) {
            if (v.finish != parent) {
                dfs(v.finish, ver, v.weight + way);
            }
        }
        timeOut[ver] = ++currTime;
    }

 public:
    explicit LCA(int quantity) : quantity(quantity) {
        logQuntity = 1;
        while ((1 << logQuntity) <= quantity) {
            logQuntity++;
        }
        this->tree.resize(quantity);
        this->treeInput();

        this->depth.resize(quantity);
        this->sumWeight.resize(quantity);
        this->parents.resize(quantity, vector<int>(logQuntity + 1));
        this->timeIn.resize(quantity);
        this->timeOut.resize(quantity);

        this->dfs();
    }

    bool isParent(int parent, int child) {
        return timeIn[parent] <= timeIn[child] &&
               timeOut[parent] >= timeOut[child];
    }

    int lca(int u, int v) {
        if (isParent(u, v)) {
            return u;
        }
        if (isParent(v, u)) {
            return v;
        }
        for (int k = logQuntity; k >= 0; --k) {
            if (!isParent(parents[u][k], v)) {
                u = parents[u][k];
            }
        }
        return parents[u][0];
    }

    int64_t lcaQuery(int u, int v) {
        int lca = this->lca(u, v);
        return sumWeight[u] - sumWeight[lca] + sumWeight[v] - sumWeight[lca];
    }
};
