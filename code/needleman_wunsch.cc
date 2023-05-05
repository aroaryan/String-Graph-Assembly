#include "needleman_wunsch.h"
#include <vector>
#include <algorithm>
using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

float needlemanWunschCost(const string& s1, const string& s2, float match_reward, float mismatch_cost) {
    vector<char> s1_vec(s1.begin(), s1.end());
    vector<char> s2_vec(s2.begin(), s2.end());
    int n = s1_vec.size();
    int m = s2_vec.size();
    vector<vector<int>> subMatches;
    subMatches.resize(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) {
        subMatches[i][0] = i * -mismatch_cost;
    }
    for (int j = 0; j <= m; j++) {
        subMatches[0][j] = j * -mismatch_cost;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            subMatches[i][j] = max(subMatches[i - 1][j] - mismatch_cost, subMatches[i][j - 1] - mismatch_cost);
            if (s1_vec[i - 1] == s2_vec[j - 1]) {
                subMatches[i][j] = max(subMatches[i][j], subMatches[i - 1][j - 1] + match_reward);
            }
        }
    }
    return subMatches[n][m];
}