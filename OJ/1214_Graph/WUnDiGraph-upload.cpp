#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

template<class T>
class SeqUnion{
protected:
    map<T, T> data;
public:
    SeqUnion();
    SeqUnion(const int* arr, int lenght);
    
    void Union(T p, T q);
    bool connected(T p, T q) const;
    T find(T p) const;
    void insert(const T elem, const T leader);
    void insert(const T* arr, int lenght, const T leader);
    void erase(T elem);
    void print() const;
};

template<class T>
SeqUnion<T>::SeqUnion(){

}

template<class T>
SeqUnion<T>::SeqUnion(const int* arr, int length){
    for(int i=0;i<length;i++){
        data.insert(pair<int, int>(i, arr[i]));
    }
}

template<class T>
void SeqUnion<T>::Union(T p, T q){
    T a = find(p), b = find(q);
    for(auto it=data.begin();it!=data.end();it++){
        if(it->second==a){
            it->second = b;
        }
    }
}

template<class T>
bool SeqUnion<T>::connected(T p, T q) const{
    if(data.find(p)==data.end()||data.find(q)==data.end()){
        return false;
    }

    if(find(p)==find(q)){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void SeqUnion<T>::print() const{
    for(auto it=data.begin();it!=data.end();it++){
        cout<<"["<<it->first<<"]: "<<it->second<<' ';
    }
    cout<<endl;
}

template<class T>
T SeqUnion<T>::find(T p) const{
    auto it = data.find(p);
    if(it==data.end()){
        return -1;
    }
    else{
        return it->second;
    }
}

template<class T>
void SeqUnion<T>::insert(const T elem, const T leader){
    bool flag = false;
    T group;
    
    // 对添加数组进行查找
    if(elem == leader){
        flag = true;
        group = leader;
    }   
    
    // 对原始数组进行查找
    if(!flag){
        auto it = data.find(leader);
        if(it==data.end()){
            cerr<<"[error] Don't have the leader!"<<endl;
            return;
        }

        group = it->second;
        while(group!=it->first){
            it = data.find(group);
            group = it->second;
        }
    }

    auto it = data.find(elem);

    if(it->second!=group){
        // 发生二义性 退出 并且删除原来数组
        if(it!=data.end()){
            cerr<<"[error] Element has ambiguity!"<<endl;
            return;
        }
        
        data.insert(pair<T, T>(elem, group));
    }
}

template<class T>
void SeqUnion<T>::insert(const T* arr, int length, const T leader){
    bool flag = false;
    T group;
    
    // 对添加数组进行查找
    for(int i=0;i<length;i++){
        if(arr[i]==leader){
            group = leader;
            flag = true;
            break;
        }
    }    
    
    // 对原始数组进行查找
    if(!flag){
        auto it = data.find(leader);
        if(it==data.end()){
            cerr<<"[error] Don't have the leader!"<<endl;
            return;
        }

        group = it->second;
        while(group!=it->first){
            it = data.find(group);
            group = it->second;
        }
    }

    for(int i=0;i<length;i++){
        auto it = data.find(arr[i]);

        if(it->second!=group){
            // 发生二义性 退出 并且删除原来数组
            if(it!=data.end()){
                cerr<<"[error] Element has ambiguity!"<<endl;
                for(int j=0;j<i;j++){
                    data.erase(arr[j]);
                }
                return;
            }
           
            data.insert(pair<T, T>(arr[i], group));
        }
    }
}

template<class T>
void SeqUnion<T>::erase(T elem){
    auto it = data.find(elem);
    if(it==data.end()){
        cerr<<"[error} Elem doesn't exist!"<<endl;
        return;
    }
    
    data.earse(elem);

    T leader = elem;
    if(it->first==it->second){
        // 首先找到替换leader
        for(it=data.begin();it!=data.end();it++){
            if(it->second==leader){
                it->second = it->first;
                leader = it->first;
                break;
            }
        }
        // 然后添加新的leader
        for(it++;it!=data.end();it++){
            if(it->second==leader){
                it->second = it->first;
            }
        }
    }

}

namespace seqUnion{
    void test(){
        int group[][3] = {{0, 5, 6}, {1, 2, 7}, {3, 4, 8}};
        int leader[] = {0, 1, 8};
        SeqUnion<int> s1;
        for(int i=0;i<3;i++){
            s1.insert(group[i], 3, leader[i]);
        }

        s1.print();

        int arr[] = {0, 1, 1, 8, 8, 0, 0, 1, 8};
        int len = 9;
        SeqUnion<int> s2(arr, len);
        s2.print();
        int a[] = {10, 11, 12, 13, 8};
        s2.insert(a, 5, 10);
        s2.print();
        s2.insert(19, 2);
        s2.print();
        cout<<s2.connected(2, 3)<<' '<<s2.connected(1, 2)<<endl;
        s2.Union(0, 1);
        s2.print();
    }
};

// 利用邻接矩阵构建 加权无向图

// we use edge to be symbol of line
template<class T>
struct Edge{
    T begin, end;
    int weight;
    
    Edge(const T& begin, const T& end, const T& weight=1){
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

template<class T>
class WDiGraph{
private:
    int maxNodeNum;
    map<T, int> nodes;
    T** data;
    
    // depth-first-search
    void DFS(const T& elem, bool* visted, vector<T>& result);
public:
    WDiGraph(int n=0);
    WDiGraph(T* elems, int** data, const int& nodeNum);
    
    bool find(const T& node);
    bool find(const Edge<T>& edge);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const Edge<T>& edge);
    void insertEdge(const T& a, const T& b, const int& weight=1);

    // get the size of lines and nodes
    int sizeOfLines() const;
    int sizeOfNodes() const;

    // get the degree of a node
    int degree(const T& node);

    vector<T> DFSTraverse(const T& elem=T());
    vector<T> BFSTraverse(const T& elem=T());

    int minTreeWeight();

    void print() const;
};

template<class T>
int WDiGraph<T>::minTreeWeight(){
    // 优先队列 greater 小根堆 less 大根堆
    priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edges;
    for(int i=0;i<maxNodeNum;i++){
        for(int j=i+1;j<maxNodeNum;j++){
            if(data[i][j]){
                Edge<T> edge(i, j, data[i][j]);
                edges.push(edge);
            }
        }
    }
    
    map<T, T> treeNodes;
    int edgeNum = nodes.size() - 1;
    int totalWeight = 0;
    while(edgeNum){
        Edge<T> edge = edges.top();
        edges.pop();

        // 查找元素是否存在
        T begin = edge.begin, end = edge.end;
        
        SeqUnion<T> treeNodes;
        if(treeNodes.find(begin)==-1){
            treeNodes.insert(begin, begin);
        }
        if(treeNodes.find(end)==-1){
            treeNodes.insert(end, end);
        }

        if(treeNodes.connected(begin, end)){
            continue;
        }
        else{
            treeNodes.Union(begin, end);
            totalWeight += edge.weight;
        }

        edgeNum--;
    }

    return totalWeight;
}

template<class T>
void WDiGraph<T>::DFS(const T& elem, bool* visited, vector<T>& result){
    // index->current index, visted->record the index has been travsed
    const int& current = nodes[elem];
    if(visited[current]){
        return;
    }
    
    visited[current] = true;
    result.push_back(elem);

    // traverse the adjacency elem
    for(auto it=nodes.begin();it!=nodes.end();it++){
        const int& adjacency = it->second;
        if(data[current][adjacency]&&!visited[adjacency]){
            DFS(it->first, visited, result);
        }
    }
}

template<class T>
vector<T> WDiGraph<T>::DFSTraverse(const T& elem){
    if(!find(elem)&&elem!=T()){
        cerr<<"[Error] "<<elem<<" dones't exist!";
        exit(-1);
    }

    vector<T> result(0);
    bool* visited = new bool[sizeOfNodes()];
    for(int i=0;i<sizeOfNodes();i++){
        visited[i] = false;
    }

    if(elem!=T()){
        DFS(elem, visited, result);
    }
    else{
        DFS(nodes.begin()->first, visited, result);
    }
    return result;
}

template<class T>
vector<T> WDiGraph<T>::BFSTraverse(const T& elem){
    if(!find(elem)&&elem!=T()){
        cerr<<"[Error] "<<elem<<" dones't exist!";
        exit(-1);
    }

    // initialize the var
    T current;
    int index;
    vector<T> result(0);
    bool* visited = new bool[nodes.size()];
    for(int i=0;i<nodes.size();i++){
        visited[i] = false;
    }

    // start traversing
    queue<T> adjacencys;
    if(elem==T()){
        adjacencys.push(nodes.begin()->first);
    }
    else{
        adjacencys.push(elem);
    }
    
    while(!adjacencys.empty()){
        current = adjacencys.front();
        index = nodes[current];
        adjacencys.pop();
        
        result.push_back(current);
        visited[index] = true;

        for(auto it=nodes.begin();it!=nodes.end();it++){
            const int& adjacency = it->second;

            // 1. 判断连通 2. 是否存在过
            if(data[index][adjacency]&&!visited[adjacency]){
                adjacencys.push(it->first);
                visited[adjacency] = true;
            }
        }
    }

    return result;
}

template<class T>
WDiGraph<T>::WDiGraph(int maxNodeNum){
    // initialize the data matrix
    data = new T*[maxNodeNum];
    for(int i=0;i<maxNodeNum;i++){
        data[i] = new T[maxNodeNum];
        for(int j=0;j<maxNodeNum;j++){
            data[i][j] = T();
        }
    }

    this->maxNodeNum = maxNodeNum;
}

template<class T>
WDiGraph<T>::WDiGraph(T* elems, int** data, const int& nodeNum){
    this->data = new T*[nodeNum];
    for(int i=0;i<nodeNum;i++){
        this->data[i] = new T[nodeNum];
        for(int j=0;j<nodeNum;j++){
            this->data[i][j] = data[i][j];
        }
    }

    for(int i=0;i<nodeNum;i++){
        nodes.insert({elems[i], i});
    }
    
    this->maxNodeNum = nodeNum;
}

template<class T>
bool WDiGraph<T>::insertNode(const T& node){
    // not exist
    if(!this->find(node)){
        if(nodes.size()>=maxNodeNum){
            cerr<<"[Error] The undirectedGraph is full."<<endl;
            exit(-1);
            return false;
        }
        
        nodes.insert(pair<T, int>(node, nodes.size()));
        return true;
    }
    // exist
    else{
        return false;
    }
}

template<class T>
bool WDiGraph<T>::find(const T& node){
    return nodes.find(node)!=nodes.end();
}

template<class T>
bool WDiGraph<T>::find(const Edge<T>& line){
    const T& l = line.begin; 
    const T& r = line.end;
    if(this->find(l)&&this->find(r)){
        return data[nodes[l]][nodes[r]];
    }
    else{
        return false;
    }
}

template<class T>
void WDiGraph<T>::insertEdge(const T& a, const T& b, const int& weight){
    // whether the nodes exist or not, if not inset it
    if(!this->find(a)){
        this->insertNode(a);
    }
    if(!this->find(b)){
        this->insertNode(b);
    }

    data[nodes[a]][nodes[b]] = weight;
    data[nodes[b]][nodes[a]] = weight;
}

template<class T>
void WDiGraph<T>::insertEdge(const Edge<T>& edge){
    insertEdge(edge.begin, edge.end, edge.weight);
}

template<class T>
void WDiGraph<T>::print() const{
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        for(auto it2=nodes.begin();it2!=nodes.end();it2++){
            cout<<data[it1->second][it2->second]<<' ';
        }
        cout<<endl;
    }
}

template<class T>
int WDiGraph<T>::sizeOfLines() const{
    int size = 0;
    for(int i=0;i<maxNodeNum;i++){
        for(int j=i+1;j<maxNodeNum;j++){
            size += data[i][j];
        }
    }
    
    return size;
}

template<class T>
int WDiGraph<T>::sizeOfNodes() const{
    return nodes.size();
}

template<class T>
int WDiGraph<T>::degree(const T& node) {
    int index = nodes[node];
    int degree = 0;
    for(int i=0;i<maxNodeNum;i++){
        degree += data[index][i]; 
    }
    return degree;
}


namespace testfun{
    template<class T>
    void print(const vector<T>& arr){
        for(auto it=arr.begin();it!=arr.end();it++){
            cout<<*it<<' ';
        }
        cout<<endl;
    }

    void UndirectedGrapTest(){
        int n = 4, m = 7;
        WDiGraph<int> graph(n);
        Edge<int> lines[] = {{2, 4}, {1, 3}, {2, 1}, {1, 4},
                {4, 2}, {4, 1}, {2, 1}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Edge<int> line = lines[i];
            graph.insertEdge(line);
        }   

        // graph.insertNode(10);

        graph.print();

        cout<<"Lines: "<<graph.sizeOfLines()<<" Nodes: "<<graph.sizeOfNodes()<<endl;
        
        // test find func
        cout<<"Let's test the find func"<<endl;
        cout<<graph.find(Edge<int>(10, 1))<<' '<<graph.find(Edge<int>(2, 3))<<endl;

        // test degree func
        cout<<"Let's test the degree func"<<endl;
        for(int i=1;i<=4;i++){
            cout<<graph.degree(i)<<' ';
        }
        cout<<endl;
    }

    void TravserseTest(){
        int n = 5, m = 7;
        WDiGraph<int> graph(n);
        Edge<int> edges[] = {{1, 2}, {1, 3}, {1, 4},
                {2, 4}, {2, 5}, {3, 5}, {4, 5}
            };

        for(int i=0;i<m;i++){
            graph.insertEdge(edges[i]);
        }
        // graph.print();

        const vector<int>& DFSResult = graph.DFSTraverse(1);
        print(DFSResult);

        const vector<int>& BFSArr = graph.BFSTraverse(1);
        print(BFSArr);
    }

    void MinTreeTest(){
        const int len = 4;
        int elems[] = {1, 2, 3, 4};
        int testArr[len][len] = {{0, 2, 4, 0} ,{2, 0 ,3, 5}, { 4, 3, 0, 1}, {0, 5, 1, 0}};

        int **arr;
        arr = new int*[len];
        for(int i=0;i<len;i++){
            arr[i] = new int[len];
            for(int j=0;j<len;j++){
                arr[i][j] = testArr[i][j];
            }
        }

        WDiGraph<int> graph(elems, arr, len);
        graph.print();

        cout<<graph.minTreeWeight();
    }
    
    void solver(){
        int n, m;
        cin>>n>>m;
        WDiGraph<int> graph(n);

        int a, b, w;
        for(int i=0;i<m;i++){
            cin>>a>>b;
            
            graph.insertEdge(a, b);
        }

        // const vector<int>& DFSArr = graph.DFSTraverse();
        // print(DFSArr);

        const vector<int>& BFSArr = graph.BFSTraverse(1);
        print(BFSArr);
    }

    void solver3(){
        int len = 4;
        cin>>len;        
        int *elems = new int[len];
        for(int i=0;i<len;i++){
            elems[i] = i + 1;
        }

        int **arr;
        arr = new int*[len];
        for(int i=0;i<len;i++){
            arr[i] = new int[len];
            for(int j=0;j<len;j++){
                cin>>arr[i][j];
            }
        }

        WDiGraph<int> graph(elems, arr, len);

        cout<<graph.minTreeWeight();
    }
};

#define Edge Edge<int>

int main(){
    // testfun::TravserseTest();
    // testfun::MinTreeTest();
    testfun::solver3();
    return 0;
}