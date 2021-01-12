/*
 *  leecode problem 87: Scramble String
 */
class Solution {
public:
    bool isScramble(string s1, string s2) {
    if (s1.length() != s2.length()) {
                return false;
            }
            if (s1 == s2) {
                return true;
            }

            int n = s1.length();

            vector<vector<vector<bool> > > v(n, vector<vector<bool> >(n, vector<bool>(n+1, false)));
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                v[i][j][1] = s1[i] == s2[j];
                }
            }
            
            for (int k=2; k<=n; k++) {
                for (int i=0; i<=n-k; i++) {
                    for (int j=0; j<=n-k; j++) {
                        for (int m=1; m<k; m++) {
                            if ((v[i][j][m] && v[i+m][j+m][k-m]) ||
                                (v[i+m][j][k-m] && v[i][j+k-m][m])) {
                                v[i][j][k] = true;
                            }
                        }
                    }
                }
            }

            return v[0][0][n];
  
    
    }
};
