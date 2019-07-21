// B.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

#define MMM 5
#define DEFAULT 333
struct node
{
	int *key;      //关键码数组
	int key_num;      //节点当前的关键码个数
					  //T *data      //数据    is_leaf为0时，则初始化data，为1时不初始化data，只当其占个空间而已
					  //bool is_leaf;      //0-叶节点   1-内部结点
	node *parent;      //父节点
	node **child;      //子节点数组  内部节点时才初始化
	node *next;      //叶节点的后继节点
					 //node *pre;      //叶节点的前驱节点

	node() :key(NULL), key_num(0), parent(NULL), child(NULL), next(NULL)
	{
		key = new int[MMM + 1];
	}
	//~node()      //用类对象来表示节点时，需要析构函数，用来删除对象空间以及堆区
	//{
	//    delete key;
	//    key = NULL;
	//    delete parent;
	//    parent = NULL;
	//    if (child != NULL)
	//    {
	//        for (int i = 0; i < key_num; i++)
	//        {
	//            //delete child[i];
	//            child[i] = NULL;
	//        }
	//        child = NULL;
	//    }
	//    /*else
	//    {
	//        delete data;
	//        data = NULL;
	//    }*/
	//}   
};

class B_plus_tree
{
private:
	node *broot;
	node *bhead;
public:
	B_plus_tree() :broot(new node), bhead(new node)
	{
		bhead = broot;
	}
	~B_plus_tree()
	{
		if (broot != NULL)
		{
			Destory(broot);
		}
		broot = NULL;
		bhead = NULL;
	}

	node* Get_root();      //获取根节点
	node* Search(const int k);      //查找关键码为k的节点
	node* Find(const int k);      //查找关键码为k的节点
	bool Insert(const int k);      //插入关键码
	void Split(node *&root, int pos);      //分裂节点
	bool Remove(const int k);      //删除叶节点中值为k的关键码及其数据
	void Adjust(node *root);      //删除后调整B+树
	void Level_order();      //层序遍历
	void List_order();      //链表遍历
	void Destory(node *root);      //销毁B+树
};

node* B_plus_tree::Get_root()
{
	return broot;
}

node* B_plus_tree::Search(const int k)
{
	if (broot->key_num == 0)
	{
		cout << "B+树为空，查找失败!" << endl;
		return NULL;
	}
	if (broot->key[broot->key_num - 1] < k)
	{
		cout << k << " 不是B+树的关键码!" << endl;
		return NULL;
	}
	node *root = new node;
	if (broot->child != NULL)
	{
		root->child = new node*[MMM + 1];
	}
	root = broot;
	while (root->child != NULL)
	{
		for (int i = 0; i < root->key_num; i++)
		{
			if (root->key[i] >= k)
			{
				root = root->child[i];
				break;
			}
		}
	}
	int low = 0;
	int high = root->key_num - 1;
	int middle;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (root->key[middle] == k)
		{
			cout << k << " 是B+树的关键码!" << endl;
			return root;
		}
		else if (root->key[middle] < k)
		{
			low = middle + 1;
		}
		else
		{
			high = middle - 1;
		}
	}
	cout << k << " 不是B+树的关键码!" << endl;
	return NULL;
}

node* B_plus_tree::Find(const int k)
{
	node *head = bhead;
	while (head != NULL)
	{
		if (head->key[head->key_num - 1] < k)
		{
			head = head->next;
		}
		else
		{
			break;
		}
	}
	if (head == NULL)
	{
		cout << k << " 不是B+树的关键码!" << endl;
		return NULL;
	}
	else
	{
		int low = 0;
		int high = head->key_num - 1;
		int middle;
		while (low <= high)
		{
			middle = (low + high) / 2;
			if (head->key[middle] == k)
			{
				cout << k << " 是B+树的关键码!" << endl;
				return head;
			}
			else if (head->key[middle] < k)
			{
				low = middle + 1;
			}
			else
			{
				high = middle - 1;
			}
		}
		cout << k << " 不是B+树的关键码!" << endl;
		return NULL;
	}

}

bool B_plus_tree::Insert(const int k)
{
	if (Search(k) != NULL)
	{
		cout << k << " 已经是B+树的关键码!" << endl;
		return false;
	}
	if (broot->key_num == 0)
	{
		broot->key_num++;
		bhead = broot;
		bhead->next = NULL;
		broot->key[0] = k;
		return true;
	}
	node *root = new node;
	if (broot->child != NULL)
	{
		root->child = new node*[MMM + 1];
	}
	root = broot;
	int i, j;
	if (root->key[root->key_num - 1] < k)      //比B+树中最大关键码大
	{
		while (root->child != NULL)      //从上至下调整内部节点的某个关键码
		{
			root->key[root->key_num - 1] = k;
			root = root->child[root->key_num - 1];
		}
		root->key[root->key_num] = k;
		root->key_num++;
		if (root->key_num == MMM + 1)
		{
			Split(root, (0 + MMM) / 2);
		}
		return true;
	}
	else      //比B+树中最大关键码小，不用调整，寻找其合适插入位置即可
	{
		while (root->child != NULL)
		{
			for (i = 0; i < root->key_num; i++)
			{
				if (root->key[i] > k)
				{
					root = root->child[i];
					break;
				}
			}
		}
		for (i = 0; i < root->key_num; i++)
		{
			if (root->key[i] > k)
			{
				for (j = root->key_num - 1; j >= i; j--)
				{
					root->key[j + 1] = root->key[j];
				}
				root->key[i] = k;
				root->key_num++;
				break;
			}
		}
		if (root->key_num == MMM + 1)
		{
			Split(root, (0 + MMM) / 2);
		}
		return true;
	}
}

void B_plus_tree::Split(node *&root, int pos)
{
	int i, j;
	node *other = new node;
	for (i = pos + 1; i < root->key_num; i++)      //如果root为叶子节点，则要把数据一起传过去
	{
		other->key[i - pos - 1] = root->key[i];
	}
	other->parent = root->parent;
	if (root->child != NULL)
	{
		other->child = new node*[MMM + 1];
		for (i = 0; i < MMM + 1; i++)
		{
			other->child[i] = NULL;
		}
		for (i = pos + 1; i < root->key_num; i++)
		{
			other->child[i - pos - 1] = root->child[i];
			root->child[i]->parent = other;
			root->child[i] = NULL;
		}
	}
	root->key_num = pos + 1;
	other->key_num = MMM - pos;
	if (root->parent == NULL)
	{
		broot = new node;      //新根节点
		broot->child = new node*[MMM + 1];
		for (i = 0; i < MMM + 1; i++)
		{
			broot->child[i] = NULL;
		}
		broot->key_num += 2;
		broot->parent = NULL;
		broot->child[0] = root;
		broot->key[0] = root->key[root->key_num - 1];
		root->parent = broot;
		broot->child[1] = other;
		broot->key[1] = other->key[other->key_num - 1];
		other->parent = broot;
		if (root->child == NULL)
		{
			root->next = other;
			other->next = NULL;
			bhead = root;
		}
		return;
	}
	else
	{
		node *p = new node;
		p->child = new node*[MMM + 1];
		/*for (i = 0; i < MMM + 1; i++)
		{
		p->child[i] = NULL;
		}*/
		p = root->parent;
		for (i = 0; i < p->key_num; i++)
		{
			if (p->child[i] == root)
			{
				for (j = p->key_num - 1; j > i; j--)
				{
					p->key[j + 1] = p->key[j];
					p->child[j + 1] = p->child[j];      //孩子也要跟着一起移动
				}
				p->key[i] = root->key[root->key_num - 1];
				p->key[i + 1] = other->key[other->key_num - 1];
				p->child[i + 1] = other;
				p->key_num++;
				other->parent = p;
				root->parent = p;
				break;
			}
		}
		if (root->child == NULL)
		{
			other->next = root->next;
			root->next = other;
		}
		if (p->key_num == MMM + 1)
		{
			Split(p, (0 + MMM) / 2);
		}
	}
}

void B_plus_tree::Level_order()
{
	if (broot == 0)
	{
		cout << "B树为空，层序遍历失败!" << endl;
		return;
	}
	node **qu = new node*[DEFAULT];
	int front = 0;
	int rear = 0;
	qu[front] = qu[rear++] = broot;
	int max = DEFAULT;      //假设循环空间足够大，要不然还得判断是不是装满了
	cout << "B树的层序遍历为:{";
	while (front != rear)
	{
		node *p = qu[front];
		front = (front + 1) % max;
		if (p != NULL)
		{
			cout << "[ ";
			for (int i = 0; i < p->key_num; i++)
			{
				cout << p->key[i] << " ";
			}
			cout << "]";
		}
		if (p->child != NULL)
		{
			for (int j = 0; j < p->key_num; j++)
			{
				qu[rear] = p->child[j];
				rear = (rear + 1) % max;
			}
		}
	}
	cout << "}";
}

void B_plus_tree::List_order()
{
	node *head = bhead;
	if (head == NULL)
	{
		cout << "B+树为空，遍历失败!" << endl;
		return;
	}
	else
	{
		cout << "链式遍历为:{";
		while (head != NULL)
		{
			cout << "[ ";
			for (int i = 0; i < head->key_num; i++)
			{
				cout << head->key[i] << " ";
			}
			cout << "]";
			head = head->next;
		}
		cout << "}";
	}
}

bool B_plus_tree::Remove(const int k)
{
	node *root = Search(k);
	if (root == NULL)
	{
		cout << k << " 不是B+的关键码!" << endl;
		return false;
	}
	int low, high, middle;
	low = 0;
	high = root->key_num - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (root->key[middle] == k)
		{
			break;
		}
		else if (root->key[middle] > k)
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}
	int i;
	if (low > high)
	{
		cout << k << " 不是B+的关键码!" << endl;
		return false;
	}
	else
	{
		if (root->key[root->key_num - 1] == k)      //修改内部节点的关键码,删除的关键码为此节点的最大关键码
		{

			if (root->parent != NULL)
			{
				int second = root->key[root->key_num - 2];
				node *curr = new node;
				curr->child = new node*[MMM + 1];
				curr = root->parent;
				while (curr != NULL)
				{
					for (i = curr->key_num - 1; i >= 0; i--)
					{
						if (curr->key[i] == k)
						{
							curr->key[i] = second;
							if (i == curr->key_num - 1)      //如果k依旧是父节点中最大的一个关键码，往上走
							{
								curr = curr->parent;
							}
							else
							{
								curr = NULL;      //如果不是，curr置空，结束循环
							}
							break;
						}
					}
				}
			}
		}
		for (i = middle; i < root->key_num - 1; i++)
		{
			root->key[i] = root->key[i + 1];
		}
		root->key_num--;
		if (root->key_num >= (MMM + 1) / 2)
		{
			return true;
		}
		else
		{
			Adjust(root);
		}
	}
	return true;
}

void B_plus_tree::Adjust(node *root)
{
	if (root->parent == NULL)      //到根节点，不用调整
	{
		return;
	}
	node *p = new node;
	p->child = new node*[MMM + 1];
	p = root->parent;
	int i, index = 0;
	for (i = 0; i < p->key_num; i++)
	{
		if (p->child[i] == root)
		{
			index = i;
			break;
		}
	}
	if (index == 0)
	{
		if (p->child[index + 1] != NULL && p->child[index + 1]->key_num >(MMM + 1) / 2)
		{
			node *right = new node;
			if (root->child != NULL)
			{
				right->child = new node*[MMM + 1];
			}
			right = p->child[index + 1];
			p->key[index] = right->key[0];
			root->key_num++;
			root->key[root->key_num - 1] = right->key[0];
			for (i = 0; i < right->key_num - 1; i++)
			{
				right[i] = right[i + 1];
			}
			if (root->child != NULL)
			{
				root->child[root->key_num - 1] = right->child[0];
				right->child[0]->parent = root;
				for (i = 0; i < right->key_num - 1; i++)
				{
					right->child[i] = right->child[i + 1];
				}
				right->child[right->key_num - 1] = NULL;
			}
			right->key_num--;
			return;
		}
		if (p->child[index + 1] != NULL && p->child[index + 1]->key_num == (MMM + 1) / 2)
		{
			node *right = new node;
			if (root->child != NULL)
			{
				right->child = new node*[MMM + 1];
			}
			right = p->child[index + 1];
			p->key[index] = p->key[index + 1];
			int mmm = root->key_num;
			for (i = 0; i < right->key_num; i++)
			{
				root->key_num++;
				root->key[root->key_num - 1] = right->key[i];
			}
			if (root->child == NULL)
			{
				root->next = right->next;
				right->next = NULL;
			}
			else
			{
				for (i = 0; i < right->key_num; i++)
				{
					mmm++;
					root->child[mmm - 1] = right->child[i];
					right->child[i]->parent = root;
				}
			}
			for (i = index + 1; i < p->key_num - 1; i++)
			{
				p->key[i] = p->key[i + 1];
				p->child[i] = p->child[i + 1];
			}
			p->key_num--;
			if (p == broot && p->key_num == 0)
			{
				p = NULL;
				broot = root;
				broot->parent = NULL;
				return;
			}
			if (p->key_num < (MMM + 1) / 2)
			{
				Adjust(p);
			}
		}
	}
	if (index > 0 && index <= p->key_num - 1)
	{

		if (p->child[index - 1] != NULL && p->child[index - 1]->key_num > (MMM + 1) / 2)
		{
			node *left = new node;
			if (root->child != NULL)
			{
				left->child = new node*[MMM + 1];
			}
			left = p->child[index - 1];
			p->key[index - 1] = left->key[left->key_num - 2];
			for (i = root->key_num - 1; i >= 0; i--)
			{
				root->key[i + 1] = root->key[i];
			}
			root->key[0] = left->key[left->key_num - 1];
			if (root->child != NULL)
			{
				for (i = root->key_num - 1; i >= 0; i--)
				{
					root->child[i + 1] = root->child[i];
				}
				root->child[0] = left->child[left->key_num - 1];
				left->child[left->key_num - 1]->parent = root;
				left->child[left->key_num - 1] = NULL;
			}
			root->key_num++;
			left->key_num--;
			return;
		}
		if (p->child[index - 1] != NULL && p->child[index - 1]->key_num == (MMM + 1) / 2)
		{
			node *left = new node;
			if (root->child != NULL)
			{
				left->child = new node*[MMM + 1];
			}
			left = p->child[index - 1];
			p->key[index - 1] = p->key[index];
			int mmm = left->key_num;
			for (i = 0; i < root->key_num; i++)
			{
				left->key_num++;
				left->key[left->key_num - 1] = root->key[i];
			}
			if (root->child == NULL)
			{
				left->next = root->next;
				root->next = NULL;
			}
			else
			{
				for (i = 0; i < root->key_num; i++)
				{
					mmm++;
					left->child[mmm - 1] = root->child[i];
					root->child[i]->parent = left;
				}
			}
			for (i = index; i < p->key_num - 1; i++)
			{
				p->key[i] = p->key[i + 1];
				p->child[i] = p->child[i + 1];
			}
			p->key_num--;
			if (p == broot && p->key_num == 0)
			{
				p = NULL;
				broot = root;
				broot->parent = NULL;
				return;
			}
			if (p->key_num < (MMM + 1) / 2)
			{
				Adjust(p);
			}
		}
	}
}

void B_plus_tree::Destory(node *root)
{
	if (broot == NULL)
	{
		cout << "B+树为空，销毁失败!" << endl;
		return;
	}
	if (root->child != NULL)      //删除节点
	{
		for (int i = 0; i < root->key_num; i++)
		{
			Destory(root->child[i]);
		}
		if (root->parent == NULL)      //删除叶子节点
		{
			while (bhead->next == NULL)
			{
				node *head = bhead;
				bhead = bhead->next;
				delete head;
			}
			bhead = NULL;
			broot = NULL;
		}
		delete root;      //删除内部结点
		root = NULL;
	}
	else
	{
		return;
	}
}

void main()
{
	B_plus_tree tree;
	//int arr[27] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 };
	int arr[27] = { 27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1 };
	//int arr[11] = { 22,44,33,55,11,77,66,99,88,10 };
	for (int i = 0; i < 27; i++)
	{
		tree.Insert(arr[i]);
	}
	tree.Level_order();
	cout << endl;
	tree.List_order();
	cout << endl;
	tree.Search(23);
	tree.Find(23);
	tree.Insert(28);
	tree.Level_order();
	cout << endl;
	tree.List_order();
	cout << endl;
	tree.Remove(18);
	tree.Level_order();
	cout << endl;
	tree.List_order();
	cout << endl;
	tree.Remove(9);
	tree.Level_order();
	cout << endl;
	tree.List_order();
	cout << endl;
	tree.Destory(tree.Get_root());
	tree.Level_order();
	tree.List_order();



	int a;

	cin >> a; //为了查看结果
}
