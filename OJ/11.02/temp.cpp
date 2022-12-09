#include <iostream>
using namespace std;


int solv(int *a, int begin, int mid, int end)
{
    int nCount = 0,length,pRight,pLeft,i=0,*b,k=0;
    length = end - begin + 1;
    b=new int[length];
    pRight = begin;//��ʼָ�����������ͷ��
    pLeft = mid + 1;
    for (i = 0; i < length ; ++i)
    {
        if (pRight > mid || pLeft > end)
        {
            break;
        }
        if (a[pRight] <= a[pLeft])
        {
            b[k]=a[pRight];//b�д�Ž�С������ʵ����������
            ++pRight;
            ++k;
        }
        else
        {
            b[k]=a[pLeft];
            nCount += mid - pRight + 1;//һ������������һ��Ⱥ���һ������������к�����������Ⱥ�����һ���
            ++pLeft;
            ++k;
        }
    }
    while (pRight <= mid)//��ĳһ��ָ���Ѿ�ָ��β��������Ԫ���Ѿ����úã�ֻ�轫��һ����ʣ��Ԫ�����뼴��
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
        a[begin + i] = b[i];//��b��Ԫ�ظ��ƽ���a����Ӧλ��
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

