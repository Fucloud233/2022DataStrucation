#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

template<class T>
struct Edge{
    T begin, end;
    int weight;
    
    Edge(const T& begin, const T& end, const int& weight=1){
        this->begin = begin;
        this->end = end;
        this->weight = weight;
    }
};

// compare function
template<class T>
bool operator<(const Edge<T>& edge1, const Edge<T>& edge2){
    return edge1.weight < edge2.weight;
}

template<class T>
bool operator>(const Edge<T>& edge1, const Edge<T>& edge2){
    return edge1.weight > edge2.weight;
}

#define INF numeric_limits<int>::max()

int minTreeWeight(int** data, int size, int start, int minDiff){
    // 优先级队列存边
    priority_queue<Edge<int>, vector<Edge<int>>, greater<Edge<int>>> edges;
    // 记录已经存在的点
    set<int> treeNodes;
    // 用于迭代停止
    int edgeNum = size;

    // 用于第一次搜索
    edges.push(Edge<int>(0, 0, 0));

    int diff = numeric_limits<int>::min();
    while(edgeNum&&!edges.empty()){
        // 取边
        Edge<int> edge = edges.top();  edges.pop();

        // 判断节点是否存在
        int begin = edge.begin, end = edge.end;
        if(treeNodes.find(end)!=treeNodes.end()){
            continue;
        }
        treeNodes.insert(end);
        if(edge.weight>=minDiff){
            return minDiff;
        }
        else if(edge.weight>diff){
            diff = edge.weight;
        }

        // insert surrounded node of end node
        for(int i=0;i<size;i++){
            int adjency = i;
            int weight = data[end][i];

            if(weight!=INF&&treeNodes.find(adjency)==treeNodes.end()){
                edges.push(Edge<int>(end, adjency, weight));
            }
        }

        edgeNum--;
    }

    if(edgeNum)
        return -1;

    return diff;
}

int solver(vector<Edge<int>> edges, int size){
    sort(edges.begin(), edges.end());

    // 初始化邻接矩阵
    int **arr = new int*[size];
    for(int i=0;i<size;i++){
        arr[i] = new int[size];
        for(int j=0;j<size;j++){
            arr[i][j] = INF;
        }
    }

    // 这还是遍历权的方法
    int minWeight = numeric_limits<int>::max();
    for(auto it=edges.begin();it!=edges.end();it++){
        for(auto jt=it;jt!=edges.end();jt++){
            int begin = jt->begin, end = jt->end;
            int weight = jt->weight - it->weight;

            arr[begin][end] = weight;
            arr[end][begin] = weight;           
        }

        // 更新迭代
        int temp = minTreeWeight(arr, size, it->begin, minWeight);
       
        if(temp!=-1){
            minWeight = min(temp, minWeight);
            cout<<temp<<endl;
        }

        arr[it->begin][it->end] = INF;
        arr[it->end][it->begin] = INF;
    }
    
    return minWeight;
}

#include <fstream>
#include <string>

int main(){
    // open file
    int num = 0;
    fstream file;
    string fileDir = "./5/";
    string dataFile = fileDir + to_string(num) + ".txt";
    string resultFile = fileDir + "ans_" + to_string(num) + ".txt";
    file.open(dataFile);
    cout<<"Example "<<num<<endl;

    // calculate the result
    vector<Edge<int>> edges;
    int m, n;
    file>>n>>m;
    for(int i=0;i<m;i++){
        int a, b, w;
        file>>a>>b>>w;
        edges.push_back(Edge<int>(a-1, b-1, w));
    }
    cout<<"Result: "<<solver(edges, n)<<endl;
    file.close();

    // 打印正确答案
    file.open(resultFile);
    int result;
    file>>result;
    cout<<"Answer: "<<result;
    file.close();
}