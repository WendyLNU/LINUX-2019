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
 
    cout<<"---���򴴽��������ĵ�һ�ַ��� ��������Ϊ A B C # # # D # #---------- "<<endl;
    cout<<"���������򴴽�����������,��'#'�ű�ʾ�ýڵ�ΪNULL������������ʾ��"<<endl;
 
    BinaryTreeNode *T;
    CreateBinaryTree(T);
    cout<<"����1����������Ϊ��";
    PreorderTree(T);
    cout<<endl;
 
    cout<<"����1����������Ϊ��";
    InorderTree(T);
    cout<<endl;
 
    cout<<"����1�ĺ�������Ϊ��";
    InorderTree(T);
    cout<<endl;
 
    cout<<"-----���򴴽��������ĵ�һ�ַ��� ��������Ϊ A B C # # # D # #-------- "<<endl;
    cout<<"���������򴴽����������У���'#'�ű�ʾ�ýڵ�ΪNULL������������ʾ��"<<endl;
 
    BinaryTreeNode *T1;
    T1=CreateBinaryTree2();
 
    cout<<"����2����������Ϊ��";
    PreorderTree(T1);
    cout<<endl;
 
        cout<<"����2����������Ϊ��";
    InorderTree(T1);
    cout<<endl;
 
    cout<<"����2�ĺ�������Ϊ��";
    InorderTree(T1);
    cout<<endl;
}
