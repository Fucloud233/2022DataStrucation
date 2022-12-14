#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

// we use edge to be symbol of line
template<class T>
struct Edge{
    T begin, end;
    
    Edge(const T& begin, const T& end){
        this->begin = begin;
        this->end = end;
    }
};

template<class T>
class UndirectedGraph{
private:
    int maxNodeNum;
    map<T, int> nodes;
    T** data;
    
    // depth-first-search
    void DFS(const T& elem, bool* visted, vector<T>& result);
public:
    UndirectedGraph(int n=0);
    bool find(const T& node);
    bool find(const Edge<T>& edge);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const Edge<T>& edge);
    void insertEdge(const T& a, const T& b);

    // get the size of lines and nodes
    int sizeOfLines() const;
    int sizeOfNodes() const;

    // get the degree of a node
    int degree(const T& node);

    vector<T> DFSTraverse(const T& elem=T());
    vector<T> BFSTraverse(const T& elem=T());

    void print() const;
};

template<class T>
void UndirectedGraph<T>::DFS(const T& elem, bool* visited, vector<T>& result){
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
vector<T> UndirectedGraph<T>::DFSTraverse(const T& elem){
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
vector<T> UndirectedGraph<T>::BFSTraverse(const T& elem){
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
UndirectedGraph<T>::UndirectedGraph(int maxNodeNum){
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
bool UndirectedGraph<T>::insertNode(const T& node){
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
bool UndirectedGraph<T>::find(const T& node){
    return nodes.find(node)!=nodes.end();
}

template<class T>
bool UndirectedGraph<T>::find(const Edge<T>& line){
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
void UndirectedGraph<T>::insertEdge(const T& a, const T& b){
    // whether the nodes exist or not, if not inset it
    if(!this->find(a)){
        this->insertNode(a);
    }
    if(!this->find(b)){
        this->insertNode(b);
    }

    data[nodes[a]][nodes[b]] = 1;
    data[nodes[b]][nodes[a]] = 1;
}

template<class T>
void UndirectedGraph<T>::insertEdge(const Edge<T>& edge){
    insertEdge(edge.begin, edge.end);
}

template<class T>
void UndirectedGraph<T>::print() const{
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        for(auto it2=nodes.begin();it2!=nodes.end();it2++){
            cout<<data[it1->second][it2->second]<<' ';
        }
        cout<<endl;
    }
}

template<class T>
int UndirectedGraph<T>::sizeOfLines() const{
    int size = 0;
    for(int i=0;i<maxNodeNum;i++){
        for(int j=i+1;j<maxNodeNum;j++){
            size += data[i][j];
        }
    }
    
    return size;
}

template<class T>
int UndirectedGraph<T>::sizeOfNodes() const{
    return nodes.size();
}

template<class T>
int UndirectedGraph<T>::degree(const T& node) {
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
        UndirectedGraph<int> graph(n);
        Edge<int> lines[] = {{2, 4}, {1, 3}, {2, 1}, {1, 4},
                {4, 2}, {4, 1}, {2, 1}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Edge<int> line = lines[i];
            graph.insertEdge(line.begin, line.end);
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
        UndirectedGraph<int> graph(n);
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
  
    void solver(){
        int n, m;
        cin>>n>>m;
        UndirectedGraph<int> graph(n);

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
};

#define Edge Edge<int>

int main(){
    // testfun::TravserseTest();
    testfun::solver();
    return 0;
}