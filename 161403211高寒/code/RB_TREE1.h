/*
 * RB_TREE1.h
 *
 *  Created on: 2019年5月14日
 *      Author: gaohan
 */
#ifndef RB_TREE_H
#define RB_TREE_H

#include<vector>
const int BLACK = -1;
const int RED = 1;


static int number1 = 0;
static int number2 = 0;
static int number3 = 0;
static int number4 = 0;
static int number5 = 0;
static int number6 = 0;


struct RB_TREE_NODE{

public:
    RB_TREE_NODE(int a)
    {
        key = a;
        color = BLACK;
        p =0;
        left = 0;
        right = 0;
    }
    ~RB_TREE_NODE()
    {
    }
    int key;
    int color;
    RB_TREE_NODE* p;
    RB_TREE_NODE* left;
    RB_TREE_NODE* right;

};

static RB_TREE_NODE NIL = { 0 };
#define PNIL (&NIL)

struct RB_TREE
{
    RB_TREE()
    {
        root->left = PNIL;
        root->right = PNIL;
        root->p = PNIL;
    }
    RB_TREE_NODE* root=PNIL;

    ////插入节点z
    void RB_TREE_INSERT(RB_TREE* root, RB_TREE_NODE* z);
    ///插入节点z后对该树进行调整，使之重新满足红黑树的条件
    void RB_TREE_INSERT_FIXUP(RB_TREE*root, RB_TREE_NODE* z);

    ////删除节点z
    void RB_TREE_DELETE(RB_TREE* root, RB_TREE_NODE* z);
    ///删除节点z后对该树进行调整，使该树重新满足红黑树的条件
    void RB_TREE_DELETE_FIXUP(RB_TREE* root, RB_TREE_NODE*z);


    ///x的前驱,否则返回nullptr
    RB_TREE_NODE*  RB_TREE_PREDECESSOR(RB_TREE* root, RB_TREE_NODE* x);
    ///x的后驱，否则返回nullptr
    RB_TREE_NODE*  RB_TREE_SUCCESSOR(RB_TREE* root, RB_TREE_NODE* x);


    ///以x为根的树中最小值
    RB_TREE_NODE* RB_TREE_MINMUM(RB_TREE_NODE* x);
    ///以x为根的树中的最大值
    RB_TREE_NODE* RB_TREE_MAXMUM(RB_TREE_NODE* x);


    ///对x节点进行左旋转
    void RB_LEFT_ROTATE(RB_TREE* root, RB_TREE_NODE* x);
    ///对x节点进行右旋转
    void RB_RIGHT_ROTATE(RB_TREE*root, RB_TREE_NODE* x);


    ///用以节点v为根的树替换以节点u为根的树
    void RB_TRANSPLANT(RB_TREE* root, RB_TREE_NODE* u, RB_TREE_NODE*v);
    ///搜索节点值为value的节点，并返回，搜索不到返回PNIL
    RB_TREE_NODE* RB_SEARCH(RB_TREE* root, int value);

    ////搜索所有节点值为value的节点并返回
    std::vector<RB_TREE_NODE*> RB_SEARCH_ALL(RB_TREE* root, int value);
};


void RB_TREE::RB_TREE_INSERT(RB_TREE* root, RB_TREE_NODE* z)
{
    z->left = PNIL;    ////哨兵并非空节点，new 出的RB_TREE_NODE的左右孩子为空节点不是哨兵，所以插入前，先将左右孩子置为哨兵
    z->right = PNIL;
    RB_TREE_NODE* x = RB_TREE::root;
    RB_TREE_NODE* y=PNIL;
    while (x != PNIL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if (y == PNIL)root->root = z;
    else if (z->key < y->key)y->left = z;
    else y->right = z;
    z->color = RED;
    RB_TREE_INSERT_FIXUP(root, z);
}

void RB_TREE::RB_TREE_INSERT_FIXUP(RB_TREE* root, RB_TREE_NODE*z)
{
    while (z->p->color == RED&&z->p != PNIL)
    {
        if (z->p->p->left == z->p)
        {
            RB_TREE_NODE* y = z->p->p->right;
            if (y->color == RED)
            {
                number1++;
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                number2++;
                if (z == z->p->right)
                {
                    number3++;
                    z = z->p;
                    RB_LEFT_ROTATE(root, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RB_RIGHT_ROTATE(root, z->p->p);
            }
        }
        else
        {
            RB_TREE_NODE* y = z->p->p->left;
            if (y->color == RED)
            {
                number4++;
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                number5++;
                if (z == z->p->left)
                {
                    number6++;
                    z = z->p;
                    RB_RIGHT_ROTATE(root, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RB_LEFT_ROTATE(root, z->p->p);
            }
        }
    }
    root->root->color = BLACK;
}

void RB_TREE::RB_LEFT_ROTATE(RB_TREE* root, RB_TREE_NODE* x)
{
    RB_TREE_NODE* y = x->right;
    x->right = y->left;
    if (y->left!=PNIL)
    y->left->p = x;
    y->p = x->p;
    if (x->p == PNIL)root->root = y;
    else if (x->p->left ==x)x->p->left = y;
    else x->p->right = y;
    x->p = y;
    y->left = x;
}

void RB_TREE::RB_RIGHT_ROTATE(RB_TREE*root, RB_TREE_NODE* x)
{
    RB_TREE_NODE* y = x->left;
    x->left = y->right;
    if (y->right != PNIL)
        y->right->p = x;
    y->p = x->p;
    if (x->p == PNIL)root->root = y;
    else if (x->p->left == x) x->p->left = y;
    else x->p->right = y;
    x->p = y;
    y->right = x;
}

RB_TREE_NODE*  RB_TREE::RB_TREE_PREDECESSOR(RB_TREE* root, RB_TREE_NODE* x)
{
    if (x == RB_TREE_MINMUM(root->root))return x;
    if (x->left != PNIL)return RB_TREE_MAXMUM(x->left);
    RB_TREE_NODE* y = x->p;
    while (y != PNIL&&x == y->left)
    {
        x = y;
        y = y->p;
    }
    return y;
}

RB_TREE_NODE*  RB_TREE::RB_TREE_SUCCESSOR(RB_TREE* root, RB_TREE_NODE* x)
{
    if (x == RB_TREE_MAXMUM(root->root))return x;
    if (x->right != PNIL)return RB_TREE_MINMUM(x->right);
    RB_TREE_NODE* y = x->p;
    while (y != PNIL&&x == y->right)
    {
        x = y;
        y = y->p;
    }
    return y;
}

RB_TREE_NODE* RB_TREE::RB_TREE_MINMUM(RB_TREE_NODE* x)
{
    while (x->left != PNIL)
        x = x->left;
    return x;
}

RB_TREE_NODE* RB_TREE::RB_TREE_MAXMUM(RB_TREE_NODE* x)
{
    while (x->right != PNIL)
        x = x->right;
    return x;
}

void RB_TREE::RB_TRANSPLANT(RB_TREE* root, RB_TREE_NODE* u, RB_TREE_NODE* v)
{
    if (u->p == PNIL)root->root = v;
    else if (u == u->p->left)u->p->left=v;
    else u->p->right = v;
    if (v!=PNIL)
    v->p = u->p;
}

RB_TREE_NODE* RB_TREE::RB_SEARCH(RB_TREE* root, int value)
{
    //  此为删除第一个值为value的节点
    RB_TREE_NODE* temp = root->root;
    while (temp != PNIL&&temp->key != value)
    {
        if (value < temp->key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    return temp;
}

std::vector<RB_TREE_NODE*> RB_TREE::RB_SEARCH_ALL(RB_TREE* root, int value)
{
    std::vector<RB_TREE_NODE*>result;

    RB_TREE_NODE* temp = root->root;
    while (temp != PNIL&&temp->key != value)
    {
        if (value < temp->key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }
    result.push_back(temp);
    RB_TREE_NODE* temp2 = temp;
    while(temp != PNIL)            /////寻找temp的前驱值相等的
    {
        RB_TREE_NODE* t1 = RB_TREE_PREDECESSOR(root, temp);
        if (t1!=PNIL&&t1->key == temp->key)
            result.push_back(t1);
        else break;
        temp = t1;
    }

    temp = temp2;
    while (temp!=PNIL)          ////寻找temp的后驱值相等的
    {
        RB_TREE_NODE* t1 = RB_TREE_SUCCESSOR(root, temp);
        if (t1!=PNIL&&t1->key==temp->key)
          result.push_back(t1);
        else break;
        temp = t1;
    }
    return result;
}

void RB_TREE::RB_TREE_DELETE(RB_TREE* root, RB_TREE_NODE* z)
{
    RB_TREE_NODE* y = z;
    RB_TREE_NODE* x;
    int origin_color = y->color;

    if (z->left == PNIL)
    {
        x = z->right;
        RB_TRANSPLANT(root, z, z->right);
    }
    else if (z->right == PNIL)
    {
        x = z->left;
        RB_TRANSPLANT(root, z, z->left);
    }
    else
    {
        y = RB_TREE_MINMUM(z->right);
        origin_color = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;   ////防止y的子节点都是哨兵，进行删除调整时，需要找到x的父节点，而哨兵没有父节点。
        }
        else
        {
            RB_TRANSPLANT(root, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RB_TRANSPLANT(root, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;

        z->p = nullptr;      ///////删除节点z时，对父节点，子节点指针置为空，只删除节点z的区域
        z->right = nullptr;
        z->left = nullptr;
        delete z;
    }
    if (origin_color == BLACK)
    {
        RB_TREE_DELETE_FIXUP(root, x);
    }
}

void RB_TREE:: RB_TREE_DELETE_FIXUP(RB_TREE* root, RB_TREE_NODE*z)
{
    while (z != root->root&&z->color == BLACK)
    {
        if (z == z->p->left)
        {
            RB_TREE_NODE* y = z->p->right;
            if (y->color == RED)   /////case1
            {
                y->color = BLACK;
                z->p->color = RED;
                RB_LEFT_ROTATE(root, z->p);
                y = z->p->right;   ////转到case2，3，4中的一种
            }
            if (y->left->color == BLACK&&y->right->color == BLACK)
            {
                y->color = RED;    ////case2
                z = z->p;
            }
            else
            {
                if (y->right->color == BLACK)
                {
                    y->left->color = BLACK;
                    y->color = RED;
                    RB_RIGHT_ROTATE(root, y);   ////case3 转到case4
                    y = z->p->right;
                }
                y->color = z->p->color;
                z->p->color = BLACK;          ////case4;
                y->right->color = BLACK;
                RB_LEFT_ROTATE(root, z->p);
                z = root->root;
            }
        }
        else             ////与以上left和right互换
        {
            RB_TREE_NODE* y = z->p->left;
            if (y->color == RED)
            {
                y->color = BLACK;
                z->p->color = RED;
                RB_RIGHT_ROTATE(root, z->p);
                y = z->p->left;
            }
            if (y->right->color == BLACK&&y->left->color == BLACK)
            {
                y->color = RED;
                z = z->p;
            }
            else
            {
                if (y->left->color == BLACK)
                {
                    y->right->color = BLACK;
                    y->color = RED;
                    RB_LEFT_ROTATE(root, y);
                    y = z->p->left;
                }
                y->color = z->p->color;
                z->p->color = BLACK;
                y->left->color = BLACK;
                RB_RIGHT_ROTATE(root, z->p);
                z = root->root;
            }
        }
    }
    z->color = BLACK;
}
#endif
