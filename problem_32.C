 /*
  * leecode problem 32: Longest Valid Parentheses
  */
 class Solution {
public:
    int longestValidParentheses(string s) {
        int nLen = s.length();
        vector<int> d(nLen, -1);
        stack<int> idxStack;
        stack<int> elemStack;

        for (int i=0; i<nLen; i++) {
            if (elemStack.size() > 0) {
                if (elemStack.top() == '(' && s[i] == ')') {
                    elemStack.pop();
                    int idx = idxStack.top();
                    idxStack.pop();
                    d[i] = idx;

                    if (idx-1 >= 0 && d[idx-1] != -1) {
                        d[i] = d[idx-1];
                    }

                    continue;
                }
            }

            elemStack.push(s[i]);
            idxStack.push(i);
        }

        int max = -1;
        int pos = -1;
        for (int i=0; i<nLen; i++) {
            if (d[i] >=0) {
                if (i-d[i] > max) {
                    max = i-d[i];
                    pos = i;
                }
            }
        }

        return max+1;  
    }
};
