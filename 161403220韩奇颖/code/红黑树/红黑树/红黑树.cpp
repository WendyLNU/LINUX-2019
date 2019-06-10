// 红黑树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS 1

#include "RBTree.h"

void Test()
{
	int a[9] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	RBTree<int, int> brt;

	for (int i = 0; i < 9; i++)
	{
		brt.Insret(a[i], i);
	}

	brt.InOrder();
	cout << "IsRBTree?" << brt.IsRBTree() << endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}
