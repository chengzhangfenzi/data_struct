#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0

typedef int data_t;
typedef struct
{
	data_t data[MAXSIZE];
	int top;//栈顶元素所在的数组下标位置
}SqStack;//顺序栈的结构定义

int PushStack(SqStack *s,data_t e)//压栈函数（头结点指针）
{
	if(s->top==MAXSIZE-1)//判满->将头结点的栈顶值是否等于数组长减1
	{
		printf("Stack is Full\n");
		return ERROR;
	}
	s->top++;//栈顶的位置上升
	s->data[s->top]=e;//将压栈的数值赋值到每一个节点的栈顶数据域中
	return OK;
}

int PopStack(SqStack *s,data_t *e)//弹栈
{
	if(s->top==-1)//判空，栈顶是否存在
	{
		printf("Stack is Empty\n");
		return ERROR;
	}
	*e=s->data[s->top];//将弹栈的数据从栈顶节点依次取出
	s->top--;//栈顶的位置下降
	return OK;
}
SqStack* CreateEmptyStack()//创建空栈函数
{
    SqStack *stack = (SqStack*)malloc(sizeof(SqStack));//给顺序栈划分空间，
    if(stack==NULL)//判空，头结点指针为空
    {
        printf("CreateEmptyStack Error\n");
        exit(0);
    }
    stack->top=-1;//栈顶为-1，使得这是一个空栈函数
    return stack;
}
int EmptyStack(SqStack *s)//判断栈是否是空栈函数（头结点指针）
{
    return -1==s->top?OK:ERROR;//若栈顶位置为-1则为空否则为假
}
int FullStack(SqStack *s)//判断栈是否是满栈函数
{
    return MAXSIZE-1==s->top?OK:ERROR;
}
int ClearStack(SqStack *s)//清空栈内元素函数
{
    s->top=-1;//将空节点的栈顶位置置为-1，表示空栈
    return OK;
}
int main()
{
	//调用各函数实现功能
    SqStack *stack = CreateEmptyStack();
    data_t data;
    PushStack(stack,20);//调用压栈函数
    PushStack(stack,30);//调用压栈函数
    PopStack(stack,&data);//调用弹栈函数
    printf("pop:%d\n",data);//输出压栈的数据
    PopStack(stack,&data);//调用压栈函数
    printf("pop:%d\n",data);//输出压栈数据
    PopStack(stack,&data);//调用压栈函数
    printf("pop:%d\n",data);//输出压栈数据
    if(EmptyStack(stack)==OK)//调用判空函数判空
        printf("Stack is Empty!\n");//输出栈是空的
    if(FullStack(stack)==OK)//调用满栈函数判满
        printf("Stack is Full!\n");//输出这是个满栈
	
    return 0;
}

