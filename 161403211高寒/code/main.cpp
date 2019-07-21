/*
 * main.cpp
 *
 *  Created on: 2019年5月13日
 *      Author: gaohan
 */
#include <iostream>
#include <cstdlib>

using namespace std;

#include "BTree.h"

int main(){
    BTree<int> btree(3);
    int init[]={1,3,5,7,4,2,8,0,6,9,29,13,25,11,32,55,34,22,76,45
        ,14,26,33,88,87,92,44,54,23,12,21,99,19,27,57,18,72,124,158,234
    ,187,218,382,122,111,222,333,872,123};
    for (int i=0; i<49; i++){
        btree.Insert(init[i]);

    }

    btree.Print();
    cout << endl << endl << endl;

    Triple<int> result = btree.Search(13);
    cout << result.m_pfind->GetKey(result.m_nfind) << endl;
    cout << endl << endl << endl;

    for (int i=0; i<49; i++){
        btree.Remove(init[i]);

        btree.Print();
        cout << endl << endl << endl;

    }

    return 0;
}




