#include<iostream>
#include<set>

using namespace std;

int main()
{
	set<int> arr;
	int m, n, temp;
	cin>>m>>n;
	for(int i=0;i<m;i++){
		cin>>temp;
		arr.insert(temp);
	}
	
	if(n<=arr.size()){
		set<int>::iterator it = arr.begin();
		for(int i=0;i<n-1;i++)
			it++;
		cout<<*it;
	}
	else
		cout<<"¡°NO result¡±";
}
