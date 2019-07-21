// B.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
using namespace std;

#define MMM 5
#define DEFAULT 333
struct node
{
	int *key;      //�ؼ�������
	int key_num;      //�ڵ㵱ǰ�Ĺؼ������
					  //T *data      //����    is_leafΪ0ʱ�����ʼ��data��Ϊ1ʱ����ʼ��data��ֻ����ռ���ռ����
					  //bool is_leaf;      //0-Ҷ�ڵ�   1-�ڲ����
	node *parent;      //���ڵ�
	node **child;      //�ӽڵ�����  �ڲ��ڵ�ʱ�ų�ʼ��
	node *next;      //Ҷ�ڵ�ĺ�̽ڵ�
					 //node *pre;      //Ҷ�ڵ��ǰ���ڵ�

	node() :key(NULL), key_num(0), parent(NULL), child(NULL), next(NULL)
	{
		key = new int[MMM + 1];
	}
	//~node()      //�����������ʾ�ڵ�ʱ����Ҫ��������������ɾ������ռ��Լ�����
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

	node* Get_root();      //��ȡ���ڵ�
	node* Search(const int k);      //���ҹؼ���Ϊk�Ľڵ�
	node* Find(const int k);      //���ҹؼ���Ϊk�Ľڵ�
	bool Insert(const int k);      //����ؼ���
	void Split(node *&root, int pos);      //���ѽڵ�
	bool Remove(const int k);      //ɾ��Ҷ�ڵ���ֵΪk�Ĺؼ��뼰������
	void Adjust(node *root);      //ɾ�������B+��
	void Level_order();      //�������
	void List_order();      //�������
	void Destory(node *root);      //����B+��
};

node* B_plus_tree::Get_root()
{
	return broot;
}

node* B_plus_tree::Search(const int k)
{
	if (broot->key_num == 0)
	{
		cout << "B+��Ϊ�գ�����ʧ��!" << endl;
		return NULL;
	}
	if (broot->key[broot->key_num - 1] < k)
	{
		cout << k << " ����B+���Ĺؼ���!" << endl;
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
			cout << k << " ��B+���Ĺؼ���!" << endl;
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
	cout << k << " ����B+���Ĺؼ���!" << endl;
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
		cout << k << " ����B+���Ĺؼ���!" << endl;
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
				cout << k << " ��B+���Ĺؼ���!" << endl;
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
		cout << k << " ����B+���Ĺؼ���!" << endl;
		return NULL;
	}

}

bool B_plus_tree::Insert(const int k)
{
	if (Search(k) != NULL)
	{
		cout << k << " �Ѿ���B+���Ĺؼ���!" << endl;
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
	if (root->key[root->key_num - 1] < k)      //��B+�������ؼ����
	{
		while (root->child != NULL)      //�������µ����ڲ��ڵ��ĳ���ؼ���
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
	else      //��B+�������ؼ���С�����õ�����Ѱ������ʲ���λ�ü���
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
	for (i = pos + 1; i < root->key_num; i++)      //���rootΪҶ�ӽڵ㣬��Ҫ������һ�𴫹�ȥ
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
		broot = new node;      //�¸��ڵ�
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
					p->child[j + 1] = p->child[j];      //����ҲҪ����һ���ƶ�
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
		cout << "B��Ϊ�գ��������ʧ��!" << endl;
		return;
	}
	node **qu = new node*[DEFAULT];
	int front = 0;
	int rear = 0;
	qu[front] = qu[rear++] = broot;
	int max = DEFAULT;      //����ѭ���ռ��㹻��Ҫ��Ȼ�����ж��ǲ���װ����
	cout << "B���Ĳ������Ϊ:{";
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
		cout << "B+��Ϊ�գ�����ʧ��!" << endl;
		return;
	}
	else
	{
		cout << "��ʽ����Ϊ:{";
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
		cout << k << " ����B+�Ĺؼ���!" << endl;
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
		cout << k << " ����B+�Ĺؼ���!" << endl;
		return false;
	}
	else
	{
		if (root->key[root->key_num - 1] == k)      //�޸��ڲ��ڵ�Ĺؼ���,ɾ���Ĺؼ���Ϊ�˽ڵ�����ؼ���
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
							if (i == curr->key_num - 1)      //���k�����Ǹ��ڵ�������һ���ؼ��룬������
							{
								curr = curr->parent;
							}
							else
							{
								curr = NULL;      //������ǣ�curr�ÿգ�����ѭ��
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
	if (root->parent == NULL)      //�����ڵ㣬���õ���
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
		cout << "B+��Ϊ�գ�����ʧ��!" << endl;
		return;
	}
	if (root->child != NULL)      //ɾ���ڵ�
	{
		for (int i = 0; i < root->key_num; i++)
		{
			Destory(root->child[i]);
		}
		if (root->parent == NULL)      //ɾ��Ҷ�ӽڵ�
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
		delete root;      //ɾ���ڲ����
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

	cin >> a; //Ϊ�˲鿴���
}
