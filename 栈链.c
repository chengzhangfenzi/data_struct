#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int data_t;
typedef struct StackNode
{
	data_t data;
	struct StackNode *next;//定义结构类型的指针域
}LinkStack;//重定义链栈结构体
LinkStack *CreateEmptyStack()//创建栈函数
{
	LinkStack *s;//定义链栈类型的工作指针变量
	s = (LinkStack*)malloc(sizeof(LinkStack));//动态划分链栈空间
	if(s==NULL)
	{
		perror("Create Empty Stack Error");
		exit(0);
	}//若if没有执行则证明该位置有效，可以创建栈
	s->next=NULL;//保证要避免野指针的出现
	return s;
}
int ClearLinkStack(LinkStack *stack)//清空栈函数（头结点指针）
{
	if(!stack)//如果头结点指针不存在
		return ERROR;
	LinkStack *node;//定义栈顶指针
	while(stack->next!=NULL)//直到栈顶指针置空为止
	{
		node=stack->next;//将栈顶指针指向头结点指针
		stack->next=node->next;//将将头节点指针的指针域指向下一个节点的指针
		free(node);//释放节点指针
	}
	return OK;
}
int DestroyLinkStack(LinkStack *stack)//销毁栈函数
{
	if(stack)//头结点指针存在
		ClearLinkStack(stack);//调用清空栈函数
	free(stack);//释放头结点空间
	stack=NULL;//避免野指针的出现
	return OK;
}
int EmptyLinkStack(LinkStack *stack)//判断栈是否为空（空栈的判断函数）
{
	if(stack==NULL)//若是头结点指针置空，输出错误
	{
		printf("Empty Error\n");
		return -1;//由于栈顶的最小值为0，因此判空错误的返回应是-1
	}
	else
	{
		return NULL==stack->next?OK:ERROR;//判空成功则OK，否则错误。
	}
}
int PushStack(LinkStack *s,data_t e)//压栈函数
{
	if(s==NULL)//栈顶指针置空，压栈不能够执行
	{
		printf("PushStack Error\n");
		return ERROR;
	}
	LinkStack *p=(LinkStack*)malloc(sizeof(LinkStack));//划分空间给压入栈中的元素，用工作指针p接收
	p->data=e;//将该元素赋值到工作指针的数据域中
	p->next=s->next;//将工作指针的后继指向栈顶的后继
	s->next=p;//将栈顶的后继指向工作指针（头插法）
	return OK;
}
int PopStack(LinkStack *s,data_t *e)//弹栈函数（栈顶指针s，数据指针e）
{
	LinkStack *p;//工作指针
	if(s==NULL)//判断栈顶是否为空
	{
		printf("PopStack Error\n");
		return ERROR;
	}
	if(EmptyLinkStack(s)==OK)//判断栈是否为空
	{
		printf("The Stack is Empty\n");
		return ERROR;
	}
	*e=s->next->data;//将要弹出的数值从栈顶的后继节点指向的数据域里头取出给主函数
	p=s->next;//工作指针指向栈顶的后继节点
	s->next=s->next->next;//将栈顶的后继节点指向栈顶后继节点的后继节点（删除栈顶节点即删除p指针所指向节点的后继节点）
	free(p);//释放工作指针所占的空间
	return OK;
}

int main()
{
	
	data_t data;//数据域
	LinkStack *stack = CreateEmptyStack();//调用创建的空栈链函数
	PushStack(stack,20);//调用压栈函数
	PushStack(stack,30);//调用出栈函数
	PopStack(stack,&data);//调用弹栈函数
	printf("Pop:%d\n",data);//输出弹栈的数据
	PopStack(stack,&data);//调用弹栈函数
	printf("Pop:%d\n",data);//输出弹栈的数据
	PopStack(stack,&data);//调用弹栈函数
	printf("Pop:%d\n",data);//输出弹栈数据
	PushStack(stack,20);//调用出栈函数
	PushStack(stack,30);//调用出栈函数
	if(DestroyLinkStack(stack)==OK)//调用销毁栈函数是否成功
	{
		printf("Desroy LinkStack Success\n");//输出销毁成功
	}
	return 0;
	
}

