#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef char data_t;
typedef struct BiTNode
{
	int num;//节点编号
	data_t data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
char btree[]="AB#D##C##";//给定的遍历
int PreOrderTraverse(BiTree T)//前序遍历函数
{
	if(T==NULL)
		return;
	printf("%c ",T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}
int InOrderTraverse(BiTree T)//中序遍历函数
{
	if(T==NULL)
		return;
	PreOrderTraverse(T->lchild);
	printf("%c ",T->data);
	PreOrderTraverse(T->rchild);
}
int PostOrderTraverse(BiTree T)//后序遍历函数
{
	if(T==NULL)
			return;
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
	printf("%c ",T->data);
}
BiTree CreateBiTree()//创建二叉树函数
{
	data_t data;
	static int i=0;//使用静态变量使得不同层次的递归共用一个变量i从而得到bitree内存储的值
	if(!strlen(btree))//bitree数组长度是否为0
	{
		printf("can't creat the btree\n");
		return NULL;
	}
	data = btree[i++];//递增字符串不同位置的字符赋值给每个节点
	if(data=='#')
		return NULL;//为#返回空
	else
	{
		BiTree T=(BiTree)malloc(sizeof(BiTNode));//给定义的结构题划分空间
		if(!T)//若是划不到空间则不能够创建二叉树
		{
			printf("can't creat the BiTree\n");
			exit(0);
		}
		T->data=data;//将数组里的每个字符存储在每个节点指针所指向的数据域
		T->lchild=CreateBiTree();//指针指向每个节点左孩子树调用函数本身的函数
		T->rchild=CreateBiTree();//指针指向每个节点右孩子树调用函数本身
		return T;//返回的这个指针是指向节点的指针，那个节点的哪边孩子调用的就返回给那个孩子，直到调用结束返回给根节点为止
	}
}
int main()
{
	BiTree root=CreateBiTree();//调用递归函数
	printf("Preorder:\n");
	PreOrderTraverse(root);//调用前序遍历函数
	printf("\n");

	printf("Inorder:\n");
	InOrderTraverse(root);//调用中序遍历函数
	printf("\n");

	printf("Postorder:\n");
	PostOrderTraverse(root);//调用后序遍历函数
	printf("\n");

	return 0;
}
