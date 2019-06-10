package stack1;

public interface stack{
	 
	// 压栈
	public void push(Object element);
 
	// 出栈
	public Object pop();
 
	//判断是否为空
	public boolean isEmpty();
 
	//返回栈的大小
	public int size();
 
	//返回栈顶对象的一个引用
	public Object peek();
 
	//栈的toString打印
	public String toString();
	
}
