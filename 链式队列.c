#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct node_t
{
	data_t data;
	struct node_t *next;
}linknode_t,*linklist_t;
typedef struct
{
	linklist_t front,rear;
}linkqueue_t;

linkqueue_t *CreateEmptyLinkqueue()
{
	linkqueue_t *lq;
	lq=(linkqueue_t *)malloc(sizeof(linkqueue_t));
	lq->front=lq->rear=(linklist_t)malloc(sizeof(linknode_t));
	lq->front->next=NULL;
	return lq;
}

int Emptylinkqueue(linkqueue_t *lq)
{
	return lq->front==lq->rear?OK:ERROR;
}

int ClearLinkqueue(linkqueue_t *lq)
{
	if(lq->front==NULL)
	return OK;
}

int EnQueue(linkqueue_t *lq,data_t value)
{
	lq->rear->next=(linklist_t)malloc(sizeof(linknode_t));
	lq->rear=lq->rear->next;
	lq->rear->data=value;
	lq->rear->next=NULL;
	return OK;
}

data_t DeQueue(linkqueue_t *lq)
{
	data_t value;
	linklist_t p;
	if(lq->front==NULL)
	{
		printf("CreateEmptySequeue error\n");
		exit(0);
	}
	p=lq->front->next;
	lq->front->next=p->next;
	value=p->data;
	free(p);
	if(lq->front==NULL)
	{
		printf("CreateEmptySequeue error\n");
		exit(0);
	}
		return value;
}

int main()
{
	
	 linkqueue_t *queue=CreateEmptyLinkqueue();
	 data_t data;
     	 EnQueue(queue,20);
	EnQueue(queue,30);
	EnQueue(queue,40);
	EnQueue(queue,50);
	 data=DeQueue(queue);
	 printf("De:%d\n",data);
 	data=DeQueue(queue);
	 printf("De:%d\n",data);
 	data=DeQueue(queue);
	 printf("De:%d\n",data);
	if(Emptylinkqueue(queue)==OK)
		printf("queue is Empty!\n");
	return 0;
	
}


