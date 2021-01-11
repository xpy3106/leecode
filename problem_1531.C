//leecode problem 1531. String Compression II
#include <iostream>
#include <string>
#include <set>
#include <ctype.h>
/*
 * Note:
 * 1. lens[n+1][k+1][26][n+1]
 *  For lens[i][j][m][l], it stores minimal compressed string length for
 *  substr from 0 to i, after deleting j chars, ending with l repeated
 *  m+'a' char.
 *  An example, for string 'aabcaaa', lens[6][2][0][5] = 2, which means
 *  after deleting 2 chars 'bc', it ends with 5 repeated 'a', and the minimal
 *  compressed length is 2.
 */

using namespace std;

bool flag = true;

class Solution {
  public:
    int getLengthOfOptimalCompression(string s, int k) {
            int len = s.length();
            if (k >= len) {
                return 0;
            }
            // init lens
            int lens[len][k+1][26][len+1];
            for (int i=0; i<len; i++) {
                for (int j=0; j<k+1; j++) {
                    for (int m=0; m<26; m++) {
                        for (int n=0; n<len+1; n++) {
                            if (i == 0 && j == 0 && m == s[i]-'a' && n == 1) {
                                // lens[0][0][s[0]-'a'][1] = 1
                                lens[i][j][m][n] = 1;
                            } else if (i+1 == j && m == s[i]-'a' && n == 0) {
                                // lens[i][j+1][s[0-'a'][0] = 0
                                lens[i][j][m][n] = 0;
                            } else {
                                lens[i][j][m][n] = -1;
                            }
                        }
                    }
                }
            }

            for (int i=0; i<len-1; i++) {
                int maxj = k > i+1 ? i+2 : k+1;
                for (int j=0; j<maxj; j++) {
                    for (int m=0; m<26; m++) {
                        for (int cnt=0; cnt<len+1; cnt++) {
                            int cur = lens[i][j][m][cnt];
                            if (cur == -1) {
                               continue;
                            }
                            if (cnt == len+1) {
                              continue;
                            }
                            
                            if (cur == 0) {
                               lens[i+1][j][s[i+1]-'a'][1] = 1;
                            } else {
                                // update lens[i+1][j+1]
                                if (j < maxj-1) {// notice, no over array range
                                    if (lens[i+1][j+1][m][cnt] == -1) {
                                        lens[i+1][j+1][m][cnt] = cur;
                                    } else {
                                        if (lens[i+1][j+1][m][cnt] > cur) {
                                            lens[i+1][j+1][m][cnt] = cur;
                                        }
                                    }
                                }
                                // update lens[i+1][j]
                                if (m != s[i+1]-'a') {
                                    if (lens[i+1][j][s[i+1]-'a'][1] == -1) {
                                        lens[i+1][j][s[i+1]-'a'][1] = cur + 1;
                                    } else {
                                        if (lens[i+1][j][s[i+1]-'a'][1] > cur + 1) {
                                            lens[i+1][j][s[i+1]-'a'][1] = cur + 1;
                                        }
                                    }
                                } else {
                                    int add = 0;
                                    // --a --aa: -a =>-a2
                                    // --aaaaaaaaa --aaaaaaaaa: -a9 => -a10
                                    // --aaa...aaa (99 repteaed a) --aaa...aaaa: -a99=> -a100
                                    if (cnt == 1 || cnt == 9 || cnt == 99) {
                                        add++;
                                    }
                                    if (lens[i+1][j][s[i+1]-'a'][cnt+1] == -1) {
                                        lens[i+1][j][s[i+1]-'a'][cnt+1] = cur + add;
                                    } else {
                                        if (lens[i+1][j][s[i+1]-'a'][cnt+1] > cur + add) {
                                            lens[i+1][j][s[i+1]-'a'][cnt+1] = cur + add;
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }

            int ret = len;
            for (int m=0; m<26; m++) {
                for (int cnt=0; cnt<len+1; cnt++) {
                    int tmp = lens[len-1][k][m][cnt];
                    ret = tmp > 0 && ret > tmp ? tmp : ret;
                }
            }
            return ret;
        }
};

int main(int argc, char **argv) {
    Solution s;
    cout<<argv[1]<<" "<<argv[2]<<endl;
    cout<<"string length is: "<<string(argv[1]).length()<<endl;
    string str = argv[1];
    int k = stoi(argv[2]);
    int ret = s.getLengthOfOptimalCompression(str, k);
    cout<<ret<<endl;
    return 0;
}
