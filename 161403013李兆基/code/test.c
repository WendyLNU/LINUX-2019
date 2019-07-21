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

struct book *creatbook();                          //创建链表
struct book *addbook(struct book *head);           //添加图书
int yanzheng(struct book *head,int m);             //验证新添加的图书编码是否已存在
void deletebook(struct book *head);                //删除图书
void fprint(struct book *head);                    //将链表写入文件
struct book *load();                               //从文件中读取信息并建成链表
void print_book(struct book *head);                //将链表信息输出
void chaxun(struct book *head);                    //查询图书信息
void num_chaxun(struct book *head);                //按图书编号查询图书
void wname_chaxun(struct book *head);              //按作者名查询图书
void sort_chaxun(struct book *head);               //按类别查询图书
void time_chaxun(struct book *head);               //按出版时间查询图书
void bname_chaxun(struct book *head);              //按图书名查询图书
void xiugai(struct book *head);                    //修改图书信息
void paixu(struct book *head);                     //对图书进行排序
void num_paixu(struct book *head);                 //按图书编号排序
void time_paixu(struct book *head);                //按图书出版时间排序
void price_paixu(struct book *head);               //按图书价格排序
void bname_paixu(struct book *head);               //按图书名排序
void wname_paixu(struct book *head);               //按作者名排序


int main()
{
	int choice,n,x,y=1,c,c1=123456;
	char a,d,b[10],b1[10]="lzj";                      //用户名是lzj  密码是123456
	struct book *head=NULL;
	while(y){

		system("cls");
        printf("\n\n\n\n\n\n\n");
	    printf("                                                  LNU Library System          \n\n\n");
	    printf("                                               辽宁大学图书信息管理系统         \n\n\n\n");
		printf("\n");
		printf("\n");
		printf("         ===1-用户登录===\n");
		printf("         ===0-退出系统===\n");
		printf("       请输入选择:");
		scanf("%d",&n);
		printf("\n");
		getchar();
		switch(n){
		case 0:
			y=0;
			break;
		case 1:
	    printf("       请输入您的用户名:");
        gets(b);
	    printf("\n");
	    printf("       请输入您的密码:");
	    scanf("%d",&c);
	    printf("\n");
	    if(strcmp(b,b1)!=0||c!=c1){
	       printf("           验证失败,请重新输入!\n");
		   scanf("%c",&d);
	       getchar();
	       system("cls");
		}
  	    else{
		    printf("             验证通过!请按Enter键进入!\n");
		    scanf("%c",&d);
		    getchar();
		    x=1;

	        while(x){
	            system("cls");
	            printf("                             ------------------\n");
	            printf("                             *图书信息管理系统*\n");
  	            printf("                             ------------------\n\n");
                printf("                ___________________________________________\n\n");
                printf("               |                                           |\n\n");
                printf("               |     1-添加图书             2-删除图书     |\n\n");
                printf("               |     3-图书列表             4-图书排序     |\n\n");
                printf("               |     5-查询图书             6-修改图书     |\n\n");
                printf("               |     7-录入数据             0-退出系统     |\n\n");
                printf("               |___________________________________________|\n\n");
                printf("               \n\n");
	            printf("请输入所选择的序号:");
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
				      printf("文件为空,请先录入数据!\n");
				      getchar();
				      break;
				   }
			      else{
				     head=addbook(head);
				     printf("添加成功!\n");
                     printf("是否将新信息保存到文件?(y/n)\n");
                     scanf("%c",&a);
				     getchar();
				     switch(a){
				     case 'n':
					     break;
				     case 'y':
				         fprint(head);
					     printf("保存成功!\n");
					     getchar();
				         break;
					 }
				     break;
				  }

		       case 2:
			     head=load();
                 if(head==NULL){
				     printf("文件为空,请先录入数据!\n");
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
				     printf("文件为空,请先录入数据!\n");
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
				     printf("文件为空,请先录入数据!\n");
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
				         printf("文件为空,请先录入数据!\n");
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
				       printf("文件为空,请先录入数据!\n");
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
			         printf("注意:输入图书编码为0时结束!\n");
                     head=creatbook();
                     printf("是否将输入的信息保存到文件以覆盖文件中已存在的信息?(y/n)\n");
                     getchar();
				     scanf("%c",&a);
				     getchar();
					 switch(a){
					 case 'n':
					     break;
				     case 'y':
				         fprint(head);
					     printf("保存成功!\n");
					     getchar();
					     break;
					 }
				     break;
		       default:
			       printf("您的输入有误,请重新输入!\n");
			       getchar();
			       break;
				}

			}
		}
		break;
		default:
			printf("        您的输入有误!  请重新输入!\n");
			getchar();
			break;
		}
	}
}
//录入数据并形成链表
struct book *creatbook()
{
	struct book *head,*tail,*p;
	int num,time,n;
	char bname[50],wname[20],press[50],sort[50];
	float price;
	int size=sizeof(struct book);
	head=tail=NULL;
	printf("请输入图书编号:");
	scanf("%d",&num);
    printf("请输入图书名:");
    scanf("%s",bname);
	getchar();
    printf("请输入作者名:");
    scanf("%s",wname);
	getchar();
    printf("请输入出版社:");
    scanf("%s",press);
	getchar();
	printf("请输入类别:");
    scanf("%s",sort);
	getchar();
    printf("请输入出版时间:");
    scanf("%d",&time);
	getchar();
    printf("请输入价格:");
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
        printf("请输入图书编号:");
	    scanf("%d",&num);
		n=yanzheng(head,num);
		if(n==0)
			break;
		else
			printf("您输入的编号已存在,请重新输入!\n");
	}while(1);
		if(num==0)
			break;
		else
		{
			printf("请输入图书名:");
			scanf("%s",bname);
			getchar();
			printf("请输入作者名:");
			scanf("%s",wname);
			getchar();
			printf("请输入出版社:");
			scanf("%s",press);
			getchar();
			printf("请输入类别:");
			scanf("%s",sort);
			getchar();
			printf("请输入出版时间:");
			scanf("%d",&time);
			getchar();
			printf("请输入价格:");
			scanf("%f",&price);
			getchar();
		}
	}
	return head;
}

//插入结点，并且插入后仍按一定顺序
struct book *addbook(struct book *head)
{

	struct book *ptr,*p1,*p2,*p;
    char bname[50],wname[20],press[50],sort[50];
	int size=sizeof(struct book);
    int num,time,n=1;
	float price;
	do{
        printf("请输入图书编号:");
	    scanf("%d",&num);
		n=yanzheng(head,num);
		if(n==0)
			break;
		else
			printf("您输入的编号已存在,请重新输入!\n");
	}while(1);
    printf("请输入图书名:");
    scanf("%s",bname);
	getchar();
    printf("请输入作者名:");
    scanf("%s",wname);
	getchar();
    printf("请输入出版社:");
    scanf("%s",press);
	getchar();
	printf("请输入类别:");
    scanf("%s",sort);
	getchar();
    printf("请输入出版时间:");
    scanf("%d",&time);
	getchar();
    printf("请输入价格:");
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
//验证添加的图书编号是否已存在
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

//将新链表写入文件中
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
//从文件中读取图书信息
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
//将整个链表的信息输出
void print_book(struct book *head)
{
	struct book *ptr;
	if(head==NULL){
		printf("\n没有信息!\n");
		return;
	}
	printf("                                 图书信息列表如下\n");
	printf("            ==========================================================\n");
	printf("             编号   图书名   作者名   出版社   类别   出版时间   价格\n");
	for(ptr=head;ptr;ptr=ptr->next)
		printf("              %d       %s        %s        %s       %s       %d     %.2f\n",ptr->num,ptr->bname,ptr->wname,ptr->press,ptr->sort,ptr->time,ptr->price);
	printf("            ==========================================================\n");
}
//删除图书信息
void deletebook(struct book *head)
{
	int a;
	char b,ch='1';
	struct book *p1,*p2;
	FILE *fp;
	printf("请输入要删除的图书编号:");
	scanf("%d",&a);
    p1=head;
    if(p1->num==a&&p1->next==NULL){          //对于文件中只有一组数据
		printf("是否清空文件!(y/n)\n");
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
			printf("文件已清空!\n");
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
                printf("是否确定从文件中彻底删除该图书?(y/n)\n");
			    getchar();
                scanf("%c",&b);

                switch(b){
		        case 'n':
			       break;
	            case 'y':
		           fprint(head);
		           printf("删除成功!\n");
	               getchar();
	               break;
				}
			}

		    else{
		       printf("没有找到要删除的数据!\n");
		       getchar();
			}
		}
        else if(p1==head){
		    head=p1->next;
            printf("是否确定从文件中彻底删除该图书?(y/n)\n");
		    getchar();
            scanf("%c",&b);

		    switch(b){
		    case 'n':
  	             break;
	        case 'y':
		         fprint(head);
	             printf("删除成功!\n");
                 getchar();
		         break;
			}

		}
	    else{
		    p2->next=p1->next;
            printf("是否确定从文件中彻底删除该图书?(y/n)\n");
	  	    getchar();
            scanf("%c",&b);

		    switch(b){
		    case 'n':
  	             break;
	        case 'y':
		         fprint(head);
	             printf("删除成功!\n");
                 getchar();
		         break;
			}
		}
	}

}
//图书查询
void chaxun(struct book *head)
{
	int a;
	printf("               ==========================================================\n");
	printf("\n");
	printf("                     ** 1-按图书编号查询        2-按图书名查询 **\n");
	printf("\n");
	printf("                     ** 3-按图书类别查询        4-按作者名查询 **\n");
	printf("\n");
	printf("                     ** 5-按出版时间查询        0-退出查询     **\n");
	printf("\n");
	printf("               ==========================================================\n");
	printf("请输入所选择的编号:");
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
		printf("您的输入有误!\n");
		break;
	}
}
//按编号查询图书信息
void num_chaxun(struct book *head)
{
	int a;
	struct book *p;
	printf("请选择您要查询的图书编号:");
	scanf("%d",&a);
	getchar();
	p=head;
    while(p!=NULL){
		if(p->num==a)
			break;
		p=p->next;
	}

	if(p==NULL){
		printf("没有找到该编号的图书!\n");
	}
	else{
		printf("                        你所查询的图书信息如下\n");
		printf(" =========================================================================\n");
		printf(" **   编号    图书名    作者名    出版社    类别    出版时间     价格   **\n");
		printf(" **    %d        %s         %s         %s        %s        %d       %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
		printf(" =========================================================================\n");
	}
}
//按图书名查询图书信息
void bname_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("请选择您要查询的图书名:");
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
		printf("没有找到该图书名的图书!\n");

	}
	else{
    printf("                        你所查询的图书信息如下\n");
	printf(" =========================================================================\n");
	printf(" **   编号    图书名    作者名    出版社    类别    出版时间     价格   **\n");
    while(p!=NULL){
		if(strcmp(p->bname,a)==0){
				printf(" **    %d        %s         %s        %s         %s       %d        %.2f  **\n",p->num,p->bname,p->wname,p->press,p->sort,p->time,p->price);
		}
    p=p->next;
	}
    printf(" =========================================================================\n");
	}

}
//按作者名查询图书信息
void wname_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("请选择您要查询的图书作者名:");
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
		printf("没有找到该图书名的图书!\n");

	}
	else{
    printf("                        你所查询的图书信息如下\n");
	printf(" =========================================================================\n");
	printf(" **   编号    图书名    作者名    出版社    类别    出版时间     价格   **\n");
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
//按图书类别查询图书信息
void sort_chaxun(struct book *head)
{
	char a[50];
	int flag=0;
	struct book *p;
	printf("请选择您要查询的图书类别:");
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
		printf("没有找到该图书名的图书!\n");

	}
	else{
    printf("                        你所查询的图书信息如下\n");
	printf(" =========================================================================\n");
	printf(" **   编号    图书名    作者名    出版社    类别    出版时间     价格   **\n");
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
//按图书出版时间查询图书信息
void time_chaxun(struct book *head)
{
	int a,flag=0;
	struct book *p;
	printf("请选择您要查询的图书出版时间:");
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
		printf("没有找到该图书名的图书!\n");

	}
	else{
    printf("                        你所查询的图书信息如下\n");
	printf(" =========================================================================\n");
	printf(" **   编号    图书名    作者名    出版社    类别    出版时间     价格   **\n");
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
//修改图书信息
void xiugai(struct book *head)
{
	int a,b;
	char c;
	struct book *p;
	printf("请输入要修改的图书编号:");
	scanf("%d",&a);
	p=head;
	while(p!=NULL){
		if(p->num==a)
			break;
		p=p->next;
	}
	if(p==NULL){
		printf("没有找到该编号的图书!\n");
		getchar();
	}
	else{
		printf("              ============================================================\n");
		printf("\n");
		printf("              **  1-编号               2-图书名              3-作者名   **\n");
		printf("\n");
		printf("              **  4-出版社             5-类别                6-出版时间 **\n");
		printf("\n");
		printf("              **  7-价格               8-修改全部            0-放弃修改 **\n");
		printf("\n");
		printf("              ============================================================\n");
		printf("请选择你要修改的信息编号:");
		scanf("%d",&b);
		getchar();
		switch(b){
		case 1:
			printf("请输入新编号:");
			scanf("%d",&p->num);
			printf("修改成功!\n");
			getchar();
			break;
		case 2:
			printf("请输入新图书名:");
			gets(p->bname);
			printf("修改成功!\n");
			break;
		case 3:
			printf("请输入新作者名:");
			gets(p->wname);
			printf("修改成功!\n");
			break;
		case 4:
			printf("请输入新出版社:");
			gets(p->press);
			printf("修改成功!\n");
			break;
		case 5:
			printf("请输入新类别:");
			gets(p->sort);
			printf("修改成功!\n");
			break;
		case 6:
			printf("请输入新出版时间:");
			scanf("%d",&p->time);
			printf("修改成功!\n");
			getchar();
			break;
		case 7:
			printf("请输入新价格:");
			scanf("%f",&p->price);
			printf("修改成功!\n");
			getchar();
			break;
		case 8:
			printf("请输入新图书编号:");
			scanf("%d",&p->num);
            printf("请输入新图书名:");
            scanf("%s",p->bname);
	        getchar();
            printf("请输入新作者名:");
            scanf("%s",p->wname);
	        getchar();
            printf("请输入新出版社:");
            scanf("%s",p->press);
	        getchar();
	        printf("请输入新类别:");
            scanf("%s",p->sort);
	        getchar();
            printf("请输入新出版时间:");
            scanf("%d",&p->time);
	        getchar();
            printf("请输入新价格:");
            scanf("%f",&p->price);
	        getchar();
			printf("修改成功!\n");
			getchar();
			break;
		case 0:
			break;
		default :
			printf("您的输入有误!\n");
			break;
		}
        printf("是否将修改后的信息保存到文件中?(y/n)\n");
        scanf("%c",&c);
        getchar();
	    switch(c){
		case 'n':
			break;
		 case 'y':
		    fprint(head);
			printf("保存成功!\n");
			getchar();
			break;
		}

	}
}
//图书排序
void paixu(struct book *head)
{
	int a;
    printf("           ================================================================\n");
    printf("\n");
	printf("                 **  1-按图书编号排序         2-按出版时间排序   **\n");
	printf("\n");
	printf("                 **  3-按图书价格排序         4-按图书名排序     **\n");
	printf("\n");
	printf("                 **  5-按作者名排序           0-取消排序操作     **\n");
	printf("\n");
	printf("           ================================================================\n");
	printf("请输入您选择的编号:");
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
		printf("您的输入有误!\n");
		break;
	}
}

//按图书编号排序
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
    printf("排序成功!\n");
	printf("是否显示排序结果?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ================================================================\n");
	    printf("        ** 编号   图书名   作者名   出版社   类别   出版时间    价格  **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ================================================================\n");
		break;
	default:
		printf("您的输入有误!\n");
		break;
	}
}
//按出版时间排序
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
	printf("排序成功!\n");
	printf("是否显示排序结果?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** 编号   图书名   作者名   出版社   类别   出版时间    价格 **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("您的输入有误!\n");
		break;
	}
}
//按图书价格排序
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
    printf("排序成功!\n");
	printf("是否显示排序结果?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** 编号   图书名   作者名   出版社   类别   出版时间    价格 **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("您的输入有误!\n");
		break;
	}
}

//按图书名排序
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
    printf("排序成功!\n");
	printf("是否显示排序结果?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** 编号   图书名   作者名   出版社   类别   出版时间    价格 **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("您的输入有误!\n");
		break;
	}
}

//按作者名排序
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
    printf("排序成功!\n");
	printf("是否显示排序结果?(y/n)\n");
	scanf("%s",&b);
    getchar();
	switch(b){
	case 'n':
		break;
	case 'y':
	    printf("        ===============================================================\n");
	    printf("        ** 编号   图书名   作者名   出版社   类别   出版时间    价格 **\n");
	    for(i=0;i<n;i++){
			printf("        **  %d       %s        %s        %s        %s      %d      %.2f **\n",a[i]->num,a[i]->bname,a[i]->wname,a[i]->press,a[i]->sort,a[i]->time,a[i]->price);
		}
		printf("        ===============================================================\n");
		break;
	default:
		printf("您的输入有误!\n");
		break;
	}
}
