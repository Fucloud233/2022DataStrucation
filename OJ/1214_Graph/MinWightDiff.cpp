#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <limits>
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

int minTreeWeight(int** data, int size, int minDiff){
    // 优先级队列存边
    priority_queue<Edge<int>, vector<Edge<int>>, greater<Edge<int>>> edges;
    // 记录已经存在的点
    set<int> treeNodes;
    // 记录总权重
    // 用于迭代停止
    int edgeNum = size;

    // 用于记录遍历源头
    int origin = 0;
    
    edges.push(Edge<int>(origin, origin, 0));

    int maxDiff = 0;    

    while(edgeNum&&!edges.empty()){
        // 取边
        Edge<int> edge = edges.top();  edges.pop();

        // 判断节点是否存在
        int begin = edge.begin, end = edge.end;
        if(treeNodes.find(end)!=treeNodes.end()){
            continue;
        }

        treeNodes.insert(end);
        if(edge.weight>minDiff){
            return minDiff;
        }
        else if(edge.weight>maxDiff){
            maxDiff = edge.weight;
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

    return maxDiff;
}

int solver(const vector<Edge<int>>& edges, int size){
    if(edges.size()<size-1){
        return -1;
    }
    set<int> nodes;
    set<int> weights;
    for(auto it=edges.begin(); it!=edges.end(); it++){
        nodes.insert(it->begin);
        nodes.insert(it->end);
        weights.insert(it->weight);
    }

    if(nodes.size()!=size){
        return -1;
    }

    int **arr = new int*[size];
    for(int i=0;i<size;i++){
        arr[i] = new int[size];
        for(int j=0;j<size;j++){
            arr[i][j] = INF;
        }
    }

    int minWeight = numeric_limits<int>::max();
    for(auto it=weights.begin();it!=weights.end();it++){
        for(auto jt=edges.begin();jt!=edges.end();jt++){
            int i = jt->begin, j = jt->end;
            int w = abs(jt->weight-*it);
            arr[i][j] = w;
            arr[j][i] = w;
        }

        minWeight = minTreeWeight(arr, size, minWeight);
    }
    
    return minWeight;
}

int main(){
    vector<Edge<int>> edges;
    int m, n;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a, b, w;
        cin>>a>>b>>w;
        edges.push_back(Edge<int>(a-1, b-1, w));
    }

    cout<<solver(edges, n);
}