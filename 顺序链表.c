#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct
{
	data_t data[MAXSIZE];//定长情况下
	int length;//表长
}SqList;
SqList *CreateEmptySqList()//定长
{
	SqList *sq;
	if(NULL==(sq = (SqList*)malloc(sizeof(SqList))))
	{
		printf("CreateEmptySqList Error\n");
		exit(0);
	}
	sq->length=0;//要保证创建的顺序表是空的
	return sq;
}

int GetElem(SqList *L,int i,data_t *e)//获得顺序表第i个位置的元素（获取元素的函数）
{
	if(i>=L->length || i<0)//第i个位置的元素是否在合法的位置上
	{
		perror("No this Element");
		return ERROR;
	}
	*e=L->data[i];//将指针变量e指向指针变量L指向第i个位置的元素数据并取出来。
	return OK;
}
int ListInsert(SqList *L,int i,data_t e)//在线性表的第i个位置插入元素e（插入元素的函数）
{
	int k;
	if(L->length==MAXSIZE)//线性表已满
	{
		printf("SqList is Full\n");
		return ERROR;//不能够插入
	}
	if(i<0 || i>L->length)//i不在线性表的范围内
	{
		printf("Position Error\n");
		return ERROR;//不能够插入
	}
	if(i<L->length)//若插入位置不在表尾
	{
		for(k=L->length-1;k>=i;k--)//当前位置开始到表尾所有元素向后移动1格，k
			L->data[k+1]=L->data[k];
	}
	L->data[i]=e;//插入新元素
	L->length++;//由于插入新元素，因此有效长度要要相应增加。
	return OK;
}
int ListDelete(SqList *L,int i,data_t *e)//删除线性表的第i个位置元素，并用e得到删除的值（删除元素的函数）
{
	int k;
	if(L->length==0)//线性表为空
	{
		printf("SqList is Empty\n");
		return ERROR;
	}
	if(i<0 || i>=L->length)//i不在线性表的范围内
	{
		printf("Position Error\n");
		return ERROR;
	}
	*e=L->data[i];//取走元素
	if(i<L->length-1)//若删除位置不在表尾，由于已取走一个有效元素
	{
		for(k=i;k<L->length-1;k++)
			L->data[k]=L->data[k+1];
	}
	L->length--;//有效元素要减少
	return OK;
}
int PrintList(SqList *L)//遍历打印整个顺序表(输出整个顺序表)
{
    int k;
    data_t temp=0;
    if(L->length==0)
    {
        printf("线性表为空！\n");
        return ERROR;
    }
    for(k=0;k<L->length;k++)
    {
        GetElem(L,k,&temp);//函数的调用
        printf("%d\t",temp);//输出第i个位置上的元素
    }
    printf("\n");
    return OK;
}
int main()
{
	int i;
	data_t data;
	SqList *sq = CreateEmptySqList();//调用已创建的空顺序表函数
	for(i=0;i<5;i++)
	{
		sq->data[sq->length]=i;//指针sq指向数组data里的（指针sq指向表长）的有效数据（下标）
		sq->length++;//指针sq指向的表长最大值为4
	}
	if(GetElem(sq,3,&data)==OK)//判定得到的第3个位置的元素的合法性，并调用获取元素的函数
	{
		printf("data is %d\n",data);//输出第三个位置的数据
	}
	PrintList(sq);//调用输出顺序表函数
	ListInsert(sq,2,20);//调用插入线性表的函数
	PrintList(sq);//调用输出顺序表函数
	ListDelete(sq,2,&data);//调用删除线性表函数
	PrintList(sq);//调用输出顺序表函数
	return 0;
}

