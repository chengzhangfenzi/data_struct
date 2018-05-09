#include<stdio.h>
#include<stdlib.h>
#define ONEMIN 5
#define FIVEMIN 12
#define ONEHOUR 12
#define BALLQUE 28
#define OK 1
#define ERROR 0
//定义顺序队列
typedef int data_t;
typedef struct
{
	data_t *data;
	int front;
	int rear;
	int max;
}SqQueue;
//定义顺序栈
typedef struct
{
	data_t *data;
	int top;
	int max;
}SqStack;
//创建顺序栈->判空->判满->压栈->弹栈
SqStack *CreateEmptyStack(int length)//创建栈
{
	SqStack *stack=(SqStack*)malloc(sizeof(SqStack));
	if(stack==NULL)
	{
		printf("没有存储空间\n");
		exit(0);
	}
	stack->data=(data_t *)malloc(length*sizeof(data_t));
	stack->max=length;
	stack->top=-1;
	return stack;
}
int EmptyStack(SqStack *s)//判断栈是否是空栈
{
	return s->top==-1?OK:ERROR;
}
int FullStack(SqStack *s)//判断栈是否是满栈
{
	return s->max-1==s->top?OK:ERROR;
}
int PushStack(SqStack *s,data_t e)//压栈
{
	if(s->max-1==s->top)
	{
		printf("栈已经满了\n");
		return ERROR;
	}
	s->top++;
	s->data[s->top]=e;
	return OK;
}
data_t PopStack(SqStack *s)//弹栈
{
	if(s->top==-1)
	{
		printf("该栈为空栈\n");
		return ERROR;
	}
	s->top--;
	data_t e=s->data[s->top];
	return OK;
}
//创建顺序队列->判空->判满->入队->出队
SqQueue *CreateEmptyQueue(int length)//创建队列
{
	SqQueue *sq=(SqQueue*)malloc(sizeof(SqQueue));
	if(sq==NULL)
	{
		printf("没有存储空间分配\n");
		exit(0);
	}
	sq->data=(data_t*)malloc(length*sizeof(data_t));
	sq->max=length;
	sq->rear=0;
	sq->front=0;
	return sq;
}
int EmptyQueue(SqQueue *Q)//判断队是否为空
{
	if(Q==NULL)
	{
		printf("EmptyStack ERROR\n");
		return -1;
	}

	return Q->rear==Q->front?OK:ERROR;
}
int FullQueue(SqQueue *Q)//判断队是否已满
{
	if(Q==NULL)
	{
		printf("EmptyStack ERROR\n");
		return -1;
	}
	else if((Q->rear+1)%Q->max==Q->front)
	{
		return OK;
	}
	else
		return ERROR;
	
}
int EnQueue(SqQueue *Q,data_t e)//入队
{
     if(FullQueue(Q)==OK)
	 {
		 printf("Queue is full\n");
		 return ERROR;
	 }
	 Q->data[Q->rear]=e;
	 Q->rear=(Q->rear+1)%Q->max;
	 return OK;
}
int DeQueue(SqQueue *Q,data_t *e)//出队
{
	if(EmptyQueue(Q)==OK)
	{
		printf("Queue is Empty\n");
		return ERROR;
	}
	*e=Q->data[Q->front];
	Q->front=(Q->front+1)%Q->max;
	return OK;
}
//时间运行的函数
int ShowTime(SqStack *one_hour,SqStack *five_min,SqStack  *one_min)
{
	int hour,min;
	min=(five_min->top+1)*5+(one_min->top+1);
	hour=one_hour->top+1;
	printf("time:%d:%d\n",hour,min);
}
//主函数实现调用功能并打印时间
int main()
{
	SqStack *one_min=CreateEmptyStack(ONEMIN);//1分钟栈
	SqStack *five_min=CreateEmptyStack(FIVEMIN);
	SqStack *one_hour=CreateEmptyStack(ONEHOUR);
	SqQueue *ballque=CreateEmptyQueue(BALLQUE);
	int i;
	data_t data;
	for(i=1;i<ballque->max-1;i++)
	{
		EnQueue(ballque,i);
	}
	while(1)
    {
		DeQueue(ballque,&data);
		PushStack(one_min,data);
		if(FullStack(one_min)==OK)
		{
			for(i=0;i<one_min->max-1;i++)
			{
				EnQueue(ballque,PopStack(one_min));	
			}
				PushStack(five_min,PopStack(one_min));
		}
		if(FullStack(five_min)==OK)
		{
			for(i=0;i<five_min->max-1;i++)
			{
				EnQueue(ballque,PopStack(five_min));
			}
			PushStack(one_hour,PopStack(five_min));
		}
		if(FullStack(one_hour)==OK)
		{
			for(i=0;i<one_hour->max;i++)
			{
					EnQueue(ballque,PopStack(one_hour));
			}
		}
		ShowTime(one_hour,five_min,one_min);
		sleep(1);
	}

	return 0;
}

