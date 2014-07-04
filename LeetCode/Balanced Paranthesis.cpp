class Solution {
public:
    vector<string>ans;
    int L,limt;
    string sol;
    void generSet(int pos,int open) {
        if(pos==L){
            ans.push_back(sol);
            return;
        }

        if(open<limt){
            sol[pos]='(';
            generSet(pos+1,open+1);
        }

        int close=pos-open;
        if(close<open){
            sol[pos]=')';
            generSet(pos+1,open);
        }
    }

    vector<string> generateParenthesis(int n) {
        L=n*2,limt=n;
        ans.clear();

        sol.assign(L,' ');
        generSet(0,0);
        return ans;
    }
};
