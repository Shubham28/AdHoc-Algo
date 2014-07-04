class Solution {
public:

    bool isPalindrome(string s) {
        int L=s.size();
        int fr=0,to=L-1;
        while(fr<L && to>=0){
            while(!isalnum(s[fr]) && fr<L)      fr++;
            while(!isalnum(s[to]) && to>=0)     to--;

            if(tolower(s[fr])!=tolower(s[to]) && fr<L && to>=0)
                return 0;

            fr++,to--;
        }
        return 1;
    }
};
