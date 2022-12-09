#include <iostream>
#include <functional>
#include <vector>
// #include <algorithm>
#include <string>
#include <set>

#include "BinaryHeap.h"
using namespace std;

template<class T, class cmp = greater<T>>
class CMP{
private:
    bool answer;
public:
    // template<class cmp>
    CMP(T& a, T& b, cmp mode);
    // template<class cmp>
    // CMP(T& a, T& b, cmp mode);
};

template<class T, class cmp>
CMP<T, cmp>::CMP(T& a, T& b, cmp mode){
    this->answer = mode(a, b);
    cout<<"answer: "<<this->answer<<endl;
}

// template<class T, class cmp>
// CMP<T>::CMP(T& a, T& b, cmp mode){
//     this->answer = mode(a, b);
//     cout<<"answer: "<<endl;
// }

template<class T>
struct compare{
    bool operator()(const T& left, const T& right){
        return left>right;
    }
};

// template<class T>
// struct greater{

// };
template<class T>
void print(T word){
    cout<< word <<endl;
}


#include <algorithm>
namespace HeapTest{
    void test1(){
        cout<<"START HEAPTEST!"<<endl;
        vector<char> word = {'T','P', 'R', 'N','H','O','A','E','I','G'};
        BinaryHeap<char> heap(word);
        heap.print(true);

        cout<<"After pop:"<<endl;
        heap.pop();
        heap.print(true);
        
        cout<<"Origin: ";
        heap.print(false);
        cout<<"After Sorting: ";
        heap.sort();
        heap.print(false);

        // sort(word.begin(), word.end());
        // BinaryHeap<char> bigRoot(word);
        // bigRoot.print(true);
    }

    void heapSortTest(){
        int arr[] = {2, 8, 4, 6, 1, 10, 7, 3, 5, 9};
        int length = 10;
        BinaryHeap<int> heap(arr, length);
        heap.print();

        cout<<"Origin: "<<endl;
        heap.print();
        cout<<"After sorting: "<<endl;
        heap.sort(); heap.print();
    }
};


int main(){
    int a = 3, b = 4;
    CMP<int> c(a, b, greater<int>());

    string word = "Hello";
    print(word);

    vector<int> v;
    // sort(v.begin(), v.end(), std::greater<int>());
    // compare<int> cmp;
    compare<int> cmp;
    cout<<cmp(b,a);

    // HeapTest::heapSortTest();
}