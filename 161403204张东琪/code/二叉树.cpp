#include<iostream>
#include<stdlib.h>
#include<malloc.h>
 
using namespace std;
 
typedef struct BinaryTreeNode{
    char value;
    struct  BinaryTreeNode *left;
     struct BinaryTreeNode *right;
};
 
void CreateBinaryTree(BinaryTreeNode * &T)
{
 
    char data;
    cin>>data;
    if(data=='#')
        T=NULL;
    else 
    {
         T=new BinaryTreeNode;
         T->value=data;
 
         CreateBinaryTree(T->left);
         CreateBinaryTree(T->right);
    }
}
 
 
BinaryTreeNode * CreateBinaryTree2()
{
    BinaryTreeNode *T;
 
    char data;
    cin>>data;
 
    if(data=='#')
        T=NULL;
    else
    {
        T=new BinaryTreeNode;
        T->value=data;
 
        T->left=CreateBinaryTree2();
        T->right=CreateBinaryTree2();
    }
 
    return T;
}
 
void PreorderTree(BinaryTreeNode *T)
{
    if(T==NULL)
        return;
    cout<<T->value<<" ";
    PreorderTree(T->left);
    PreorderTree(T->right);
}
void InorderTree(BinaryTreeNode *T)
{
    if(T==NULL)
        return;
    InorderTree(T->left);
    cout<<T->value<<" ";
    InorderTree(T->right);
}
 
void PostorderTree(BinaryTreeNode *T)
{
    if(T==NULL)
        return;
    PostorderTree(T->left);
    PostorderTree(T->right);
    cout<<T->value<<" ";
}
 
 
void main()
{
 
    cout<<"---先序创建二叉树的第一种方法 输入序列为 A B C # # # D # #---------- "<<endl;
    cout<<"请输入先序创建二叉树序列,以'#'号表示该节点为NULL，序列如上所示："<<endl;
 
    BinaryTreeNode *T;
    CreateBinaryTree(T);
    cout<<"方法1的先序序列为：";
    PreorderTree(T);
    cout<<endl;
 
    cout<<"方法1的中序序列为：";
    InorderTree(T);
    cout<<endl;
 
    cout<<"方法1的后序序列为：";
    InorderTree(T);
    cout<<endl;
 
    cout<<"-----先序创建二叉树的第一种方法 输入序列为 A B C # # # D # #-------- "<<endl;
    cout<<"请输入先序创建二叉树序列，以'#'号表示该节点为NULL，序列如上所示："<<endl;
 
    BinaryTreeNode *T1;
    T1=CreateBinaryTree2();
 
    cout<<"方法2的先序序列为：";
    PreorderTree(T1);
    cout<<endl;
 
        cout<<"方法2的中序序列为：";
    InorderTree(T1);
    cout<<endl;
 
    cout<<"方法2的后序序列为：";
    InorderTree(T1);
    cout<<endl;
}
