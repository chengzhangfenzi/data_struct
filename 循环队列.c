#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct
{
	data_t data[MAXSIZE];
	int front;//队头位置
	int rear;//队尾下一个位置
}SqQueue;

SqQueue *CreateEmptyQueue()//创建队列
{
	SqQueue *sq = (SqQueue*)malloc(sizeof(SqQueue));
	if(sq==NULL)
	{
		printf("CreateEmptyQueue Error\n");
		return NULL;
	}
	sq->front=0;
	sq->rear=0;
	return sq;
}
int DestroyQueue(SqQueue *Q)//销毁队列
{
	if(Q==NULL)
	{
		printf("DestroyQueue Error\n");
		return ERROR;
	}
	free(Q);
	Q=NULL;
	return OK;
}
int QueueLength(SqQueue *Q)//求当前队列长度
{
	return (Q->rear - Q->front + MAXSIZE)%MAXSIZE;
}
int EmptyQueue(SqQueue *Q)//判断队是否为空
{
	if(Q==NULL)
	{
		printf("EmptyQueue Error\n");
		return -1;
	}
	if(Q->rear==Q->front)
		return OK;
	else
		return ERROR;
}
int FullQueue(SqQueue *Q)//判断队是否已满
{
	if(Q==NULL)
	{
		printf("EmptyQueue Error\n");
		return -1;
	}
	if((Q->rear+1)%MAXSIZE==Q->front)
		return OK;
	else
		return ERROR;
}
int EnQueue(SqQueue *Q,data_t e)//元素e入队
{
	if(FullQueue(Q)==OK)
	{
		printf("Queue is Full\n");
		return ERROR;
	}
	Q->data[Q->rear]=e;
	Q->rear=(Q->rear+1)%MAXSIZE;
	return OK;
}
int DeQueue(SqQueue *Q,data_t *e)//元素出队，出队元素存储在e中
{
	if(EmptyQueue(Q)==OK)
	{
		printf("Queue is Empty\n");
		return ERROR;
	}
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;
	return OK;
}
int main()
{
	
	SqQueue *queue = CreateEmptyQueue();
	data_t data;
	EnQueue(queue,20);
	EnQueue(queue,30);
	EnQueue(queue,40);
	DeQueue(queue,&data);
	printf("DeQueue:%d\n",data);
	DeQueue(queue,&data);
	printf("DeQueue:%d\n",data);
	DeQueue(queue,&data);
	printf("DeQueue:%d\n",data);
	DeQueue(queue,&data);
	printf("DeQueue:%d\n",data);//此处应输出1个“队列为空”
	for(data=0;data<25;data++)//此处应输出6个“队列已满”
    {
        EnQueue(queue,data);
    }
	if(DestroyQueue(queue)==OK)
        printf("DestroyQueue success\n");
	return 0;
	
}
