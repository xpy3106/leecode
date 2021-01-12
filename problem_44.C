/*
 *  leecode problem 44: Wildcard Matching
 */
class Solution {
public:
    bool isMatch(string s, string p) {
            if (p == "*") {
            return true;
        }

        if (p == "" && s == "") {
            return true;
        } else if ((p == "" && s != "") || (p != "" && s == "")) {
            return false;
        }

        int sLen = s.length();
        int pLen = p.length();

        int **d = new int*[pLen];
        for (int i = 0; i < pLen; i++) {
            d[i] = new int[sLen];
        }
        for (int i = 0; i < pLen; i++) {
            for (int j = 0; j < sLen; j++) {
                d[i][j] = -1;
            }
        }

        int i = 0;
        int j = 0;
        int nextj = 0;
        int m = 0;
        bool updFlg = false;
        while (i < pLen && j < sLen) {
            switch (p[i]) {
                case '*':
                    if (j > 0) {
                        d[i][j-1] = i;
                    }

                    m = (j > 0) ? j-1 : 0;
                    for (int k = j; k < sLen; k++) {
                        if (i > 0) {
                            if (d[i-1][m] == i-1) {
                                d[i][k] = i;
                            } else {
                                goto RET;
                            }
                        } else {
                            d[i][k] = i;
                        }
                    }

                    i++;

                    break;
                case '?':
                    nextj = sLen - 1;
                    updFlg = false;

                    for (int k = j; k < sLen; k++) {
                        if (i > 0) {
                            m = (k > 0) ? k-1 : 0;
                            if (d[i-1][m] == i-1) {
                                d[i][k] = i;
                                updFlg = true;
                                if (nextj > k) {
                                    nextj = k;
                                }
                            }
                        } else {
                            d[i][j] = i;                            
                            updFlg = true;                             
                            nextj = j;
                            break;
                        }
                    }

                    if (!updFlg) {
                        goto RET;
                    } else {
                        j = nextj + 1;
                        i++;
                    }

                    break;
                default:
                    nextj = sLen - 1;
                    updFlg = false;

                    for (int k = j; k < sLen; k++) {
                        if (i > 0) {
                            m = (k > 0) ? k-1 : 0;
                            if (d[i-1][m] == i-1 && p[i] == s[k]) {
                                d[i][k] = i;
                                updFlg = true;
                                if (nextj > k) {
                                    nextj = k;
                                }
                            }
                        } else {
                            if (p[i] == s[j]) {
                                d[i][j] = i;
                                updFlg = true;
                                nextj = j;
                                break;
                            }
                        }
                    }

                    if (!updFlg) {
                        goto RET;
                    } else {
                        j = nextj + 1;
                        i++;
                    }

                    break;
            }

            if (j == sLen) {
                bool allStarFlg = true;
                for (int k = i; k < pLen; k++) {
                    if (p[k] != '*') {
                        allStarFlg = false;
                        break;
                    }
                }
                if (allStarFlg) {
                    d[pLen-1][j-1] = pLen-1;
                }
            }

            //cout<<"dump: "<<endl;
            //dump(d, pLen, sLen);
        }
RET:
        bool ret = false;

        // check if d[m-1][n-1] == m-1
        if (d[pLen-1][sLen-1] == pLen-1) {
            ret = true;
        }

        for (int i=0; i<pLen; i++) {
            delete [] d[i];
        }
        delete [] d;

        return ret;
    }
};
