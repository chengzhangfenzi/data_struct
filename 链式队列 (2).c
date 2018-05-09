#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int data_t;

typedef struct node_t//普通单链表节点
{
	data_t data;
	struct node_t *next;

} linknode_t, *linklist_t;

typedef struct//链式队列的头结点
{
	linklist_t front, rear;
} linkqueue_t;

linkqueue_t *CreateEmptyLinkqueue()//创建空队列
{
	linkqueue_t *queue;

	queue = (linkqueue_t *)malloc(sizeof(linkqueue_t));
	if (NULL == queue)
	{
		perror("Create Empty LinkQueue Error");
		return NULL;
	}
	queue->rear = queue->front = NULL;

	return queue;
}

int ClearLinkqueue(linkqueue_t *queue)//清空队列
{
	linknode_t *node_remove;

	node_remove = queue->front;
	while (NULL != node_remove)
	{
		queue->front = queue->front->next;
		free (node_remove);
		node_remove = queue->front;
	}
	queue->front = NULL;
	queue->rear = NULL;
	return OK;
}

int DestroyLinkqueue(linkqueue_t *queue)//销毁队列
{
	if (queue)
	{
		ClearLinkqueue(queue);
		free(queue);
		return OK;
	}
	else
	{
		printf("DestroyLinkqueue Error\n");
		return ERROR;
	}
}
int EmptyLinkqueue(linkqueue_t *queue)//判定队列是否为空
{
	if (!queue)
	{
		printf("EmptyLinkqueue Error\n");
		return -1;
	}
	return queue->front == NULL ? OK : ERROR;
}

int EnQueue(linkqueue_t *queue, data_t x)//入队
{
	linknode_t *node_new;

	if (!queue)
	{
		printf("EnQueue Error\n");
		return ERROR;
	}
	node_new = (linknode_t *)malloc(sizeof(linknode_t));
	node_new->data = x;
	node_new->next = NULL;

	if(EmptyLinkqueue(queue)==OK)
	{
		queue->front = queue->rear = node_new;
	}
	else
	{
		queue->rear->next = node_new;
		queue->rear = node_new;
	}

	return OK;
}

int DeQueue(linkqueue_t *queue, data_t *x)//出队
{
	linknode_t *node_remove;

	if(!queue)
	{
		printf("DeQueue Error\n");
		return ERROR;
	}
	if(EmptyLinkqueue(queue)==OK)
    {
        printf("queue is Empty\n");
        return ERROR;
    }
	node_remove = queue->front;

	queue->front = node_remove->next;

	if (NULL == queue->front)
		queue->rear = NULL;
	*x = node_remove->data;

	free(node_remove);
	return OK;
}

int VisitQueue(linkqueue_t *queue)//遍历队列
{
	linknode_t *node;

	printf("aueue = {");

	node = queue->front;
	if (NULL == node) {
		printf("}\n");
		return OK;
	}
	while (NULL != node) {
		printf("%d,", node->data);
		node = node->next;
	}
	printf("\b}\n");

	return OK;
}
int main()
{
	
	linkqueue_t *queue = (linkqueue_t*)malloc(sizeof(linkqueue_t));
	data_t data;
	int i;
	EnQueue(queue,20);
	EnQueue(queue,30);
	DeQueue(queue,&data);
	printf("data is %d\n",data);
	DeQueue(queue,&data);
	printf("data is %d\n",data);
	DeQueue(queue,&data);
	printf("data is %d\n",data);
	for(i=0;i<20;i++)
	{
		EnQueue(queue,i);
	}
	VisitQueue(queue);
	for(i=0;i<25;i++)//应打印出5个Error
	{
		DeQueue(queue,&data);
		printf("data is %d\n",data);
	}
	if(DestroyLinkqueue(queue)==OK)
	{
		printf("DestroyLinkqueue success\n");
	}
	return 0;
	
}

