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
struct Node{
    T node;
    int weight;

    Node(const T& node, const int& weight=1){
        this->node = node;
        this->weight = weight;
    }

    bool operator==(const int& num){
        return this->node==num;
    }
};

template<class T>
class AdjacencyWDiGraph{
private:
    map<T, list<Node<T>>> beginNodes;
    map<T, list<Node<T>>> endNodes;
    int edgeNum;

public:
    AdjacencyWDiGraph();
    bool find(const T& node);
    bool find(const Edge<T>& edge);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const T& a, const T& b, const int& weight=1);
    
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
AdjacencyWDiGraph<T>::AdjacencyWDiGraph(){
    this->edgeNum = 0;
}

template<class T>
bool AdjacencyWDiGraph<T>::find(const T& node){
    const bool& flag1 = beginNodes.find(node)!=beginNodes.end();
    const bool& flag2 = endNodes.find(node)!=endNodes.end();
    return flag1&&flag2;
}

template<class T>
bool AdjacencyWDiGraph<T>::find(const Edge<T>& edge){
    list<Node<T>>& l = beginNodes[edge.begin];
    for(auto it=l.begin();it!=l.end();it++){
        if(*it==edge.end){
            return true;
        }
    }

    return false;
}

template<class T>
bool AdjacencyWDiGraph<T>::insertNode(const T& node){
    if(this->find(node)){
        return false;
    }
    
    beginNodes.insert({node, list<Node<T>>()});
    endNodes.insert({node, list<Node<T>>()});
    return true;
}

template<class T>
void AdjacencyWDiGraph<T>::insertEdge(const T& a, const T& b, const int& weight){
    insertNode(a);
    insertNode(b);

    if(find(Edge<T>(a, b))){
        return;
    }

    beginNodes[a].push_back(Node<T>(b, weight));
    endNodes[b].push_back(Node<T>(a, weight));
    this->edgeNum++;
}

template<class T>
void AdjacencyWDiGraph<T>::eraseEdge(const Edge<T>& edge){
    if(!this->find(edge)){
        return;
    }

    // erase the end node in begin list
    list<Node<T>>& al = beginNodes[edge.begin];
    for(auto it=al.begin();it!=al.end();it++){
        if(*it==edge.end){
            al.erase(it);
            break;
        }
    }
    
    // earse the begin node in end list
    list<Node<T>>& bl = endNodes[edge.end];
    for(auto it=bl.begin();it!=bl.end();it++){
        if(*it==edge.begin){
            bl.erase(it);
            break;
        }
    }

    edgeNum--;
}

template<class T>
int AdjacencyWDiGraph<T>::numOfEdges() const{
    return this->edgeNum;
}

template<class T>
int AdjacencyWDiGraph<T>::numOfNodes() const{
    return beginNodes.size();
}

template<class T>
int AdjacencyWDiGraph<T>::inDegree(const T& node){
    return this->endNodes[node].size();
}

template<class T>
int AdjacencyWDiGraph<T>::outDegree(const T& node){
    return this->beginNodes[node].size();
}

template<class T>
void AdjacencyWDiGraph<T>::print() const{
    cout<<"BeginNode: "<<endl;
    for(auto it1=beginNodes.begin();it1!=beginNodes.end();it1++){
        cout<<"["<<it1->first<<"]: ";
        const list<Node<T>>& l = it1->second;
        
        for(auto it2=l.begin();it2!=l.end();it2++){
            cout<<it2->node<<' ';
        }
        cout<<endl;
    }

    cout<<"EndNodes: "<<endl;
    for(auto it1=endNodes.begin();it1!=endNodes.end();it1++){
        cout<<"["<<it1->first<<"]: ";
        const list<Node<T>>& l = it1->second;
        
        for(auto it2=l.begin();it2!=l.end();it2++){
            cout<<it2->node<<' ';
        }
        cout<<endl;
    }
}


namespace testfun{
    void test(){
        int n = 4, m = 7;
        AdjacencyWDiGraph<int> graph;
        Edge<int> edges[] = {{2, 4, 1}, {1, 3, 2}, {2, 1, 3}, {1, 4, 4},
                {4, 2, 5}, {2, 1, 8}, {1, 4, 6}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Edge<int>& edge = edges[i];
            graph.insertEdge(edge.begin, edge.end, edge.weight);
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
        AdjacencyWDiGraph<int> graph;
        for(int i=0;i<m;i++){
            int a, b, w;
            cin>>a>>b>>w;
            
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