#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
using namespace std;

template <class T>
class Term
{
public:
    //All members of Term are public by default
    T coef; //coefficient
    T exp;  //exponent
    Term()
    {
        coef = 0;
        exp = 0;
    }
    Term(T c, T e) : coef(c), exp(e) {}
    Term Set(int c, int e)
    {
        coef = c;
        exp = e;
        return *this;
    };
};

template <class T>
class Chain; //forward declaration
template <class T>
class ChainIterator;

template <typename valType>
inline ostream &operator<<(ostream &os, const Term<valType> &term)
{
    os << term.coef << "x^" << term.exp;
    return os;
}

template <class T>
class ChainNode
{
    friend class Chain<T>;
    friend class ChainIterator<T>;

public:
    ChainNode(){};
    ChainNode(const T &);

private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class Chain
{
public:
    Chain() { first = 0; };
    void Delete(void); //delete the first element after first
    int Length();
    void Add(const T &element); //add a new node after first
    void Invert();
    void Concatenate(Chain<T> b);
    void InsertBack(const T &element);
    void displayAll();

    ChainIterator<T> begin() const { return ChainIterator<T>(first); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

private:
    ChainNode<T> *first;
};

template <class T>
class ChainIterator
{
private:
    //const Chain<T>* list; //refers to an existing list
    ChainNode<T> *current; //points to a node in list
public:
    //ChainIterator(const Chain<T>& l) :list(l), current(l.first) {};
    ChainIterator() {}
    ChainIterator(ChainNode<T> *node) : current(node) {}
    //dereferencing operators
    T &operator*() const { return current->data; }
    T *operator->() const { return &current->data; }
    bool operator&&(ChainIterator<T> iter) const
    {
        return current != NULL && iter.current != NULL;
    }
    bool isEmpty() const { return current == NULL; }
    //increment
    ChainIterator<T> operator++(int); //post increment
    ChainIterator<T> &operator++();   //preincrement
    bool NotNull();                   //check the current element in list is non-null
    bool NextNotNull();               //check the next element in list is non-null
    T *Next();                        //return a pointer to the next element of list
};
template <class T>
ChainNode<T>::ChainNode(const T &element)
{
    data = element;
    link = 0;
}
template <class T>
void Chain<T>::Delete(void) //delete the first element after first
{
    ChainNode<T> *current, *next;
    next = first->link;
    if (first != nullptr) //non-empty list
    {
        ChainNode<T> *temp = first;
        first = next;
        delete temp;
    }
    else
        cout << "Empty List: not deleted" << endl;
}
template <class T>
void Chain<T>::Add(const T &element) //add a new node after first
{
    ChainNode<T> *newnode = new ChainNode<T>(element);
    if (!first) //insert into empty list
    {
        first = newnode;
        return;
    }
    //insert a new node after first
    newnode->link = first;
    first = newnode;
}

template <class T>
void Chain<T>::Invert()
{
    ChainNode<T> *p = first, *q = 0; //q trails p
    while (p)
    {
        ChainNode<T> *r = q;
        q = p;       //r trails q
        p = p->link; //p moves to next node
        q->link = r; //link q to preceding node
    }
    first = q;
}

template <class T>
void Chain<T>::Concatenate(Chain<T> b)
{
    if (!first)
    {
        first = b.first;
        return;
    }
    if (b.first)
    {
        for (ChainNode<T> *p = first; p->link; p = p->link)
        {
            p->link = b.first;
        }
    }
}

template <class T>
void Chain<T>::InsertBack(const T &element)
{
    ChainNode<T> *newnode = new ChainNode<T>(element);
    if (!first)
    {
        first = newnode;
        return;
    }
    ChainNode<T> *curr = first;
    while (curr->link != NULL)
    {
        curr = curr->link;
    }
    curr->link = newnode;
}
template <class T>
void Chain<T>::displayAll()
{
    if (!first)
        return;
    ChainNode<T> *curr = first;
    while (curr != NULL)
    {
        cout << curr->data << "+";
        curr = curr->link;
    }
    cout << endl;
}
// pre-increment
template <class T>
ChainIterator<T> &ChainIterator<T>::operator++()
{
    current = current->link;
    return *this;
}

//post increment
template <class T>
ChainIterator<T> ChainIterator<T>::operator++(int)
{
    ChainIterator<T> old = *this;
    current = current->link;
    return old;
}

//check the current element in list is non-null
template <class T>
bool ChainIterator<T>::NotNull()
{
    if (current)
        return 1;
    else
        return 0;
}

//check the next element in list is non-null
template <class T>
bool ChainIterator<T>::NextNotNull()
{
    if (current && current->link)
        return 1;
    else
        return 0;
}

//return a pointer to the next element of list
template <class T>
T *ChainIterator<T>::Next()
{
    if (current)
    {
        current = current->link;
        return &current->data;
    }
    else
        return 0;
}

/*
class Polynomial
*/
template <class T>
class Polynomial
{
public:
    Polynomial() {}
    Polynomial(Chain<Term<T> > *terms) : poly(terms) {}
    Polynomial<T> operator+(const Polynomial<T> &b) const;
    void add(T coef, T exponent);
    void addAll(Polynomial<T> *poly);
    void display();

    //T Evaluate(T&) const;
    int Eval(int a);
    Polynomial<T> operator*(const Polynomial<T> &b) const;
    Polynomial<T> Multiply(Polynomial<T> &);
    // Polynomial(const Polynomial& p);
    // friend istream& operator >> (istream&, Polynomial&);
    friend ostream &operator<<(ostream &, Polynomial &);
    // const Polynomial& operator = (const Polynomial&) const;
    //~Polynomial();
    Polynomial operator-(const Polynomial &) const;

private:
    Chain<Term<T> > poly;
};

//구현한 부분
ostream &operator<<(ostream &os, Polynomial<int> &p)
{
    p.poly.displayAll();
    return os;
}

//구현한 부분
template <class T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T> &b) const
{
    Term<T> temp;
    ChainIterator<Term<T> > ai = poly.begin(), bi = b.poly.begin();
    Polynomial<T> c;

    while (ai && bi)
    { //current nodes are not null

        if (ai->exp == bi->exp)
        {
            int sum = ai->coef - bi->coef;
            if (sum)
                c.poly.InsertBack(temp.Set(sum, ai->exp));
            ai++, bi++; //advance to next term
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.InsertBack(temp.Set(-1 * (bi->coef), bi->exp));
            bi++; //next term of b
        }
    }

    while (!ai.isEmpty())
    { //copy rest of a
        c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
        ai++;
    }
    while (!bi.isEmpty())
    { //copy rest of b
        c.poly.InsertBack(temp.Set(-1 * (bi->coef), bi->exp));
        bi++;
    }
    return c;
}

template <class T>
int Polynomial<T>::Eval(int a)
{
    Term<T> temp;
    ChainIterator<Term<T> > ai = poly.begin();

    int result = 0;

    while (ai.NotNull())
    {
        result += ai->coef * pow(a, ai->exp);
        ai.Next();
    }
    return result;
}
template <class T>
void Polynomial<T>::add(T coef, T exponent)
{
    Term<T> *newTerm = new Term<T>(coef, exponent);
    this->poly.Add(*newTerm);
}

template <class T>
void Polynomial<T>::addAll(Polynomial<T> *b)
{
    ChainIterator<Term<T> > iterB = b->poly.begin();

    while (iterB.NotNull())
    {
        Term<T> dataB = *iterB;
        add(dataB.coef, dataB.exp);
        iterB.Next();
    }
}

template <class T>
void Polynomial<T>::display()
{
    poly.displayAll();
}

template <class T>
Polynomial<T> Polynomial<T>::Multiply(Polynomial<T> &b)
{
    Term<T> temp;
    ChainIterator<Term<T> > ai = poly.begin(), bi = b.poly.begin();
    Polynomial<T> c;
    while (!ai.isEmpty())
    {
        while (!bi.isEmpty())
        {
            int coeff = ai->coef * bi->coef;
            int expp = ai->exp + bi->exp;
            if (coeff)
                c.poly.InsertBack(temp.Set(coeff, expp));
            bi++;
        }
        ai++;
        bi = b.poly.begin();
    }
    return c;
}

template <class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T> &b) const
{
    Term<T> temp;
    ChainIterator<Term<T> > ai = poly.begin(), bi = b.poly.begin();
    Polynomial<T> c;

    while (ai && bi)
    { //current nodes are not null

        if (ai->exp == bi->exp)
        {
            int sum = ai->coef + bi->coef;
            if (sum)
                c.poly.InsertBack(temp.Set(sum, ai->exp));
            ai++, bi++; //advance to next term
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
            bi++; //next term of b
        }
    }

    while (!ai.isEmpty())
    { //copy rest of a
        c.poly.InsertBack(temp.Set(ai->coef, ai->exp));
        ai++;
    }
    while (!bi.isEmpty())
    { //copy rest of b
        c.poly.InsertBack(temp.Set(bi->coef, bi->exp));
        bi++;
    }
    return c;
}
template <class T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T> &b) const
{
    Term<T> temp;
    ChainIterator<Term<T> > ai = poly.begin(), bi = b.poly.begin();

    Polynomial<T> c;

    while (!ai.isEmpty())
    {
        while (!bi.isEmpty())
        {
            int coeff = ai->coef * bi->coef;
            int expp = ai->exp + bi->exp;
            if (coeff)
                c.poly.InsertBack(temp.Set(coeff, expp));
            bi++;
        }
        ai++;
        bi = b.poly.begin();
    }

    return c;
}

int main(void)
{

    Polynomial<int> a, b, sum, sub, mul1, mul2;

    char select;
    Term<int> *tempTerm;
    ChainNode<Term<int> > cn;
    Chain<Term<int> > ca, cb;
    ChainIterator<Term<int> > iter;
    int c, e;

    cout << endl
         << "Select command: a: Add_a, b: Add_b, p: a + b, s: a - b, m: a * b, d: DisplayAll, e: a(5)=? b(5)=? , q: exit" << endl;
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            cout << "Add a new term to a: " << endl;
            cout << "input coef: ";
            cin >> c;
            cout << "input exp: ";
            cin >> e;
            a.add(c, e);
            break;
        case 'b':
            cout << "Add a new term to b: " << endl;
            cout << "input coef: ";
            cin >> c;
            cout << "input exp: ";
            cin >> e;
            b.add(c, e);
            break;
        case 'p': //a+b
            //cout << "a+b: ";
            //a.addAll(&b);
            cout << "a= ";
            a.display();
            cout << "b= ";
            b.display();
            sum = a + b;
            //cout << sum;
            cout << "a+b: "; //1. f(x)+f(y) 구현
            sum.display();
            break;
        case 's':
            cout << "a= ";
            cout << a;
            cout << "b= ";
            cout << b;
            cout << "a-b= "; //5. f(x)-g(x) 구현함
            sub = a - b;
            cout << sub;
            break;
        case 'm':
            cout << "a= ";
            a.display();
            cout << "b= ";
            b.display();
            mul1 = a * b; // 2. f(x)*g(x) 구현함
            cout << "(mul1)a*b = ";
            mul1.display();
            mul2 = a.Multiply(b); // Multiply 구현함
            cout << "(mul2)a.Multiply(b) = ";
            mul2.display();
            break;
        case 'e': // 3. f(5) 구현함
            cout << "a(5)= ";
            cout << a.Eval(5) << endl;
            cout << "b(5)= ";
            cout << b.Eval(5) << endl;
            break;
        case 'd':
            cout << "display all: " << endl;
            cout << a; //4. cout<<f 구현함
            cout << b;
            break;
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
        }
        cout << endl;
        cout << "Select command: a: Add_a, b: Add_b, p: a + b, s: a - b, m: a * b, d: DisplayAll, e: a(5)=? b(5)=? , q: exit" << endl;
        cin >> select;
    }
    system("pause");
    return 0;
}