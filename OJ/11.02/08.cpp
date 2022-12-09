#include<iostream>
#include<map>
#include<algorithm>

using namespace std;

int main(){
	map<int, int> arr;
	int temp;
	for(int i=0;i<10;i++){
		cin>>temp;
		arr.insert(pair<int, int>(temp, i));
	}
	
	map<int, int>::iterator it;
	for(it = arr.begin();it!=arr.end();it++){
		if(it==arr.begin())
			cout<<it->first;
		else
			cout<<' '<<it->first;
	}
	
	cout<<endl;
	
	for(it = arr.begin();it!=arr.end();it++){
		if(it==arr.begin())
			cout<<it->second+1;
		else
			cout<<' '<<it->second+1;
	}
}
