/*
힙정렬 알고리즘
*/
#include <stdio.h>
#include <iostream>
using namespace std;

int number = 9;
int heap[9] = {7, 6, 5, 8, 3, 5, 9, 1, 6};

int main(void)
{
    // 먼저 전체 트리구조를 힙 구조로 바꾸어준다. (최대 힙 구조!!)
    for (int i = 1; i < number; i++)
    {
        int c = i;
        do
        {
            int root = (c - 1) / 2; // 특정한 원소의 부모를 가리킴
            if (heap[root] < heap[c])
            {
                int temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            c = root; // 자식의 부모로 이동해서 반복적으로 수행해주면 됨.
        } while (c != 0);
    }
    //크기를 줄여가며 반복적으로 힙을 구성
    for (int i = number - 1; i >= 0; i--)
    {
        // 1. 전체트리의 root 노드와 가장 마지막 노드를 바꾸어준다.
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;
        int root = 0;
        int c;
        do
        {
            c = 2 * root + 1;
            // 자식 중에 더 큰 값을 찾기
            if (heap[c] < heap[c + 1] && c < i - 1)
            {
                c++;
            }
            // 루트보다 자식이 더 크면 교환
            if (heap[root] < heap[c] && c < i)
            {
                int temp = heap[root];
                heap[root] = heap[c];
                heap[c] = temp;
            }
            root = c;
        } while (c < i);
    }
    for (int i = 0; i < number; i++)
    {
        cout << heap[i] << " ";
    }
}