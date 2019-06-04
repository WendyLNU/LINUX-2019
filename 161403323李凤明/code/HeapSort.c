/*
利用大顶堆(小顶堆)堆顶记录的是最大关键字(最小关键字)这一特性,
使得每次从无序中选择最大记录(最小记录)变得简单。
首先根据该数组元素构建一个完全二叉树
构造初始堆：
从最后一个非叶节点开始调整，
每次调整都是从父节点、左孩子节点、右孩子节点三者中选择最大者跟父节点进行交换
(交换之后可能造成被交换的孩子节点不满足堆的性质，因此每次交换之后要重新对被交换的孩子节点进行调整)。
有了初始堆之后就可以进行排序了
*/



#include<stdio.h>
typedef int ElementType;
int arr1[11]={0,2,87,39,49,34,62,53,6,44,98};
#define LeftChild(i) (2 * (i) + 1)

void Swap(int* a,int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void PercDown(int  A[], int i, int N){
    int child;
    ElementType Tmp;

    for (Tmp = A[i]; 2*i+1 < N; i = child){
        child = 2*i+1; //注意数组下标是从0开始的，所以左孩子的下标不是2*i
        if (child != N - 1 && A[child + 1] > A[child])
            ++child;                //找到最大的儿子节点
        if (Tmp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = Tmp;
}

void HeapSort(int A[], int N){
    int i;
    for (i = N / 2; i >= 0; --i)
        PercDown(A, i, N);    //构造堆
    for(i=N-1;i>0;--i)
    {
        Swap(&A[0],&A[i]);        //将最大元素（根）与数组末尾元素交换，从而删除最大元素，重新构造堆
        PercDown(A, 0, i);
    }
}

void Print(int A[],int N){
    int i;
    for(i=0;i<N;i++)
    {
        printf("%d ",A[i]);
    }
}

int main()
{
    int arr[10]={2,87,39,49,34,62,53,6,44,98};
    printf("排序前:");
    Print(arr,10);
    printf("\n");
    HeapSort(arr,10);
    printf("排序后:");
    Print(arr,10);
    printf("\n");
    return 0;
}
