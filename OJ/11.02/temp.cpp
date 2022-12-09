#include <iostream>
using namespace std;


int solv(int *a, int begin, int mid, int end)
{
    int nCount = 0,length,pRight,pLeft,i=0,*b,k=0;
    length = end - begin + 1;
    b=new int[length];
    pRight = begin;//起始指针均置于区间头部
    pLeft = mid + 1;
    for (i = 0; i < length ; ++i)
    {
        if (pRight > mid || pLeft > end)
        {
            break;
        }
        if (a[pRight] <= a[pLeft])
        {
            b[k]=a[pRight];//b中存放较小的数以实现升序排列
            ++pRight;
            ++k;
        }
        else
        {
            b[k]=a[pLeft];
            nCount += mid - pRight + 1;//一旦左数列中有一项比后面一项大，则左数列中后面所有项均比后面那一项大。
            ++pLeft;
            ++k;
        }
    }
    while (pRight <= mid)//若某一段指针已经指到尾部，即其元素已经安置好，只需将另一段中剩下元素置入即可
    {
        b[k]=a[pRight];
        ++pRight;
        ++k;
    }

    while (pLeft <= end)
    {
        b[k]=a[pLeft];
        ++pLeft;
        ++k;
    }
    for (i = 0; i < length; ++i)
    {
        a[begin + i] = b[i];//将b中元素复制进入a的相应位置
    }
    delete[] b;
    return nCount;
}

int countAndsplit(int *a, int begin,int end)
{
    if(begin==end)
        return 0;
    else
    {
        int right,left,mid;
        mid = (begin + end) / 2;
        right=countAndsplit(a, begin, mid);
        left=countAndsplit(a, mid + 1, end);
        return (right +left + solv(a, begin, mid, end));
    }
}

int main()
{
    int *a;
    int n,i;
    while (1)
    {
        cin >> n;
        if (n == 0)
            break;
        a = new int[n];
        for ( i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        cout<<countAndsplit(a, 0,n-1)<<endl;
    }
    return 0;
}

