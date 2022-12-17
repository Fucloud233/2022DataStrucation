#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

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
class AdjGraph{
protected:
    int maxNodeNum;
    map<T, int> nodes;
    T** data;
    bool directed;

private:
    // depth-first-search
    void DFS(const T& elem, bool* visted, vector<T>& result);
    
public:
    AdjGraph(int n=0, bool directed=false);
    AdjGraph(T* elems, int** data, const int& nodeNum, bool directed=true);
    
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
    map<T, int> getShortestPath(const T& source);



    void print() const;
};

template<class T>
map<T, int> AdjGraph<T>::getShortestPath(const T& source){
    // record the info
    map<T, int> distance;
    vector<Edge<T>> edges;

    // initialize the variable
    for(auto it=nodes.begin();it!=nodes.end();it++){
        distance.insert({it->first, -1});
        for(auto jt=nodes.begin();jt!=nodes.end();jt++){
            int weight = data[it->second][jt->second];
            if(weight)
                edges.push_back({it->first, jt->first, weight});
        }
    }
    distance[source] = 0;

    // calculate the distance
    bool flag = true;
    while(flag){
        flag = false;

        for(auto it=edges.begin(); it!=edges.end();it++){
            T begin = it->begin, end = it->end;
            int weight = distance[begin] + it->weight;

            if(distance[begin]==-1){
                continue;
            }
            else if(distance[end]==-1||weight<distance[end]){
                distance[end] = weight;
                flag = true;
            }
        }
    }

    // ouput result;
    distance.erase(source);
    return distance;
}

template<class T>
int AdjGraph<T>::minTreeWeight(){
    // 优先队列 greater 小根堆 less 大根堆
    
    // 优先级队列存边
    priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edges;
    // 记录已经存在的点
    set<T> treeNodes;
    // 记录总权重
    int totalWeight = 0;
    // 用于迭代停止
    int edgeNum = nodes.size();

    // 用于记录遍历源头
    T origin = nodes.begin()->first;
    edges.push(Edge<T>(origin, origin, 0));

    while(edgeNum&&!edges.empty()){
        // 取边
        Edge<T> edge = edges.top();  edges.pop();

        // 判断节点是否存在
        T begin = edge.begin, end = edge.end;
        if(treeNodes.find(end)!=treeNodes.end()){
            continue;
        }

        treeNodes.insert(end);

        totalWeight += edge.weight;

        // insert surrounded node of end node
        for(auto it=nodes.begin();it!=nodes.end();it++){
            T adjency = it->first;
            int weight = data[nodes[end]][nodes[adjency]];

            if(weight&&treeNodes.find(adjency)==treeNodes.end()){
                edges.push(Edge<T>(end, adjency, weight));
            }
        }

        edgeNum--;
    }

    return totalWeight;
}

template<class T>
void AdjGraph<T>::DFS(const T& elem, bool* visited, vector<T>& result){
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
vector<T> AdjGraph<T>::DFSTraverse(const T& elem){
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
vector<T> AdjGraph<T>::BFSTraverse(const T& elem){
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
AdjGraph<T>::AdjGraph(int maxNodeNum, bool directed){
    // initialize the data matrix
    data = new T*[maxNodeNum];
    for(int i=0;i<maxNodeNum;i++){
        data[i] = new T[maxNodeNum];
        for(int j=0;j<maxNodeNum;j++){
            data[i][j] = T();
        }
    }

    this->maxNodeNum = maxNodeNum;
    this->directed = directed;
}

template<class T>
AdjGraph<T>::AdjGraph(T* elems, int** data, const int& nodeNum, bool directed){
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
    this->directed = directed;
}

template<class T>
bool AdjGraph<T>::insertNode(const T& node){
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
bool AdjGraph<T>::find(const T& node){
    return nodes.find(node)!=nodes.end();
}

template<class T>
bool AdjGraph<T>::find(const Edge<T>& line){
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
void AdjGraph<T>::insertEdge(const T& a, const T& b, const int& weight){
    // whether the nodes exist or not, if not inset it
    if(!this->find(a)){
        this->insertNode(a);
    }
    if(!this->find(b)){
        this->insertNode(b);
    }

    data[nodes[a]][nodes[b]] = weight;
    if(!this->directed)
        data[nodes[b]][nodes[a]] = weight;
}

template<class T>
void AdjGraph<T>::insertEdge(const Edge<T>& edge){
    insertEdge(edge.begin, edge.end, edge.weight);
}

template<class T>
void AdjGraph<T>::print() const{
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        for(auto it2=nodes.begin();it2!=nodes.end();it2++){
            cout<<data[it1->second][it2->second]<<' ';
        }
        cout<<endl;
    }
}

template<class T>
int AdjGraph<T>::sizeOfLines() const{
    int size = 0;
    for(int i=0;i<maxNodeNum;i++){
        for(int j=i+1;j<maxNodeNum;j++){
            size += data[i][j];
        }
    }
    
    return size;
}

template<class T>
int AdjGraph<T>::sizeOfNodes() const{
    return nodes.size();
}

template<class T>
int AdjGraph<T>::degree(const T& node) {
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
        AdjGraph<int> graph(n);
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
        AdjGraph<int> graph(n);
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

        AdjGraph<int> graph(elems, arr, len);
        graph.print();

        cout<<graph.minTreeWeight();
    }
    
    void solver(){
        int n, m;
        cin>>n>>m;
        AdjGraph<int> graph(n);

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

        AdjGraph<int> graph(elems, arr, len, false);

        cout<<graph.minTreeWeight();
    }

    void ShortestTest(){
        const int len = 4;
        int elems[] = {1, 2, 3, 4};
        int testArr[len][len] = {{0, 3, 0, 1} ,{0, 0 ,4, 0}, { 2, 0, 0, 0}, {0, 0, 1, 0}};
        int source = 1;      
        int **arr = NULL;  

        arr = new int*[len];
        for(int i=0;i<len;i++){
            arr[i] = new int[len];
            for(int j=0;j<len;j++){
                arr[i][j] = testArr[i][j];
            }
        }
       
        AdjGraph<int> graph(elems, arr, len, true);
        // graph.print();

        map<int, int> res = graph.getShortestPath(1);
        for(auto it=res.begin();it!=res.end();it++){
            cout<<it->second<<' ';
        }

    }

    void solver4(){
        int len = 4, source = 1;      
        int **arr = NULL;  
        cin>>len>>source;

        arr = new int*[len];
        for(int i=0;i<len;i++){
            arr[i] = new int[len];
            for(int j=0;j<len;j++){
                cin>>arr[i][j];
            }
        }

        int *elems = new int[len];
        for(int i=0;i<len;i++){
            elems[i] = i + 1;
        }
       
        AdjGraph<int> graph(elems, arr, len, true);
        // graph.print();

        map<int, int> res = graph.getShortestPath(1);
        for(auto it=res.begin();it!=res.end();it++){
            cout<<it->second<<' ';
        }      
    }
};

#define Edge Edge<int>

int main(){
    // testfun::TravserseTest();
    // testfun::MinTreeTest();
    // testfun::solver();
    testfun::solver4();
    return 0;
}