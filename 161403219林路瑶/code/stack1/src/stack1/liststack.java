package stack1;


public class liststack implements stack{
	
	/**
	 * 链表类
	 */
	private static class ListNode{
		public Object element;
		public ListNode next;
		public ListNode(Object element){
			this.element = element;
		}
	}
	
    private ListNode top; //指向栈顶
    private int count;//标记栈的大小
    
    //构造器
    public liststack()
    {
        top = null;
        count = 0;
    }
    
    //栈的大小
    public int size() {
        return count;
    }
    
    //栈是否为空
    public boolean isEmpty() {
        return (size() == 0);
    }
    
    //将元素压入栈
    public void push(Object element) {
        ListNode node = new ListNode(element);
        node.next = top;
        top = node;
        count++;
    }
    
    //栈顶部元素弹出 
    public Object pop() {
        if(isEmpty())
        {
            System.out.println("stack is empty!");
            System.exit(1);
        }
        Object result = top.element;
        top = top.next;
        count--;
        return result;
    }
    
    //获取栈顶部的元素
    public Object peek() {
        Object result =  top.element;
        return result;
    }
    
    
    //测试
    public static void main(String[] args){
        liststack stack = new liststack();
        System.out.println("将0到10依次压栈");
        for(int i = 0;i < 10;i++)
            stack.push(i);
        System.out.println("连续执行5次出栈操作");
        for(int i = 0;i < 5;i++)
            stack.pop();
        System.out.println("栈为空吗？： " + stack.isEmpty());
        System.out.println("栈的大小为： " + stack.size());
        System.out.println("栈顶元素为： " + stack.top.element);
        System.out.println("栈顶元素为： " + stack.peek());   
    }
	
}