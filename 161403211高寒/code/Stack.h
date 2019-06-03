class Node
{
public:
	int data;
	Node *next;
};

class Stack
{
public:
	Stack();
	void Push(int data);//入栈
	void Pop();//出栈
	void Print();//打印栈
private:
	Node *top;//栈顶
	Node *buttom;//栈底
	int size;//栈元素数量
};
