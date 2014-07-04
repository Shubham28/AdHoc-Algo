class Solution {
public:
    string addBinary(string a, string b) {
        if(a.size()>b.size())
            swap(a,b);

        string s1=reverse(a.begin(),a.end());
        string s2=reverse(b.begin(),b.end());

        int l1=s1.size(),l2=s2.size();

        string res="";
        int carry=0;
        
        for(int i=0;i<l2;i++){
            int d1,d2=s2[i]-'0';

            d1=(l1>=i)?0:(s1[i]-'0');

            int sum=d1+d2+carry;
            char c=(sum%2)+'0';
            carry=sum/2;
        
            res+=c;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};