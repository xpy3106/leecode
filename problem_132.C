/*
 * leecode problem 132: Palindrome Partitioning II
 */
class Solution {
public:
    int minCut(string s) {
        int sLen = s.length();

        vector<vector<int> > dp(sLen, vector<int>(sLen, 0));
        for (int i=0; i<sLen; i++) {
            dp[i][i] = 1;
        }

        vector<int> ret(sLen, 0);
        for (int i=0; i<sLen; i++) {
            ret[i] = i;
        }

        for (int idx=1; idx<sLen; idx++) {
            if (s[idx-1] == s[idx]) {
                dp[idx-1][idx] = 1;
                ret[idx] = idx > 1 ? ret[idx-2] + 1 : 0;
            }

            if (dp[0][idx-1]) {
                int start = 0;
                int end = idx;
                while ((start < end) && (s[start] == s[end])) {
                    start++;
                    end--;
                }
                if (start >= end) {
                    dp[0][idx] = 1;
                    ret[idx] = 0;
                }
            }

            int tmp = ret[idx-1] + 1;
            for (int k=1; k<idx; k++) {
                if (dp[k][idx-1] && s[k-1] == s[idx]) {
                    dp[k-1][idx] = 1;
                    int cut = k > 1 ? ret[k-2] + 1 : 0;
                    if (tmp > cut) {
                        tmp = cut;
                    }
                }
            }

            if (ret[idx] > tmp) {
                ret[idx] = tmp;
            }
        }

        return ret[sLen-1];
    }
};
