/*
 * main.cpp
 *
 *  Created on: 2019年5月14日
 *      Author: gaohan
 */
#include"RB_TREE1.h"
#include<iostream>
using namespace std;


void print(RB_TREE* root)    /////从小到大输出所有的树节点值
{
    RB_TREE_NODE* pmin = root->RB_TREE_MINMUM(root->root);
    RB_TREE_NODE* pmax = root->RB_TREE_MAXMUM(root->root);
    int i = 0;
    while (true)
    {
        if (i++ % 10 == 0)cout << endl;
        cout << pmin->key << " ";
        if (pmin == pmax)break;
        pmin = root->RB_TREE_SUCCESSOR(root, pmin);
    }

    cout <<endl<< endl << "++++++++++++++++++++++++++++++++++++++" << endl;
}
int main()
{
    int a[1000];
    for (int i = 0; i < 1000; i++)
    {
        a[i] = rand() % 100;
    }

    RB_TREE* root = new RB_TREE();
    for (int i = 0; i < 100; i++)
    {
        RB_TREE_NODE* z = new RB_TREE_NODE(a[i]);
        root->RB_TREE_INSERT(root,z);
    }

    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    RB_TREE_NODE* pmin = root->RB_TREE_MINMUM(root->root);
    RB_TREE_NODE* pmax = root->RB_TREE_MAXMUM(root->root);
    print(root);
    cout << endl << endl << "++++++++++++++++++++++++++++++++" << endl;


    vector<RB_TREE_NODE*>result1 = root->RB_SEARCH_ALL(root, 50);
    for (RB_TREE_NODE* temp : result1)
    {
        cout << temp->key << " ";
    }

    vector<RB_TREE_NODE*>result2 = root->RB_SEARCH_ALL(root, 29);
    for (RB_TREE_NODE* temp : result2)
    {
        cout << temp->key << " ";
    }

    vector<RB_TREE_NODE*>result3 = root->RB_SEARCH_ALL(root, 82);
    for (RB_TREE_NODE* temp : result3)
    {
        cout << temp->key << " ";
    }

    cout << endl << "++++++++++++++++++++++++++++++++++++++" << endl;


    for (RB_TREE_NODE* temp : result1)
    {
        if (temp != PNIL)root->RB_TREE_DELETE(root,temp);
    }
    print(root);
    for (RB_TREE_NODE* temp : result2)
    {
        if (temp != PNIL)root->RB_TREE_DELETE(root, temp);
    }
    print(root);
    for (RB_TREE_NODE* temp : result3)
    {
        if (temp != PNIL)root->RB_TREE_DELETE(root, temp);
    }
    print(root);

    /////对应插入的case情况
    cout << endl << number1 << " " << number2 << " " << number3 << " " << number4 << " " << number5 << " " << number6 << endl;
    cout << endl << "====================" << endl;
    cout << root->root->key << " " << root->root->color << endl;

    cout << root->root->left->key << " " << root->root->left->color << endl;
    cout << root->root->right->key << " " << root->root->right->color << endl;

    cout << root->root->left->left->key << " " << root->root->left->left->color << endl;
    cout << root->root->left->right->key << " " << root->root->left->right->color << endl;

    cout << root->root->right->left->key << " " << root->root->right->left->color << endl;
    cout << root->root->right->right->key << " " << root->root->right->right->color << endl;


}



