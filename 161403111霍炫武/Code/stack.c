#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EmptyTOS (-1)      //数组堆栈需要
#define MinStackSize (5)   //数组堆栈需要


//堆栈函数的声明
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;

bool IsEmpty(Stack S);                          //检测堆栈是否为空
Stack CreateStack();                            //创建堆栈
void DisposeStack(Stack);                       //毁灭堆栈
void Push(ElementType X, Stack S);              //元素进栈
ElementType Pop(Stack S);                       //元素出栈
void MakeEmpty(Stack S);                        //清空堆栈中的元素
//ElementType Pop(Stack S);                     //元素出栈   (数组实现)
bool IsFull(Stack S);                           //检测堆栈是否已满 （数组实现需要）
void printStack(Stack S);                       //输出堆栈中的元素
struct Node {               //链表结构
	ElementType Element;
	PtrToNode Next;
};

//struct Node {               //数组结构
//	int Capacity;      //容量
//	int TopOfStack:    //栈顶
//	ElementType *Array;
//};



int main()
{
	int number, flag;
	ElementType X;
	Stack S;

	flag = 1;

   	printf("|           堆栈的基本使用           |\n");
    printf("|************************************|\n");
   	printf("|            1. 创建堆栈             |\n");
   	printf("|            2. 销毁堆栈             |\n");
   	printf("|            3. 入栈                 |\n");
   	printf("|            4. 出栈                 |\n");
   	printf("|            5. 打印堆栈元素         |\n");
   	printf("|************************************|\n");

    while (flag) {
    printf("请选择功能 ：                      \n");
	 	scanf("%d", &number);
		switch(number) {
			case 1 :
				S = CreateStack();
				break;

			case 2 :
				if (S) {
					DisposeStack(S);
				} else
					printf("堆栈不存在！！！\n");
				break;

			case 3 :
				if (S) {
					printf("请输入需要插入的元素：");
					scanf("%d", &X);
					Push(X, S);
				} else
					printf("堆栈不存在！！！\n");
				break;

			case 4 :
				if (S) {
					Pop(S);
				} else
					printf("堆栈不存在！！！\n");
				break;

			case 5 :
				if (S) {
					printf("堆栈中元素如下：");
					printStack(S);
				} else
					printf("堆栈不存在！！！\n");
				break;

			default :
				printf("程序运行结束，请按任意键退出！！！\n");
				flag = 0;
			}
		}

   return 0;
}



//函数定义

bool IsEmpty(Stack S)                             //检测堆栈是否为空 （链表）
{
	return S->Next == NULL;
}

//bool IsEmpty(Stack S)                           //检测堆栈是否为空  (数组)
//{
//	return S->TopOfStack == EmptyTOS;
//}

Stack CreateStack()                               //创建堆栈   （链表）
{
	Stack S;

	if (!(S = malloc(sizeof(struct Node))))
		exit(-1);
	S->Next = NULL;

	return S;
 }

// Stack CreateStack(int MaxElements)             //创建堆栈    (数组)
//{
//	Stack S;
//
//	if (MaxElements < MinStackSize) {
//		printf("堆栈空间太小了！！");
//		return -1;
//	}
//
//	if (!(S = malloc(sizeof(struct Node))))
//		exit(-1);
//	if (!(S->Array = malloc(sizeof((ElementType) * MaxStackSize))))
//		exit(-1);
//	S->Capacity = MaxStackSize;
//
//	return S;
// }

 void DisposeStack(Stack S)                       //毁灭堆栈 （链表）
 {
 	PtrToNode P, TmpCell;

 	P = S->Next;
 	S->Next = NULL;
	while (P) {
 		TmpCell = P->Next;
 		free(P);
 		P = TmpCell;
 	}

 	free(S);
 }

// void DisposeStack(Stack S)                     //毁灭堆栈    （数组）
// {
// 	if (S != NULL) {
// 		free(S->Array);
// 		free(S);
//	 }
// }

void Push(ElementType X, Stack S)                  //元素进栈    （链表）
{
	PtrToNode TmpCell;

	if (!(TmpCell = malloc(sizeof(struct Node))))
		exit(-1);
	else {
		TmpCell->Element = X;
		TmpCell->Next = NULL;
	}

	TmpCell->Next = S->Next;
	S->Next = TmpCell;
}

//void Push(ElementType X, Stack S)                 //元素进栈    （数组）
//{
//	if (!IsFull(S))
//		S->Array[++TopOfStack] = X;
//	else
//		printf("堆栈已满！！\n");
//}

ElementType Pop(Stack S)                            //元素出栈    （链表）
{
	Stack TmpCell;
	ElementType X;

	if (IsEmpty(S)) {
		printf("堆栈为空！！！\n");
		return -1;
	}
	else {
		TmpCell = S->Next;
		S->Next = TmpCell->Next;
		X = TmpCell->Element;
		free(TmpCell);

		return X;
	}
}

//ElementType Pop(Stack S)                          //元素出栈    （数组）
//{
//	if (!IsEmpty(S))
//		return S->Array[TopOfStack--];
//	else
//		printf("堆栈为空，出栈异常！！！\n");
//}

void MakeEmpty(Stack S)                             //清空堆栈中的元素    （链表）
{
	PtrToNode P, TmpCell;

	P = S->Next;
	S->Next = NULL;
	while (P) {
		TmpCell = P->Next;
		free(P);
		P = TmpCell;
	}
}

//void MakeEmpty(Stack S)                            //清空堆栈中的元素    （数组）
//{
//	S->TopOfStack == EmptyTOS;
//}

//bool IsFull(Stack S)                               //检测堆栈是否已满 （数组实现需要）
//{
//	return S->(++TopOfStack) == S->Capacity;
//}
//
void printStack(Stack S)                             //打印堆栈中元素
{
	ElementType P;
	while (!IsEmpty(S)) {
		P = Pop(S);
		printf("%d  ", P);
	}
	printf("\n");
}

