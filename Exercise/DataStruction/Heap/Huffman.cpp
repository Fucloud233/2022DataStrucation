#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "BinaryHeap.h"
using namespace std;

// 用于存储队列的数据
class TreeNode{
public:
    // 频率
    char data;
    int frequency;
    // 数据(如果是父节点 则为空)
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(char data, int frequency, TreeNode* l=NULL, TreeNode*r=NULL){
        this->frequency = frequency;
        this->data = data;
        this->left = l; this->right = r;
    }

    bool operator>(const TreeNode& a){
        return this->frequency>a.frequency;
    }

    bool operator<(const TreeNode& a){
        return this->frequency<a.frequency;
    }
};

class CharData{
public:
    int frequency;
    string code;

    CharData(int frequency = 0, string code = ""){
        this->frequency = frequency;
        this->code = code;
    }
};

// 用于传入比较函数
struct nodeCmp{
    bool operator()(TreeNode* a, TreeNode* b){
        return (*a)<(*b);
    }
};

class HuffmanTree{
private:
    TreeNode* root;
    map<char, CharData> data;

    void makeTree(){
        vector<TreeNode*> array;
        for(auto it=data.begin();it!=data.end();it++){
            // 创建节点队列
            TreeNode* node = new TreeNode(it->first, it->second.frequency);
            array.push_back(node);

        }

        while(array.size()>1)
        {
            // 对数组进行排序
            sort(array.begin(), array.end(), nodeCmp());

            // 取最小的两个 进行合并
            int topFrequency = array[0]->frequency + array[1]->frequency;
            // if(array[0]<array[1])   // 控制左大右小
            //     swap(array[0], array[1]);

            TreeNode* top = new TreeNode(0, topFrequency, array[0], array[1]); 
              
            array.erase(array.begin());
            array.erase(array.begin());
            array.push_back(top);
        }

        root = array[0];
    }

    void makeTreeWithHeap(){
        BinaryHeap<TreeNode*, nodeCmp> heap;
        for(auto it=data.begin();it!=data.end();it++){
            // 创建节点队列
            TreeNode* node = new TreeNode(it->first, it->second.frequency);
            heap.push(node);
        }

        while(heap.size()>1)
        {
            // 取最小的两个 进行合并
            TreeNode* left = heap.top(); heap.pop();
            TreeNode* right = heap.top(); heap.pop();
            int topFrequency = left->frequency + right->frequency;

            TreeNode* top = new TreeNode(0, topFrequency, left, right); 
            heap.push(top);
        }

        root = heap.top();
        heap.pop();
    }

    void makeCode(TreeNode* node, string preCode){
        if(!node)
            return;
        
        // 只需要对当前位置分析即可
        if(node->data){
            data[node->data].code = preCode;
        }
        else{
            makeCode(node->left, preCode+"0");
            makeCode(node->right, preCode+"1");
        }
    }
    
    // 递归删除哈夫曼树
    void deTree(TreeNode* node){
        if(!node){
            return;
        }
        deTree(node->left);
        deTree(node->right);
        delete node;
    }

    void recordFrequency(const string &word){
        for(int i=0;i<word.size();i++){
            auto it = data.find(word[i]);
            if(it!=data.end())
                it->second.frequency++;
            else
                data.insert(pair<char, CharData>(word[i], CharData(1)));
        }
    }

public:
    HuffmanTree(const string& text){
        // 1. 记录字符出现的频率
        this->recordFrequency(text);
        // 2. 建立哈夫曼树
        // this->makeTree();
        this->makeTreeWithHeap();
        // 3. 生成哈夫曼编码
        this->makeCode(root, "");
    }

    ~HuffmanTree(){
        deTree(root);
    }

    void printCode(){
        for(auto it=data.begin();it!=data.end();it++){
            // cout<<"["<<it->first<<"]: "<<it->second<<endl;
            cout<<it->first<<": "<<it->second.code<<endl;
        }
    }

    TreeNode* getTree(){
        return root;
    }

    map<char, string> getCode(){
        map<char, string> code;
        for(auto it=data.begin();it!=data.end();it++)
            code.insert(pair<char, string>(it->first, it->second.code));
        return code;
    }
};


void print(const vector<pair<char, int>> &arr){
    for(auto it=arr.begin();it!=arr.end();it++){
        cout<<"'"<<it->first<<"': "<<it->second<<endl;
    }
    cout<<endl;
}

namespace huffmanTest{
    void test(){
        // string input = "Sun Yat-sen University";
        string input = "aaaaaaaaaaaaaaaaaaaa bbbbbbbbbbbbbbb ccccccc";
        HuffmanTree huffmanTree(input);
        // TreeNode* tree = huffmanTree.getHuffmanTree();
        huffmanTree.printCode();
        
        // print(frequency);
        
    }

    // void test2(){
    //     // test();
    //     string temp;

    //     while (getline(cin, temp)) {
    //         if(temp == "0") {
    //             break;
    //         }
            
    //         HuffmanTree huffmanTree(temp);
    //         // TreeNode* tree = huffmanTree.getHuffmanTree();
    //         huffmanTree.printCode();
    //     }
    // }
};

int main(){
    huffmanTest::test();    
}