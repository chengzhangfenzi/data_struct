#include <stdio.h>
#include <stdlib.h>
int number[11]={0,12,16,24,35,47,59,62,73,88,99};//待查表，第一个元素是哨兵位而不是待查数据，待查数据从下标1（第二个元素）开始
int Sequential_Search(int *a,int n,int key)
{
    int i;
    for(i=1;i<=n;i++)
    {
        if(a[i]==key)
            return i;//返回查找到的下标
    }
    return 0;//返回0代表查找失败
}
int Sequential_Search2(int *a,int n,int key)
{
    int i;
    a[0]=key;//设置哨兵
    i=n;
    while(a[i]!=key)
    {
        i--;
    }
    return i;//返回0则查找失败
}
int Binary_Search(int *a,int n,int key)
{
    int low,high,mid;
    low=1;
    high=n;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(key<a[mid])
            high=mid-1;
        else if(key>a[mid])
            low=mid+1;
        else
            return mid;
    }
    return 0;
}
int Interpolation_Search(int *a,int n,int key)//插值查找
{
    int low,high,mid;
    low=1;
    high=n;
    while(low<=high)
    {
        mid=low+(high-low)*(key-a[low])/(a[high]-a[low]);
        if(key<a[mid])
            high=mid-1;
        else if(key>a[mid])
            low=mid+1;
        else
            return mid;
    }
    return 0;
}
int main()
{
    int position;
    position = Binary_Search(number,10,47);
    printf("Position is %d\n",position);
    return 0;
}

