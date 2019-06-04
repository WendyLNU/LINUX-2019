#include <iostream>
#include <cstring>
// 用栈来处理一般的中缀计算表达式
// 这里 只实现了 最基本的 + - * /  
using namespace std; 
int campareToChar(char ch){// 判断字符的优先级 
    switch(ch){
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2; // * / 的优先级高 
        default: return -1; 
    } 
}  
double createToNum(char stack[], int len);// 将转换的后缀表达式计算出来 

int main(int argc, char** argv) {
    char cinStr[1000] = {'\0'};         // 存储输入进来的字符串 
    char stackS1[1000] = {'\0'};        // 保存后缀表达式  
    char tempS2[1000] = {'\0'};         // 临时保存运算符  
    int topS1 = 0;
    int topS2 = 0;
    double num[1000];
    cout << "输入要计算的式子: " << endl; 
    cin >> cinStr;  // 输入字符串 

    int i = 0;
    while(cinStr[i] != '\0'){                       // 转换成后缀表达式 
        if(cinStr[i] == '('){                       // 遇到左括号直接进到后缀表达式
            tempS2[topS2++] = cinStr[i]; 
        }else if(cinStr[i] == ')'){                 // 遇到右括号就开始查找左括号 
            while(tempS2[topS2 - 1] != '('){
                stackS1[topS1++] = tempS2[--topS2]; // 将 所有'('前的 运算符全部弹出到后缀表达式
            } 
            topS2--;                                // 丢弃'(' 
        }else if(cinStr[i] >= '0' && cinStr[i] <= '9' || cinStr[i] == '.'){// 数字和 . 直接进到后缀表达式
            stackS1[topS1++] = cinStr[i];
        }else{                                      // 处理运算符 
            stackS1[topS1++] = ' ';
            if(topS2 == 0){                         // 如果栈里面没有运算符符 
                tempS2[topS2++] = cinStr[i]; 
            }else{                                  // 如果有
                                                    // 将比自己优先级高或相同的运算符弹出到后缀表达式 
                if(campareToChar(tempS2[topS2 - 1]) >= campareToChar(cinStr[i])){
                    while(topS2 >0 && campareToChar(tempS2[topS2 - 1]) >= campareToChar(cinStr[i])){
                        stackS1[topS1++] = tempS2[--topS2]; 
                    }
                } 
                tempS2[topS2++] = cinStr[i];        // 将字符压如栈 
            } 
        }     
        i++;
    } 
    while(topS2-- > 0){// 最后将栈里面的剩余的运算符弹出到后缀表达式 
        stackS1[topS1++] = tempS2[topS2];
    }
    double temp = createToNum(stackS1, topS1); // 计算 
    cout << "cinStr(输入的中缀表达式) = " << cinStr << endl; 
    cout << "stackS1(后缀表达式)      =  " << stackS1 << endl; // 打印结果 
    cout << "计算出来的值为           = " << temp << endl; 
    return 0;
}
double createToNum(char stack[], int len){// 将转换的后缀表达式计算出来 
    double num[1000] = {0};
    int numTop = 0;
    int i = 0; 
    while(i <= len){
        if(stack[i] <= '9' && stack[i] >= '0'){
            double x = 0;   // 记录数字 
            int k  = 0;     // 记录小数位数 
            while(stack[i] <= '9' && stack[i] >= '0') {// 处理整数部分 
                x = x * 10 + stack[i++] - '0'; 
            }
            if(stack[i] == '.'){// 处理小数部分 
                i++; // 跳过小数点 
                while(stack[i] <= '9' && stack[i] >= '0') {// 处理整数部分 
                    x = x * 10 + stack[i++] - '0'; 
                    k++;// 小数位数增加 
                }
                while(k-- > 0){// 转换成小数 
                    x = x / 10; 
                }
            } 
            num[numTop++] = x;// 记录数字 
            i--; 
        } else{// 运算符 + - * / 
            switch(stack[i]){
                case '+':num[numTop - 2] = num[numTop - 2] + num[numTop - 1]; 
                    numTop--; // 因为两个数运算生成一个 所以 数字减少一个 
                    break; 
                case '-':num[numTop - 2] = num[numTop - 2] - num[numTop - 1];
                    numTop--; 
                    break; 
                case '*':num[numTop - 2] = num[numTop - 2] * num[numTop - 1];
                    numTop--; 
                    break; 
                case '/':num[numTop - 2] = num[numTop - 2] / num[numTop - 1];
                    numTop--; 
                    break; 
                default: // 防止空格干扰  
                    break;
            }
        }						
        i++;// 继续下一个 
    }
    return num[0]; // 计算好的结果 存在第一个 
}

