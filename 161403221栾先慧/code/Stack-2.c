
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define OPT_ADD 43 /* + */
#define OPT_SUB 45 /* - */
#define OPT_MUL 42 /* * */
#define OPT_DIV 47 /* / */
#define L_BRACK 40 /* ( */
 
typedef struct _stack {
    int data; /* 栈内元素 */
    struct _stack *next;
}Stack; /* 定义栈结构! */
 
/**
* 压栈
* 头插法,将数据压到头结点
**/
bool push_stack(Stack **stack, int data)
{
    Stack *p = (Stack*)malloc(sizeof(Stack));
    if (NULL == p) exit(-1); /* 申请内存都不行,挂了 */
    p->data = data;
    p->next = *stack;
    *stack = p;
    return true;
}
 
/**
* 弹栈
* 头指针就是栈顶
**/
int pop_stack(Stack **stack)
{
    Stack *p = *stack; /* 缓存头指针   */
    if (NULL == p) {/* 栈已经空了   */
    return -1;
    }
    int data = p->data; /* 缓存栈顶数据 */
    *stack = p->next; /* 栈顶移动     */
    free(p);/* 释放内存     */
    return data;
}
 
/**
* 获取栈顶元素
**/
int get_top_stack(Stack *stack)
{
    return stack->data; /* 头指针就是栈顶 */
}
 
/**
* 判断栈空
**/
bool stack_is_empty(Stack *stack)
{
    return NULL == stack; /* 头指针都空了 */
}
 
/**
* 显示所有栈元素
**/
void show_stack(Stack *stack)
{
    while (NULL != stack) {
        printf("%d,", stack->data);
        stack = stack->next; /* 从栈顶依次打印 */
    }
    printf("\n");
}
 
/**
* 计算a和b在mode符号的运算结果 
**/
int cal(int a,int b,int mode)
{
    int re = -1;
    switch(mode) {
    case OPT_ADD:re = a + b;break;
    case OPT_SUB:re = a - b;break;
    case OPT_MUL:re = a * b;break;
    case OPT_DIV:re = a / b;break;
    default:break;
    }
    return re;
}
/**
* 符号优先级判断 
* 返回： 1(opt1>opt2)   -1(opt1<opt2)   0(opt1=opt2) 
* 注意符号的ASSIC码：43(+) 45(-) 42(*) 47(/) 
**/
int opt_max(int opt1,int opt2)
{
    if(OPT_MUL == opt1 || OPT_DIV == opt1) {
        if(OPT_ADD == opt2 || OPT_SUB == opt2) {
        return 1;
        }
     return 0;
    } else {
        if(OPT_MUL == opt2 || OPT_DIV == opt2) {
        return -1;
        }
    return 0;
    }
}
 
/**
* 计算表达式
**/
int calculate(const char *expr)
{
    int num1, num2, opt1, opt2;
    Stack *num = NULL;
    Stack *opt = NULL;
    while ('\0' != *expr) {
        if ('(' == *expr) { /* 左括号 */
            push_stack(&opt, (int)*expr++); /* 压符号栈 */
        } 
        else if (')' == *expr) { /* 右括号 */
            expr++; /* 指针加1 */
            while (true) {
                if (L_BRACK == get_top_stack(opt)) {
                    pop_stack(&opt);
                    break; /* 如果当前栈顶是(则弾栈退出 */
                } 
                else { /* 否则弾两个数字，一个符号进行运算 */
                num2 = pop_stack(&num);
                num1 = pop_stack(&num);
                opt2 = pop_stack(&opt);
                push_stack(&num, cal(num1, num2, opt2));
                }
            }
        } 
        else if ('9' >= *expr && '0' <= *expr) { /* 数字 */
            sscanf(expr, "%d", &num1);
            push_stack(&num, num1);
            num2 = 0; /* 记录num1的长度 */
            while (0 != num1) {num2++; num1 /= 10;}
            expr += num2; /* 指针移动指定长度 */
        } 
        else { /* 加减乘除,这4个符号 */
            opt1 = (int)*expr++;
            while (true) {
                if (stack_is_empty(opt) || L_BRACK == get_top_stack(opt)) {
                    push_stack(&opt, opt1);
                    break;
                } 
                else {
                    opt2 = get_top_stack(opt);
                    if (0 < opt_max(opt1, opt2)) { /* 当前获取的符号优先级大于栈顶符号 */
                        push_stack(&opt, opt1);
                        break;
                    } 
                    else { /* 栈顶优先级高或者平级则 */
                        num2 = pop_stack(&num);
                        num1 = pop_stack(&num);
                        opt2 = pop_stack(&opt);
                        push_stack(&num, cal(num1, num2, opt2));
                    }
                }
            }
        }
    }
    opt1 = get_top_stack(opt);
    if(OPT_MUL == opt1 || OPT_DIV == opt1) {
    num2 = pop_stack(&num);
    num1 = pop_stack(&num);
    opt2 = pop_stack(&opt);
    push_stack(&num, cal(num1, num2, opt2));
    }
    num2 = pop_stack(&num);
    num1 = pop_stack(&num);
    opt2 = pop_stack(&opt);
    free(num);
    free(opt); /* 释放内存 */
    return cal(num1, num2, opt2);
}
 
 
/**
* 主程序
* 放在最下面,避免重复声明函数
* 不可连续乘除
**/
int main(int argc, char *argv[])
{
    char buf[64] = {0};
    scanf("%s", buf);getchar();
    printf("%s=%d\n", buf, calculate(buf));
    return 0;
}