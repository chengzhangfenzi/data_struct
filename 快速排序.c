#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10

typedef struct
{
	int r[MAXSIZE];
	int length;
}Sqlist;

int QSort1(Sqlist *L,int left,int right)
{
	int i=left,j=right;
	if(left>=right)
		return;
	int key=L->r[left];
	while(i<j)
	{
		while(L->r[j]>=key&&i<j)
			j--;
		L->r[i]=L->r[j];
		while(L->r[i]<=key&&i<j)
			i++;
		L->r[j]=L->r[i];
	}
	L->r[i]=key;
	QSort1(L,left,i-1);
	QSort1(L,i+1,right);
}

int print(Sqlist *L)
{
	int i;
	for(i=0;i<L->length;i++)
		printf("%d ",L->r[i]);
	printf("\n");
}

int main()
{
	Sqlist data;
	data.length=sizeof(data.r)/sizeof(data.r[0]);
	data.r[0]=9;
	data.r[1]=1;
	data.r[2]=5;
	data.r[3]=8;
	data.r[4]=3;
	data.r[5]=7;
	data.r[6]=4;
	data.r[7]=6;
	data.r[8]=2;
	data.r[9]=10;
	QSort1(&data,0,data.length-1);
	print(&data);
	return 0;
}
