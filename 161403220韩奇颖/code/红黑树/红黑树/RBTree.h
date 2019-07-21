#pragma once

#include <iostream>
using namespace std;
#include <stdlib.h>

enum COLOR { RED, BLACK };

template <class K, class V>
struct RBTreeNode
{
	RBTreeNode(const K& key, const V& value)
		:_pLeftChild(NULL)
		, _pRightChild(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)
	{}

	RBTreeNode<K, V>* _pLeftChild;
	RBTreeNode<K, V>* _pRightChild;
	RBTreeNode<K, V>* _pParent;
	K _key;
	V _value;
	COLOR _color;
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
	typedef RBTreeNode<K, V>* pNode;
public:

	RBTree()
		:_pRoot(NULL)
	{}

	void InOrder()
	{
		_InOrder(_pRoot);
	}
	//插入
	bool Insret(const K& key, const V& value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value);
			_pRoot->_color = BLACK;
			return true;
		}
		pNode parent = NULL;
		pNode cur = _pRoot;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_pLeftChild;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_pRightChild;
			}
			else
				return false;
		}
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_pRightChild = cur;
			cur->_pParent = parent;
		}
		else
		{
			parent->_pLeftChild = cur;
			cur->_pParent = parent;
		}
		//父节点存在且为红
		while (parent&&parent->_color == RED)
		{
			//祖父节点
			pNode grandfather = parent->_pParent;
			//父节点是祖父节点的左孩子
			if (parent == grandfather->_pLeftChild)
			{
				//叔叔节点
				pNode uncle = grandfather->_pRightChild;
				if (uncle&&uncle->_color == RED)
				{
					//情况三 叔叔节点存在且为红，将叔叔节点和双亲节点的颜色改为黑色，祖父节点改为红色
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;

					//将祖父节点当做cur继续向上调整
					grandfather = cur;
					parent = cur->_pParent;
				}
				//情况四和五 叔叔节点不存在或者叔叔节点为黑色
				else
				{
					//四、parent为grandfather的左孩子，cur为parent的右孩子
					if (cur = parent->_pRightChild)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					//parent为grantfather的左孩子，cur为parent的左孩子
					RotateR(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;

					break;
				}
			}
			//parent为grantfather的右孩子
			else if (parent == grandfather->_pRightChild)
			{
				pNode uncle = grandfather->_pLeftChild;
				if (uncle&&uncle->_color == RED)
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grandfather->_color = RED;

					grandfather = cur;
					parent = cur->_pParent;
				}
				else
				{
					if (cur = parent->_pLeftChild)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfather);
					parent->_color = BLACK;
					grandfather->_color = RED;

					break;
				}
			}
		}
		_pRoot->_color = BLACK;
		return true;
	}

	//判断是否为红黑树
	bool IsRBTree()
	{
		if (_pRoot == NULL)
			return true;
		if (_pRoot&&_pRoot->_color == RED)
			return false;
		//求一条路径(最左路径)黑色节点的个数，作为基准值
		int blacknum = 0;
		pNode left = _pRoot;
		while (left)
		{
			if (left->_color == BLACK)
				blacknum++;
			left = left->_pLeftChild;
		}
		int num = 0;
		return _IsRBTree(_pRoot, num, blacknum);
	}

	bool _IsRBTree(pNode pRoot, int num, const int blacknum)
	{
		if (pRoot == NULL)
			return true;
		if (pRoot->_color == RED&&pRoot->_pParent->_color == RED)
		{
			cout << "存在连续的红节点：" << pRoot->_key << endl;
			return false;
		}

		if (pRoot->_color == BLACK)
			num++;
		if (pRoot->_pLeftChild == NULL&&pRoot->_pRightChild == NULL)
		{
			if (blacknum != num)
			{
				cout << "每条路径上的黑色节点不全部相等" << endl;
				return false;
			}
		}

		return _IsRBTree(pRoot->_pLeftChild, num, blacknum)
			&& _IsRBTree(pRoot->_pRightChild, num, blacknum);
	}


private:

	void _InOrder(pNode pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeftChild);
			cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
			_InOrder(pRoot->_pRightChild);
		}
	}
	void RotateL(pNode parent)
	{
		pNode SubR = parent->_pRightChild;
		pNode SubRL = SubR->_pLeftChild;

		parent->_pRightChild = SubRL;
		if (SubRL)
			SubRL->_pParent = parent;

		SubR->_pLeftChild = parent;
		pNode pparent = parent->_pParent;
		SubR->_pParent = pparent;
		parent->_pParent = SubR;

		if (parent == _pRoot)
		{
			_pRoot = SubR;
		}
		else
		{
			if (pparent->_pLeftChild == parent)
				pparent->_pLeftChild = SubR;
			else
				pparent->_pRightChild = SubR;
		}
	}

	void RotateR(pNode parent)
	{
		pNode SubL = parent->_pLeftChild;
		pNode SubLR = SubL->_pRightChild;

		parent->_pLeftChild = SubLR;
		if (SubLR)
			SubLR->_pParent = parent;

		SubL->_pRightChild = parent;
		pNode pparent = parent->_pParent;
		parent->_pParent = SubL;
		SubL->_pParent = pparent;

		if (parent == _pRoot)
		{
			_pRoot = SubL;
		}
		else
		{
			if (pparent->_pLeftChild == parent)
				pparent->_pLeftChild = SubL;
			else
				pparent->_pRightChild = SubL;
		}
	}

	bool _IsRBTree(pNode pRoot)
	{
		if (pRoot == NULL)
			return true;

	}
private:
	pNode _pRoot;
};