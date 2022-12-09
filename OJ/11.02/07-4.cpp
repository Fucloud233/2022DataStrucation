#include<iostream>
using namespace std;


long long solv(long long *a, long long begin, long long mid, long long end){
	long long count =0, l = begin, r = mid+1, t = 0;
	long long len = end - begin + 1;
	long long *b = new long long[len];
	
	while(l<=mid&&r<=end){
		if(a[l]<=a[r]){
			b[t++] = a[l++];
		}
		else{
			count += mid - l + 1;
			b[t++] = a[r++];
		}
	}
	
	while(l<=mid){
		b[t++] = a[l++];
	}
	
	while(r<=end){
		b[t++] = a[r++];
	}
	
	for(long long i=0;i<len;i++){
		a [begin + i] = b[i];
	}
	
	delete [] b;
	return count;
}

long long coutAndSplit(long long *a, long long begin, long long end){
	if(begin==end)
		return 0;
	else{
		long long right, left, mid;
		mid = (begin+end)/2;
		right = coutAndSplit(a, begin, mid);
		left = coutAndSplit(a, mid+1, end);
		return (right + left + solv(a, begin, mid, end));
		}
	}

int main(){
	long long *a;
	long long n;
	while(true){
		cin>>n;
		if(!n){
			break;
		}
		
		a = new long long[n];
		for(long long i=0;i<n;i++){
			cin>> a[i];
		}
		
		cout<<coutAndSplit(a, 0, n-1)<<endl;
	}
	
	return 0;
}


