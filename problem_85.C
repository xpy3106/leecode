/*
 *  leecode problem 85: Maximal Rectangle
 */
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int max = 0;
        for (int i=0; i<n; i++) {
            vector<char> ret = matrix[i];
            int tmp = findMax(ret, 1);
            max = (max < tmp) ? tmp : max;
            for (int j=i+1; j<n; j++) {
                andOp(ret, matrix[j]);
                tmp = findMax(ret, j-i+1);
                if (tmp == 0) {
                    break;
                } else {
                    max = (max < tmp) ? tmp : max;
                }
            }
        }

        return max;
    }

    int findMax(vector<char> &v, int n) {
        int *p = new int[v.size()];
        int max = -1;
        for (int i=0; i<v.size(); i++) {
            if (v[i] == '0') {
                p[i] = -1;
            } else {
                if (i > 0 && p[i-1] >= 0) {
                    p[i] = p[i-1];
                } else {
                    p[i] = i;
                }
            }

            if (p[i] >= 0 && max < (i-p[i]+1)) {
                max = i-p[i]+1;
            }
        }

        delete [] p;

        return ((max <= 0) ? 0 : max) * n;
    }

    void andOp(vector<char> &ret, vector<char> v) {
        for (int i=0; i<ret.size(); i++) {
            if (ret[i] == '1' && v[i] == '1') {
                ret[i] = '1';
            } else {
                ret[i] = '0';
            }
        }
    }
};
