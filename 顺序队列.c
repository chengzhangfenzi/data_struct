#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct
{
	data_t data[MAX];
	int front;
	int rear;
}sequeue_t;
sequeue_t *CreateEmptySequeue()
{
	sequeue_t *sq=(sequeue_t *)malloc(sizeof(sequeue_t));
	sq->front=sq->rear=MAX-1;
	return sq;
}
int EmptySequeue(sequeue_t *sq)
{
	return sq->front==sq->rear?OK:ERROR;
}
int FullSequeue(sequeue_t *sq)
{
	return (sq->rear+1)%MAX==sq->front?OK:ERROR;
}
int ClearSequeue(sequeue_t *sq)
{
	if(sq->rear==sq->front)
	return OK;
}
int EnQueue(sequeue_t *sq,data_t value)
{
	if((sq->rear+1)%MAX==sq->front)
	{
		printf("the queue is full\n");
		return ERROR;
	}
	sq->data[sq->rear]=value;
	sq->rear=(sq->rear+1)%MAX;
	return OK;
}
data_t DeQueue(sequeue_t *sq,data_t *e)
{
	if(sq->rear==sq->front)
	{
		printf("CreateEmptySequeue error\n");
		exit(0);
	}
	*e=sq->data[sq->front];
	sq->front=(sq->front+1)%MAX;
		return OK;
}
int main()
{
	sequeue_t *queue=CreateEmptySequeue();
	data_t data;
     EnQueue(queue,20);
     EnQueue(queue,30);
     EnQueue(queue,40);
	 DeQueue(queue,&data);
	 printf("De:%d\n",data);
	 DeQueue(queue,&data);
	 printf("De:%d\n",data);
	 DeQueue(queue,&data);
	 printf("De:%d\n",data);
	 DeQueue(queue,&data);
	 printf("De:%d\n",data);
	if(EmptySequeue(queue)==OK)
		printf("queue is Empty!\n");
	if(FullSequeue(queue)==OK)
		printf("queue is Full!\n");
}

