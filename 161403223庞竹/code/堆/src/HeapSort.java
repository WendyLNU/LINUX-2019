
 
public class HeapSort {
   
  /** 
   * 调整为小顶堆（排序后结果为从大到小）
   * 
   * @param array是待调整的堆数组 
   * @param s是待调整的数组元素的位置
   * @param length是数组的长度
   * 
   */
  public static void heapAdjustS(int[] array, int s, int length) {
    int tmp = array[s];
    int child = 2 * s + 1;// 左孩子结点的位置
    System.out.println("待调整结点为：array[" + s + "] = " + tmp);
    while (child < length) {
      // child + 1 是当前调整结点的右孩子
      // 如果有右孩子且小于左孩子，使用右孩子与结点进行比较，否则使用左孩子
      if (child + 1 < length && array[child] > array[child + 1]) {
        child++;
      }
      System.out.println("将与子孩子 array[" + child + "] = " + array[child] + " 进行比较");
      // 如果较小的子孩子比此结点小
      if (array[s] > array[child]) {
        System.out.println("子孩子比其小，交换位置");
        array[s] = array[child];// 把较小的子孩子向上移动，替换当前待调整结点
        s = child;// 待调整结点移动到较小子孩子原来的位置
        array[child] = tmp;
        child = 2 * s + 1;// 继续判断待调整结点是否需要继续调整 
        if (child >= length) {
          System.out.println("没有子孩子了，调整结束");
        } else {
          System.out.println("继续与新的子孩子进行比较");
        }
    } else {
        System.out.println("子孩子均比其大，调整结束");
        break;// 当前待调整结点小于它的左右孩子，不需调整，直接退出
      }
    }
  }
   
  /** 
   * 调整为大顶堆（排序后结果为从小到大）
   * 
   * @param array是待调整的堆数组 
   * @param s是待调整的数组元素的位置
   * @param length是数组的长度
   * 
   */
  public static void heapAdjustB(int[] array, int s, int length) {
    int tmp = array[s];
    int child = 2 * s + 1;// 左孩子结点的位置
    System.out.println("待调整结点为：array[" + s + "] = " + tmp);
    while (child < length) {
      // child + 1 是当前调整结点的右孩子
      // 如果有右孩子且大于左孩子，使用右孩子与结点进行比较，否则使用左孩子
      if (child + 1 < length && array[child] < array[child + 1]) {
        child++;
      }
      System.out.println("将与子孩子 array[" + child + "] = " + array[child] + " 进行比较");
      // 如果较大的子孩子比此结点大
      if (array[s] < array[child]) {
        System.out.println("子孩子比其大，交换位置");
        array[s] = array[child];// 把较大的子孩子向上移动，替换当前待调整结点
        s = child;// 待调整结点移动到较大子孩子原来的位置
        array[child] = tmp;
        child = 2 * s + 1;// 继续判断待调整结点是否需要继续调整
         
        if (child >= length) {
          System.out.println("没有子孩子了，调整结束");
        } else {
          System.out.println("继续与新的子孩子进行比较");
        }
        // continue;
      } else {
        System.out.println("子孩子均比其小，调整结束");
        break;// 当前待调整结点大于它的左右孩子，不需调整，直接退出
      }
    }
  }
    
  /**
   * 堆排序算法
   * 
   * @param array
   * @param inverse true 为倒序排列，false 为正序排列
   */
  public static void heapSort(int[] array, boolean inverse) {
    // 初始堆
    // 最后一个有孩子的结点位置 i = (length - 1) / 2, 以此向上调整各结点使其符合堆
    System.out.println("初始堆开始");
    for (int i = (array.length - 1) / 2; i >= 0; i--) {
      if (inverse) {
        heapAdjustS(array, i, array.length);
      } else {
        heapAdjustB(array, i, array.length);
      }
    }
    System.out.println("初始堆结束");
    for (int i = array.length - 1; i > 0; i--) {
      // 交换堆顶元素H[0]和堆中最后一个元素
      int tmp = array[i];
      array[i] = array[0];
      array[0] = tmp;
      // 每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整
      if (inverse) {
        heapAdjustS(array, 0, i);
      } else {
        heapAdjustB(array, 0, i);
      }
    }
  }
 
  public static void main(String[] args) {
    int[] array = { 49, 38, 65, 97, 76, 13, 27, 49 };
    heapSort(array, false);
    for (int i : array) {
      System.out.print(i + " ");
    }
  }
 
}