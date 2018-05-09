#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct
{
    int r[MAXSIZE];//存储待排序数据
    int length;//记录顺序表的长度
}Sqlist;
void swap(Sqlist *L,int i,int j)//交换数据函数
{
    int temp = L->r[i];
    L->r[i] = L->r[j];
    L->r[j] = temp;
}
void print(Sqlist *L)//打印数据函数
{
    int i;
    for(i=0;i<L->length;i++)
        printf("%d  ",L->r[i]);
    printf("\n");
}
void BubbleSort(Sqlist *L)//冒泡排序
{
    int i,j;
    for(i=0;i<L->length-1;i++)
    {
        for(j=0;j<L->length-i-1;j++)
        {
            if(L->r[j]>L->r[j+1])
                swap(L,j,j+1);
        }
    }
}
void BubbleSort2(Sqlist *L)//冒泡排序改进版1：增加标志位
{
    int i,j;
    int flag = 1;
    for(i=0;i<L->length-1 && flag;i++)
    {
        flag = 0;
        for(j=0;j<L->length-i-1;j++)
        {
            if(L->r[j]>L->r[j+1])
            {
                swap(L,j,j+1);
                flag = 1;
            }
        }
    }
}
void BubbleSort3(Sqlist *L)//冒泡排序改进版2：双向移动数据（鸡尾酒排序）
{
    int i,j;
    for(i=0;i<L->length/2;i++)
    {
        for(j=i;j<L->length-i-1;j++)
        {
            if(L->r[j]>L->r[j+1])
                swap(L,j,j+1);
        }
        for(j=L->length-1-(i+1);j>i;j--)
        {
            if(L->r[j]<L->r[j-1])
                swap(L,j-1,j);
        }
    }
}
void SelectSort(Sqlist *L)//直接选择排序
{
    int i,j,min;//min是当次循环的最小值的下标
    for(i=0;i<L->length;i++)
    {
        min=i;
        for(j=i+1;j<L->length;j++)
        {
            if(L->r[min]>L->r[j])
                min=j;
        }
        if(i!=min)
            swap(L,i,min);
    }
}
void InsertSort(Sqlist *L)//直接插入排序
{
    int i,j,tmp;
    if(L->r[0]>L->r[1])//首先保证前2个元素有序，这样后续元素才能插入
        swap(L,0,1);
	//for(i=1;i<L->length;i++)//1个数是序列
    for(i=2;i<L->length;i++)//插入L->r[i]元素
    {
        if(L->r[i]<L->r[i-1])
        {
            tmp=L->r[i];
            for(j=i-1;L->r[j]>tmp&&j>=0;j--)//将所有大于L->r[i]元素都后移，空出位置
                L->r[j+1]=L->r[j];
            L->r[j+1]=tmp;//插入正确位置
        }
    }
}
void ShellSort(Sqlist *L)
{
	int i,j,tmp;
	int increment;
	for(increment=1;increment<=L->length/4;increment=increment*2+1);//计算合适增量
	//该增量计算方法由Hibbard于1963年发表，增量为1,3,7,15……2^i-1，最接近n/4的值
	//使用该种增量可使得时间复杂度达到O(n^(3/2))
	//printf("increment是%d\n",increment);
	for(;increment>0;increment=(increment-1)/2)
	{
		for(i=increment;i<L->length;i++)
		{
			tmp = L->r[i];
			for(j=i-increment;j>=0&&tmp<L->r[j];j-=increment)
				L->r[j+increment]=L->r[j];
			L->r[j+increment]=tmp;
		}
	}
}
void QSort1(Sqlist *L,int left,int right)//快速排序
{
    int i=left,j=right;
    if(left>=right)//递归出口
        return;
    int key = L->r[left];
    while(i<j)
    {
        while(L->r[j]>=key && i<j)
            j--;
        L->r[i]=L->r[j];
        while(L->r[i]<=key && i<j)
            i++;
        L->r[j]=L->r[i];
    }
    L->r[i]=key;
    QSort1(L,left,i-1);
    QSort1(L,i+1,right);
}
/*快速排序算法写法2*/
int Partition(Sqlist *L,int low,int high)
{
   int pivotkey,tmp;
   pivotkey=L->r[low];
   tmp=pivotkey;
   while(low<high)
   {
       while(low<high && L->r[high]>=pivotkey)
        high--;
       L->r[low]=L->r[high];
       while(low<high && L->r[low]<=pivotkey)
        low++;
       L->r[high]=L->r[low];
   }
   L->r[low]=tmp;
   return low;
}
void QSort2(Sqlist *L,int low,int high)
{
    int pivot;
    if(low<high)
    {
        pivot = Partition(L,low,high);
        QSort2(L,low,pivot-1);
        QSort2(L,pivot+1,high);
    }
}
/*快速排序算法写法2end*/
int main()
{
    Sqlist data;
    data.r[0]=9;data.r[1]=1;data.r[2]=5;data.r[3]=8;data.r[4]=3;data.r[5]=7;data.r[6]=4;data.r[7]=6;data.r[8]=2;data.r[9]=10;
    data.length=sizeof(data.r)/sizeof(data.r[0]);
    BubbleSort(&data);
    BubbleSort2(&data);
    BubbleSort3(&data);
    SelectSort(&data);
    InsertSort(&data);
	ShellSort(&data);
    QSort1(&data,0,data.length-1);
    QSort2(&data,0,data.length-1);
    print(&data);
    return 0;
}

