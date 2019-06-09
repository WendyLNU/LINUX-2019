#include <iostream>

using namespace std;

template<class T>
class doubleHeap
{
public:
    doubleHeap(
        int _size,
        int _type // 1 : max heap 2 : min heap
        );
    void extractTop(T &top);
    void deleteTop();
    bool addElement(T _new_element);
    bool empty();
    bool full();
    void printHeap(int root, int level); // for debug

private:
    void swap(int i, int j);
    int leftChild(int i);
    int rightChild(int i);
    int parent(int i);
    bool comp(int i, int j); // if the nodes should exchange

private:
    T *data;
    int max_size;
    int size;
    int type;
};

template<class T>
doubleHeap<T>::doubleHeap(int _size, int _type)
{
    max_size = 10;
    if(_size >= 10)
        max_size = _size;
    data = new T[max_size];
    size = 0;
    type = 1; // default max heap
    if(_type == 1 || type == 2)
        type = _type;
}

template<class T>
void doubleHeap<T>::extractTop(T &top)
{
    if(size == 0)
        return;

    top = data[0];
}

template<class T>
void doubleHeap<T>::deleteTop()
{
    if(size == 0)
        return;

    data[0] = data[size - 1];
    size --;

    int cur = 0; // start from the root
    int lChildIndex;
    int rChildIndex;

    // begin exchanging the node and check if it's been a heap
    while(true)
    {
        if(cur >= size) // the heap is null
            break;

        rChildIndex = rightChild(cur);
        lChildIndex = leftChild(cur);

        if(lChildIndex >= size) // right child and left child has been a null
            break;
        else if(rChildIndex >= size) // rightChild null, left not
        {
            if(comp(cur, lChildIndex))
            {
                swap(cur, lChildIndex);
                cur = lChildIndex;
            }
            else
                break; // has been a heap
        }
        else // left and right are not null
        {
            if(comp(cur, rChildIndex) || comp(cur, lChildIndex))
            {
                if(comp(lChildIndex, rChildIndex))
                {
                    swap(cur, rChildIndex);
                    cur = rChildIndex;
                }
                else
                {
                    swap(cur, lChildIndex);
                    cur = lChildIndex;
                }
            }
            else
                break;
        }
    }
}

template<class T>
bool doubleHeap<T>::addElement(T _new_element)
{
    data[size] = _new_element;
    size ++;

    int cur = size - 1;
    int parentIndex;
    while(true)
    {
        if(cur == 0)
            break;

        parentIndex = parent(cur);
        if(comp(parentIndex, cur))
        {
            swap(cur, parentIndex);
            cur = parentIndex;
        }
        else
            break;
    }
	return 0;
}

template<class T>
bool doubleHeap<T>::empty()
{
    return size == 0;
}

template<class T>
bool doubleHeap<T>::full()
{
    return max_size == size;
}

template<class T>
void doubleHeap<T>::swap(int i, int j)
{
    T ex;
    ex = data[i];
    data[i] = data[j];
    data[j] = ex;
}

template<class T>
int doubleHeap<T>::leftChild(int i)
{
    return 2 * (i + 1) - 1;
}

template<class T>
int doubleHeap<T>::rightChild(int i)
{
    return 2 * (i + 1);
}

template<class T>
int doubleHeap<T>::parent(int i)
{
    return (i + i) / 2 - 1;
}

template<class T>
bool doubleHeap<T>::comp(int i, int j)
{
    if(type == 1) // max heap
    {
        return data[i] < data[j];
    }
    else // min heap
    {
        return data[i] > data[j];
    }
}

template<class T>
void doubleHeap<T>::printHeap(int root, int level)
{
    int i;

    if(root >= size)
        return;

    printHeap(leftChild(root), level + 1);
    for(i = 0; i < level; i ++)
        cout << "\t";
    cout << data[root] << endl;
    printHeap(rightChild(root), level + 1);
}

int main()
{
    int a[] = {1, 10, 6, 23, 7, 8, 90, 12, 45, 76, 33, 25, 3, 17, 70, 10};
    int i, aLen = 16, e;
    doubleHeap<int> maxHeap(100, 1);

    for(i = 0; i < aLen; i ++)
    {
        maxHeap.addElement(a[i]);
    }

    maxHeap.printHeap(0, 0);

    // heap sort
    while(!maxHeap.empty())
    {
        maxHeap.extractTop(e);
        cout << e << " ";
        maxHeap.deleteTop();

    }
    cout << "\n";
    return 0;
}
