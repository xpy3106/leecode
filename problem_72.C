// leecode problem 72: Edit Distance
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word2.length();
        int n = word1.length();

        if (m == 0 || n == 0) {
            return m + n;
        }

        if (m > n) {
            string stmp;
            stmp = word1;
            word1 = word2;
            word2 = stmp;
            int tmp;
            tmp = m;
            m = n;
            n = tmp;
        }

        int **p = new int*[m];
        for (int i=0; i<m; i++) {
            p[i] = new int[n];
        }
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                p[i][j] = 0;
            }
        }

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (i == 0 && j == 0) {
                    p[i][j] = (word2[i] == word1[j]) ? 0 : 1;
                } else if (i == 0) {
                    if (word2[i] == word1[j]) {
                        p[i][j] = j;
                    } else {
                        p[i][j] = p[i][j-1] + 1;
                    }
                } else if (j == 0) {
                    if (word2[i] == word1[j]) {
                        p[i][j] = i;
                    } else {
                        p[i][j] = p[i-1][j] + 1;
                    }
                } else {
                    if (word2[i] == word1[j]) {
                        p[i][j] = p[i-1][j-1];
                    } else {
                        int max = i;
                        if (i < j) {
                            max = j;
                        }
                        max += 1;
                        int tmp = p[i-1][j] + 1;
                        if (tmp > max) {
                            tmp = max;
                        }
                        p[i][j] = tmp;
                        tmp = p[i][j-1] + 1;
                        if (tmp > max) {
                            tmp = max;
                        }
                        if (p[i][j] > tmp) {
                            p[i][j]= tmp;
                        }
                        tmp = p[i-1][j-1] + 1;
                        if (p[i][j] > tmp) {
                            p[i][j]= tmp;
                        }
                    }
                }
            }
        }

        //dump(p, m, n);

        int ret = p[m-1][n-1];
        for (int i=0; i<m; i++) {
            delete [] p[i];
        }
        delete [] p;

        return ret;
    }
};
