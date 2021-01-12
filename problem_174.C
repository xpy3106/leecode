/*
 *  leecode problem 174: Dungeon Game
 */
#include <vector>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& s) {
        int m = s.size();
        int n = s[0].size();
        // init health matrix
        // h[i][j] indicate at health value to go to s[n-1][n-1]
        vector<vector<int> > h(m, vector<int>(n, 0));
        h[m-1][n-1] = 1;
        if (s[m-1][n-1] < 0) {
            h[m-1][n-1] -= s[m-1][n-1];
        }
        for (int i=m-1; i>=0; i--) {
            for (int j=n-1; j>=0; j--) {
                if (i == m-1 && j == n-1) {
                    continue;
                } else {
                    if (i+1 <= m-1) {
                        int dis = h[i+1][j] - s[i][j];
                        if (dis <= 0) {
                            h[i][j] = 1;
                        } else {
                            if (h[i][j] == 0 || h[i][j] > dis) {
                                h[i][j] = dis;
                            }
                        }
                    }

                    if (j+1 <= n-1) {
                        int dis = h[i][j+1] - s[i][j];
                        if (dis <= 0) {
                            h[i][j] = 1;
                        } else {
                            if (h[i][j] == 0 || h[i][j] > dis) {
                                h[i][j] = dis;
                            }
                        }
                    }
                }
            }
        }
        
        return h[0][0];
    }
};
