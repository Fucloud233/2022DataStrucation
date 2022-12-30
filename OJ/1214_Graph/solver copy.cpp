/*
 * POJ_2421.cpp
 *
 *  Created on: 2013年11月8日
 *      Author: Administrator
 */
 
 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

 
using namespace std;
 
struct edge{
	int begin;
	int end;
	int weight;
	
	edge(){
		begin = 0;
		end = 0; 
		weight = 0;
	}

	edge(int a, int b, int w){
		begin = a;
		end = b;
		weight = w;
	}
};
 
const int maxn = 110;
int father[maxn];
// edge e[maxn*maxn];

vector<edge> e;
int map[maxn][maxn];
int n,m;
 
int find(int x){
	if( x == father[x]){
		return x;
	}
 
	father[x] = find(father[x]);
	return father[x];
}

class UnionFind{
private:
    int *leader;
    int size;

public:
    UnionFind(int size){
        size++;

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
        if(x==leader[x]){
            return x;
        }

        leader[x] = find(leader[x]);
        return leader[x];
    }

    void connect(int p, int q){
        leader[find(p)] = find(q);
    }
};
 
int kruscal(vector<edge> edges, int size, int start){//使用kruscal算法来生成最小生成树并计算带权路径和
	int i;
	int sum = 0;//用sum来记录最小s生成树的边权和
    int max = numeric_limits<int>::min();
    int min = numeric_limits<int>::max();
    int count = 0;
 
	UnionFind u(n);

	for( i = start ; i <= m ; ++i){//枚举有序边集中的每一条边
		edge E = e[i];
		int fx = u.find(E.begin);
		int fy = u.find(E.end);
 
		if(fx != fy){//若第k条边的两个端点i,j 分别属于两颗不同的子树
			
			u.connect(E.begin, E.end);
			// father[fx] = fy;//则将节点i所在的子树并入节点j所在的子树中
			sum += e[i].weight;
 
 
			//求解每种生成树的(max - min)值
			count++;
			if(e[i].weight > max){
				max = e[i].weight;
			}
			if(e[i].weight < min){
				min = e[i].weight;
			}
 
		}
	}
 
	if(count != n-1){//不是生成树
		return -1;
	}
	return max - min;
}
 
bool compare(const edge& a , const edge& b){
	return a.weight < b.weight;
}
 
//以上是用kruscal算法来解决问题的基本模板.....
 
 #include <iostream>
 #include <fstream>

int main(){
    // open file
    int num = 2;
    fstream file;
    string fileDir = "./5/";
    string dataFile = fileDir + to_string(num) + ".txt";
    string resultFile = fileDir + "ans_" + to_string(num) + ".txt";
    file.open(dataFile);
    cout<<"Example "<<num<<endl;
	
	vector<edge> edges;
	edges.push_back(edge);
	file>>n>>m;
	e.push_back(edge());
	int i,j;
	for(i = 1 ; i <= m ; ++i){
		// file>>e[i].begin>>e[i].end>>e[i].weight;
		int a, b, w;
		file>>a>>b>>w;
		edges.push_back(edge(a, b, w));

	}
	sort(e.begin()+1,e.end(),compare);//kruscal算法要求边有序..特别需要注意的是排序的起点和终点

    // calculate the result
    int slim = numeric_limits<int>::max();
	slim = min(slim,kruscal(1));
	if(slim != -1){
		for(int i = 2 ; i <= m ; ++i){
			int temp = kruscal(i);

			if(temp >= 0){
				slim = min(slim,temp);
			}
		}
	}

	cout<<"result: "<<slim;
	return 0;

    // 打印正确答案
    file.open(resultFile);
    int result;
    file>>result;
    cout<<"Answer: "<<result;
    file.close();
}

// int main(){
// 	cin>>n>>m;
 
// 	int i,j;
// 	for(i = 1 ; i <= m ; ++i){
// 		cin>>e[i].begin>>e[i].end>>e[i].weight;
// 	}
// 	sort(e+1,e+m+1,compare);//kruscal算法要求边有序..特别需要注意的是排序的起点和终点

// 	/**
// 	 *
// 	 * 求生成树中最大边权值和最小边权值之差最小的:
// 	 * 枚举每一条边,将其作为下界,向右寻找一个上界...
// 	 * 使得生成树的最大边权值-最小边权值的差最小
// 	 *
// 	 */
// 	int slim = numeric_limits<int>::max();
// 	slim = min(slim,kruscal(1));
// 	if(slim != -1){
// 		for(i = 2 ; i <= m ; ++i){
// 			int temp = kruscal(i);

// 			if(temp >= 0){
// 				slim = min(slim,temp);
// 			}
// 		}
// 	}

// 	cout<<slim;
// 	return 0;
// }