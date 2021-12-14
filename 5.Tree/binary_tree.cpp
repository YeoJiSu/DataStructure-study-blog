#include <iostream>

using namespace std;

int number = 15;

// 하나의 노드 정보를 선언한다.
typedef struct node *treePointer;
typedef struct node
{
    int data;
    treePointer leftChild, rightChild;
} node;

// 전위 순회
void preorder(treePointer ptr)
{
    if (ptr)
    { //포인터가 어떠한 데이터를 가지고 있다면
        cout << ptr->data << " ";
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}
// 중위 순회
void inorder(treePointer ptr)
{
    if (ptr)
    { //포인터가 어떠한 데이터를 가지고 있다면
        inorder(ptr->leftChild);
        cout << ptr->data << " ";
        inorder(ptr->rightChild);
    }
}
// 후위 순회
void postorder(treePointer ptr)
{
    if (ptr)
    { //포인터가 어떠한 데이터를 가지고 있다면
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        cout << ptr->data << " ";
    }
}
int main(void)
{
    // 그래프 만들기
    node nodes[number + 1];
    for (int i = 1; i <= number; i++)
    {
        nodes[i].data = i;
        nodes[i].leftChild = NULL;
        nodes[i].rightChild = NULL;
    }
    for (int i = 1; i <= number; i++)
    {
        if (i % 2 == 0)
        {
            // 부모의 left가 자기자신 가리키도록
            nodes[i / 2].leftChild = &nodes[i];
        }
        else
        {
            nodes[i / 2].rightChild = &nodes[i];
        }
    }
    preorder(&nodes[1]);
    cout << endl;
    inorder(&nodes[1]);
    cout << endl;
    postorder(&nodes[1]);
    cout << endl;
}
