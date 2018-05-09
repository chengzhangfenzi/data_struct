//注意：该文件操作的单链表为带头结点单链表，头结点数据无效
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct Node
{
	data_t data;
	struct Node *next;//定义结构体Node类型的指针变量next
}Node;
typedef struct Node *LinkList;//重新定义结构体Node类型的指针为链表类型（struct Node *==LinkList）

int GetElem(LinkList L,int i,data_t *data)//读取单链表的第i个元素（获得元素函数）L头节点指针变量，data为data_t*型的指针变量，第i个元素指获得的元素个数i
{
	int j;
	LinkList p;//工作指针
	p = L->next;//附初始值给工作节点指针
	j = 1;//从1号节点开始
	while(p && j<i)//直到我们的工作指针置空为止，工作指针置空是由于我们需要最后一个节点能够有效往前一个指针传,而后一个工作指针则没有这样的效果.
	{
		p = p->next;//让p指向下一个节点，让下一个指针链接上一个指针，p->next指的是后一个工作节点的指针
		j++;//节点号递增
	}
	if(!p)//若if没有执行则证明位置有效，可以获得数据
	{
		printf("%d position error\n",i);
		return ERROR;//有可能工作指针指向的位置无效。
	}
	*data = p->data;//将指针数据data指向工作指针指向的数据并取出来（获得该位置的该元素）
	return OK;
}

int ListInsert(LinkList L,int i,data_t e)//插入新节点数据是e，使其成为第i个节点（插入元素函数）
{
	int j;
	LinkList p,s;//s专门指插入节点指针
	p=L;//工作指针取初值为头指针
	j=1;//将1号节点作为初始节点
	while(p && j<i)//寻找i的位置，直到工作指针置空为止
	{
		p=p->next;//将下一个工作指针赋值给工作指针
		j++;//节点递增
	}
	if(!p)//p为NULL
	{
		printf("%d position error\n",i);
		return ERROR;//有可能工作指针指向的位置无效
	}
	//若if没有执行则证明位置有效，可以插入数据
	s=(LinkList)malloc(sizeof(Node));//创建链表中每个节点所用的存储空间
	s->data=e;//把插入数值e放到链表的存储空间指向的data_t类型的变量data中
	s->next=p->next;//把下一个工作指针赋值给插入的工作指针的后继
	p->next=s;//把插入的工作指针赋值给头指针的后继（两者位置不能够颠倒）
	return OK;
}

int ListDelete(LinkList L,int i,data_t *e)//删除第i个位置节点,
{
	int j;//定义节点数
	LinkList p,q;//定义工作指针p以及要删除的数据e位置的指针q
	if(L->next==NULL)//若是头结点指针置空
	{
		printf("LinkList is Empty!\n");
		return ERROR;//整个链表不存在
	}
	p=L;//将头结点指针赋值给工作指针
	j=1;//从1号节点开始
	while(p->next && j<i)//直到下一个工作指针置空为止（在这个要删除的节点位置之前）
	{
		p=p->next;//将后工作节点赋值给目前的工作节点
		j++;//将要删除的节点位置之前的有效节点都找出来
	}
	if(!(p->next))
	{
		printf("%d position error\n",i);
		return ERROR;//若if没有执行则证明位置有效，可以删除数据，说明给节点位置无效
	}
	q=p->next;//找到要删除链表内的前驱节点，并将后一工作节点赋值给该要删除的节点的指针
	p->next=q->next;//将要删除节点的指针的后继赋值给工作指针的后继。
	*e=q->data;//指针e指向该要删除节点的数据，并回馈给主函数（删除该数据）
	free(q);//将该数据删除后的空间释放掉节省空间
	return OK;
}

LinkList CreateEmptyLinklist()//创建一个空表，空表只有头结点（创建空链表函数）
{
    LinkList p;
    p = (LinkList)malloc(sizeof(Node));//指针p指向划给该空链表的存储空间
    if(p==NULL)//若if没有执行则证明位置有效，可以插入数据
    {
        perror("CreateEmptyLinkList error");
        exit(0);
    }
    //p->data=-255;//表示无效数据
    p->next=NULL;//防止野指针的出现
    return p;
}

LinkList CreateListHead(LinkList L,int n)//创建链表（头插法）头节点指针  节点总数（头插法函数）
{
	LinkList p;//工作指针
	int i;//初始节点
	srand(time(NULL));//调用产生随机数的函数
	for(i=0;i<n;i++)
	{
		p = (LinkList)malloc(sizeof(Node));//给每一个节点动态分配内存空间用指针p接收
		p->data = rand()%100+1;//产生的随机数放入到工作指针指向的数据区域中
		p->next = L->next;//将头指针指向的后继赋值给相应节点的工作指针指向的后继中
		L->next = p;//将该节点工作指针赋值给头指针的后继(注意顺序千万不能颠倒)
	}
	return L;//返回该工作节点指针
}

LinkList CreateListTail(LinkList L,int n)//创建链表（尾插法）（尾插法函数）
{
	LinkList p,r;//定义工作指针p以及指向链表表尾的指针
	int i;//初始节点
	srand(time(NULL));//调用产生随机数的函数
	r = L;//将头节点的指针赋值给表尾指针
	for(i=0;i<n;i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;//该节点数据域接收产生的随机数
		r->next = p;//将工作指针赋值给表尾指针的后继
		r = p;//将工作指针赋值给表尾指针
	}
	r->next = NULL;//链表封尾，防止野指针的出现
	return L;//返回尾指针
}

int ClearList(LinkList L)//清空链表（清空链表函数）
{
	LinkList p,q;//输入两个指针p和q
	p=L->next;//将工作指针指向头指针的后继
	while(p)//工作指针依次找节点
	{
		q=p->next;//将当前节点下的指针指向下一个节点
		free(p);//释放当前的节点
		p=q;//将当前节点的指针指向工作指针
	}
	L->next=NULL;//将头结点的指针后继置为空
	return OK;
}
int PrintList(LinkList L)//遍历打印整个链表（打印链表函数）
{
    LinkList p=L->next;//工作指针指向头指针的后继
    while(p)//依次将节点的位置找出
    {
        printf("%d\t",p->data);//输出每个节点的数据
        p=p->next;//将工作指针指向下一个节点
    }
    printf("\n");
    return OK;
}

int ListReverse(LinkList L)//练习1：单链表反序（函数）（1断开头结点与1号节点的联系，同时使得1号节点为头节点；2在判空的前提下反序排列）
{
	LinkList p,q;//p为正序工作指针，q为反序工作节点的指针
	p=L->next;//正序工作指针指向1号节点的指针
	L->next=NULL;//断开头结点的指针使得1号节点为头指针
	while(p!=NULL)
    {
        q=p;//将要反序工作指针指向正序工作指针
        p=p->next;//将正序工作指针指向下一个节点
        q->next=L->next;//将下一个反序工作指针的后继指向下一个正序工作指针
        L->next=q;//将将头指针的后继指向反序工作指针
    }
	return OK;
}

LinkList Adjmax(LinkList h)//练习2：寻找最大元素对（找最大元素对函数）
{
	LinkList p, p1, q;//定义三个指针，p1为最大元素指针，q为相邻工作指针
	int m0, m1;//定义两个变量
	p = h->next;//工作指针指向1号指针
	p1 = p;//最大元素工作指针指向工作指针
	if(p1 == NULL)//没有表
		return  p1;     //表空返回
	q = p->next;
	if(q == NULL)//只有一个节点
		return  p1;      //表长=1时的返回
	m0 = p->data + q->data;         //相邻两结点data值之和
	while (q->next!=NULL)//直到最大工作指针置空为止
	{
		p = q;//工作指针指向相邻元素指针
		q = q->next;     //取下一对相邻结点的指针（最大元素工作指针指向相邻工作指针）
		m1 = p->data + q->data;//相邻两结点data值之和
		if(m1 > m0)//找到相邻元素相加的最大值
		{
			p1 = p;//将最大指针指向工作指针
			m0 = m1;//并输出最大值给主函数
		}
	}//取和为最大的第一结点指针
	return p1;//返回最大值指针
}
int main()
{
    
    LinkList head1,head2;//定义结构类型的两个头指针
    int i;
    data_t data=12;//数据域里头的数据12
    head1=CreateEmptyLinklist();//调用创建头结点链表函数
    head2=CreateEmptyLinklist();//调用创建头结点链表函数
    printf("head1\n");
    head1=CreateListHead(head1,15);//调用创建头插法链表函数
    PrintList(head1);//调用打印链表函数
	printf("head2\n");//调用打印链表函数
    head2=CreateListTail(head2,15);//调用创建尾插法链表函数
    PrintList(head2);//调用打印链表函数
	scanf("%d",&i);//输入要插入的元素的位置
    printf("Insert head1 %d position, data is %d\n",i,data);//输出插入元素数据的位置及数据
    ListInsert(head1,i,data);//调用链表插入函数
    PrintList(head1);//调用打印链表函数
    scanf("%d",&i);//输入要删除元素的位置
    ListDelete(head1,i,&data);//调用删除元素函数
    printf("Delete head1 %d position, data is %d\n",i,data);//输出要删除的元素位置以及数据
    PrintList(head1);//调用打印链表函数
	LinkList adjmax = Adjmax(head1);//调用寻找最大元素对函数
    printf("Adjmax data is %d, Adjmax data next data is %d\n",adjmax->data,adjmax->next->data);//输出的最大值是，与其相邻的值是，
	ListReverse(head1);//调用单链表反序函数
	printf("Reserve head1:\n");
	PrintList(head1);//调用打印链表函数
    if(ClearList(head1)==OK)//如果清空单链表成功
    {
        printf("head1 Clear success\n");//头节点的指针被删除
    }
    if(ClearList(head2)==OK)
    {
        printf("head2 Clear success\n");
    }
   
    return 0;
}

