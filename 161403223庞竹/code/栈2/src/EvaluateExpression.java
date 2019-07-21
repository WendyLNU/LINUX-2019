import java.io.IOException;
import java.util.Scanner;
import java.util.Stack;

/**
 * 表达式求值 算符优先法
 * 3*(5-2)#  #在这里表示结尾
 *
 * 思路：
 * 使用两个栈，分别是操作数栈 存储数字 和操作符栈 存储运算符
 * 读入表达式时
 * 如果是操作数 则入操作数栈
 * 如果是运算符 则入操作符栈
 * 当运算符入栈时，和操作符栈栈顶元素比较优先级
 * 如果优先级比栈顶元素高，则入栈,并接收下一个字符
 * 如果和栈顶元素相同，则脱括号 并接收下一个字符 （ 因为相同只有( )括号）
 * 如果小于栈顶元素优先级，则操作数出栈，操作符出栈 并计算运算结果再入栈
 *
 * 关键点：循环的退出条件 直到运算全部结束，即当前栈顶元素和读入的操作符均为#
 *
 * 例子：
 * 3*(5-2)#
 *
 * 算符优先级：
 * + -按顺序先后，先来优先级大于后来的，即从左到右依次计算
 * * / 优先级大于+ - ， 与* /比较则 先来的优先级大于后来的
 * + - * / 优先级均大于(  小于)
 */
public class EvaluateExpression {

    private static Stack<Character> stackOPR = new Stack<>(); //操作符栈
    private static Stack<Integer> stackOPN = new Stack<>();//操作数栈

    public static void main(String[] args) throws IOException {
    	System.out.println("请输入计算式（以#结尾）：");
        char c = (char) System.in.read();
        stackOPR.push('#');
        while (c != '#' ||  stackOPR.peek() != '#') {
            if (isOPN(c)) { //判断是否是操作数
                //是 则入操作数栈 ，读入下一个
                stackOPN.push(c-48); //asc码 '0'转为int是48  A是65 a是97
                c = (char) System.in.read();
            } else {
                switch (isPrior(c)) {
                    case '>':  //优先级比栈顶元素大 ，则入栈,并接收下一个字符
                        stackOPR.push(c);
                        c = (char) System.in.read();
                        break;
                    case '='://优先级和栈顶元素相同
                        stackOPR.pop(); //脱去括号
                        c = (char) System.in.read();
                        break;
                    case '<': //优先级比栈顶元素小，则操作数出栈，操作符出栈，运算之后入栈。即意思是优先级高的先运算
                        int b = stackOPN.pop();//顺序靠后的操作数
                        int a = stackOPN.pop();//顺序靠前的操作数
                        stackOPN.push(Option(a, b, stackOPR.pop()));
                        break;
                }
            }
        }
        System.out.println("计算结果为:"+stackOPN.pop());
    }

    //返回和栈顶元素优先级的比较结果，> 表示优先级大于栈顶元素 <  表示优先级小于栈顶元素 =表示优先级相等
    static char isPrior(Character c) {
        char c2 = stackOPR.peek();
        if (c == '+' || c == '-') { //c为后进入的操作符，c2为之前进入的操作符
            //如果同为+ - 则c2的优先级大于c  同理 * /就更不用说了
            if (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/') {  //所以和栈顶元素相比 优先级要小
                return '<';
            }
            if (c2 == '(') {
                return '>';
            }
            if (c2 == ')') {
                return '<';
            }
            if (c2 == '#') {
                return '>'; //#是定义为预算结束的标志符 比所有的操作符优先级都小
            }
        }
        if (c == '*' || c == '/') {
            if (c2 == '+' || c2 == '-') {
                return '>';
            }

            if (c2 == '*' || c2 == '/') {
                return '<';
            }
            if (c2 == '(') {
                return '>';
            }
            if (c2 == ')') {
                return '<';
            }
            if (c2 == '#') {
                return '>';
            }
        }


        if (c == '(') {
            return '>';
        }
        if (c == ')') {
            if (c2 != '(') {
                return '<';
            } else {
                return '=';
            }
        }

        if (c == '#') {
            if (c2 != '#') {
                return '<';
            } else {
                return '=';
            }
        }
        return 0;
    }


    static int Option(int a, int b, Character c) {
        switch (c) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
        }
        return 0;
    }

    static boolean isOPN(char c) {
        if (c == '+' || c == '-' || c == '*' || c == '/'||c=='('||c==')'||c=='#') {
            return false;
        } else {
            return true;
        }
    }

}
