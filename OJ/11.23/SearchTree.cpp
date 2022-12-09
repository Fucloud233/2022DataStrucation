#include<iostream>
#include<vector>
#include<queue>
using namespace std;

bool checkSearchTree(vector<int>& a, vector<int>& b){
    // 首先判断是否为空
    if(a.empty()&&b.empty()){
        return true;
    }

    // 然后判断首元素是否相同
    if(a[0]!=b[0]||a.size()!=b.size())
        return false;

    // 进行分类
    vector<int> aLeft, bLeft, aRight, bRight;
    for(int i=1;i<a.size();i++){
        if(a[i]<a[0]){
            aLeft.push_back(a[i]);
        }
        else{
            aRight.push_back(a[i]);
        }

        if(b[i]<b[0]){
            bLeft.push_back(b[i]);
        }
        else{
            bRight.push_back(b[i]);
        }
    }

    return checkSearchTree(aLeft, bLeft)*checkSearchTree(aRight, bRight);
}

void test(){
    vector<int> a({4, 5, 0, 2, 1});
    vector<int> b({1, 2, 0, 4, 5});
    vector<int> c({4, 5, 0, 2, 1});

    cout<<checkSearchTree(a, b)<<' ';
    cout<<checkSearchTree(a, c);
}

int main(){
    // test();
    vector<vector<int>> data;
    int n;
    while(true){
        cin>>n;
        if(!n){
            break;
        }

        // 获取数据
        for(int i=0;i<n+1;i++){
            char temp[10];
            cin>>temp;
            vector<int> single;
            int j =0;
            while(temp[j]){
                single.push_back(temp[j++]-'0');
            }
            data.push_back(single);
        }

        // 处理数据
        for(int i=0;i<n;i++){
            bool result = checkSearchTree(data[0], data[i+1]);
            if(result){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }

        }

        data.clear();
    }

    return 0;
}