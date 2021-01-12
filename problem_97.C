/*
 * leecode problem 97: Interleaving String
 */
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();

    if (len1 + len2 != len3) {
        return false;
    }   

    bool s[len1+1][len2+1];

    for (int i=0; i<len1+1; i++) {
        for (int j=0; j<len2+1; j++) {
            if (i == 0 && j == 0) {
                s[i][j] = true;
            } else if (i == 0) {
                s[i][j] = s[i][j-1] && s2[j-1] == s3[i+j-1];
            } else if (j == 0) {
                s[i][j] = s[i-1][j] && s1[i-1] == s3[i+j-1];
            } else {
                s[i][j] = (s[i-1][j] && s3[i+j-1] == s1[i-1] ) || (s[i][j-1] && s3[i+j-1] == s2[j-1]);
            }   
        }   
    }   

    return s[len1][len2];
    }
};
