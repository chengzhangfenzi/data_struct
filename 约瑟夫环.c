#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

/* use a cycle linked list without header node */
typedef struct node_t
{
	data_t data;//定义数据域
	struct node_t *next;//定义指针域
} linknode_t, *linklist_t;//定义不带头结点的循环链表
//注意：该题目使用的为不带头结点的循环链表
int main()
{
	int i, n, m, k;
	linklist_t p, q;//定义两个工作指针,p工作指针寻找被杀人的位置，q工作指针寻找起始人的位置
	printf("total N people will join this suicide game, please input N:");//总 n 人将加入这个自杀游戏, 请输入 N
	scanf("%d", &n);
	printf( "people stand in a circle, assume everyone is assigned\n"
		"a sequence number from 1 to %d.\n"\
		"which one would you like to start the number off (1~%d):", n, n);/*人们站在一个圆圈, 假设每个人都被分配;
		序列号从1到n;你想从第k个开始数字？（1~n）*/
	scanf("%d", &k);
	printf("every Xth people should kill himself, please decide the X:");//每个 Xth 的人都应该自杀, 请决定 X:
	scanf("%d", &m);

	if (n < 1 || k > n || m < 1) //判断数据是否合法
	{
		printf("input error!\n");
		return -1;
	}

	printf("game is starting ...\n");//游戏开始

	/* added the first one（添加了第一个） */
	//第一部分：创建n个人的循环链表
	p = q = (linklist_t)malloc(sizeof(linknode_t));//给循环链表分配空间，这两个指针同时指向该空间
	p->data = 1;//将第一个人赋值给工作指针p的数据域

	/* added other left people（添加了其他剩下人员） */
	for (i = 2; i <= n; i++) //从第二人开始，依次循环划分动态空间给其他人
	{
		q->next = (linklist_t)malloc(sizeof(linknode_t));//划分动态空间用工作指针q的后继接收
		q = q->next;//将工作指针q指向工作指针的后继
		q->data = i;//将人数依次放入工作指针q的的的数据域中
	}
	/* complete the circle（结束循环） */
	q->next = p;//将工作指针q的后继指向工作指针p
	/* find the people ahead of #k */
	//第二部分：寻找起始位置
	q = p;//将工作指针q指向工作指针p 
	while (q->next != p) //直到工作指针q的后继等于工作指针p为止
	{
		if (q->next->data == k)//寻找起始位置k的前驱节点（如果工作指针q找到起始节点）
			break;//退出该循环
		q = q->next;//此时工作指针q指向q的后继节点
	}
	//第三部分：开始Johsph环逻辑
	while (q->next != q) { /* till the last one（直到最后一个为止） */

		/* every m people（到自杀的人m） */
		for (i = 0; i < m - 1; i++)//删除m号节点需要寻找它的前驱(m-1号)节点
		{
			q = q->next;//此时工作指针q指向它的后继节点（此时指向的是被杀的人；找到被杀人）
		}

		/* kill the m-th people （杀掉第m个人）*/
		p = q->next;//找到被杀人的前驱节点（被杀人的节点指向前驱节点）
		q->next = p->next;//被杀人的前驱节点指向被杀人的后继节点
		printf("%-2d was killed\n", p->data);//将此人杀掉
		free(p);//释放被杀人所占节点的空间
	}

	/* kill the last one（杀了最后一个） */
	printf("%-2d was alive\n", q->data);//最后一人作为起始人存活下来
	free(q);//释放最后一人所占节点的空间

	return 0;
}

