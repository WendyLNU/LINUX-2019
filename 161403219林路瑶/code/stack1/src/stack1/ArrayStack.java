package stack1;


public class ArrayStack implements stack {
 
	private Object[] contents;  //栈内元素
	private int top;  //top标记下一个入栈的位置，同时也表示栈的容量大小，跟链式实现的count比较
	private static int SIZE = 10;  //初始长度
 
	//初始化
	public ArrayStack() {
		contents = new Object[SIZE];
		top = 0;
	}
 
	//当容量不够时，借助于申请一个辅助空间,每次扩展容量一倍
	public void expand() {
		Object[] larger = new Object[size() * 2];
		for (int index = 0; index < top; index++)
			larger[index] = contents[index];
		contents = larger;
	}
 
	//栈的大小
	public int size() {
		return top;
	}
 
	//判断栈是否为空
	public boolean isEmpty() {
		return (size() == 0);
	}
 
	//元素压入栈
	public void push(Object element) {
		if (top == contents.length){
			expand();
		}
		contents[top] = element;
		top++;
	}
 
	//栈顶元素的弹出
	public Object pop() {
		if (isEmpty()) {
			System.out.println("stack is empty!");
			System.exit(1);
		}
		Object result = contents[top - 1];
		contents[top - 1] = null; // 出栈
		top--;
		return result;
	}
 
	//获取栈顶元素
	public Object peek() {
		Object result;
		if (isEmpty())
			result = null;
		else
			result = contents[top - 1];
		return result;
	}
 
	//测试
	public static void main(String[] args) {
		ArrayStack stack = new ArrayStack();
		System.out.println("将0到24依次压栈，然后连续10次出栈");
		for (int i = 0; i < 25; i++)
			stack.push(i);
		for (int i = 0; i < 10; i++)
			stack.pop();
		System.out.println("栈的大小为： " + stack.size());
		System.out.println("栈为空吗？： " + stack.isEmpty());
		System.out.println("栈顶元素为： " + stack.peek());
	}

}
