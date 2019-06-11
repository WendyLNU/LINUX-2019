#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

///宏定义
#define ElemType int
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//堆结构体，以小根堆为基准
typedef struct HeapNode
{
	int verb;
	struct HeapNode *left;
	struct HeapNode *right;
}HeapNode,*Heap;

//堆的插入
void insertHeap(int v,Heap &L)
{
	if(!L)
	{
		L=new HeapNode;
		L->verb=v;
		L->left=NULL;
		L->right=NULL;
		return;
	}
	if(!(L->left)) insertHeap(v,L->left);
	else if(!(L->right)) 
	{
		insertHeap(v,L->right);
		if(L->left->verb>v)
		{
			int t=L->left->verb;
			L->left->verb=v;
			L->right->verb=t;
		}
	}
	else if(v<L->verb) insertHeap(v,L->left);
	else insertHeap(v,L->right);
	if(L->left->verb<L->verb)
	{
		int t=L->left->verb;
		L->left->verb=L->verb;
		L->verb=t;
	}
}

//堆的调整
void initHeap(Heap &L)
{
	if(!(L->left)||!(L->right)) return; 
	if(L->left->verb>L->right->verb)
	{
		Heap tp=L->left;
		L->left=L->right;
		L->right=tp;
	}
	if(L->left) initHeap(L->left);
	else return;
	if(L->verb>L->left->verb)
	{
		int t=L->verb;
		L->verb=L->left->verb;
		L->left->verb=t;
	}
}

//堆的删除
void deleteHeap(Heap &L)
{
	if(!(L->left)) 
	{
		if(!(L->right))
		{
			L=NULL;
			return;
		}
		L=L->right;
		return;
	}
	L->verb=L->left->verb;
	deleteHeap(L->left);
	if(L->right&&L->verb>L->right->verb)
	{
		insertHeap(L->verb,L->right);
		L=L->right;
	}
}

//BFS输出二叉堆树形图
void bfs(Heap L)
{
	queue<Heap> q,tq;
	bool sign=false;
	Heap mp;
	q.push(L);
	while(!q.empty())	
	{
		sign=false;
		while(!q.empty()) 
		{
			tq.push(q.front());
			if(q.front()->verb!=-1) sign=true;
			q.pop();
		}
		if(!sign) break;
		while(!tq.empty())
		{
			Heap tp=tq.front();
			if(tp->verb!=-1) printf("%d ",tp->verb);
			else printf("空 ");
			if(tp->left) q.push(tp->left);
			else 
			{
				mp=new HeapNode;
				mp->verb=-1;
				mp->left=mp->right=NULL;
				q.push(mp);
			}
			if(tp->right) q.push(tp->right);
			else 
			{
				mp=new HeapNode;
				mp->verb=-1;
				mp->left=mp->right=NULL;
				q.push(mp);
			}
			tq.pop();
		}
		printf("\n");
	}
}

int main()
{
	int num;
	Heap root=NULL;
	cout<<"请输入整数个数：";
	cin>>num;
	int a[100];
	cout<<"请依次按顺序输入整数数据，每个数据一行，注意输入数据不能有误。"<<endl;
	for(int i=0;i<num;i++)
	{
		scanf("%d",&a[i]);
		insertHeap(a[i],root);
	}
	initHeap(root);
	cout<<"树形图如下："<<endl;
	bfs(root);
	cout<<"按照小根堆从小到大排序为：";
	while(root)
	{
		printf("%d ",root->verb);
		initHeap(root);
		deleteHeap(root);
	}
	printf("\n");
	getchar();getchar();
	return 0;
}
