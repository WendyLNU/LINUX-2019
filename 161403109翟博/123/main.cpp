
#include<stdio.h>
#include<stdlib.h>

/*
arr[start+1...end]�������ѵĶ��壬
��arr[start]���뵽����arr[start+1...end]�У�
����arr[start]��λ�ã�ʹarr[start...end]Ҳ��Ϊ����
ע�����������0��ʼ������ţ�Ҳ���Ƕ���ѵĸ��ڵ����Ϊ0��
������Ϊi�������ӽڵ����ŷֱ�Ϊ2i+1��2i+2
*/
void HeapAdjustDown(int *arr,int start,int end)
{
	int temp = arr[start];	//���浱ǰ�ڵ�
	int i = 2*start+1;		//�ýڵ�������������е�λ�����
	while(i<=end)
	{
		//�ҳ����Һ����������Ǹ�
		if(i+1<=end && arr[i+1]>arr[i])
			i++;
		//������϶ѵĶ��壬���õ���λ��
		if(arr[i]<=temp)
			break;
		//�����ӽڵ������ƶ����滻���丸�ڵ�
		arr[start] = arr[i];
		start = i;
		i = 2*start+1;
	}
	arr[start] = temp;
}

/*
��������˳��Ϊ��С����
�����Ҫ��������
*/
void Heap_Sort(int *arr,int len)
{
	int i;
	//�����齨��Ϊ����
	//��һ����Ҷ�ӽڵ��λ�����Ϊlen/2-1
	for(i=len/2-1;i>=0;i--)
		HeapAdjustDown(arr,i,len-1);
	//���ж�����
	for(i=len-1;i>0;i--)
	{
		//�Ѷ�Ԫ�غ����һ��Ԫ�ؽ���λ�ã�
		//��������һ��λ�ñ��������������
		//ÿ��ѭ�����ν��δ����ֵ�ڷŽ���ǰ��һ��λ�ã�
		//�����õ���˳����Ǵ�С����
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		//��arr[0...i-1]���µ���Ϊ����
		HeapAdjustDown(arr,0,i-1);
	}
}

int main()
{
	int num;
	printf("�����������Ԫ�صĸ�����");
	scanf("%d",&num);

	int i;
	int *arr = (int *)malloc(num*sizeof(int));
	printf("������������%d��Ԫ�أ�����Ϊ��������",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);

	printf("��������˳��");
	Heap_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}
