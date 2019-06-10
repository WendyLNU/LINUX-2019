package stack1;

import java.util.Collections;
import java.util.HashMap;
import java.util.Stack;
 
public class StackUse {
 
	/**
	 * 栈的典型应用 其一：平衡符号 括号的匹配 利用堆栈来处理，符合条件就弹出，否则push进去
	 */
	public static boolean isValid(String s) {
		HashMap<Character, Character> map = new HashMap<Character, Character>();
		map.put('(', ')');
		map.put('[', ']');
		map.put('{', '}');
 
		java.util.Stack<Character> stack = new java.util.Stack<Character>();
 
		for (int i = 0; i < s.length(); i++) {
			char curr = s.charAt(i);
 
			if (map.keySet().contains(curr)) {
				stack.push(curr);
			} else if (map.values().contains(curr)) {
				if (!stack.empty() && map.get(stack.peek()) == curr) {
					stack.pop(); // 如果满足条件，stack最上面的字符弹出
				} else {
					return false; // 否则返回错误
				}
			}
		}
 
		// 当所有的字符都处理完毕之后，判断当前的stack是否为空。
		// 如果为空，则说明所有都匹配，那么返回true
		// 如果不为空，则说明有不匹配的点，返回false
		return stack.empty();
	}
 
	/**
	 * 栈的典型应用 其二：将表达式转换成为后缀式栈 转换的规则是： 1、将符号放入符号栈中，将元素输出
	 * 2、若符号栈中顶部的元素的优先级小于下一个读入的符号的优先级，则下一个符号进栈
	 * 3、若符号栈中顶部的元素的优先级大于下一个读入的符号的优先级，则将符号栈中的符号弹出，直到遇见小于这个读入符号优先级的符号 然后这个读入符号进栈
	 * 4、对于右括号")"，它具有最高的优先级，直到遇见"("左括号，将这两个符号同时扔掉，继续向下读取
	 * 
	 * @param expression
	 */
	// 运用运算符ASCII码-40做索引的运算符优先级，依次是（ ） ＊ ＋ ， － . / 八个字符 规定八个字符的优先级顺序
	private int[] operatPriority = new int[] { 0, 3, 2, 1, -1, 1, 0, 2 };
 
	private java.util.Stack<String> prepare(String expression) {
 
		java.util.Stack<String> postfixStack = new java.util.Stack<String>();// 后缀式栈
		java.util.Stack<Character> opStack = new java.util.Stack<Character>();// 运算符栈
 
		opStack.push(',');// 运算符放入栈底元素逗号，此符号优先级最低
 
		char[] arr = expression.toCharArray();
		int currentIndex = 0; // 当前字符的位置
		int count = 0; // 上次算术运算符到本次算术运算符的字符的长度便于或者之间的数值
		char currentOp, peekOp; // 当前操作符和栈顶操作符
 
		for (int i = 0; i < arr.length; i++) {
			currentOp = arr[i];
			if (isOperator(currentOp)) {// 如果当前字符是运算符
 
				if (count > 0) {
					postfixStack.push(new String(arr, currentIndex, count));// 取两个运算符之间的数字
				}
				peekOp = opStack.peek();
				if (currentOp == ')') {// 遇到反括号则将运算符栈中的元素移除到后缀式栈中直到遇到左括号
					while (opStack.peek() != '(') {
						postfixStack.push(String.valueOf(opStack.pop()));
					}
					opStack.pop(); // 将'('弹出扔掉
				} else {
					// 当前字符优先级不大于字符栈顶的字符优先级时，字符栈顶元素弹出并放入输出栈
					while (currentOp != '(' && peekOp != ','
							&& compare(currentOp, peekOp)) {
						postfixStack.push(String.valueOf(opStack.pop()));
						peekOp = opStack.peek();
					}
					// 讲比较之后的读入的字符放到字符栈
					opStack.push(currentOp);
				}
				count = 0;
				currentIndex = i + 1; // 当前index加一，继续向下读取
			} else {
				count++;
			}
		}
 
		// 最后一个字符不是括号或者其他运算符的则加入后缀式栈中
		if (count > 1 || (count == 1 && !isOperator(arr[currentIndex]))) {
			postfixStack.push(new String(arr, currentIndex, count));
		}
 
		// 将字符栈中的符合条件的元素都添加到输出栈中
		while (opStack.peek() != ',') {
			postfixStack.push(String.valueOf(opStack.pop()));// 将操作符栈中的剩余的元素添加到后缀式栈中
		}
 
		return postfixStack;
	}
 
	// 判断是否为算术符号
	private boolean isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '('
				|| c == ')';
	}
 
	// 利用ASCII码-40做下标去算术符号优先级
	public boolean compare(char cur, char peek) {// 如果是peek优先级高于cur，返回true，默认都是peek优先级要低
		boolean result = false;
		if (operatPriority[(peek) - 40] >= operatPriority[(cur) - 40]) {
			result = true;
		}
		return result;
	}
 
	/**
	 * 栈的典型应用 其三：计算后缀表达式 按照给定的表达式计算
	 * 
	 * @param expression
	 *            要计算的表达式例如:5+12*(3+5)/7
	 * @return
	 */
	public String calculate(String expression) {
		java.util.Stack<String> resultStack = new java.util.Stack<String>();
 
		// 获取后缀表达式
		java.util.Stack<String> postfixStack = prepare(expression);
		Collections.reverse(postfixStack); // 转换之后的栈是按顺序存储的，计算的时候是从peek开始算，所以要反转一下
		String firstValue, secondValue, currentValue;// 参与计算的第一个值，第二个值和算术运算符
 
		while (!postfixStack.isEmpty()) {
			currentValue = postfixStack.pop();
			if (!isOperator(currentValue.charAt(0))) {// 如果不是运算符则存入操作数栈中
				resultStack.push(currentValue);
			} else {// 如果是运算符则从操作数栈中取两个值和该数值一起参与运算
				secondValue = resultStack.pop();
				firstValue = resultStack.pop();
				String tempResult = calculate(firstValue, secondValue,
						currentValue.charAt(0));
				resultStack.push(tempResult);
			}
		}
 
		return resultStack.peek();
	}
 
	// 按照给定的算术运算符做计算
	private String calculate(String firstValue, String secondValue,
			char currentOp) {
		String result = "";
		switch (currentOp) {
		case '+':
			result = String.valueOf(Double.parseDouble(firstValue)
					+ Double.parseDouble(secondValue));
			break;
		case '-':
			result = String.valueOf(Double.parseDouble(firstValue)
					- Double.parseDouble(secondValue));
			break;
		case '*':
			result = String.valueOf(Double.parseDouble(firstValue)
					* Double.parseDouble(secondValue));
			break;
		case '/':
			result = String.valueOf(Double.parseDouble(firstValue)
					/ Double.parseDouble(secondValue));
			break;
		}
		return result;
	}
 
	/**
	 * 栈的典型应用其四： 数制转换
	 * 
	 * @param number
	 *            待转换的数
	 * @return 转换后的字符串
	 */
	private String numChange(int number) {
		// 这里举个转换成8进制的例子
		java.util.Stack<String> stack = new Stack<String>();
		while (number > 0) {
			stack.push(number % 8 + "");
			number = number / 8;
		}
 
		StringBuilder sb = new StringBuilder();
		while (!stack.isEmpty()) {
			sb.append(stack.pop());
		}
 
		return sb.toString();
	}
	private class Point {
		int x = 0;
		int y = 0;
 
		public Point() {
			this(0, 0);
		}
 
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
 
		public boolean equals(Point p) {
			return (x == p.x) && (y == p.y);
		}
 
		@Override
		public String toString() {
			return "(" + x + ", " + y + ")";
		}
	}
 
	private int[][] maze = null; // 迷宫图
	private Stack<Point> stack = new Stack<Point>(); // 栈区，用来保存路径信息
	// 寻路方法
		public void go() {
			Point out = new Point(maze.length - 1, maze[0].length - 1); // 出口
			Point in = new Point(0, 0); // 入口
			Point curNode = in; // 当前点为入口
			Point nextNode = null; // 下一个访问点(目标点)
	 
			while (!curNode.equals(out)) {
				nextNode = new Point(curNode.x, curNode.y); // 设置目标点为当前点，便于下面偏移
	 
				// 如果下方是空的，则目标点向下偏移,优先向下走
				if ((curNode.x + 1) < maze.length
						&& maze[curNode.x + 1][curNode.y] == 0) {
					nextNode.x++;
				}
	 
				// 如果右边是空的，则目标点向右偏移
				else if ((curNode.y + 1) < maze[0].length
						&& maze[curNode.x][curNode.y + 1] == 0) {
					nextNode.y++;
				}
	 
				// 如果上方是空的，则目标点向上偏移
				else if ((curNode.x - 1) >= 0
						&& maze[curNode.x - 1][curNode.y] == 0) {
					nextNode.x--;
				}
	 
				// 如果左边是空的，则目标点向左偏移
				else if ((curNode.y - 1) >= 0
						&& maze[curNode.x][curNode.y - 1] == 0) {
					nextNode.y--;
				}
	 
				// 这里是没有路的状态
				else {
					maze[curNode.x][curNode.y] = 3; // 标记为死路
					if (stack.isEmpty()) { // 判断栈是否为空
						System.out.println("Non solution");
						return;
					}
					curNode = stack.pop(); // 弹出上一次的点
					continue; // 继续循环
				}
	 
				// 如果有路的话会执行到这里
				stack.push(curNode); // 当前点压入栈中
				maze[curNode.x][curNode.y] = 2; // 标记为已走
				curNode = nextNode; // 移动当前点
			}
	 
			if (nextNode.equals(out)) {
				stack.push(nextNode); // 将出口点添加到当前路劲中
				maze[nextNode.x][nextNode.y] = 2; // 标记为已走
			}
	 
			System.out.println("5,该迷宫的一条可行路径为：");
			for (int i = 0; i < stack.size(); i++) {
				System.out.println(stack.elementAt(i));
			}
	 
		}
		// 测试
		public static void main(String[] args) {
			StackUse t = new StackUse();
	 
			// 字符平衡的判断
			System.out.println("1,字符串括号是否匹配："+t.isValid("{{}[]()00}0"));
	 
			// 中缀转后缀
			System.out.println("2,算式的后缀表达式:"+"\n"+t.prepare("1+2+3*4"));
	 
			// 后缀表达式的计算
			System.out.println("3,算式‘1+2+3×4’的计算结果："+t.calculate("1+2+3*4"));
	 
			// 数制转换的计算
			System.out.println("4,数制转换结果："+t.numChange(8));
	 
			// 迷宫求解
			t.maze = new int[][] { { 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0 },
					{ 1, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 0 } };
					t.go();
					 
		}
	}
