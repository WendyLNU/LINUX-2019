#include<stdio.h>
typedef int ElementType;
int arr1[11]={0,2,87,39,49,34,62,53,6,44,98};
#define LeftChild(i) (2 * (i) + 1)

void Swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}


void PercDown(int  A[], int i, int N)
{
    int child;
    ElementType Tmp;

    for (Tmp = A[i]; 2*i+1 < N; i = child){
        child = 2*i+1; //注意数组下标是从0开始的，所以左孩子的求发不是2*i
        if (child != N - 1 && A[child + 1] > A[child])
            ++child;                //找到最大的儿子节点
        if (Tmp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = Tmp;
}

void HeapSort(int A[], int N)
{
    int i;
    for (i = N / 2; i >= 0; --i)
        PercDown(A, i, N);    //构造堆
    for(i=N-1;i>0;--i)
    {
        Swap(&A[0],&A[i]);        //将最大元素（根）与数组末尾元素交换，从而删除最大元素，重新构造堆
        PercDown(A, 0, i);
    }
}

void Print(int A[],int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        printf(" %d ",A[i]);
    }
}
int main()
{
    int arr[10]={2,87,39,49,34,62,53,6,44,98};
    Print(arr,10);
    printf("\n");
    HeapSort(arr,10);
    Print(arr,10);
    printf("\n");
    return 0;
}
