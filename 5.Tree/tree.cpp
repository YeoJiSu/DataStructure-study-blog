// 다항식을 prefix로 변환하여 tree 생성하기
// 변수는 char 로 선언
// 연산자는 + - * / 만 사용
// 구현 성공 !
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
//Stack==>
const int DefaultSize = 10;
enum Boolean
{
    FALSE,
    TRUE
};

template <class KeyType>
class Stack
{
public:
    Stack(int MaxStackSize = DefaultSize);
    Boolean IsFull();
    Boolean IsEmpty() const;
    void Add(const KeyType &item);
    KeyType *Delete(KeyType &);
    void StackEmpty() { cout << "empty" << endl; };
    void StackFull() { cout << "full<endl"; };
    void Output();

    KeyType &Top() const; //추가
    void Pop();           //추가

private:
    KeyType *stack;
    int top;
    int MaxSize;
    void ChangingSize(KeyType *&f, const int oldSize, const int newSize); //추가
};
template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize), top(-1)
{
    if (MaxSize < 1)
        throw "Stack size must be>0";
    stack = new KeyType[MaxSize];
}
template <class KeyType>
inline Boolean Stack<KeyType>::IsFull()
{
    if (top == MaxSize - 1)
        return TRUE;
    else
        return FALSE;
}
template <class KeyType>
inline Boolean Stack<KeyType>::IsEmpty() const
{
    if (top == -1)
        return TRUE;
    else
        return FALSE;
}
template <class KeyType>
void Stack<KeyType>::Add(const KeyType &x)
{
    if (IsFull())
        StackFull();
    else
        stack[++top] = x;
}
template <class KeyType>
KeyType *Stack<KeyType>::Delete(KeyType &x)
{
    if (IsEmpty())
    {
        StackEmpty();
        return 0;
    }
    x = stack[top--];
    return &x;
}
template <class KeyType>
void Stack<KeyType>::Output()
{
    cout << "top = " << top << endl;
    for (int i = 0; i <= top; i++)
    {
        cout << i << ":" << stack[i] << endl;
    }
}
template <class KeyType>
void Stack<KeyType>::Pop()
{
    if (IsEmpty())
        throw "Stack is empty. Cannot delete";
    top--;
}
template <class KeyType>
inline KeyType &Stack<KeyType>::Top() const
{
    if (IsEmpty())
        throw "Stack is empty. Cannot access";
    return stack[top];
}
template <class KeyType>
void Stack<KeyType>::ChangingSize(KeyType *&f, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw "New length must be >= 0";

    KeyType *temp = new KeyType[newSize];
    int number = min(oldSize, newSize);
    copy(f, f + number, temp);
    delete[] f;
    f = temp;
}
int isp(char opt)
{
    if (opt == '*' || opt == '/')
        return 2;
    else if (opt == '+' || opt == '-')
        return 3;
    else
        return 8;
}

int icp(char opt)
{
    if (opt == '*' || opt == '/')
        return 2;
    else if (opt == '+' || opt == '-')
        return 3;
    else
        return 0;
}
bool isOperand(char x)
{
    if (x == '+' || x == '-' || x == '*' || x == '/' || x == '#')
        return false;
    else
        return true;
}

string Prefix(string infix)
{
    Stack<char> stack;
    stack.Add('#');

    Stack<char> temp;

    int index = infix.length() - 1;

    for (char x = infix[index]; x != '#'; x = infix[--index])
    {
        if (isOperand(x))
            temp.Add(x);
        else if (x == '(')
        {
            for (; stack.Top() != ')'; stack.Pop())
                temp.Add(stack.Top());
            stack.Pop();
        }
        else if (x == ' ')
            continue;
        else
        {
            for (; isp(stack.Top()) < icp(x); stack.Pop())
                temp.Add(stack.Top());
            stack.Add(x);
        }
    }
    while (!stack.IsEmpty())
    {
        temp.Add(stack.Top());
        stack.Pop();
    }
    string prefix;
    for (; !temp.IsEmpty(); temp.Pop())
        prefix += temp.Top();
    return prefix;
}

//Queue==>
template <class KeyType>
class Queue
{
public:
    Queue(int MaxQueueSize = 5);
    bool IsFull();
    void Add(const KeyType &item);
    bool IsEmpty();
    KeyType *Delete(KeyType &);
    void QueueEmpty() { cout << "empty" << endl; };
    void QueueFull() { cout << "full" << endl; };
    void Output();

private:
    int front;
    int rear;
    KeyType *queue;
    int MaxSize;
};
template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize)
{
    queue = new KeyType[MaxSize];
    front = rear = -1;
}
template <class KeyType>
inline bool Queue<KeyType>::IsFull()
{
    if (rear == MaxSize - 1)
        return true;
    else
        return false;
}
template <class KeyType>
inline bool Queue<KeyType>::IsEmpty()
{
    if (front == rear)
        return true;
    else
        return false;
}
template <class KeyType>
void Queue<KeyType>::Add(const KeyType &x)
{
    if (IsFull())
        QueueFull();
    else
        queue[++rear] = x;
}
template <class KeyType>
KeyType *Queue<KeyType>::Delete(KeyType &x)
{
    if (IsEmpty())
    {
        QueueEmpty();
        return 0;
    }
    x = queue[++front];
    return &x;
}
template <class KeyType>
void Queue<KeyType>::Output()
{
    cout << "front = " << front << "rear =" << rear << endl;
    for (int i = front + 1; i <= rear; i++)
    {
        cout << i << ":" << queue[i] << endl;
    }
}
//Tree==>
class Tree;
class TreeNode
{
    friend class Tree;
    friend class InorderIterator;
    friend int equal(TreeNode *, TreeNode *);

private:
    TreeNode *LeftChild;
    char data;
    TreeNode *RightChild;
    TreeNode()
    {
        LeftChild = RightChild = 0;
    };
    TreeNode(char ch, TreeNode *Lefty, TreeNode *Righty)
    {
        data = ch;
        LeftChild = Lefty;
        RightChild = Righty;
    }
};

class Tree
{
    friend int operator==(const Tree &, const Tree &);
    friend class InorderIterator;

private:
    TreeNode *root;
    void inorder(TreeNode *);
    void preorder(TreeNode *);
    void postorder(TreeNode *);
    TreeNode *copy(TreeNode *);

public:
    Tree(const Tree &);
    Tree() { root = 0; };
    bool Insert(char);
    void inorder();
    void preorder();
    void postorder();
    void NoStackInorder();
    void NonrecInorder();
    void LevelOrder();
};

// Node* Tree::InorderSucc(Node* current)
// {
//   Node* temp = current->RightChild;
//   if (current->RightChild !=null)
//     while (temp->LeftChild != null) temp = temp->LeftChild;
//     return temp;
// }
class InorderIterator
{
public:
    char *Next();
    InorderIterator(Tree tree) : t(tree)
    {
        CurrentNode = t.root;
    };

private:
    Tree t;
    Stack<TreeNode *> s;
    TreeNode *CurrentNode;
};

char *InorderIterator::Next()
{
    while (CurrentNode)
    {
        s.Add(CurrentNode);
        CurrentNode = CurrentNode->LeftChild;
    }
    if (!s.IsEmpty())
    {
        CurrentNode = *s.Delete(CurrentNode);
        char &temp = CurrentNode->data;
        CurrentNode = CurrentNode->RightChild;
        return &temp;
    }
    else
        return 0;
}

void Tree::inorder()
{
    inorder(root);
}
void Tree::preorder()
{
    preorder(root);
}
void Tree::postorder()
{
    postorder(root);
}
void Tree::inorder(TreeNode *CurrentNode)
{
    if (CurrentNode)
    {
        inorder(CurrentNode->LeftChild);
        cout << " " << CurrentNode->data;
        inorder(CurrentNode->RightChild);
    }
}
void Tree::preorder(TreeNode *CurrentNode)
{
    if (CurrentNode)
    {
        cout << CurrentNode->data << " ";
        preorder(CurrentNode->LeftChild);
        preorder(CurrentNode->RightChild);
    }
}
void Tree::postorder(TreeNode *CurrentNode)
{
    if (CurrentNode)
    {
        postorder(CurrentNode->LeftChild);
        postorder(CurrentNode->RightChild);
        cout << CurrentNode->data << " ";
    }
}
Tree::Tree(const Tree &s)
{
    root = copy(s.root);
}
TreeNode *Tree::copy(TreeNode *orignode)
{
    if (orignode)
    {
        TreeNode *temp = new TreeNode;
        temp->data = orignode->data;
        temp->LeftChild = copy(orignode->LeftChild);
        temp->RightChild = copy(orignode->RightChild);
        return temp;
    }
    else
        return 0;
}

//Driver
int operator==(const Tree &s, const Tree &t)
{
    return equal(s.root, t.root);
}

//Workhorse
int equal(TreeNode *a, TreeNode *b)
{

    if ((!a) && (!b))
        return 1;
    if (a && b && (a->data == b->data) && equal(a->LeftChild, b->LeftChild) && equal(a->RightChild, b->RightChild))
        return 1;
    return 0;
}

bool Tree::Insert(char x)
{
    TreeNode *p = root;
    TreeNode *q = 0;
    while (p)
    {
        q = p;
        if (x == p->data)
            return false;
        if (x < p->data)
            p = p->LeftChild;
        else
            p = p->RightChild;
    }
    p = new TreeNode;
    p->LeftChild = p->RightChild = 0;
    p->data = x;
    if (!root)
        root = p;
    else if (x < q->data)
        q->LeftChild = p;
    else
        q->RightChild = p;
    return true;
}

void Tree::NonrecInorder()
{
    Stack<TreeNode *> s;
    TreeNode *CurrentNode = root;
    while (1)
    {
        while (CurrentNode)
        {
            s.Add(CurrentNode);
            CurrentNode = CurrentNode->LeftChild;
        }
        if (!s.IsEmpty())
        {
            CurrentNode = *s.Delete(CurrentNode);
            cout << CurrentNode->data << " ";
            CurrentNode = CurrentNode->RightChild;
        }
        else
            break;
    }
}
void Tree::LevelOrder()
{
    Queue<TreeNode *> q;
    TreeNode *CurrentNode = root;
    while (CurrentNode)
    {
        cout << CurrentNode->data << endl;
        if (CurrentNode->LeftChild)
            q.Add(CurrentNode->LeftChild);
        if (CurrentNode->RightChild)
            q.Add(CurrentNode->RightChild);
        CurrentNode = *q.Delete(CurrentNode);
    }
}
void Tree::NoStackInorder()
{
    if (!root)
        return;
    TreeNode *top = 0, *LastRight = 0, *p, *q, *r, *r1;
    p = q = root;
    while (1)
    {
        while (1)
        {
            if ((!p->LeftChild) && (!p->RightChild))
            {
                cout << p->data;
                break;
            }
            if (!p->LeftChild)
            {
                cout << p->data;
                r = p->RightChild;
                p->RightChild = q;
                q = p;
                p = r;
            }
            else
            {
                r = p->LeftChild;
                p->LeftChild = q;
                q = p;
                p = r;
            }
        }
        TreeNode *av = p;
        while (1)
        {
            if (p == root)
                return;
            if (!q->LeftChild)
            {
                r = q->RightChild;
                q->RightChild = p;
                p = q;
                q = r;
            }
            else if (!q->RightChild)
            {
                r = q->LeftChild;
                q->LeftChild = p;
                p = q;
                q = r;
                cout << p->data;
            }
            else
            {
                if (q == LastRight)
                {
                    r = top;
                    LastRight = r->LeftChild;
                    top = r->RightChild;
                    r->LeftChild = r->RightChild = 0;
                    r = q->RightChild;
                    q->RightChild = p;
                    p = q;
                    q = r;
                }
                else
                {
                    cout << q->data;
                    av->LeftChild = LastRight;
                    av->RightChild = top;
                    top = av;
                    LastRight = q;
                    r = q->LeftChild;
                    q->LeftChild = p;
                    r1 = q->RightChild;
                    q->RightChild = r;
                    p = r1;
                    break;
                }
            }
        }
    }
}

int main()
{
    Tree t, tx;
    int eq = -1;
    char select = 'i';
    int max = 0, x = 0;
    while (select != 'q')
    {
        string input, fixed;
        cout << "BinarySearchTree. Select i:Insert, d:Inorder, e:NonrecInorder, f:preorder, g:postorder, h:copy and compare, q:Quit => ";
        cin >> select;
        switch (select)
        {
        case 'i':
            cout << "Infix식을 입력하세요: ";
            cin >> input;
            fixed = Prefix('#' + input);
            //입력받은 input의 앞에 '#'을 붙혀서 연산

            cout << "Prefix식 : ";
            unsigned int i;
            for (i = 1; i < fixed.length(); i++)
            {
                cout << fixed[i] << " ";
                if (!t.Insert(fixed[i]))
                    cout << "Inset Duplicated data" << endl;
            }
            cout << endl;
            break;
        case 'd':
            t.inorder();
            cout << endl;
            break;
        case 'e':
            t.NonrecInorder();
            cout << endl;
            break;
        case 'f':
            t.preorder();
            cout << endl;
            break;
        case 'g':
            t.postorder();
            cout << endl;
            break;
        case 'h':
            tx = t;               // copy
            eq = (tx == Tree(t)); // compare
            if (eq)
            {
                cout << "compare result: true" << endl;
            }
            else
            {
                cout << "compare result: false" << endl;
            }
            break;
        case 'q':
            cout << "Quit" << endl;
            break;
        default:
            cout << "WRONG INPUT" << endl;
            cout << "Re-Enter" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}