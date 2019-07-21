#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define EmptyTOS (-1)      //�����ջ��Ҫ 
#define MinStackSize (5)   //�����ջ��Ҫ 
 
 
//��ջ���������� 
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;
 
bool IsEmpty(Stack S);                          //����ջ�Ƿ�Ϊ��
Stack CreateStack();                            //������ջ
void DisposeStack(Stack);                       //�����ջ 
void Push(ElementType X, Stack S);              //Ԫ�ؽ�ջ 
ElementType Pop(Stack S);                       //Ԫ�س�ջ 
void MakeEmpty(Stack S);                        //��ն�ջ�е�Ԫ��
//ElementType Pop(Stack S);                     //Ԫ�س�ջ   (����ʵ��)
bool IsFull(Stack S);                           //����ջ�Ƿ����� ������ʵ����Ҫ�� 
void printStack(Stack S);                       //�����ջ�е�Ԫ�� 
struct Node {               //����ṹ  
	ElementType Element;
	PtrToNode Next;
}; 
 
//struct Node {               //����ṹ  
//	int Capacity;      //����  
//	int TopOfStack:    //ջ�� 
//	ElementType *Array; 
//};
 
 
 
int main()
{
	int number, flag;
	ElementType X;
	Stack S; 
 
	flag = 1;
	
   	printf("|           ��ջ�Ļ���ʹ��           |\n");
    printf("|************************************|\n");	
   	printf("|            1. ������ջ             |\n");	
   	printf("|            2. ���ٶ�ջ             |\n");	
   	printf("|            3. ��ջ                 |\n");	
   	printf("|            4. ��ջ                 |\n");	
   	printf("|            5. ��ӡ��ջԪ��         |\n");	
   	printf("|************************************|\n");
   	
    while (flag) {
    printf("��ѡ���� ��                      \n");
	 	scanf("%d", &number);
		switch(number) {
			case 1 :
				S = CreateStack();
				break; 
			
			case 2 :
				if (S) {
					DisposeStack(S);
				} else 
					printf("��ջ�����ڣ�����\n"); 
				break;
				
			case 3 :
				if (S) {
					printf("��������Ҫ�����Ԫ�أ�");
					scanf("%d", &X);
					Push(X, S); 
				} else
					printf("��ջ�����ڣ�����\n"); 
				break;
				
			case 4 :
				if (S) {
					Pop(S); 
				} else
					printf("��ջ�����ڣ�����\n"); 
				break;
				 
			case 5 :
				if (S) {
					printf("��ջ��Ԫ�����£�");
					printStack(S); 
				} else
					printf("��ջ�����ڣ�����\n"); 
				break; 
				
			default :
				printf("�������н������밴������˳�������\n");
				flag = 0;	
			} 
		}  		
		
   return 0; 
}
 
 
 
//��������
 
bool IsEmpty(Stack S)                             //����ջ�Ƿ�Ϊ�� ������ 
{
	return S->Next == NULL;
}
 
//bool IsEmpty(Stack S)                           //����ջ�Ƿ�Ϊ��  (����)
//{
//	return S->TopOfStack == EmptyTOS;
//}
 
Stack CreateStack()                               //������ջ   ������ 
{
	Stack S;
	
	if (!(S = malloc(sizeof(struct Node))))
		exit(-1);
	S->Next = NULL;
	
	return S;	
 } 
 
// Stack CreateStack(int MaxElements)             //������ջ    (����)
//{
//	Stack S;
//	
//	if (MaxElements < MinStackSize) {
//		printf("��ջ�ռ�̫С�ˣ���");
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
 
 void DisposeStack(Stack S)                       //�����ջ ������ 
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
 		
// void DisposeStack(Stack S)                     //�����ջ    �����飩 
// {
// 	if (S != NULL) {
// 		free(S->Array);
// 		free(S);
//	 }	
// } 		
 
void Push(ElementType X, Stack S)                  //Ԫ�ؽ�ջ    ������ 
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
 
//void Push(ElementType X, Stack S)                 //Ԫ�ؽ�ջ    �����飩 
//{
//	if (!IsFull(S))
//		S->Array[++TopOfStack] = X;
//	else
//		printf("��ջ��������\n");	
//}
 
ElementType Pop(Stack S)                            //Ԫ�س�ջ    ������ 
{
	Stack TmpCell;
	ElementType X;
	
	if (IsEmpty(S)) {
		printf("��ջΪ�գ�����\n");
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
 
//ElementType Pop(Stack S)                          //Ԫ�س�ջ    �����飩 
//{
//	if (!IsEmpty(S))
//		return S->Array[TopOfStack--];
//	else
//		printf("��ջΪ�գ���ջ�쳣������\n");		
//}
 
void MakeEmpty(Stack S)                             //��ն�ջ�е�Ԫ��    ������ 
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
 
//void MakeEmpty(Stack S)                            //��ն�ջ�е�Ԫ��    �����飩 
//{
//	S->TopOfStack == EmptyTOS;
//}
 
//bool IsFull(Stack S)                               //����ջ�Ƿ����� ������ʵ����Ҫ�� 
//{
//	return S->(++TopOfStack) == S->Capacity;
//}
// 
void printStack(Stack S)                             //��ӡ��ջ��Ԫ�� 
{
	ElementType P;
	while (!IsEmpty(S)) {
		P = Pop(S);
		printf("%d  ", P);
	} 
	printf("\n");
}

