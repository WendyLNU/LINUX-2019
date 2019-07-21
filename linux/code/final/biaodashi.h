
typedef struct stack{	
	DATA data[SIZE+1];   //����Ԫ��  topΪo��ʾջΪ�� 
	int top;   //����ջ��
	 } seqStack;

seqStack *seqStackInit(){	
	seqStack *p;	
	if(p=(seqStack *)malloc(sizeof(seqStack)))  //�����ڴ�
	{	
		p->top=0;	
		return p;	
	} 	
	return NULL;  //�����ڴ�ʧ�� 
} 
int seqStackIsempty(seqStack *s)  //ջ�Ƿ�Ϊ��
{
	return(s->top==0);
} 
int seqStackIsfull(seqStack *s)  //ջ�Ƿ���
{
	return(s->top==SIZE);
} 

void seqStackClear(seqStack *s)
{
	s->top=0;   //���ջ 
}
void seqStackfree(seqStack *s)  //�ͷ�ջ�Ŀռ� 
{
	if(s)
	  free(s); 
} 

int seqStackPush(seqStack *s,DATA data){	
	if((s->top+1)>SIZE)       //ջ����һ��λ�ó������λ�� 	
	{		
		printf("ջ���\n");	
		return 0;	
	}	
	s->data[++s->top]=data;   //�޸�ջ��ָ�룬��Ԫ����ջ
	return 1;
}

int seqStackPop(seqStack *s)     //��ջ
{
	if(s->top==0)
	{
		printf("ջΪ��:\n");
		exit(0);
	}
	return (s->data[s->top--]);  //��ջ������Ԫ�� 
} 

DATA seqStackPeek(seqStack *s)  //����ջ��Ԫ��
{
	if(s->top==0)
	{
		printf("ջΪ��");
		exit(0);
	}
	return (s->data[s->top]); //����ջ��Ԫ�� 
} 