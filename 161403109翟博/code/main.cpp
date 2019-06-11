

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<Windows.h>
#define STACK_SIZE 6
void Empty(struct Stack *temp);/*����һ����ջ�ĸ�������*/
struct Stack *CreateStack(void);/*����һ����ջ*/
int IsEmpty(struct Stack *S);/*����ջ�Ƿ�Ϊ��*/
void Push( struct Stack*sp);    /*��ջ����*/
int Top(struct Stack*temp); /*����ջ��Ԫ��*/
void Pop(struct Stack*temp);    /*��ջ����Ԫ��*/
void Rebuild(struct Stack *p);  /*�ͷ�ջ�ռ�*/
void Print();               /*�˵���ӡ*/
void Exit();                /*�˳�*/

struct Stack {                  /*ջ������*/
    int Element;
    struct Stack *next;
};
struct Stack *stack = NULL;
int main(void) {
    char ch = '\0';
    while (1) {
        system("cls");
        fflush(stdin);
        Print();
        scanf(" %c",&ch);
        switch (ch) {
        case'a':
            stack=CreateStack();
            break;
        case'b':
            Push(stack);
            break;
        case'c':
            Top(stack);
            break;
        case'd':
            Pop(stack);
            break;
        case'e':
            Rebuild(stack);
            break;
        case'f':
            Exit();
            break;
        default:
            printf("�޴�ѡ����!\n");
            system("pause");
            break;
        }
    }
    return 0;
}

void Rebuild(struct Stack *p) {
    if (p==NULL) {
        printf("Must use CreateStack first!");
        return;
    }
    struct Stack *temp = NULL;
    struct Stack *tt = NULL;
    temp = p;
    p->next = NULL;
    while (temp != NULL) {
        tt = temp->next;
        free(temp);
        temp = tt;
    }
    puts("Rebuild!\n");
    system("pause");
}
void Exit() {   /*����������˳�*/
    int i = 0;
    printf("�˳���");
    for (i = 4; i > 0; --i) {
        Sleep(200);
        printf(".");
    }
    exit(0);
}
void Print()
{
    printf("-----���˵���������:\n");
    printf("-----a.����һ��ջ\n");
    printf("-----b.Push��ջ\n");
    printf("-----c.Top����ջ��Ԫ��\n");
    printf("-----d.Pop��ջ\n");
    printf("-----e.�ͷ�ջ�ռ�\n");
    printf("-----f.�˳�\n");
}


int IsEmpty(struct Stack *S) {
    return S->next == NULL?1:0;
}

struct Stack *CreateStack(void){
    struct Stack *temp=NULL;
    struct Stack *current = NULL;
    struct Stack *last = NULL;
    int size = STACK_SIZE;
    int a = 0;
    temp = (struct Stack*)malloc(sizeof(struct Stack));
    while (size-- > 0)
    {
        current = (struct Stack*)malloc(sizeof(struct Stack));
        if (temp == NULL)
            temp = current;
        if (last != NULL)
            last->next = current;

        current->next = NULL;
        last = current;
    }
    puts("Created!");
    return (temp);
}

void Empty(struct Stack *temp) {
    if (temp == NULL) {
        printf("Must use CreateStack first!");
        return;
    }
    else
        temp->next = NULL;
}

void Push( struct Stack*sp)
{
    int x=0;
    struct Stack *temp = NULL;
    temp = (struct Stack*)malloc(sizeof(struct Stack));
    if (temp == NULL) {
        printf( "out of space!");
    }
    else {
        printf("Please enter a Element x!\n");
        scanf("%d",&x);
        temp->Element = x;
        temp->next = sp->next;
        sp->next = temp;
    }
}

int Top(struct Stack*temp) {
    if (!IsEmpty(temp))
        return temp->next->Element;
    printf( "Empty stack");
    return 0;
}

void Pop(struct Stack*temp) {
    struct Stack *first = NULL;
    if(IsEmpty(temp))
        printf("Empty stack");
    else
    {
        first = temp->next;
        temp->next = temp->next->next;
        free(first);
    }
}


