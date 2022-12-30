#include <iostream>
#include <vector>
using namespace std;

vector<long> data;

void initial(){
    data.push_back(0);
    data.push_back(1);
}

long sovler(int num){
    if(data.size()-1<num){
        for(long i=data.size();i<=num;i++){
            data.push_back(data[i-1]+data[i-2]);
        }
    }

    return data[num];
    // long a = 0, b = 1, temp;
    // if(num==0){
    //     return a;
    // }
    // else if(num==1){
    //     return b;
    // }
    
    // for(int i=2;i<=num;i++){
    //     temp = a + b;
    //     a = b;
    //     b = temp;
    // }

    // return b;
}

int main(){
    initial();
    
    int num;
    while(cin>>num){
        cout<<sovler(num)<<endl;
    }
}