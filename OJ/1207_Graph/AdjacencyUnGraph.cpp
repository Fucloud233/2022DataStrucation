#include <map>
#include <list>
#include <iostream>
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
class AdjacencyUnGraph{
private:
    map<T, list<T>> nodes;
    int edgeNum;
public:
    AdjacencyUnGraph();
    bool find(const T& node);
    bool find(const Edge<T>& edge);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const T& a, const T& b);
    
    // erase elem
    void eraseEdge(const Edge<T>& edge);

    // get the size of lines and nodes
    int numOfNodes() const;
    int numOfEdges() const;

    // get the degree of a node
    int inDegree(const T& node);
    int outDegree(const T& node);

    void print() const;
};

template<class T>
AdjacencyUnGraph<T>::AdjacencyUnGraph(){
    this->edgeNum = 0;
}

template<class T>
bool AdjacencyUnGraph<T>::find(const T& node){
    return nodes.find(node)!=nodes.end();
}

template<class T>
bool AdjacencyUnGraph<T>::find(const Edge<T>& edge){
    list<T>& l = nodes[edge.begin];
    for(auto it=l.begin();it!=l.end();it++){
        if(*it==edge.end){
            return true;
        }
    }

    return false;
}

template<class T>
bool AdjacencyUnGraph<T>::insertNode(const T& node){
    if(this->find(node)){
        return false;
    }
    
    nodes.insert(pair<T, list<T>>(node, list<T>()));
    return true;
}

template<class T>
void AdjacencyUnGraph<T>::insertEdge(const T& a, const T& b){
    insertNode(a);
    insertNode(b);

    if(find(Edge<T>(a, b))){
        return;
    }

    nodes[a].push_back(b);
    nodes[b].push_back(a);
    this->edgeNum++;
}

template<class T>
void AdjacencyUnGraph<T>::eraseEdge(const Edge<T>& edge){
    if(!this->find(edge)){
        return;
    }

    // erase the end node in begin list
    list<T>& al = nodes[edge.begin];
    for(auto it=al.begin();it!=al.end();it++){
        if(*it==edge.end){
            al.erase(it);
            break;
        }
    }
    
    // earse the begin node in end list
    list<T>& bl = nodes[edge.end];
    for(auto it=bl.begin();it!=bl.end();it++){
        if(*it==edge.begin){
            bl.erase(it);
            break;
        }
    }

    edgeNum--;
}

template<class T>
int AdjacencyUnGraph<T>::numOfEdges() const{
    return this->edgeNum;
}

template<class T>
int AdjacencyUnGraph<T>::numOfNodes() const{
    return nodes.size();
}

template<class T>
int AdjacencyUnGraph<T>::inDegree(const T& node){
    return this->nodes[node].size();
}

template<class T>
int AdjacencyUnGraph<T>::outDegree(const T& node){
    return this->nodes[node].size();
}

template<class T>
void AdjacencyUnGraph<T>::print() const{
    for(auto it1=nodes.begin();it1!=nodes.end();it1++){
        cout<<"["<<it1->first<<"]: ";
        const list<T>& l = it1->second;
        
        for(auto it2=l.begin();it2!=l.end();it2++){
            cout<<*it2<<' ';
        }
        cout<<endl;
    }
}


namespace testfun{
    void test(){
        int n = 4, m = 7;
        AdjacencyUnGraph<int> graph;
        Edge<int> edges[] = {{2, 4}, {1, 3}, {2, 1}, {1, 4},
                {4, 2}, {4, 1}, {2, 1}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Edge<int>& edge = edges[i];
            graph.insertEdge(edge.begin, edge.end);
        }   
        graph.print();

        // test the erase func
        graph.eraseEdge(Edge<int>(1, 3));
        graph.print();

        return;
    }

    void solver(){
        int n, m;
        cin>>n>>m;
        AdjacencyUnGraph<int> graph;
        for(int i=0;i<m;i++){
            int a, b;
            cin>>a>>b;
            
            graph.insertEdge(a, b);
        }

        cout<<graph.numOfEdges()<<endl;
        graph.eraseEdge(Edge<int>(2, 1));
        cout<<graph.numOfEdges()<<endl;
        cout<<graph.find(Edge<int>(3, 1))<<endl;
        cout<<graph.find(Edge<int>(1, 3))<<endl;
        cout<<graph.inDegree(3)<<endl;
        cout<<graph.outDegree(1)<<endl;
    }
}

int main(){
    // testfun::test();
    testfun::solver();
}