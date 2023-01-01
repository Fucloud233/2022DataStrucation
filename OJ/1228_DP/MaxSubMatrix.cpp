#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int maxSubSequence(const vector<int>& array){
    // 如果空数组 直接返回0
    if(!array.size()){
        return 0;
    }

    vector<int> maxSub(array.size());
    maxSub[0] = array[0];
    // int max = numeric_limits<int>::min();
    int maxNum = array[0];
    
    for(int i=1;i<array.size();i++){
        maxSub[i] = maxSub[i-1] > 0 ? maxSub[i-1] + array[i] : array[i];
        if(maxSub[i] > maxNum){
            maxNum = maxSub[i];
        }
    }

    return maxNum;
}

int maxSubMatrix(const vector<vector<int>>& matrix){
    vector<vector<int>> total = matrix;

    // 方便得到上下之和
    for(int i=1;i<matrix[0].size();i++){
        for(int j=0;j<matrix.size();j++){
            total[i][j] += total[i-1][j];
        }
    }

    int maxNum = numeric_limits<int>::min();

    // 起始列和终止列
    for(int i=0;i<matrix.size();i++){
        for(int j=i;j<matrix.size();j++){
            // 对二维矩阵进行降维
            vector<int> result(matrix[0].size(), 0);
            
            for(int k=0;k<matrix[0].size();k++){
                if(i==0){
                    result[k] = total[j][k];
                }
                else{
                    // 第i-j列的和
                    result[k] = total[j][k] - total[i-1][k];
                }
            }
            
            int maximal = maxSubSequence(result);
            
            if(maximal>maxNum){
                maxNum = maximal;
            }
        }
    }

    return maxNum;
}

int main(){
    int n;
    
    cin>> n;
    vector<vector<int>> matrix;

    for(int i=0;i<n;i++){
        matrix.push_back(vector<int>(n, 0));
        for(int j=0;j<n;j++){
            cin>>matrix[i][j];
        }
    }

    cout<<maxSubMatrix(matrix);

    // vector<int> testArr;
    // testArr.push_back(5);
    // cout<<maxSubSequence(testArr);

    // vector<vector<int>> testMatrix;
    // testMatrix.push_back(vector<int>(1, 0));
    // testMatrix[0][0] = 5;
    // cout<<maxSubMatrix(testMatrix);

}