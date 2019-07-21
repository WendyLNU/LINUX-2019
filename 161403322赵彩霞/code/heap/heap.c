#include <stdio.h> 
#define NA -1 
void swap(int *a,int *b)//该函数用于交换两个变量的值 
{ 
	int temp=*a; 
	*a=*b; 
	*b=temp; 
} 
void HeapAdjust(int H[],int start,int end)//堆调整，将start和end之间的元素调整为最大堆 
{ 
	int temp=H[start]; 
	int parent=start,child; 
	while(2*parent<=end) 
	{ 
		child=2*parent; 
		if(child!=end&&H[child]<H[child+1])++child; 
		if(temp>H[child])break; 
		else H[parent]=H[child]; 
		parent=child; 
	} H[parent]=temp; 
} 
void HeapSort(int H[],int L,int R) 
{ 
	for(int i=(R-L+1)/2;i>=L;--i)//调整整个二叉树为最大堆 
	HeapAdjust(H,i,R); 
	for(int i=R;i>=L;--i) 
	{ 
		swap(&H[L],&H[i]); 
		HeapAdjust(H,L,i-1); 
	}
} 
int main()
{ 
	
	int a[]={NA,1,3,63,5,78,9,12,52,8};//从1开始存入数据 
	printf("Previous Arrary:"); 
	for(int i=1;i<=9;++i) 
		printf(" %d",a[i]); 
	HeapSort(a,1,9); 
	printf("\nSorted Arrary:"); 
	for(int i=1;i<=9;++i) 
		printf(" %d",a[i]); 
	printf("\n"); 
	return 0; 
}

