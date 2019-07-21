package stack1;


public class liststack implements stack{
	
	/**
	 * ������
	 */
	private static class ListNode{
		public Object element;
		public ListNode next;
		public ListNode(Object element){
			this.element = element;
		}
	}
	
    private ListNode top; //ָ��ջ��
    private int count;//���ջ�Ĵ�С
    
    //������
    public liststack()
    {
        top = null;
        count = 0;
    }
    
    //ջ�Ĵ�С
    public int size() {
        return count;
    }
    
    //ջ�Ƿ�Ϊ��
    public boolean isEmpty() {
        return (size() == 0);
    }
    
    //��Ԫ��ѹ��ջ
    public void push(Object element) {
        ListNode node = new ListNode(element);
        node.next = top;
        top = node;
        count++;
    }
    
    //ջ����Ԫ�ص��� 
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
    
    //��ȡջ������Ԫ��
    public Object peek() {
        Object result =  top.element;
        return result;
    }
    
    
    //����
    public static void main(String[] args){
        liststack stack = new liststack();
        System.out.println("��0��10����ѹջ");
        for(int i = 0;i < 10;i++)
            stack.push(i);
        System.out.println("����ִ��5�γ�ջ����");
        for(int i = 0;i < 5;i++)
            stack.pop();
        System.out.println("ջΪ���𣿣� " + stack.isEmpty());
        System.out.println("ջ�Ĵ�СΪ�� " + stack.size());
        System.out.println("ջ��Ԫ��Ϊ�� " + stack.top.element);
        System.out.println("ջ��Ԫ��Ϊ�� " + stack.peek());   
    }
	
}