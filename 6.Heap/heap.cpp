/* 
난수를 사용하여 106 ~ 107개의 heap을 만들고 insert, delete 처리 시간과 
ordered list로서 sort된 결과를 유지하고 insert후에도 sort 결과를 유지하고, 
delete후에도 sorted 결과를 유지하기 위한 자료구조를 제안하고 구현후 처리 시간을 측정한다.
*/
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;

const int HeapSize = 1000;
enum Boolean
{
    FALSE,
    TRUE
};

template <class Type>
class Element
{
public:
    Type key;

    Element() {}
    Element(Type key) : key(key) {}
};

template <class Type>
class MaxPQ
{
public:
    virtual void Insert(const Element<Type> &) = 0;
    ;
    virtual Element<Type> *DeleteMax(Element<Type> &) = 0;
};

template <class Type>
class MaxHeap : public MaxPQ<Type>
{
public:
    MaxHeap(int sz = HeapSize)
    {
        MaxSize = sz;
        n = 0;
        heap = new Element<Type>{MaxSize + 1};
    };
    void display();
    void Insert(const Element<Type> &x);
    Element<Type> *DeleteMax(Element<Type> &);

private:
    Element<Type> *heap;
    int n;
    int MaxSize;
    void HeapEmpty() { cout << "Heap Empty"
                            << "\n"; };
    void HeapFull() { cout << "Heap Full"; };
};

template <class Type>
void MaxHeap<Type>::display()
{
    int i;
    cout << "MaxHeap:: (i, heap[i].key): ";
    for (i = 1; i <= n; i++)
        cout << "(" << i << ", " << heap[i].key << ") ";
    cout << "\n";
}

template <class Type>
void MaxHeap<Type>::Insert(const Element<Type> &x)
{
    int i;
    if (n == MaxSize)
    {
        HeapFull();
        return;
    }
    n++;
    for (i = n; 1;)
    {
        if (i == 1)
            break;
        if (x.key <= heap[i / 2].key)
            break;
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = x;
}

template <class Type>
Element<Type> *MaxHeap<Type>::DeleteMax(Element<Type> &x)
{
    int i, j;
    if (!n)
    {
        HeapEmpty();
        return 0;
    }
    x = heap[1];
    Element<Type> k = heap[n];
    n--;
    for (i = 1, j = 2; j <= n;)
    {
        if (j < n)
            if (heap[j].key < heap[j + 1].key)
                j++;
        if (k.key >= heap[j].key)
            break;
        heap[i] = heap[j];
        i = j;
        j *= 2;
    }
    heap[i] = k;
    return &x;
}

int main()
{
    clock_t start1, end1;
    double result1, result2;

    int select = 0;
    int data = 0;
    //pow(10, 6)
    MaxHeap<int> heap(10);
    Element<int> ele;

    Element<int> *deletedEle = nullptr;

    srand(time(NULL));
    start1 = clock();

    for (int i = 0; i < 10; i++)
    {
        //printf("난수 : %d \n", rand()%100);
        data = rand() % 100;
        heap.Insert(Element<int>(data));
        heap.display();
    }
    end1 = clock();
    result1 = (double)(end1 - start1) / 1000;
    cout << result1; //결과 출력

    clock_t start2, end2;
    start2 = clock();
    for (int i = 0; i < 10; i++)
    {
        deletedEle = heap.DeleteMax(ele);
        //heap.display();
    }
    end2 = clock();
    result2 = (double)(end2 - start2) / 1000;
    printf("%f초", result2); //결과 출력

    // do{
    //   cout<<endl<<"Max Tree. Select: 1 insert, 2 display, 3 delete, >=5 exit" << endl;
    //   cin >> select;
    //   switch (select) {
    //     case 1:
    //       cout<< "input value: ";
    //       cin >> data;
    //       heap.Insert(Element<int>(data));
    //       heap.display();
    //       break;
    //     case 2:
    //       heap.display();
    //       break;
    //     case 3:
    //       deletedEle = heap.DeleteMax(ele);
    //       if (deletedEle != nullptr) {
    //         cout <<"deleted element: " << deletedEle->key << endl;
    //       }
    //       cout<< "current max heap: "<<endl;
    //       heap.display();
    //       break;
    //     case 5:
    //       exit(1);
    //       break;
    //   }
    // }while(select <5);

    return 0;
}