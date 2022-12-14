#include<map>
#include<iostream>
using namespace std;


// we use edge to be symbol of line
template<class T>
struct Line{
    T begin, end;
    
    Line(const T& begin, const T& end){
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
public:
    UndirectedGraph(int n=0);
    bool find(const T& node);
    bool find(const Line<T>& line);

    // insert elem
    bool insertNode(const T& node);
    void insertEdge(const T& a, const T& b);

    // get the size of lines and nodes
    int sizeOfLines() const;
    int sizeOfNodes() const;

    // get the degree of a node
    int degree(const T& node);

    void print() const;
};

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
bool UndirectedGraph<T>::find(const Line<T>& line){
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
    void UndirectedGrapTest(){
        int n = 4, m = 7;
        UndirectedGraph<int> graph(n);
        Line<int> lines[] = {{2, 4}, {1, 3}, {2, 1}, {1, 4},
                {4, 2}, {4, 1}, {2, 1}
            };

        // insert the lines
        for(int i=0;i<m;i++){
            Line<int> line = lines[i];
            graph.insertEdge(line.begin, line.end);
        }   

        graph.insertNode(10);

        graph.print();

        cout<<"Lines: "<<graph.sizeOfLines()<<" Nodes: "<<graph.sizeOfNodes()<<endl;
        
        // test find func
        cout<<"Let's test the find func"<<endl;
        cout<<graph.find(Line<int>(10, 1))<<' '<<graph.find(Line<int>(2, 3))<<endl;

        // test degree func
        cout<<"Let's test the degree func"<<endl;
        for(int i=1;i<=4;i++){
            cout<<graph.degree(i)<<' ';
        }
        cout<<endl;
    }
};

#define Line Line<int>

int main(){
    testfun::UndirectedGrapTest();
    return 0;

    int n, m;
    cin>>n>>m;
    UndirectedGraph<int> graph(n);
    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        
        graph.insertEdge(a, b);
    }

    cout<<graph.sizeOfLines()<<endl;
    cout<<graph.find(Line(3, 1))<<endl;
    cout<<graph.find(Line(1, 3))<<endl;
    cout<<graph.degree(3)<<endl;
    cout<<graph.degree(1)<<endl;
}