package stack1;


public class ArrayStack implements stack {
 
	private Object[] contents;  //ջ��Ԫ��
	private int top;  //top�����һ����ջ��λ�ã�ͬʱҲ��ʾջ��������С������ʽʵ�ֵ�count�Ƚ�
	private static int SIZE = 10;  //��ʼ����
 
	//��ʼ��
	public ArrayStack() {
		contents = new Object[SIZE];
		top = 0;
	}
 
	//����������ʱ������������һ�������ռ�,ÿ����չ����һ��
	public void expand() {
		Object[] larger = new Object[size() * 2];
		for (int index = 0; index < top; index++)
			larger[index] = contents[index];
		contents = larger;
	}
 
	//ջ�Ĵ�С
	public int size() {
		return top;
	}
 
	//�ж�ջ�Ƿ�Ϊ��
	public boolean isEmpty() {
		return (size() == 0);
	}
 
	//Ԫ��ѹ��ջ
	public void push(Object element) {
		if (top == contents.length){
			expand();
		}
		contents[top] = element;
		top++;
	}
 
	//ջ��Ԫ�صĵ���
	public Object pop() {
		if (isEmpty()) {
			System.out.println("stack is empty!");
			System.exit(1);
		}
		Object result = contents[top - 1];
		contents[top - 1] = null; // ��ջ
		top--;
		return result;
	}
 
	//��ȡջ��Ԫ��
	public Object peek() {
		Object result;
		if (isEmpty())
			result = null;
		else
			result = contents[top - 1];
		return result;
	}
 
	//����
	public static void main(String[] args) {
		ArrayStack stack = new ArrayStack();
		System.out.println("��0��24����ѹջ��Ȼ������10�γ�ջ");
		for (int i = 0; i < 25; i++)
			stack.push(i);
		for (int i = 0; i < 10; i++)
			stack.pop();
		System.out.println("ջ�Ĵ�СΪ�� " + stack.size());
		System.out.println("ջΪ���𣿣� " + stack.isEmpty());
		System.out.println("ջ��Ԫ��Ϊ�� " + stack.peek());
	}

}
