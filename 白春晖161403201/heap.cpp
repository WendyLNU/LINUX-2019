#include<stdio.h>
#include<stdlib.h>
#define N  10005
typedef int ElementType;
typedef  struct HNode {/* 堆的类型定义 */
	ElementType* Data; /* 存储元素的数组 */
	int Size;          /* 堆中当前元素个数 */
	int Capacity;      /* 堆的最大容量 */
} HNode,* Heap;
typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */

#define MAXDATA  0/* 该值应根据具体情况定义为大于堆中所有可能元素的值 */
#define MINDATA 0
void PercDown(MinHeap H, int p);
void BuildHeap(MinHeap H);
void heappaixu(MinHeap H);
bool Insert2(MinHeap H, ElementType X);
void PercDown2(MinHeap H, int p);
void BuildHeap2(MinHeap H);
void heappaixu2(MinHeap H);
MinHeap CreateMinHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最小堆 */

	MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	H->Data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MINDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/

	return H;
}
MaxHeap CreateMaxHeap(int MaxSize)
{ /* 创建容量为MaxSize的空的最小堆 */

	MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	H->Data = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MINDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/

	return H;
}


bool IsFull(MinHeap H)
{
	return (H->Size == H->Capacity);
}



bool Insert(MinHeap H, ElementType X)
{ /* 将元素X插入最小堆H，其中H->Data[0]已经定义为哨兵 */
	int i;
	if (IsFull(H)) {
		printf("最小堆已满");
		return false;
	}
	i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
	for (; i!=1&&H->Data[i / 2] > X; i /= 2)
		H->Data[i] = H->Data[i / 2]; /* 上滤X */
	H->Data[i] = X; /* 将X插入 */
	return true;
}
#define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */



bool IsEmpty(MinHeap H)           
{
	return (H->Size == 0);
}



ElementType Deletemin(MinHeap H)
{
	/* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
	int Parent, Child;
	ElementType MinItem, X;

	if (IsEmpty(H)) {
		printf("最小堆已为空");
		return ERROR;
	}
	MinItem = H->Data[1]; /* 取出根结点存放的最小值 */
	//printf("%d\n", H->Size);					  /* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
	X = H->Data[H->Size--];
	H->Data[1] = X;
	//printf("%d\n", X);/* 注意当前堆的规模要减小 */
	//printf("%d\n", H->Size);
	BuildHeap(H);
	return MinItem;
}
ElementType Deletemin2(MinHeap H)
{
	/* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
	int Parent, Child;
	ElementType MinItem, X;

	if (IsEmpty(H)) {
		printf("最小堆已为空");
		return ERROR;
	}
	MinItem = H->Data[1]; /* 取出根结点存放的最小值 */
	//printf("%d\n", H->Size);					  /* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
	X = H->Data[H->Size--];
	H->Data[1] = X;
	//printf("%d\n", X);/* 注意当前堆的规模要减小 */
	//printf("%d\n", H->Size);
	BuildHeap2(H);
	return MinItem;
}


/*----------- 建造最小堆 -----------*/
void PercDown(MinHeap H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
	int Parent, Child;
	ElementType X;
	X = H->Data[p]; /* 取出根结点存放的值 */
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child] > H->Data[Child + 1]))
			Child++;  /* Child指向左右子结点的较小者 */
		if (X <= H->Data[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;   
}

void BuildHeap(MinHeap H)
{ /* 调整H->Data[]中的元素，使满足最小堆的有序性  */
  /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
	int i;
	/* 从最后一个结点的父节点开始，到根结点1 */
	for (i = H->Size / 2; i > 0; i--)
		PercDown(H, i);
}
 
int main()
{
	MinHeap minheap;
	int c, g;
	int a, b, i;

	printf("1.建一个最大堆\n2.建一个最小堆\n");
	scanf_s("%d", &c);
	while (c!=1&&c!=2)
	{
		printf("请输入1或者2\n");
		scanf_s("%d", &c);
	}
	printf("堆的容量");
	scanf_s("%d", &a);
	minheap = CreateMinHeap(a + 1);
	switch (c) {
	case 1:


		printf("输入堆中的数字，中间用空格分开");
		for (i = 1; i < a + 1; i++) {
			scanf_s("%d", &b);
			Insert2(minheap, b);
		}
		for (int i = 1; i <= minheap->Size; i++)
			printf("%d\t", minheap->Data[i]);
		printf("\n");
		break;
	case 2:

		printf("输入堆中的数字，中间用空格分开");
		for (i = 1; i < a + 1; i++) {
			scanf_s("%d", &b);
			Insert(minheap, b);
		}
		for (int i = 1; i <= minheap->Size; i++)
			printf("%d\t", minheap->Data[i]);
		printf("\n");
		 break;
	}
	printf("1.进行堆排序\n2.插入新的数字\n3删除堆中的元素\n");
	int m;
	scanf_s("%d", &m);
	int f;
	switch (m)
	{
	case 1:
		if (c == 1)
		{
			heappaixu2(minheap);
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");
		}
		else {
			heappaixu(minheap);
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");
		}
	case 2:printf("输入插入元素的个数\n");
		 
		scanf_s("%d",&f);
		minheap->Data= (int*)realloc(minheap->Data, (f+minheap->Capacity) * sizeof(int));
		minheap->Capacity += f;
		printf("输入插入堆中的数字，中间用空格分开");
		if (c == 1)
		{
			for (i = 1; i <=f; i++) {
				scanf_s("%d", &b);
				Insert2(minheap, b);
			}
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");
			break;
		}
		else {
			for (i = 1; i <= f; i++) {
				scanf_s("%d", &b);
				Insert(minheap, b);
			}
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");
			break;
		}
	case 3:printf("输入删除元素个数：");
		int n=0;
		scanf_s("%d",&n);
		if (c == 1) {
			for (; n> 0; n--)
				Deletemin2(minheap);
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");

		}
		else {
			for (; n> 0; n--)
				Deletemin(minheap);
			for (int i = 1; i <= minheap->Size; i++)
				printf("%d\t", minheap->Data[i]);
			printf("\n");

		}
	}
}
	/*int a, b, i;
	printf("最小堆的容量");
	scanf_s("%d", &a);
	MinHeap minheap = CreateMinHeap(a + 1);
	printf("输入堆中的数字，中间用空格分开");
	for (i = 1; i < a + 1; i++) {
		scanf_s("%d", &b);
		Insert(minheap, b);
	}
	for (i = 1; i <= minheap->Size; i++)
		printf("%d\t", minheap->Data[i]);
	printf("\n");
	Deletemin2(minheap);
	for (i = 1; i <= minheap->Size; i++)
		printf("%d\t", minheap->Data[i]);
	printf("\n");
	heappaixu(minheap);*/

void heappaixu(MinHeap H){
	int i = H->Size, j, m = H->Size;
	for (; m >0; m--) {
		j = H->Data[H->Size];
		H->Data[H->Size]=H->Data[1];
		H->Data[1] = j;
		H->Size--;
		BuildHeap(H);
	}H->Size = i;
}
bool Insert2(MinHeap H, ElementType X)
{ /* 将元素X插入最小堆H，其中H->Data[0]已经定义为哨兵 */
	int i;
	if (IsFull(H)) {
		printf("最大堆已满");
		return false;
	}
	i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
	for (;(i!=1)&&( H->Data[i / 2])<X; i /= 2)
		H->Data[i] = H->Data[i / 2]; /* 上滤X */
	H->Data[i] = X; /* 将X插入 */
	return true;
}
void heappaixu2(MinHeap H) {
	int i = H->Size, j, m = H->Size;
	for (; m > 0; m--) {
		j = H->Data[H->Size];
		H->Data[H->Size] = H->Data[1];
		H->Data[1] = j;
		H->Size--;
		BuildHeap2(H);
	}H->Size = i;
}
void PercDown2(MinHeap H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
	int Parent, Child;
	ElementType X;
	X = H->Data[p]; /* 取出根结点存放的值 */
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child] < H->Data[Child + 1]))
			Child++;  /* Child指向左右子结点的较小者 */
		if (X >= H->Data[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
}
void BuildHeap2(MinHeap H)
{ /* 调整H->Data[]中的元素，使满足最小堆的有序性  */
  /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
	int i;
	/* 从最后一个结点的父节点开始，到根结点1 */
	for (i = H->Size / 2; i > 0; i--)
		PercDown2(H, i);
}
