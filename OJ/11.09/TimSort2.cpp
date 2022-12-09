#include<iostream>
#include<stack>
using namespace std;

template<class T>
void print(T *arr, int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] <<' ';
    }
    cout<<endl;
}

class Seq{
public:
    int first, last, len;

    Seq(int first=0, int last=0){
        this->first = first;
        this->last = last;
        this->len = last - first + 1;
    }
};

// 将序列变成正序序列
void translate(int *arr, int n){
    int i = 0, first, last;
    bool isFirst = false;
    
    while(i<n){
        // 跳过正序序列
        while(arr[i]<=arr[i+1]&&i+1<n){
            i++;
            isFirst = true;
        }

        // 1. 如果是正序开始 需要跳过
        // 2. 如果从逆序开始 则不要跳过
        if(isFirst)
            ++i;
        
        // 跳过逆序序列
        first = i;
        while(arr[i]>=arr[i+1]&&i+1<n){
            i++;
        }
        last = i;
        

        if(last != first){
            while(last>=first){
                swap(arr[first++], arr[last--]);
            }
            i++;
        }
       
        isFirst = false;
    }
}

// 记录分区
stack<Seq>& record(int *arr, int n){
    int i = 0, first, last;
    bool isFirst = false;
    stack<Seq> *s = new stack<Seq>;

    while(i<n){
        // 跳过正序序列
        first = i;
        while(arr[i]<=arr[i+1]&&i+1<n){
            i++;
            isFirst = true;
        }
        last = i++;
        s->push(Seq(first, last));
    }

    return *s;
}

// 归并 排序
void merge_sort(int *arr, int left, int mid, int right){
    int len = right - left + 1;
    int *temp = new int[len];
    int l = left, r = mid+1, k = 0;

    while(l<=mid&&r<=right){
        if(arr[l]<arr[r]){
            temp[k++] = arr[l++];
        }
        else{
            temp[k++] = arr[r++];
        }
    }

    while(l<=mid){
        temp[k++] = arr[l++];
    }

    while(r<=right){
        temp[k++] = arr[r++];
    }

    for(k=0;k<len;k++){
        arr[left+k] = temp[k];
    }
    delete temp;
}

void mergeSort(stack<Seq> &s, int *arr, int n){
    Seq x[3];
    
    // 对于栈内有三个以上的情况
    while(s.size()>=3){
        for(int i=0;i<3;i++){
            x[i] = s.top();
            s.pop();
        }

        if(x[2].len>=x[0].len+x[1].len||x[1].len>=x[0].len||x[2].len>=x[0].len){
            merge_sort(arr, x[1].first, x[1].last, x[0].last);
            s.push(x[2]);
            s.push(Seq(x[1].first, x[0].last));
        }
        else{
            merge_sort(arr, x[2].first, x[2].last, x[1].last);
            s.push(Seq(x[2].first, x[1].last));
            s.push(x[0]);
        }

        print(arr, n);
    }

    // 对于栈内只有两种的情况
    if(s.size()==2){
        for(int i=0;i<2;i++){
            x[i] = s.top();
            s.pop();
        }

        merge_sort(arr, x[1].first, x[1].last, x[0].last);
    }
    else if(s.size()==1){
        s.pop();
    }

    print(arr, n);
}

int main(){
    int n = 5;
    int* arr;
    stack<Seq> s;

    // 获取数据
    cin>>n;
    arr = new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    // 反转逆序
    translate(arr, n);
    print(arr, n);

    // 然后记录每个分区 进行归并
    s = record(arr, n);
    mergeSort(s, arr, n);

    delete arr;
}