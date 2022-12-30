#include <iostream>
using namespace std;

void func(int m, int n, int& sum){
    if(n==0&&m==0){
        sum++;
        return;
    }
    if(m>0){
        func(m-1, n, sum);
    }
    if(n>0){
        func(m, n-1, sum);
    }
}

int main(){
    int sum = 0;
    func(8-1,  4-1, sum);
    cout<<sum;
}