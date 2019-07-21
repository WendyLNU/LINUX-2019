#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct book{
	int num;
	char bname[50];
	char wname[20];
	char press[50];
	char sort[50];
	int time;
	float price;
    struct book *next;
};

struct book *creatbook();                          //��������
struct book *addbook(struct book *head);           //���ͼ��
int yanzheng(struct book *head,int m);             //��֤����ӵ�ͼ������Ƿ��Ѵ���
void deletebook(struct book *head);                //ɾ��ͼ��
void fprint(struct book *head);                    //������д���ļ�
struct book *load();                               //���ļ��ж�ȡ��Ϣ����������
void print_book(struct book *head);                //��������Ϣ���
void chaxun(struct book *head);                    //��ѯͼ����Ϣ
void num_chaxun(struct book *head);                //��ͼ���Ų�ѯͼ��
void wname_chaxun(struct book *head);              //����������ѯͼ��
void sort_chaxun(struct book *head);               //������ѯͼ��
void time_chaxun(struct book *head);               //������ʱ���ѯͼ��
void bname_chaxun(struct book *head);              //��ͼ������ѯͼ��
void xiugai(struct book *head);                    //�޸�ͼ����Ϣ
void paixu(struct book *head);                     //��ͼ���������
void num_paixu(struct book *head);                 //��ͼ��������
void time_paixu(struct book *head);                //��ͼ�����ʱ������
void price_paixu(struct book *head);               //��ͼ��۸�����
void bname_paixu(struct book *head);               //��ͼ��������
void wname_paixu(struct book *head);               //������������


int main()
{
	int choice,n,x,y=1,c,c1=123456;
	char a,d,b[10],b1[10]="lzj";                      //�û�����lzj  ������123456
	struct book *head=NULL;
	while(y){

		system("cls");
        printf("\n\n\n\n\n\n\n");
	    printf("                                                  LNU Library System          \n\n\n");
	    printf("                                               ������ѧͼ����Ϣ����ϵͳ         \n\n\n\n");
		printf("\n");
		printf("\n");
		printf("         ===1-�û���¼===\n");
		printf("         ===0-�˳�ϵͳ===\n");
		printf("       ������ѡ��:");
		scanf("%d",&n);
		printf("\n");
		getchar();
		switch(n){
		case 0:
			y=0;
			break;
		case 1:
	    printf("       �����������û���:");
        gets(b);
	    printf("\n");
	    printf("       ��������������:");
	    scanf("%d",&c);
	    printf("\n");
	    if(strcmp(b,b1)!=0||c!=c1){
	       printf("           ��֤ʧ��,����������!\n");
		   scanf("%c",&d);
	       getchar();
	       system("cls");
		}
  	    else{
		    printf("             ��֤ͨ��!�밴Enter������!\n");
		    scanf("%c",&d);
		    getchar();
		    x=1;

	        while(x){
	            system("cls");
	            printf("                             ------------------\n");
	            printf("                             *ͼ����Ϣ����ϵͳ*\n");
  	            printf("                             ------------------\n\n");
                printf("                ___________________________________________\n\n");
                printf("               |                                           |\n\n");
                printf("               |     1-���ͼ��             2-ɾ��ͼ��     |\n\n");
                printf("               |     3-ͼ���б�             4-ͼ������     |\n\n");
                printf("               |     5-��ѯͼ��             6-�޸�ͼ��     |\n\n");
                printf("               |     7-¼������             0-�˳�ϵͳ     |\n\n");
                printf("               |___________________________________________|\n\n");
                printf("               \n\n");
	            printf("��������ѡ������:");
	            scanf("%d",&choice);
	            getchar();
    	        system("cls");
	            switch(choice)
				{
	            case 0:
			       x=0;break;
		        case 1:
			       head=load();
			       if(head==NULL){
				      printf("�ļ�Ϊ��,����¼������!\n");
				      getchar();
				      break;
				   }
			      else{
				     head=addbook(head);
				     printf("��ӳɹ�!\n");
                     printf("�Ƿ�����Ϣ���浽�ļ�?(y/n)\n");
                     scanf("%c",&a);
				     getchar();
				     switch(a){
				     case 'n':
					     break;
				     case 'y':
				         fprint(head);
					     printf("����ɹ�!\n");
					     getchar();
				         break;
					 }
				     break;
				  }

		       case 2:
			     head=load();
                 if(head==NULL){
				     printf("�ļ�Ϊ��,����¼������!\n");
				     getchar();
				     break;
				 }

			     else{
				     deletebook(head);
                     getchar();
				     break;
			     }
				 break;
		       case 3:
                 head=load();
			     if(head==NULL){
				     printf("�ļ�Ϊ��,����¼������!\n");
				     getchar();
				     break;
				 }
			     else{
				     print_book(head);
				     getchar();
				     break;
				 }
		       case 4:
                 head=load();
			     if(head==NULL){
				     printf("�ļ�Ϊ��,����¼������!\n");
				     getchar();
				     break;
				 }
			     else{
				     paixu(head);
				     getchar();
				 }
			     break;
               case 5:
                     head=load();
			         if(head==NULL){
				         printf("�ļ�Ϊ��,����¼������!\n");
				         getchar();
				         break;
					 }
				     else{
					     chaxun(head);
					     getchar();
					 }
				     break;
		       case 6:
                   head=load();
			       if(head==NULL){
				       printf("�ļ�Ϊ��,����¼������!\n");
				       getchar();
				       break;
				   }
				   else{
					   xiugai(head);
					   getchar();
                       break;
				   }
				   break;
               case 7:
			         printf("ע��:����ͼ�����Ϊ0ʱ����!\n");
                     head=creatbook();
                     printf("�Ƿ��������Ϣ���浽�ļ��Ը����ļ����Ѵ��ڵ���Ϣ?(y/n)\n");
                     getchar();
				     scanf("%c",&a);
				     getchar();
					 switch(a){
					 case 'n':
					     break;
				     case 'y':
				         fprint(head);
					     printf("����ɹ�!\n");
					     getchar();
					     break;
					 }
				     break;
		       default:
			       printf("������������,����������!\n");
			       getchar();
			       break;
				}

			}
		}
		break;
		default:
			printf("        ������������!  ����������!\n");
			getchar();
			break;
		}
	}
}
//¼�����ݲ��γ�����
struct book *creatbook()
{
	struct book *head,*tail,*p;
	int num,time,n;
	char bname[50],wname[20],press[50],sort[50];
	float price;
	int size=sizeof(struct book);
	head=tail=NULL;
	printf("������ͼ����:");
	scanf("%d",&num);
    printf("������ͼ����:");
    scanf("%s",bname);
	getchar();
    printf("������������:");
    scanf("%s",wname);
	getchar();
    printf("�����������:");
    scanf("%s",press);
	getchar();
	printf("���������:");
    scanf("%s",sort);
	getchar();
    printf("���������ʱ��:");
    scanf("%d",&time);
	getchar();
    printf("������۸�:");
    scanf("%f",&price);
	getchar();
	while(1){
		p=(struct book *)malloc(size);
		p->num=num;
		strcpy(p->bname,bname);
		strcpy(p->wname,wname);
		strcpy(p->press,press);
		strcpy(p->sort,sort);
		p->time=time;
		p->price=price;
		p->next=NULL;
		if(head==NULL)
			head=p;
		else
			tail->next=p;
		tail=p;
		do{
        printf("������ͼ����:");
	    scanf("%d",&num);
		n=yanzheng(head,num);
		if(n==0)
			break;
		else
			printf("������ı���Ѵ���,����������!\n");
	}while(1);
		if(num==0)
			break;
		else
		{
			printf("������ͼ����:");
			scanf("%s",bname);
			getchar();
			printf("������������:");
			scanf("%s",wname);
			getchar();
			printf("�����������:");
			scanf("%s",press);
			getchar();
			printf("���������:");
			scanf("%s",sort);
			getchar();
			printf("���������ʱ��:");
			scanf("%d",&time);
			getchar();
			printf("������۸�:");
			scanf("%f",&price);
			getchar();
		}
	}
	return head;
}

//�����㣬���Ҳ�����԰�һ��˳��
struct book *addbook(struct book *head)
{

	struct book *ptr,*p1,*p2,*p;
    char bname[50],wname[20],press[50],sort[50];
	int size=sizeof(struct book);
    int num,time,n=1;
	float price;
	do{
        printf("������ͼ����:");
	    scanf("%d",&num);
		n=yanzheng(head,num);
		if(n==0)
			break;
		else
			printf("������ı���Ѵ���,����������!\n");
	}while(1);
    printf("������ͼ����:");
    scanf("%s",bname);
	getchar();
    printf("������������:");
    scanf("%s",wname);
	getchar();
    printf("�����������:");
    scanf("%s",press);
	getchar();
	printf("���������:");
    scanf("%s",sort);
	getchar();
    printf("���������ʱ��:");
    scanf("%d",&time);
	getchar();
    printf("������۸�:");
    scanf("%f",&price);
	getchar();
	p=(struct book *)malloc(size);
    p->num=num;
    strcpy(p->bname,bname);
	strcpy(p->wname,wname);
	strcpy(p->press,press);
	strcpy(p->sort,sort);
	p->time=time;
	p->price=price;
	p2=head;
	ptr=p;
	while((ptr->num>p2->num)&&(p2->next!=NULL)){
		p1=p2;
		p2=p2->next;
	}
	if(ptr->num<=p2->num){
		if(head==p2)
			head=ptr;
		else{
			p1->next=ptr;
		    p->next=p2;
		}
	}
	else{
		p2->next=ptr;
		p->next=NULL;
	}
	return head;
}
//��֤��ӵ�ͼ�����Ƿ��Ѵ���
int yanzheng(struct book *head,int m)
{
	struct book *p;
	p=head;
	while(p!=NULL){
		if(p->num==m)
			break;
		p=p->next;
	}
	if(p==NULL)
		return 0;
	else
		return 1;
}

//��������д���ļ���
void fprint(struct book *head)
{
	FILE *fp;
	char ch='1';
	struct book *p1;
	if((fp=fopen("f1.txt","w"))==NULL){
		printf("File open error!\n");
		exit(0);
	}
	fputc(ch,fp);
	for(p1=head;p1;p1=p1->next){
		fprintf(fp,"%d %s %s %s %s %d %f\n",p1->num,p1->bname,p1->wname,p1->press,p1->sort,p1->time,p1->price);
	}
	fclose(fp);
}
//���ļ��ж�ȡͼ����Ϣ
struct book *load()
{
	FILE *fp;
	char ch;
	struct book *head,*tail,*p1;
	head=tail=NULL;
	if((fp=fopen("f1.txt","r"))==NULL){
		printf("File open error!\n");
		exit(0);
	}
	ch=fgetc(fp);
	if(ch=='1'){

	    while(!feof(fp)){
		    p1=(struct book *)malloc(sizeof(struct book));
		    fscanf(fp,"%d%s%s%s%s%d%f\n",&p1->num,p1->bname,p1->wname,p1->press,p1->sort,&p1->time,&p1->price);
		    if(head==NULL)
			    head=p1;
		    else
			    tail->next=p1;
		    tail=p1;
		}
	    tail->next=NULL;
	    fclose(fp);
        return head;
	}
	else
		return NULL;

}
//�������������Ϣ���
void print_book(struct book *head)
{
	struct book *ptr;
	if(head==NULL){
		printf("\nû����Ϣ!\n");
		return;
	}
	printf("                                 ͼ����Ϣ�б�����\n");
	printf("            ==========================================================\n");
	printf("             ���   ͼ����   ������   ������   ���   ����ʱ��   �۸�\n");
	for(ptr=head;ptr;ptr=ptr->next)
		printf("              %d       %s        %s        %s       %s       %d     %.2f\n",ptr->num,ptr->bname,ptr->wname,ptr->press,ptr->sort,ptr->time,ptr->price);
	printf("            ==========================================================\n");
}
//ɾ��ͼ����Ϣ
void deletebook(struct book *head)
{
	int a;
	char b,ch='1';
	struct book *p1,*p2;
	FILE *fp;
	printf("������Ҫɾ����ͼ����:");
	scanf("%d",&a);
    p1=head;
    if(p1->num==a&&p1->next==NULL){          //�����ļ���ֻ��һ������
		printf("�Ƿ�����ļ�!(y/n)\n");
		getchar();
		scanf("%c",&b);
		getchar();
		switch(b){
		case 'n':
			break;
		case 'y':

            if((fp=fopen("f1.txt","w"))==NULL){
		        printf("File open error!\n");
		        exit(0);
			}
            fclose(fp);
			printf("�ļ������!\n");
		}
	}
	else{
        while(p1->num!=a&&p1->next!=NULL){
		    p2=p1;
		    p1=p1->next;
		}

        if(p1->next==NULL){
	        if(p1->num==a){
		        p2->next=NULL;
                printf("�Ƿ�ȷ�����ļ��г���ɾ����ͼ��?(y/n)\n");
			    getchar();
                scanf("%c",&b);

                switch(b){
		        case 'n':
			       break;
	            case 'y':
		           fprint(head);
		           printf("ɾ���ɹ�!\n");
	               getchar();
	               break;
				}
			}

		    else{
		       printf("û���ҵ�Ҫɾ��������!\n");
		       getchar();
			}
		}
        else if(p1==head){
		    head=p1->next;
            printf("�Ƿ�ȷ�����ļ��г���ɾ����ͼ��?(y/n)\n");
		    getchar();
            scanf("%c",&b);

		    switch(b){
		    case 'n':
  	             break;
	        case 'y':
		         fprint(head);
	             printf("ɾ���ɹ�!\n");
                 getchar();
		         break;
			}

		}
	    else{
		    p2->next=p1->next;
            printf("�Ƿ�ȷ�����ļ��г���ɾ����ͼ��?(y/n)\n");
	  	    getchar();
            scanf("%c",&b);

		    switch(b){
		    case 'n':
  	             break;
	        case 'y':
		         fprint(head);
	             printf("ɾ���ɹ�!\n");
                 getchar();
		         break;
			}
		}
	}

}
//ͼ���ѯ
void chaxun(struct book *head)
{
	int a;
	printf("               ==========================================================\n");
	printf("\n");
	printf("                     ** 1-��ͼ���Ų�ѯ        2-��ͼ������ѯ **\n");
	printf("\n");
	printf("                     ** 3-��ͼ������ѯ        4-����������ѯ **\n");
	printf("\n");
	printf("                     ** 5-������ʱ���ѯ        0-�˳���ѯ     **\n");
	printf("\n");
	printf("               ==========================================================\n");
	printf("��������ѡ��ı��:");
	scanf("%d",&a);
	getchar();
	switch(a){
	case 0:
		break;
	case 1:
		num_chaxun(head);
		break;
	case 2:
		bname_chaxun(head);
		break;
	case 3:
		sort_chaxun(head);
		break;
	case 4:
		wname_chaxun(head);
		break;
	case 5:
		time_chaxun(head);
		break;
	default:
		printf("������������!\n");
		break;
	}
}
//����Ų�ѯͼ����Ϣ
void num_chaxun(struct book *head)
{
	int a;
	struct book *p;
	printf("��ѡ����Ҫ��ѯ��ͼ����:");
	scanf("%d",&a);
	getchar();
	p=head;
    while(p!=NULL){
		if(p->num==a)
			break;
		p=p->next;
	}

	if(p==NULL){
		printf("û���ҵ��ñ�ŵ�ͼ��!\n");
	}
	else{
		printf("                        ������ѯ��ͼ����Ϣ����\n");
		printf(" =========================================================================\n");
		printf(" **   ���    ͼ����    ������    ������    ���    ����ʱ��     �۸�   **\n");
		printf(" **    %d        %s         %s         %s        %s        %d       %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
		printf(" =========================================================================\n");
	}
}
//��ͼ������ѯͼ����Ϣ
void bname_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("��ѡ����Ҫ��ѯ��ͼ����:");
	gets(a);
	p=head;
	while(p!=NULL){
		if(strcmp(p->bname,a)==0){
			flag=1;
			break;
		}
		p=p->next;
	}
    if(flag==0){
		printf("û���ҵ���ͼ������ͼ��!\n");

	}
	else{
    printf("                        ������ѯ��ͼ����Ϣ����\n");
	printf(" =========================================================================\n");
	printf(" **   ���    ͼ����    ������    ������    ���    ����ʱ��     �۸�   **\n");
    while(p!=NULL){
		if(strcmp(p->bname,a)==0){
				printf(" **    %d        %s         %s        %s         %s       %d        %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
		}
    p=p->next;
	}
    printf(" =========================================================================\n");
	}

}
//����������ѯͼ����Ϣ
void wname_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("��ѡ����Ҫ��ѯ��ͼ��������:");
	gets(a);
	p=head;
    while(p!=NULL){
		if(strcmp(p->wname,a)==0){
			flag=1;
			break;
		}
		p=p->next;
	}
    if(flag==0){
		printf("û���ҵ���ͼ������ͼ��!\n");

	}
	else{
    printf("                        ������ѯ��ͼ����Ϣ����\n");
	printf(" =========================================================================\n");
	printf(" **   ���    ͼ����    ������    ������    ���    ����ʱ��     �۸�   **\n");
    while(p!=NULL){
		if(strcmp(p->wname,a)==0){
				printf(" **    %d        %s         %s        %s         %s       %d        %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
				flag=1;
		}
    p=p->next;
	}
    printf(" =========================================================================\n");
	}

}
//��ͼ������ѯͼ����Ϣ
void sort_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("��ѡ����Ҫ��ѯ��ͼ�����:");
	gets(a);
	p=head;
    while(p!=NULL){
		if(strcmp(p->sort,a)==0){
			flag=1;
			break;
		}
		p=p->next;
	}
    if(flag==0){
		printf("û���ҵ���ͼ������ͼ��!\n");

	}
	else{
    printf("                        ������ѯ��ͼ����Ϣ����\n");
	printf(" =========================================================================\n");
	printf(" **   ���    ͼ����    ������    ������    ���    ����ʱ��     �۸�   **\n");
    while(p!=NULL){
		if(strcmp(p->sort,a)==0){
				printf(" **    %d        %s         %s        %s         %s       %d        %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
				flag=1;
		}
    p=p->next;
	}
    printf(" =========================================================================\n");
	}
}
//��ͼ�����ʱ���ѯͼ����Ϣ
void time_chaxun(struct book *head)
{
	int a,flag=0;
	struct book *p;
	printf("��ѡ����Ҫ��ѯ��ͼ�����ʱ��:");
	scanf("%d",&a);
    getchar();
	p=head;
    while(p!=NULL){
		if(p->time==a){
			flag=1;
			break;
		}
		p=p->next;
	}
    if(flag==0){
		printf("û���ҵ���ͼ������ͼ��!\n");

	}
	else{
    printf("                        ������ѯ��ͼ����Ϣ����\n");
	printf(" =========================================================================\n");
	printf(" **   ���    ͼ����    ������    ������    ���    ����ʱ��     �۸�   **\n");
    while(p!=NULL){
		if(p->time==a){
				printf(" **    %d        %s         %s        %s         %s       %d        %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
				flag=1;
		}
    p=p->next;
	}
    printf(" =========================================================================\n");
	}
}
//�޸�ͼ����Ϣ
void xiugai(struct book *head)
{
	int a,b;
	char c;
	struct book *p;
	printf("������Ҫ�޸ĵ�ͼ����:");
	scanf("%d",&a);
	p=head;
	while(p!=NULL){
		if(p->num==a)
			break;
		p=p->next;
	}
	if(p==NULL){
		printf("û���ҵ��ñ�ŵ�ͼ��!\n");
		getchar();
	}
	else{
		printf("              ============================================================\n");
		printf("\n");
		printf("              **  1-���               2-ͼ����              3-������   **\n");
		printf("\n");
		printf("              **  4-������             5-���                6-����ʱ�� **\n");
		printf("\n");
		printf("              **  7-�۸�               8-�޸�ȫ��            0-�����޸� **\n");
		printf("\n");
		printf("              ============================================================\n");
		printf("��ѡ����Ҫ�޸ĵ���Ϣ���:");
		scanf("%d",&b);
		getchar();
		switch(b){
		case 1:
			printf("�������±��:");
			scanf("%d",&p->num);
			printf("�޸ĳɹ�!\n");
			getchar();
			break;
		case 2:
			printf("��������ͼ����:");
			gets(p->bname);
			printf("�޸ĳɹ�!\n");
			break;
		case 3:
			printf("��������������:");
			gets(p->wname);
			printf("�޸ĳɹ�!\n");
			break;
		case 4:
			printf("�������³�����:");
			gets(p->press);
			printf("�޸ĳɹ�!\n");
			break;
		case 5:
			printf("�����������:");
			gets(p->sort);
			printf("�޸ĳɹ�!\n");
			break;
		case 6:
			printf("�������³���ʱ��:");
			scanf("%d",&p->time);
			printf("�޸ĳɹ�!\n");
			getchar();
			break;
		case 7:
			printf("�������¼۸�:");
			scanf("%f",&p->price);
			printf("�޸ĳɹ�!\n");
			getchar();
			break;
		case 8:
			printf("��������ͼ����:");
			scanf("%d",&p->num);
            printf("��������ͼ����:");
            scanf("%s",p->bname);
	        getchar();
            printf("��������������:");
            scanf("%s",p->wname);
	        getchar();
            printf("�������³�����:");
            scanf("%s",p->press);
	        getchar();
	        printf("�����������:");
            scanf("%s",p->sort);
	        getchar();
            printf("�������³���ʱ��:");
            scanf("%d",&p->time);
	        getchar();
            printf("�������¼۸�:");
            scanf("%f",&p->price);
	        getchar();
			printf("�޸ĳɹ�!\n");
			getchar();
			break;
		case 0:
			break;
		default :
			printf("������������!\n");
			break;
		}
        printf("�Ƿ��޸ĺ����Ϣ���浽�ļ���?(y/n)\n");
        scanf("%c",&c);
        getchar();
	    switch(c){
		case 'n':
			break;
		 case 'y':
		    fprint(head);
			printf("����ɹ�!\n");
			getchar();
			break;
		}

	}
}
//ͼ������
void paixu(struct book *head)
{
	int a;
    printf("           ================================================================\n");
    printf("\n");
	printf("                 **  1-��ͼ��������         2-������ʱ������   **\n");
	printf("\n");
	printf("                 **  3-��ͼ��۸�����         4-��ͼ��������     **\n");
	printf("\n");
	printf("                 **  5-������������           0-ȡ���������     **\n");
	printf("\n");
	printf("           ================================================================\n");
	printf("��������ѡ��ı��:");
	scanf("%d",&a);
	getchar();
	switch(a){
	case 0:
		break;
	case 1:
		num_paixu(head);
		break;
	case 2:
		time_paixu(head);
		break;
	case 3:
		price_paixu(head);
		break;
	case 4:
		bname_paixu(head);
		break;
	case 5:
		wname_paixu(head);
		break;
	default:
		printf("������������!\n");
		break;
	}
}

//��ͼ��������
void num_paixu(struct book *head)
{
	struct book *a[1000],*p,*p1,*temp;
	int i,k,index,n=0;
	char b;
	p1=head;
	for(p=head;p;p=p->next)
		n++;
	for(i=0;i<n;i++){
		a[i]=p1;
		p1=p1->next;
	}
	for(k=0;k<n-1;k++){
		index=k;
		for(i=k+1;i<n;i++){
			if(a[i]->num<a[index]->num)
				index=i;
		}
        temp=a[index];
		a[index]=a[k];
		a[k]=temp;
	}
    printf("����ɹ�!\n");
	printf("�Ƿ���ʾ������?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ================================================================\n");
	    printf("        ** ���   ͼ����   ������   ������   ���   ����ʱ��    �۸�  **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ================================================================\n");
		break;
	default:
		printf("������������!\n");
		break;
	}
}
//������ʱ������
void time_paixu(struct book *head)
{
	struct book *a[1000],*p,*p1,*temp;
	int i,k,index,n=0;
	char b;
	p1=head;
	for(p=head;p;p=p->next)
		n++;
	for(i=0;i<n;i++){
		a[i]=p1;
		p1=p1->next;
	}
	for(k=0;k<n-1;k++){
		index=k;
		for(i=k+1;i<n;i++){
			if(a[i]->time<a[index]->time)
				index=i;
		}
        temp=a[index];
		a[index]=a[k];
		a[k]=temp;
	}
	printf("����ɹ�!\n");
	printf("�Ƿ���ʾ������?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** ���   ͼ����   ������   ������   ���   ����ʱ��    �۸� **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("������������!\n");
		break;
	}
}
//��ͼ��۸�����
void price_paixu(struct book *head)
{
	struct book *a[1000],*p,*p1,*temp;
	int i,k,index,n=0;
	char b;
	p1=head;
	for(p=head;p;p=p->next)
		n++;
	for(i=0;i<n;i++){
		a[i]=p1;
		p1=p1->next;
	}
	for(k=0;k<n-1;k++){
		index=k;
		for(i=k+1;i<n;i++){
			if(a[i]->price<a[index]->price)
				index=i;
		}
        temp=a[index];
		a[index]=a[k];
		a[k]=temp;
	}
    printf("����ɹ�!\n");
	printf("�Ƿ���ʾ������?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** ���   ͼ����   ������   ������   ���   ����ʱ��    �۸� **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("������������!\n");
		break;
	}
}

//��ͼ��������
void bname_paixu(struct book *head)
{
	struct book *a[1000],*p,*p1,*temp;
	int i,k,index,n=0;
	char b;
	p1=head;
	for(p=head;p;p=p->next)
		n++;
	for(i=0;i<n;i++){
		a[i]=p1;
		p1=p1->next;
	}
	for(k=0;k<n-1;k++){
		index=k;
		for(i=k+1;i<n;i++){
			if(strcmp(a[index]->bname,a[i]->bname)>0)
				index=i;
		}
        temp=a[index];
		a[index]=a[k];
		a[k]=temp;
	}
    printf("����ɹ�!\n");
	printf("�Ƿ���ʾ������?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** ���   ͼ����   ������   ������   ���   ����ʱ��    �۸� **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("������������!\n");
		break;
	}
}

//������������
void wname_paixu(struct book *head)
{
	struct book *a[1000],*p,*p1,*temp;
	int i,k,index,n=0;
	char b;
	p1=head;
	for(p=head;p;p=p->next)
		n++;
	for(i=0;i<n;i++){
		a[i]=p1;
		p1=p1->next;
	}
	for(k=0;k<n-1;k++){
		index=k;
		for(i=k+1;i<n;i++){
			if(strcmp(a[index]->wname,a[i]->wname)>0)
				index=i;
		}
        temp=a[index];
		a[index]=a[k];
		a[k]=temp;
	}
    printf("����ɹ�!\n");
	printf("�Ƿ���ʾ������?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** ���   ͼ����   ������   ������   ���   ����ʱ��    �۸� **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("������������!\n");
		break;
	}
}
