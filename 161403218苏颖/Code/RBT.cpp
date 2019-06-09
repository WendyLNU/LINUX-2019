#include<stdio.h>
#include<stdlib.h>
typedef int type;
typedef enum Color   //定义红黑树结点颜色颜色类型  
{
	red = 0,
	black = 1
}Color;
typedef struct rbtree     //定义红黑树的结构
{
	Color color;
	type key;
	struct rbtree *left;
	struct rbtree *right;
	struct rbtree *parent;

}node, *tree;

node *nil = NULL;                        //创建一个哨兵结点。这里要用哨兵去让空的叶子结点的颜色是black的，参照红黑树的定义

node* create(type key, node *left, node *right, node *parent)                       //创建结点
{
	node *p;
	p = (node*)malloc(sizeof(node));
	p->color = black;                                                        //默认颜色为black
	p->left = left;
	p->right = right;
	p->parent = parent;
	p->key = key;
	/*	printf("创造结点完毕");*/
	return p;

}

void left_rotate(tree &t, node *x)                                 //左旋，这个看图就能理解具体操作
{
	node *y = x->right;
	x->right = y->left;
	if (y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		t = y;
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

}

void right_rotate(tree &t, node *x)                   //右旋
{
	node *y = x->left;
	x->left = y->right;
	if (y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nil)
		t = y;                             //
	else
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->right = x;
	x->parent = y;
}


node* search(tree &t, type key)                        //查找元素
{
	node *x = t;
	if (x == nil || x->key == key)
	{

		return t;
	}

	if (key < x->key)
	{
		
		return search(x->left, key);
	}
	else

	{
	
		return search(x->right, key);

	}


}                                                                  //递归查找

void rb_insert_fixup(tree &t, node* z)
{
	node *y;
	while ((z->parent != nil) && (z->parent->color == red))                                //only when z's parent is red there will probably obey the red node has two black nodes
	{
		if (z->parent == z->parent->parent->left)                //z'parent is the left node
		{

			y = z->parent->parent->right;                         //let y be z's uncle node
			if (y->color == red)                                  //parent and uncle and itself are all red
			{
				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;                              //let z up to its grandpa
			}
			else
			{
				if (z == z->parent->right)                         // z is a right node
				{
					z = z->parent;
					left_rotate(t, z);

				}
				z->parent->color = black;
				z->parent->parent->color = red;
				right_rotate(t, z->parent->parent);
			}

		}
		else                                                     //z's parent is the right node
		{
			y = z->parent->parent->left;
			if (y->color == red)
			{

				z->parent->color = black;
				y->color = black;
				z->parent->parent->color = red;
				z = z->parent->parent;
			}

			else
			{
	            if (z == z->parent->left)                         // z is a left node
				{
					z = z->parent;
					right_rotate(t, z);
				}
				z->parent->color = black;
				z->parent->parent->color = red;
				left_rotate(t, z->parent->parent);
			}
		}

	}

	t->color = black;                                   //始终保持根节点是黑色
}


node* rb_insert(tree &t, node *z)                        //插入操作
{
	if (t == NULL)                                                  //t是空的树
	{
		t = (tree)malloc(sizeof(node));
		nil = (node*)malloc(sizeof(node));                       //初始化哨兵结点
		nil->color = black;          
		t->left = nil;
		t->right = nil;
		t->parent = nil;
		t->key = z->key;
		t->color = black;         
	}

	else
	{
		node *y = nil;
		node *x = t;                             //


		while (x != nil)
		{
			y = x;
			if (z->key < x->key)
				x = x->left;
			else
				x = x->right;

		}
		z->parent = y;
		if (y == nil)
			t = z;                                  
		else
		{
			if (z->key < y->key)
				y->left = z;
			else
				y->right = z;
		}
		z->left = nil;
		z->right = nil;
		z->color = red;                                     //始终保持插入的结点是红色，不符合具体性质了再用fixup调整
		rb_insert_fixup(t, z);
	}
	return t;
}
node* rb_insert_(tree &t, type k)                  
{
	node *z;
	z = create(k, NULL, NULL, NULL);
	return  rb_insert(t, z);
}


node* min(tree &m)                     //最小值
{

	node *n = m;

	if (n == nil)
		return nil;

	while (n->left != nil)
	{
		n = n->left;
	}
	return n;
}

node* successor(node *s)           //后继
{
	node *p;
	if (s->right != nil)             //结点右子树非空
	{
		return  min(s->right);
	}
	else
	{
		 p = s->parent;                //结点是左孩子，后继就是他的父节点
		while (p != nil && p->right == s)
		{                                       //结点是右孩子，向上查找，直到遇到一个有左孩子的父节点，那就是后继
			{
				s = p;
				p = p->parent;
			}
		}
		return p;
	}
	
}



void rb_delete_fixup(tree &t, node *x)
{
	node *w;
	while (x != t && x->color == black)                      //
	{
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == red)
			{
				w->color = black;
				x->parent->color = red;
				left_rotate(t, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == black && w->right->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else if (w->right->color == black)
			{
				w->left->color = black;
				w->color = red;
				right_rotate(t, w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = black;
			w->right->color = black;
			left_rotate(t, x->parent);
			x = t;                                        //

		}
		else
		{
			w = x->parent->left;
			if (w->color = red)
			{
				w->color = black;
				x->parent->color = red;
				right_rotate(t, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == black && w->right->color == black)
			{
				w->color = red;
				x = x->parent;
			}
			else if (w->left->color == black)
			{
				w->right->color = black;
				w->color = red;
				left_rotate(t, w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = black;
			w->left->color= black;
			right_rotate(t, x->parent);
			x = t;                                            //

		}
	}
	x->color = black;
}

node* rb_delete(tree &t, node *z)
{
node *y, *x;
    node *m=nil;
	node* n = z;
	if (z->left == nil || z->right == nil)
		y = z;
	else
		y = successor(n);                                  //这一行使z的右孩子发生变化
	if (y->left != nil)
		x = y->left;
	else
		x = y->right;
	x->parent = y->parent;
	if (y->parent == nil)
		t = x;                            //
	else
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	if (y != z)
	{
		z->key = (y->key);
		
	}
	if (y->color == black)
		rb_delete_fixup(t, x);
	return t;
}

node* rb_delete_(tree &t, type k)
{
	node *z;
	z = search(t, k);

	if (z != nil)
	{
		t = rb_delete(t, z);
	}
	else
		printf("无此元素");
	return t;
}


void print_tree(tree &t)                        //中序遍历打印
{
	if (t != nil && t != NULL)
	{
		print_tree(t->left);
		printf("%7d ,   %5d\n ", t->key, t->color);
		print_tree(t->right);
	}
}

int main()
{
	int i;
	tree zz = NULL, mm = NULL, nn = NULL, xx = NULL, yy = NULL;
	type k;
	int a[12] = {3,12,15,17,19,55,20,18,36,48,31,29 };
	printf("\n原来的数字是：----------------------------------------\n");
	for (i = 0; i<12; i++)
	{
		printf("%d  ", a[i]);
		zz = rb_insert_(zz, a[i]);
	}

	printf("\n中序遍历是：-------------------------------------------\n");
	printf("规定：red=0,black=1\n");
	print_tree(zz);
	printf("\n要删除的值是：---------------------------------------");
	scanf("%d", &k);
	yy = rb_delete_(zz, k);
	print_tree(yy);
	printf("\n要插入的值是：--------------------------------------");
	scanf("%d", &k);
	rb_insert_(zz, k);
	print_tree(zz);
}

