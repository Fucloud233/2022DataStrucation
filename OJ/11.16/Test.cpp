#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int main(){
    unordered_map<int, int> hash;
    int n, a, b;
    cin>>n;
    int depth = 1;
    while(cin>>a>>b){
        hash.insert({a,b});
        if(hash[a]!=b){
            depth++;
        }
    }
    cout<<depth;

    // unsigned int a = 1, deep = 1;
    // a = a<<(deep-1) - 1;
    // cout<<a;
}