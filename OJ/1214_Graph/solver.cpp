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

 
using namespace std;
 
struct edge{
	int begin;
	int end;
	int weight;
};
 
const int maxn = 110;
int father[maxn];
edge e[maxn*maxn];
int map[maxn][maxn];
int n,m;
 
int find(int x){
	if( x == father[x]){
		return x;
	}
 
	father[x] = find(father[x]);
	return father[x];
}
 
int kruscal(int start){//使用kruscal算法来生成最小生成树并计算带权路径和
	int i;
	int sum = 0;//用sum来记录最小s生成树的边权和
    int max = numeric_limits<int>::min();
    int min = numeric_limits<int>::max();
    int count = 0;
 
	for( i = 1 ; i < maxn ; ++i){
		father[i] = i;
	}
 
	for( i = start ; i <= m ; ++i){//枚举有序边集中的每一条边
		int fx = find(e[i].begin);
		int fy = find(e[i].end);
 
		if(fx != fy){//若第k条边的两个端点i,j 分别属于两颗不同的子树
			father[fx] = fy;//则将节点i所在的子树并入节点j所在的子树中
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
 
int main(){
	while(scanf("%d%d",&n,&m)!=EOF,n||m){
 
		int i,j;
		for(i = 1 ; i <= m ; ++i){
			scanf("%d%d%d",&e[i].begin,&e[i].end,&e[i].weight);
		}
		sort(e+1,e+m+1,compare);//kruscal算法要求边有序..特别需要注意的是排序的起点和终点
 
		/**
		 *
		 * 求生成树中最大边权值和最小边权值之差最小的:
		 * 枚举每一条边,将其作为下界,向右寻找一个上界...
		 * 使得生成树的最大边权值-最小边权值的差最小
		 *
		 */
		int slim = numeric_limits<int>::min();
		slim = min(slim,kruscal(1));
		if(slim != -1){
			for(i = 2 ; i <= m ; ++i){
				int temp = kruscal(i);
 
				if(temp >= 0){
					slim = min(slim,temp);
				}
			}
		}
 
		printf("%d\n",slim);
	}
 
	return 0;
}