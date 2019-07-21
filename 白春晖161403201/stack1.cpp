#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Elementtype;    //    定义数据类型

//    定义节点
typedef struct Node {
	Elementtype Element;
	struct Node* Next;
}NODE, * PNODE;

//    定义栈结构体
typedef struct Stack {
	PNODE PTOP;        //    定义栈顶节点
	PNODE PBOTTOM;        //    定义栈底节点
}STACK, * PSTACK;

//    函数声明
void InitStack(PSTACK Stack);        //    初始化栈
void PushStack(PSTACK Stack, int val);        //    入栈函数
void PopStack(PSTACK Stack, int* val);        //    出栈函数
void TraverseStack(PSTACK Stack);        //    遍历栈函数
bool IsEmpty(PSTACK Stack);        //    判断栈是否为空函数
void ClearStack(PSTACK Stack);        //    清空栈函数void sum(PSTACK Stack) {
void sum(PSTACK Stack);


//    主函数
int j = 1;
int main() {
	STACK Stack;    //    创建一个栈变量
	int val = 0;    //    定义一个变量
	InitStack(&Stack);        //    调用初始化栈函数
	int i = 10;
	while (i != 0)
	{
		printf("1.入栈操作\n2.出栈操作\n3.遍历栈\n4.判断是否为空\n5.清空栈\n6.求和\n0.退出\n");
		scanf_s("%d", &i);
		switch(i) {
		 case 1:
			printf("输入要入栈的数字");
			int k;
			scanf_s("%d", &k);
			PushStack(&Stack, k);
			break;
		case 2:
			PopStack(&Stack, &j);
			if (j != 1) {
				printf_s("%d", j);
			}
			break;
		case 3:
			TraverseStack(&Stack);
			break;
		case 4:
			IsEmpty(&Stack);
			break;
		case 5:
			ClearStack(&Stack);
			break;
		case 6:
			sum(&Stack);
			break;
		}
	}
	return 0;
}

//    定义初始化栈函数
void InitStack(PSTACK Stack) {
	PNODE PNew = (PNODE)malloc(sizeof(NODE));    //    新建一个节点
	if (PNew == NULL) {        //    判断内存是否分配成功
		printf("新节点空间分配失败！\n");
		exit(-1);
	}
	Stack->PTOP = PNew;        //    栈顶指针指向新节点
	Stack->PBOTTOM = PNew;        //    栈底指针指向新节点
	PNew->Next = NULL;        //    新节点指针指向为空
	printf("栈创建成功！\n");

}

//    定义入栈函数
//    从栈顶插入数值val
void PushStack(PSTACK Stack, int val) {
	PNODE P = (PNODE)malloc(sizeof(NODE));    //    创建新的节点用于存放变量
	if (P == NULL) {
		printf("分配空间内存失败！");
		exit(-1);
	}
	P->Element = val;    //    变量赋值给节点的数据域
	P->Next = Stack->PTOP;    //    让新建的节点指向上一个节点
	Stack->PTOP = P;        //    更新顶部节点，使其指向新建的节点
	printf("%d 入栈成功！\n", val);
}

//    定义出栈函数
//    从栈顶弹出，并将地址赋值给变量val
void PopStack(PSTACK Stack, int* val) {
	if (Stack->PBOTTOM == Stack->PTOP) {    //    判断栈是否为空
		printf("出栈失败，栈为空！\n");
		return;
	}
	PNODE P = Stack->PTOP;    //    建立一个临时节点指向栈顶节点
	*val = P->Element;    //    把栈顶节点元素弹出，地址放到变量val中
	Stack->PTOP = P->Next;    //    把栈顶指针指向上一个栈节点
	free(P);    //    释放节点内存，防止内存空间泄漏
	P = NULL;    //    防止产生野指针
	printf("已将%d从栈弹出！\n", *val);
}

//    定义判断栈是否为空函数
bool IsEmpty(PSTACK Stack) {
	if (Stack->PBOTTOM == Stack->PTOP)
	{
		printf("栈为空！\n");
		return true;
	}
	else
	{
		printf("栈不为空\n");
		return false;
	}

}

//    定义栈的遍历函数
void TraverseStack(PSTACK Stack) {
	if (IsEmpty(Stack)) {        //    判断栈是否为空
		printf("遍历栈失败，栈为空！");
		exit(-1);
	}
	PNODE P = Stack->PTOP;        //    建立一个临时节点指针，初始化时指向栈顶
									//使临时节点指针从栈顶开始遍历栈，直到栈底
	printf("遍历栈的结果为： ");
	while (P != Stack->PBOTTOM) {
		printf("%d ", P->Element);    //    打印出数据
		P = P->Next;
	}
	printf("\n");

}

//    定义栈的清空函数

void ClearStack(PSTACK Stack) {
	if (IsEmpty(Stack)) {        //    判断栈是否为空
		printf("栈已经为空，无需清空！\n");
		return;
	}
	//    创建两个节点指针用来释放栈
	PNODE P = Stack->PTOP;
	PNODE Q = NULL;
	//    清空栈
	while (P != Stack->PBOTTOM) {
		Q = P->Next;
		free(P);
		P = Q;
	}
	Stack->PTOP = Stack->PBOTTOM;    //    栈顶指向栈底指向的初始空节点
	printf("已清空栈！\n");
}
void sum(PSTACK Stack) {
	int sum = 0;
	if (IsEmpty(Stack)) {        //    判断栈是否为空
		printf("遍历栈失败，栈为空！");
		return;
	}
	PNODE P = Stack->PTOP; 
	while (P != Stack->PBOTTOM) {
		sum = sum + P->Element;   //    打印出数据
		P = P->Next;
	}
	printf("链表中的和为：%d", sum);
}