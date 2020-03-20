class SparseTable {
 private:
     vector<vector<int64_t>> sparse;
     const vector<int64_t> input;
     int n = 0;
     int m = 0;
 public:
     explicit SparseTable(const vector<int64_t>& input): input(input) {
         n = input.size();
         m = 1;
         while ((1 << m) <= n) {
             m++;
         }
         sparse.resize(n, vector<int64_t>(m+1, -1));
         this->build();
     }

     void build();
     int64_t query(int left, int right);
};

void SparseTable::build() {
    for (int i = 0; i < n; ++i) {
        sparse[i][0] = input[i];
    }
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; (i + (1 << j) - 1) < n; ++i) {
            if (sparse[i][j - 1] <
                sparse[i + (1 << (j - 1))][j - 1]) {
                sparse[i][j] = sparse[i][j - 1];
            } else {
                sparse[i][j] =
                    sparse[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int64_t SparseTable::query(int left, int right) {
    int j = log2(right - left + 1);

    if (sparse[left][j] <= sparse[right - (1 << j) + 1][j]) {
        return sparse[left][j];
    } else {
        return sparse[right - (1 << j) + 1][j];
    }
}
