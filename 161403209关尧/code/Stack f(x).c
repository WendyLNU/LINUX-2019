/*利用链栈实现计算*/
/* 栈有栈底和栈顶指针，元素是先进后出；对于栈的操作最主要的是创建、压栈、弹栈；在实现计算器时，我们输入的表达式叫做中缀表达式，我们需要将其转为后缀表达式；然后利用后缀表达式求取表达式的值；
创建了两个结构体；LinkList是一个单向链表，保存数据和指向下一个节点的指针（next）；LinkStack是栈，保存着栈顶指针和计数；
链栈是没有头结点的，将第一个节点数据域置位NULL，计数器设为-1；表示栈底； 
压栈与前面介绍链表的博文中增加链表节点的方式有差别；增加节点是把链表指针地址传递给子函数，这里是把指针传递给子函数；然后为节点申请空间，完成节点入栈； 
节点入栈是：节点指针域指向当前的top，然后top指向增加的节点（上移）；完成入栈； 
pop需要判断栈是否为空；完成数据赋值和计数减一，释放节点空间；

中缀表达式转后缀表达式 
2+(1+2)*2-6； 
这是一个中缀表达式；我们对扫描到的表示进行处理，数字输出，符号入栈； njmmmmmmmmmmmmmmmmmmmmm
第一步： 
输出：2 
入栈：+ 
第二步： 
入栈:( 
第四步: 
输出：1、2 
入栈：+ 
第五步： 
当前的总输出是：2、1、2 
栈中的符号是：+（+ 
现在扫描到）；此时需要栈中符号输出直到遇到(; 
所以第五步执行完以后： 
总输出：2 1 2 + 
栈中剩余元素:+ 
第六步： 
栈中+优先级低于* *入栈；2输出； 
总输出：2 1 2 + 2 
栈中符号：+ * 
第七步： 
-号优先级小于* *号出列； 
栈中元素：+ - 
输出：2 1 2 + 2* 
第八步： 
数字6输出； 
输出：2 1 2 + 2 * 6 
第八步： 
栈中所有符号输出得到后缀表达式： 
2 1 2 + 2 * 6 - +
后缀表达式求值 
对后缀表达式扫描：数字入栈 
第一步： 
2 1 2入栈； 
读到 + ：从栈栈中弹出两个元素，data1；data2；data2+data1入栈； 
栈中元素：2 3 
第二步： 
2入栈； 
：从栈中弹出两个元素；data2 *data1；3 2=6入栈； 
栈中元素：2 6 
第三步： 
读到元素6，入栈； 
栈中元素：2 6 6 
读到-：弹栈；data2 - data1；结果入栈 
栈中元素： 2 0 
第四步： 
+号：弹栈 data2 + data1；结果入栈； 
栈中元素 2； 
第五步： 
弹出栈中元素，为运算结果；
*/

#include<stdio.h>
#define OK 0;
#define ERROR -1
typedef int State;
typedef struct LinkList
{
    char operatorAndData;
    struct LinkList *next;
}LinkList,*LinkNode;
typedef struct LinkStact
{
    LinkNode top;
    int count;
}LinkStack;

//创建链栈(栈是一个没有头结点的单链表)
State createStack(LinkStack *S) {
    S->count = -1;
    S->top = NULL;
    return OK;
}
//push
State pushStack(LinkStack *S, char data)//压栈与前面介绍链表的博文中增加链表节点的方式有差别；增加节点是把链表指针地址传递给子函数，这里是把指针传递给子函数；然后为节点申请空间，完成节点入栈； 
 {
    LinkNode s;
    s = (LinkNode)malloc(sizeof(LinkList));
    s->operatorAndData = data;
    s->next = S->top;
    S->top = s;
    S->count++;
    return OK;
}
//pop
State popStack(LinkStack *S,char *data) {
    LinkNode p;
    //判断栈空
    if (S->top == NULL || S->count==-1) {
        return ERROR;
    }
    *data = S->top->operatorAndData;
    p = S->top;
    S->top = S->top->next;
    S->count--;
    free(p);
    return OK;
}
//创建链表用于存储输入表达式
int main() {
    LinkStack infixExpression;
    LinkStack computeStack;
    int i = 0;
    int j = 0;
    char result;
    State state;
    char inExpression[50] = { 0 };
    char postfixExpression[50] = { 0 };
    char postTmp;
    char operatorData1;
    char operatorData2;
    createStack(&infixExpression);
    createStack(&computeStack);
    gets(inExpression);

    //中缀表达式转后缀表达式
    while (inExpression[i]!='\0') {
        if (inExpression[i]<48 || inExpression[i]>57) {
            if (inExpression[i] == 41) {
                if (!(infixExpression.count < 0)) {
                    popStack(&infixExpression, &postTmp);
                    while (postTmp != 40) {
                        postfixExpression[j++] = postTmp;
                        if (!(infixExpression.count < 0))
                            popStack(&infixExpression, &postTmp);
                        else
                            break;
                    }
                }
            }
            else if (inExpression[i] == 43 || inExpression[i] == 45 ) {
                if (!(infixExpression.count < 0)) {
                    popStack(&infixExpression, &postTmp);
                    while (postTmp == 42 || postTmp == 47) {
                        postfixExpression[j++] = postTmp;
                        if (!(infixExpression.count < 0)) {
                            popStack(&infixExpression, &postTmp);
                        }
                        else
                            break;
                    }
                    pushStack(&infixExpression, postTmp);
                }
                pushStack(&infixExpression, inExpression[i]);
            }
            else {
                pushStack(&infixExpression, inExpression[i]);
            }

        }
        else {
            postfixExpression[j++] = inExpression[i];
        }
        i++;
    }
    while (!(infixExpression.count < 0)) {
        popStack(&infixExpression, &postTmp);
        postfixExpression[j++] = postTmp;
    }
    //计算后缀表达式
    i = 0;
    while (i != j) {
        if (postfixExpression[i]<48 || postfixExpression[i]>57) {
            popStack(&computeStack, &operatorData1);
            popStack(&computeStack, &operatorData2);
            if (postfixExpression[i] == 43) {
                postTmp = (operatorData2-48 + operatorData1-48)+48;
                pushStack(&computeStack, postTmp);
            }

            if (postfixExpression[i] == 45) {
                postTmp = (operatorData2 - 48) - 
                    (operatorData1 - 48) + 48;
                pushStack(&computeStack, postTmp);
            }
            if (postfixExpression[i] == 42){
                postTmp = (operatorData2 - 48) *
                    (operatorData1 - 48) + 48;
                pushStack(&computeStack, postTmp);
            }
            if (postfixExpression[i] == 47) {
                postTmp = (operatorData2 - 48) /
                    (operatorData1 - 48) + 48;
                pushStack(&computeStack, postTmp);
            }

        }
        else
            pushStack(&computeStack, postfixExpression[i]);
        i++;
    }
    popStack(&computeStack, &result);
    printf("%c\n", result);
    return OK;
}