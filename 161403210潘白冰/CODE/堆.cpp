#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

///�궨��
#define ElemType int
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//�ѽṹ�壬��С����Ϊ��׼
typedef struct HeapNode
{
	int verb;
	struct HeapNode *left;
	struct HeapNode *right;
}HeapNode,*Heap;

//�ѵĲ���
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

//�ѵĵ���
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

//�ѵ�ɾ��
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

//BFS������������ͼ
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
			else printf("�� ");
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
	cout<<"����������������";
	cin>>num;
	int a[100];
	cout<<"�����ΰ�˳�������������ݣ�ÿ������һ�У�ע���������ݲ�������"<<endl;
	for(int i=0;i<num;i++)
	{
		scanf("%d",&a[i]);
		insertHeap(a[i],root);
	}
	initHeap(root);
	cout<<"����ͼ���£�"<<endl;
	bfs(root);
	cout<<"����С���Ѵ�С��������Ϊ��";
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
