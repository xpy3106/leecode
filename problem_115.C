/*
 *  leecode problem 115: Distinct Subsequences
 */
class Solution {
public:
    int numDistinct(string s, string t) {
        int sLen = s.length();
        int tLen = t.length();
        if (sLen < tLen) {
            return 0;
        } else if (sLen == tLen) {
            if (s == t) {
                return 1;
            } else {
                return 0;
            }
        } else {
            vector<uint32_t> v(tLen, 0);
            for(int i = 0; i < sLen; i++){
                int lastDistinct = 1;
                for(int j = 0; j < tLen; j++){
                    int temp = v[j];
                    if(s[i] == t[j]){
                        v[j] += lastDistinct;
                    }
                    lastDistinct = temp;
                }
            }
            return v[tLen-1];
        }
    }
};
