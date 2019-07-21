package stack1;

import java.util.Collections;
import java.util.HashMap;
import java.util.Stack;
 
public class StackUse {
 
	/**
	 * ջ�ĵ���Ӧ�� ��һ��ƽ����� ���ŵ�ƥ�� ���ö�ջ���������������͵���������push��ȥ
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
					stack.pop(); // �������������stack��������ַ�����
				} else {
					return false; // ���򷵻ش���
				}
			}
		}
 
		// �����е��ַ����������֮���жϵ�ǰ��stack�Ƿ�Ϊ�ա�
		// ���Ϊ�գ���˵�����ж�ƥ�䣬��ô����true
		// �����Ϊ�գ���˵���в�ƥ��ĵ㣬����false
		return stack.empty();
	}
 
	/**
	 * ջ�ĵ���Ӧ�� ����������ʽת����Ϊ��׺ʽջ ת���Ĺ����ǣ� 1�������ŷ������ջ�У���Ԫ�����
	 * 2��������ջ�ж�����Ԫ�ص����ȼ�С����һ������ķ��ŵ����ȼ�������һ�����Ž�ջ
	 * 3��������ջ�ж�����Ԫ�ص����ȼ�������һ������ķ��ŵ����ȼ����򽫷���ջ�еķ��ŵ�����ֱ������С���������������ȼ��ķ��� Ȼ�����������Ž�ջ
	 * 4������������")"����������ߵ����ȼ���ֱ������"("�����ţ�������������ͬʱ�ӵ����������¶�ȡ
	 * 
	 * @param expression
	 */
	// ���������ASCII��-40����������������ȼ��������ǣ� �� �� �� �� �� . / �˸��ַ� �涨�˸��ַ������ȼ�˳��
	private int[] operatPriority = new int[] { 0, 3, 2, 1, -1, 1, 0, 2 };
 
	private java.util.Stack<String> prepare(String expression) {
 
		java.util.Stack<String> postfixStack = new java.util.Stack<String>();// ��׺ʽջ
		java.util.Stack<Character> opStack = new java.util.Stack<Character>();// �����ջ
 
		opStack.push(',');// ���������ջ��Ԫ�ض��ţ��˷������ȼ����
 
		char[] arr = expression.toCharArray();
		int currentIndex = 0; // ��ǰ�ַ���λ��
		int count = 0; // �ϴ����������������������������ַ��ĳ��ȱ��ڻ���֮�����ֵ
		char currentOp, peekOp; // ��ǰ��������ջ��������
 
		for (int i = 0; i < arr.length; i++) {
			currentOp = arr[i];
			if (isOperator(currentOp)) {// �����ǰ�ַ��������
 
				if (count > 0) {
					postfixStack.push(new String(arr, currentIndex, count));// ȡ���������֮�������
				}
				peekOp = opStack.peek();
				if (currentOp == ')') {// �����������������ջ�е�Ԫ���Ƴ�����׺ʽջ��ֱ������������
					while (opStack.peek() != '(') {
						postfixStack.push(String.valueOf(opStack.pop()));
					}
					opStack.pop(); // ��'('�����ӵ�
				} else {
					// ��ǰ�ַ����ȼ��������ַ�ջ�����ַ����ȼ�ʱ���ַ�ջ��Ԫ�ص������������ջ
					while (currentOp != '(' && peekOp != ','
							&& compare(currentOp, peekOp)) {
						postfixStack.push(String.valueOf(opStack.pop()));
						peekOp = opStack.peek();
					}
					// ���Ƚ�֮��Ķ�����ַ��ŵ��ַ�ջ
					opStack.push(currentOp);
				}
				count = 0;
				currentIndex = i + 1; // ��ǰindex��һ���������¶�ȡ
			} else {
				count++;
			}
		}
 
		// ���һ���ַ��������Ż��������������������׺ʽջ��
		if (count > 1 || (count == 1 && !isOperator(arr[currentIndex]))) {
			postfixStack.push(new String(arr, currentIndex, count));
		}
 
		// ���ַ�ջ�еķ���������Ԫ�ض���ӵ����ջ��
		while (opStack.peek() != ',') {
			postfixStack.push(String.valueOf(opStack.pop()));// ��������ջ�е�ʣ���Ԫ����ӵ���׺ʽջ��
		}
 
		return postfixStack;
	}
 
	// �ж��Ƿ�Ϊ��������
	private boolean isOperator(char c) {
		return c == '+' || c == '-' || c == '*' || c == '/' || c == '('
				|| c == ')';
	}
 
	// ����ASCII��-40���±�ȥ�����������ȼ�
	public boolean compare(char cur, char peek) {// �����peek���ȼ�����cur������true��Ĭ�϶���peek���ȼ�Ҫ��
		boolean result = false;
		if (operatPriority[(peek) - 40] >= operatPriority[(cur) - 40]) {
			result = true;
		}
		return result;
	}
 
	/**
	 * ջ�ĵ���Ӧ�� �����������׺���ʽ ���ո����ı��ʽ����
	 * 
	 * @param expression
	 *            Ҫ����ı��ʽ����:5+12*(3+5)/7
	 * @return
	 */
	public String calculate(String expression) {
		java.util.Stack<String> resultStack = new java.util.Stack<String>();
 
		// ��ȡ��׺���ʽ
		java.util.Stack<String> postfixStack = prepare(expression);
		Collections.reverse(postfixStack); // ת��֮���ջ�ǰ�˳��洢�ģ������ʱ���Ǵ�peek��ʼ�㣬����Ҫ��תһ��
		String firstValue, secondValue, currentValue;// �������ĵ�һ��ֵ���ڶ���ֵ�����������
 
		while (!postfixStack.isEmpty()) {
			currentValue = postfixStack.pop();
			if (!isOperator(currentValue.charAt(0))) {// ����������������������ջ��
				resultStack.push(currentValue);
			} else {// ������������Ӳ�����ջ��ȡ����ֵ�͸���ֵһ���������
				secondValue = resultStack.pop();
				firstValue = resultStack.pop();
				String tempResult = calculate(firstValue, secondValue,
						currentValue.charAt(0));
				resultStack.push(tempResult);
			}
		}
 
		return resultStack.peek();
	}
 
	// ���ո��������������������
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
	 * ջ�ĵ���Ӧ�����ģ� ����ת��
	 * 
	 * @param number
	 *            ��ת������
	 * @return ת������ַ���
	 */
	private String numChange(int number) {
		// ����ٸ�ת����8���Ƶ�����
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
 
	private int[][] maze = null; // �Թ�ͼ
	private Stack<Point> stack = new Stack<Point>(); // ջ������������·����Ϣ
	// Ѱ·����
		public void go() {
			Point out = new Point(maze.length - 1, maze[0].length - 1); // ����
			Point in = new Point(0, 0); // ���
			Point curNode = in; // ��ǰ��Ϊ���
			Point nextNode = null; // ��һ�����ʵ�(Ŀ���)
	 
			while (!curNode.equals(out)) {
				nextNode = new Point(curNode.x, curNode.y); // ����Ŀ���Ϊ��ǰ�㣬��������ƫ��
	 
				// ����·��ǿյģ���Ŀ�������ƫ��,����������
				if ((curNode.x + 1) < maze.length
						&& maze[curNode.x + 1][curNode.y] == 0) {
					nextNode.x++;
				}
	 
				// ����ұ��ǿյģ���Ŀ�������ƫ��
				else if ((curNode.y + 1) < maze[0].length
						&& maze[curNode.x][curNode.y + 1] == 0) {
					nextNode.y++;
				}
	 
				// ����Ϸ��ǿյģ���Ŀ�������ƫ��
				else if ((curNode.x - 1) >= 0
						&& maze[curNode.x - 1][curNode.y] == 0) {
					nextNode.x--;
				}
	 
				// �������ǿյģ���Ŀ�������ƫ��
				else if ((curNode.y - 1) >= 0
						&& maze[curNode.x][curNode.y - 1] == 0) {
					nextNode.y--;
				}
	 
				// ������û��·��״̬
				else {
					maze[curNode.x][curNode.y] = 3; // ���Ϊ��·
					if (stack.isEmpty()) { // �ж�ջ�Ƿ�Ϊ��
						System.out.println("Non solution");
						return;
					}
					curNode = stack.pop(); // ������һ�εĵ�
					continue; // ����ѭ��
				}
	 
				// �����·�Ļ���ִ�е�����
				stack.push(curNode); // ��ǰ��ѹ��ջ��
				maze[curNode.x][curNode.y] = 2; // ���Ϊ����
				curNode = nextNode; // �ƶ���ǰ��
			}
	 
			if (nextNode.equals(out)) {
				stack.push(nextNode); // �����ڵ���ӵ���ǰ·����
				maze[nextNode.x][nextNode.y] = 2; // ���Ϊ����
			}
	 
			System.out.println("5,���Թ���һ������·��Ϊ��");
			for (int i = 0; i < stack.size(); i++) {
				System.out.println(stack.elementAt(i));
			}
	 
		}
		// ����
		public static void main(String[] args) {
			StackUse t = new StackUse();
	 
			// �ַ�ƽ����ж�
			System.out.println("1,�ַ��������Ƿ�ƥ�䣺"+t.isValid("{{}[]()00}0"));
	 
			// ��׺ת��׺
			System.out.println("2,��ʽ�ĺ�׺���ʽ:"+"\n"+t.prepare("1+2+3*4"));
	 
			// ��׺���ʽ�ļ���
			System.out.println("3,��ʽ��1+2+3��4���ļ�������"+t.calculate("1+2+3*4"));
	 
			// ����ת���ļ���
			System.out.println("4,����ת�������"+t.numChange(8));
	 
			// �Թ����
			t.maze = new int[][] { { 0, 0, 0, 1, 0 }, { 0, 1, 0, 0, 0 },
					{ 1, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 1, 0 } };
					t.go();
					 
		}
	}
