public class HeapSort_delete{
//��������ѣ���array������ȫ��������˳��洢�ṹ
   private int[] buildMaxHeap(int[] array){
        //�����һ���ڵ�array.length-1�ĸ��ڵ㣨array.length-1-1��/2��ʼ��ֱ�����ڵ�0������������
        for(int i=(array.length-2)/2;i>=0;i--){ 
            adjustDownToUp(array, i,array.length);
        }
        return array;
    }
    
    //��Ԫ��array[k]���������𲽵������νṹ
    private void adjustDownToUp(int[] array,int k,int length){
        int temp = array[k];   
        for(int i=2*k+1; i<length-1; i=2*i+1){    //iΪ��ʼ��Ϊ�ڵ�k�����ӣ��ؽڵ�ϴ���ӽڵ����µ���
            if(i<length && array[i]<array[i+1]){  //ȡ�ڵ�ϴ���ӽڵ���±�
                i++;   //����ڵ���Һ���>���ӣ���ȡ�Һ��ӽڵ���±�
            }
            if(temp>=array[i]){  //���ڵ� >=������Ů�йؼ��ֽϴ��ߣ���������
                break;
            }else{   //���ڵ� <������Ů�йؼ��ֽϴ���
                array[k] = array[i];  //�������ӽ���нϴ�ֵarray[i]������˫�׽ڵ���
                k = i; //���ؼ����޸�kֵ���Ա�������µ���
            }
        }
        array[k] = temp;  //�������Ľ���ֵ��������λ��
    }
//������
public int[] heapsort(int[] array){
    array = buildMaxHeap(array); //��ʼ���ѣ�array[0]Ϊ��һ��ֵ����Ԫ��
    for(int i=array.length-1;i>1;i--){  
        int temp = array[0];  //���Ѷ�Ԫ�غͶѵ�Ԫ�ؽ��������õ���ǰ���Ԫ����ȷ������λ��
        array[0] = array[i];
        array[i] = temp;
        adjustDownToUp(array, 0,i);  //������ʣ���Ԫ������ɶ�
    }
    return array;
}
//ɾ���Ѷ�Ԫ�ز���
public int[] deleteMax(int[] array){
    //���ѵ����һ��Ԫ����Ѷ�Ԫ�ؽ������ѵ�Ԫ��ֵ��Ϊ-99999
    array[0] = array[array.length-1];
    array[array.length-1] = -99999;
    //�Դ�ʱ�ĸ��ڵ�������µ���
    adjustDownToUp(array, 0, array.length);
    return array;
}
//�������:������array�в�������data
public int[] insertData(int[] array, int data){
    array[array.length-1] = data; //���½ڵ���ڶѵ�ĩ��
    int k = array.length-1;  //��Ҫ�����Ľڵ�
    int parent = (k-1)/2;    //˫�׽ڵ�
    while(parent >=0 && data>array[parent]){
        array[k] = array[parent];  //˫�׽ڵ��µ�
        k = parent;
        if(parent != 0){
            parent = (parent-1)/2;  //�������ϱȽ�
        }else{  //���ڵ��ѵ�����ϣ�����ѭ��
            break;
        }
    }
    array[k] = data;  //������Ľ��ŵ���ȷ��λ��
    return array;
}
public void toString(int[] array){
    for(int i:array){
        System.out.print(i+" ");
    }
}

public static void main(String args[]){
    HeapSort_delete hs = new HeapSort_delete();
    int[] array = {87,45,78,32,17,65,53,9,122};
    System.out.print("��������ѣ�");
    hs.toString(hs.buildMaxHeap(array));
    System.out.print("\n"+"ɾ���Ѷ�Ԫ�أ�");
    hs.toString(hs.deleteMax(array));
    System.out.print("\n"+"����Ԫ��63:");
    hs.toString(hs.insertData(array, 63));
    System.out.print("\n"+"���������");
    hs.toString(hs.heapsort(array));    
}
}