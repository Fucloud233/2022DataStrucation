#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>

using namespace std;

class Edge{
public:
    int begin, end, weight;

    Edge(int beign, int end, int weight=1){
        this->begin = beign;
        this->end = end;
        this->weight = weight;
    }
};

bool operator<(const Edge& a, const Edge& b){
    return a.weight<b.weight;
}

class UnionFind{
private:
    int *leader;
    int size;

public:
    UnionFind(int size){
        leader = new int[size];
        for(int i=0;i<size;i++){
            leader[i] = i;
        }

        this->size = size;
    }

    ~UnionFind(){
        delete leader;
    }

    int find(int x){
        while(x!=leader[x]){
            x = leader[x];
        }

        return x;
    }

    void connect(int p, int q){
        leader[find(p)] = find(q);
    }
};

int kruscal(vector<Edge> edges, int num, int start){
    int maxW = numeric_limits<int>::min();
    int minW = numeric_limits<int>::max();
    int count = 0;

    UnionFind u(num);
    for(int i=start;i<edges.size();i++){
        Edge edge = edges[i];
        int fx = u.find(edge.begin);
        int fy = u.find(edge.end);

        if(fx!=fy){
            u.connect(edge.begin, edge.end);
            
            count++;
            if(edge.weight>maxW){
                maxW = edge.weight;
            }
            if(edge.weight<minW){
                minW = edge.weight;
            }
            // maxW = max(maxW, edge.weight);
            // minW = min(minW, edge.weight);

            
        }
    }

    if(count!=num-1){
        return -1;
    }

    return maxW - minW;
}


int solver(vector<Edge> edges, int num){
    sort(edges.begin()+1, edges.end());

    int minDiff = numeric_limits<int>::max();
    
    minDiff = min(minDiff, kruscal(edges, num, 0));
    if(minDiff==-1){
        return -1;
    }

    for(int i=1;i<edges.size();i++){
        int tempDiff = kruscal(edges, num, i);
        
        if(tempDiff>=0){
            minDiff = min(minDiff, tempDiff);
        }
    }

    return minDiff;
}

void test(){
    // open file
    int num = 2;
    fstream file;
    string fileDir = "./5/";
    string dataFile = fileDir + to_string(num) + ".txt";
    string resultFile = fileDir + "ans_" + to_string(num) + ".txt";
    file.open(dataFile);
    cout<<"Example "<<num<<endl;

    // calculate the result
    vector<Edge> edges;
    int m, n;
    file>>n>>m;
    for(int i=1;i<=m;i++){
        int a, b, w;
        file>>a>>b>>w;
        edges.push_back(Edge(a-1, b-1, w));
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

int main(){
    vector<Edge> edges;
    int m, n;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a, b, w;
        cin>>a>>b>>w;
        edges.push_back(Edge(a-1, b-1, w));
    }
    cout<<solver(edges, n)<<endl;
}