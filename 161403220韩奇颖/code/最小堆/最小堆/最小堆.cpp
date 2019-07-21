// 最小堆.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;
template<class T>
class MinHeap {
	T *heap;
	int MaxSize;
	int currentPos;

public:
	MinHeap(int MS) {
		heap = new T[MS];
		currentPos = 0;
		MaxSize = MS;
	}

	bool Insert(T data) {
		if (currentPos == MaxSize) {
			cout << "Sorry , this heap is full!" << endl;
			return false;
		}
		currentPos++;
		int targetPos = currentPos - 1;
		heap[targetPos] = data;
		while (targetPos>0) {
			int parentPos = (targetPos - 1) / 2;
			if (heap[parentPos]<heap[targetPos]) {
				break;
			}
			else {
				heap[targetPos] = heap[parentPos];
				targetPos = parentPos;
			}
		}
		return true;
	}

	void siftDown(int siftPos) {

		int siftPosition = siftPos;
		T temp = heap[siftPosition];

		int minChildPos = 2 * siftPosition + 1;
		while (minChildPos<currentPos) {          //保证比较的条件成立
			if ((minChildPos<currentPos - 1) && (heap[minChildPos]>heap[minChildPos + 1])) {
				minChildPos++;
			}
			if (temp<heap[minChildPos]) {
				break;
			}
			else {
				heap[siftPosition] = heap[minChildPos];
				siftPosition = minChildPos;
				minChildPos = 2 * siftPosition + 1;
			}
		}
		//作用：当要进行调换的位置不满足循环要求时，说明要进行调换的位置是叶子节点，那就不需要变换咯
		heap[siftPosition] = temp;

		////////////////////////////////////////////

	}

	T& deleteTop() {
		if (currentPos<0) {
			cout << "Sorry ,this heap is empty!" << endl;
		}
		T target = heap[0];
		heap[0] = heap[currentPos - 1];
		currentPos--;
		siftDown(0);
		return target;
	}
};

int main()
{
	cout << "Hello world!" << endl;
	MinHeap<int> minHeap(7);
	minHeap.Insert(1);
	minHeap.Insert(2);
	minHeap.Insert(4);
	minHeap.Insert(3);
	minHeap.Insert(6);
	minHeap.Insert(7);
	minHeap.Insert(5);
	for (int i = 1; i <= 7; i++) {
		cout << minHeap.deleteTop() << endl;
	}
	system("pause");
	return 0;
}
