/*
 *  leecode problem 10: Regular Expression Matching
 */
class Solution {
public:
    bool isMatch(string s, string p) {
        //cout<<"s="<<s<<" "<<"p="<<p<<endl;
        string subp;
        string sepstr;
        int sep = -1;
        int i = 0;
        int pLen = p.length();
        for (; i<pLen-1; i++) {
            if (p[i+1] != '*') {
                subp += p[i];
            } else {
                sep = i;
                sepstr += p[i];
                sepstr += '*';
                break;
            }
        }

        if (sep < 0 && pLen > 0) {
            subp += p[i];
        }

        //cout<<"sepstr="<<sepstr<<" ";
        //cout<<"subp="<<subp<<" "<<endl;;
        int pos = find(s, subp);
        //cout<<"pos="<<pos<<endl;

        if (pos < 0) {
            return false;
        } else if (pos >= s.length()) {
            if ((sep < 0) || (sep >=0 && i+1 == pLen-1)) {
                return true;
            }
        }

        if (sep >= 0) {
            string newp = p.substr(i+2);

            if (sepstr == ".*") {
                for (int j=pos; j<=s.length(); j++) {
                    if (isMatch(s.substr(j), newp)) {
                        return true;
                    }
                }
            } else {
                int k = pos;
                while (k < s.length() && s[k] == sepstr[0]) k++;
                for (int j=pos; j<k+1; j++) {
                    if (isMatch(s.substr(j), newp)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    int find(string s, string p) {
        if (p.length() == 0) {
            return 0;
        }

        int ret = -1;
        int i = 0;
        int j = 0;
        while (i<s.length() && j<p.length()) {
            if (p[j] == '.' || p[j] == s[i]) {
                i++;
                j++;
            } else {
                break;
            }
        }

        if (j >= p.length()) {
            ret = i;
        }

        return ret;
    }
};
