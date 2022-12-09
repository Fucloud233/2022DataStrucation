#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int m, n, temp;
	vector<vector<int>> arr;
	
	while(cin>>m>>n){
		arr.clear();
		for(int i=0;i<m;i++){
			cin>>temp;
			arr.push_back(temp);
		}
		
		sort(arr.begin(), arr.end(), std::greater<int>());
		
		for(int i=0;i<n;i++)
		{
			if(i)
				cout<<' '<<arr[i];
			else
				cout<<arr[i];
		}
		cout<<endl;
	}
}
