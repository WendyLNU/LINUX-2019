
typedef struct stack{	
	DATA data[SIZE+1];   //数据元素  top为o表示栈为空 
	int top;   //定义栈顶
	 } seqStack;

seqStack *seqStackInit(){	
	seqStack *p;	
	if(p=(seqStack *)malloc(sizeof(seqStack)))  //申请内存
	{	
		p->top=0;	
		return p;	
	} 	
	return NULL;  //申请内存失败 
} 
int seqStackIsempty(seqStack *s)  //栈是否为空
{
	return(s->top==0);
} 
int seqStackIsfull(seqStack *s)  //栈是否满
{
	return(s->top==SIZE);
} 

void seqStackClear(seqStack *s)
{
	s->top=0;   //清空栈 
}
void seqStackfree(seqStack *s)  //释放栈的空间 
{
	if(s)
	  free(s); 
} 

int seqStackPush(seqStack *s,DATA data){	
	if((s->top+1)>SIZE)       //栈的上一个位置超过最大位置 	
	{		
		printf("栈溢出\n");	
		return 0;	
	}	
	s->data[++s->top]=data;   //修改栈顶指针，把元素入栈
	return 1;
}

int seqStackPop(seqStack *s)     //出栈
{
	if(s->top==0)
	{
		printf("栈为空:\n");
		exit(0);
	}
	return (s->data[s->top--]);  //从栈顶弹出元素 
} 

DATA seqStackPeek(seqStack *s)  //读出栈顶元素
{
	if(s->top==0)
	{
		printf("栈为空");
		exit(0);
	}
	return (s->data[s->top]); //返回栈顶元素 
} 