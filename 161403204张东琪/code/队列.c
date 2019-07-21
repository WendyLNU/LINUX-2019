#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
struct Link
{
        int data;
        struct Link* next;
};
 
struct Queue
{
        struct Link* front;
        struct Link* rear;
        int size;
};
 
void QueueInit(struct Queue* queue)
{
        queue->front = NULL;
        queue->rear = NULL;
        queue->size = 0;
}
 
int QueueEmpty(struct Queue* queue)
{
        return (queue->size == 0);
}
 
void QueuePush(struct Queue* queue, const int data)
{
        struct Link* node;
        node = (struct Link*)malloc(sizeof(struct Link));
        assert(node != NULL);
        
        node->data = data;
        node->next = NULL;
        
        if(QueueEmpty(queue))
        {
            queue->front = node;
            queue->rear = node;
        }
        else
        {            
            queue->rear->next = node;
            queue->rear = node;
        }
        ++queue->size;
}
 
int QueuePop(struct Queue* queue, int* data)
{
        if (QueueEmpty(queue))
        {
                return 0;
        }
        struct Link* tmp = queue->front;
        *data = queue->front->data;
        queue->front = queue->front->next;
        free(tmp);
        --queue->size;
 
        return 1;
}
 
void QueueDestroy(struct Queue* queue)
{
     struct Link* tmp;
     while(queue->front)
     {
         tmp = queue->front;
         queue->front = queue->front->next;
         free(tmp);
     }
}
 
int main(void)
{
        struct Queue queue;
        int flag =1;
        int choice;
        int elem;
        int i;
        
        printf("**************************\n");
        printf("|      1.��������        |\n");
        printf("|        2.���          |\n");        
        printf("|        3.����          |\n");
        printf("|      4.���ٶ���        |\n");
        printf("**************************\n");
    
        while(flag)
		{
			printf("��ѡ���ܣ�\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
					
        			QueueInit(&queue);
					break; 
				case 2:
					printf("����������Ԫ�أ�");
					scanf("%d",&elem);
					QueuePush(&queue, elem);
					break;
				case 3:
					
					if(!QueueEmpty(&queue))	
					{
                		QueuePop(&queue, &i);
                		printf("���ӵ�Ԫ��Ϊ��%d\n", i);
        			}
        			break;
        		case 4:
        			QueueDestroy(&queue);
        			break;
        		default:
        			printf("�������н������밴������˳�������\n");
					flag = 0;
			}	
		 } 
       
        return 0;
}

