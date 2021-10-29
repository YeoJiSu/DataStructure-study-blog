#include <iostream>
#include <string>
#include <cctype>
using namespace std;
enum boolean
{
    FALSE,
    TRUE
};
struct Data
{
    int id; // id = 0,1,2 if the node contains char, int, float
    union
    {
        int i;
        char c;
        float f;
    };
    bool operator==(Data const d);
};
/*
class CombinedNode {
  //use union to merge different node types into one class definition
  friend class List;
  friend class ListIterator;
  private:
    Data data;
    CombinedNode* first;
};
class List {
  friend class ListIterator;
  public: 
  private:
    CombinedNode* first;
};
*/
class Node
{
    friend class List;
    friend class ListIterator;
    friend int equal(Node *, Node *);
    // equal 함수 정의
protected:
    Node *link;
    virtual Data GetData() = 0;
};

template <class Type>
class DerivedNode : public Node
{
    friend class List;
    friend class ListIterator;

public:
    DerivedNode(Type item) : data(item) { link = 0; }

private:
    Type data;
    Data GetData();
};

template <>
Data DerivedNode<char>::GetData()
{
    Data t;
    t.id = 0;
    t.c = data;
    return t;
}

template <>
Data DerivedNode<int>::GetData()
{
    Data t;
    t.id = 1;
    t.i = data;
    return t;
}
template <>
Data DerivedNode<float>::GetData()
{
    Data t;
    t.id = 2;
    t.f = data;
    return t;
}

class List
{
    friend class ListIterator;
    friend int equal(Node *, Node *);
    // equal 함수 정의
private:
    Node *first;
    Node *copy(Node *); // private function copy
public:
    List() { first = 0; }
    ~List(){};
    void Add();
    void Delete();
    Node *Search(Data);
    void copy(const List &); // public function copy
};
int equal(Node *s, Node *t)
{
    int x;
    if ((!s) && (!t))
        return 1;
    // if (s&&t (s))
    //어떻게 구현할까 ...
    return 0;
}
// public function copy
void List::copy(const List &l)
{
    first = copy(l.first);
}
// private function copy
Node *List::copy(Node *p)
{
    Node *q = 0;

    // if (p) {
    //   q =  new Node;
    //   q->

    // }
    //음.. 여기를 어떻게 구현하지?
    return q;
}
class ListIterator
{
public:
    ListIterator(const List &l) : list(l), current(l.first){};
    ListIterator &operator++();
    ListIterator operator++(int);
    Data *First();
    Node *Next();
    bool NotNull();
    bool NextNotNull();
    Data GetCurrent();
    Node *CurrentPointer();

private:
    const List &list;
    Node *current;
    Data temp;
};
bool Data::operator==(Data const d)
{
    switch (d.id)
    {
    case 0:
        if (this->c == d.c)
            return TRUE;
        break;
    case 1:
        if (this->i == d.i)
            return TRUE;
        break;
    case 2:
        if (this->f == d.f)
            return TRUE;
        break;
    }
    return FALSE;
}

void List::Add()
{
    int value;
    float num;
    char c;
    cout << "Please input data type. 0 = char, 1 = int , 2 = float" << endl;
    cin >> value;
    if (!first)
    {
        switch (value)
        {
        case 0:
            cin >> c;
            first = new DerivedNode<char>(c);
            break;
        case 1:
            cin >> value;
            first = new DerivedNode<int>(value);
            break;
        case 2:
            cin >> num;
            first = new DerivedNode<float>(num);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (value)
        {
        case 0:
        {
            cin >> c;
            Node *n = new DerivedNode<char>(c);
            n->link = first;
            first = n;
            break;
        }
        case 1:
        {
            cin >> value;
            Node *na = new DerivedNode<int>(value);
            na->link = first;
            first = na;
            break;
        }
        case 2:
        {
            cin >> num;
            Node *nb = new DerivedNode<float>(num);
            nb->link = first;
            first = nb;
            break;
        }
        default:
            break;
        }
    }
}
void List::Delete()
{
    int value;
    char c;
    float num;
    Data tmp;
    if (first == NULL)
        cout << "List is empty" << endl;
    else
    {
        cout << "Please input data type. 0 = char, 1 = int, 2 = float" << endl;
        cin >> value;
        cin.clear();
        switch (value)
        {
        case 0:
            cin >> c;
            tmp.c = c;
            tmp.id = 0;
            break;
        case 1:
            cin >> value;
            tmp.i = value;
            tmp.id = 1;
            break;
        case 2:
            cin >> value;
            tmp.f = num;
            tmp.id = 2;
            break;
        default:
            break;
        }
        Node *s = Search(tmp);
        if (s == first && !(s->link->GetData() == tmp))
        {
            Node *tmp;
            tmp = s;
            s = s->link;
            first = s;
            delete tmp;
        }
        else if (s)
        {
            Node *tmp;
            tmp = s->link;
            s->link = s->link->link;
            delete tmp;
        }
    }
}
Node *List ::Search(Data tmp)
{
    ListIterator li(*this);
    while (li.NotNull())
    {
        if (li.GetCurrent() == tmp)
            return li.CurrentPointer();
        else if (li.Next()->GetData() == tmp)
            return li.CurrentPointer();
        ++li;
    }
    return NULL;
}

Data *ListIterator::First()
{
    if (list.first)
    {
        temp = list.first->GetData();
        return &temp;
    }
    return 0;
}
Data ListIterator::GetCurrent()
{
    return current->GetData();
}
Node *ListIterator::Next()
{
    return current->link;
}
Node *ListIterator::CurrentPointer()
{
    return current;
}
ListIterator &ListIterator::operator++()
{
    current = current->link;
    return *this;
}
ListIterator ListIterator::operator++(int)
{
    ListIterator old = *this;
    current = current->link;
    return old;
}
bool ListIterator::NotNull()
{
    if (current)
        return TRUE;
    else
        return FALSE;
}
bool ListIterator::NextNotNull()
{
    if (current->link)
        return TRUE;
    else
        return FALSE;
}
ostream &operator<<(ostream &os, Data &retvalue)
{
    switch (retvalue.id)
    {
    case 0:
        cout << retvalue.c;
        break;
    case 1:
        cout << retvalue.i;
        break;
    case 2:
        cout << retvalue.f;
        break;
    default:
        break;
    }
    return os;
}
void PrintAll(const List &l)
{
    ListIterator li(l);
    if (!li.NotNull())
        return;
    Data retvalue = *li.First();
    cout << retvalue;
    if (li.NextNotNull())
        cout << " + ";
    while (li.NextNotNull() == true)
    {
        ++li; //current 를 증가시킴
        // retvalue = retvalue+ *li.Next();
        retvalue = li.GetCurrent(); //현재 current가 가르키는 node의 값을 가져옴
        cout << retvalue;
        if (li.NextNotNull())
            cout << " + ";
    }
}
//float sum(l); //sum of all floating points

int main()
{
    //cout << "Hello World!\n";
    List l;
    //implement heterogeneous linked stacks and queues
    char select;
    int max = 0, x = 0;
    cout << "Select command a: add data, d: delete data, p: print all, q: quit =>";
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            l.Add();
            break;
        case 'd':
            l.Delete();
            break;
        case 'p':
            cout << "print all: ";
            PrintAll(l);
            cout << endl;
            break;
        case 'q':
            cout << "Quit" << endl;
            break;
        default:
            cout << "WRONG INPUT" << endl;
            cout << "Re-Enter" << endl;
            break;
        }
        cout << "Select command a: add data, d: delete data, p: print all, q: quit => ";
        cin >> select;
    }
    system("pause");
    return 0;
}