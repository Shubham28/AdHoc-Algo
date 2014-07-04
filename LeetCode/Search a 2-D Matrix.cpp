class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int R=matrix.size(),C=matrix[0].size();

        int i=0,j=C-1;
        while(0<=i && i<R && 0<=j && j<C){
            if(matrix[i][j]==target)
                return 1;

            if(matrix[i][j]<target)     i++;
            else        j--;
        }
        return 0;
    }
};