#include <map>
#include <queue>
#include <iostream>
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

template<class T>
class DirectedGraph{
private:
    const int NoEdge = numeric_limits<int>::max();

    map<T, int> nodes;
    int** weights;
    // record the rest of indexes
    queue<int> indexes;

public:
    DirectedGraph(int n=0);
    bool find(const T& node);
    bool find(const Edge<T>& edge);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const T& a, const T& b, const int& weight=1);

    // get the size of lines and nodes
    int numOfNodes() const;
    int numOfEdges() const;

    // get the degree of a node
    int InDegree(const T& node);
    int OutDegree(const T& node);

    void print() const;
};

template<class T>
DirectedGraph<T>::DirectedGraph(int maxNodeNum){
    // initialize the weights matrix
    weights = new int*[maxNodeNum];
    for(int i=0;i<maxNodeNum;i++){
        weights[i] = new int[maxNodeNum];
        for(int j=0;j<maxNodeNum;j++){
            weights[i][j] = NoEdge;
        }
    }

    for(int i=0;i<maxNodeNum;i++){
        indexes.push(i);
    }
}

template<class T>
bool DirectedGraph<T>::insertNode(const T& node){
    // not exist
    if(!this->find(node)){
        if(indexes.empty()){
            cerr<<"[Error] The undirectedGraph is full."<<endl;
            exit(-1);
            return false;
        }
        
        nodes.insert(pair<T, int>(node, indexes.front()));
        indexes.pop();
        return true;
    }
    // exist
    else{
        return false;
    }
}

template<class T>
bool DirectedGraph<T>::find(const T& node){
    return nodes.find(node)!=nodes.end();
}

template<class T>
bool DirectedGraph<T>::find(const Edge<T>& line){
    const T& l = line.begin; 
    const T& r = line.end;
    if(this->find(l)&&this->find(r)){
        return weights[nodes[l]][nodes[r]]!=NoEdge;
    }
    else{
        return false;
    }
}

template<class T>
void DirectedGraph<T>::insertEdge(const T& a, const T& b, const int& weight){
    // whether the nodes exist or not, if not inset it
    if(!this->find(a)){
        this->insertNode(a);
    }
    if(!this->find(b)){
        this->insertNode(b);
    }

    weights[nodes[a]][nodes[b]] = weight;
}

template<class T>
void DirectedGraph<T>::print() const{
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        for(auto it2=nodes.begin();it2!=nodes.end();it2++){
            int w = weights[it1->second][it2->second];
            if(w!=NoEdge)
                cout<<w<<' ';
            else
                cout<<"- ";

        }
        cout<<endl;
    }
}

template<class T>
int DirectedGraph<T>::numOfEdges() const{
    int num = 0;
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        for(auto it2=nodes.begin();it2!=nodes.end();it2++){
            if(weights[it1->second][it2->second]!=NoEdge)
                num++;
        }
    }
    
    return num;
}

template<class T>
int DirectedGraph<T>::numOfNodes() const{
    return nodes.size();
}

template<class T>
int DirectedGraph<T>::InDegree(const T& node) {
    int degree = 0;
    int index = nodes[node];
    for(auto it=nodes.begin();it!=nodes.end();it++){
        if(weights[it->second][index]!=NoEdge)
            degree++ ; 
    }
    return degree;
}

template<class T>
int DirectedGraph<T>::OutDegree(const T& node) {
    int degree = 0;
    int index = nodes[node];
    for(auto it=nodes.begin();it!=nodes.end();it++){
        if(weights[index][it->second]!=NoEdge)
            degree++ ; 
    }
    return degree;
}



namespace testfun{
    void UndirectedGrapTest(){
        int n = 4, m = 7;
        DirectedGraph<int> graph(n);
        Edge<int> edges[] = {{2, 4, 1}, {1, 3, 2}, {2, 1, 3}, {1, 4, 4},
                {4, 2, 5}, {2, 1, 8}, {1, 4, 6}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Edge<int>& edge = edges[i];
            graph.insertEdge(edge.begin, edge.end, edge.weight);
        }   

        // graph.insertNode(10);

        graph.print();

        cout<<"Lines: "<<graph.numOfEdges()<<" Nodes: "<<graph.numOfNodes()<<endl;
        
        // test find func
        cout<<"Let's test the find func"<<endl;
        cout<<graph.find(Edge<int>(3, 1))<<' '<<graph.find(Edge<int>(1, 3))<<endl;

        // test degree func
        cout<<"Let's test the degree func"<<endl;
        // for(int i=1;i<=4;i++){
        //     cout<<graph.InDegree(i)<<' ';
        // }
        // cout<<endl;
        cout<<graph.InDegree(3)<<' '<<graph.OutDegree(1)<<endl;
    }

    void solve(){
        int n, m;
        cin>>n>>m;
        DirectedGraph<int> graph(n);
        for(int i=0;i<m;i++){
            int a, b, w;
            cin>>a>>b>>w;
            
            graph.insertEdge(a, b, w);
        }

        cout<<graph.numOfEdges()<<endl;
        cout<<graph.find(Edge<int>(3, 1))<<endl;
        cout<<graph.find(Edge<int>(1, 3))<<endl;
        cout<<graph.InDegree(3)<<endl;
        cout<<graph.OutDegree(1)<<endl;
    }
};


int main(){
    // testfun::UndirectedGrapTest();
    testfun::solve();
    return 0;
}