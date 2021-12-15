/*
202055565 여지수 
1번 문제
*/
/*
AOE network
*/
#include <iostream>
#include <string>

using namespace std;

namespace topo
{
    class Pair
    {
    public:
        int vertex, dur;
        Pair() {}
        Pair(int vertex, int dur) : vertex(vertex), dur(dur) {}
    };

    enum Boolean
    {
        FALSE,
        TRUE
    };

    template <class Type>
    class List;
    template <class Type>
    class ListIterator;

    template <class Type>
    class ListNode
    {
        friend class List<Type>;
        friend class ListIterator<Type>;

    private:
        Type data;
        ListNode *link;
        ListNode(Type);
    };

    template <class Type>
    ListNode<Type>::ListNode(Type Default)
    {
        data = Default;
        link = 0;
    }

    template <class Type>
    class List
    {
        friend class ListIterator<Type>;

    public:
        List() { first = 0; };
        void Insert(Type);
        void Delete(Type);

    private:
        ListNode<Type> *first;
    };

    template <class Type>
    void List<Type>::Insert(Type k)
    {
        ListNode<Type> *newnode = new ListNode<Type>(k);
        newnode->link = first;
        first = newnode;
    }
    /*
  template <class Type>
  void List<Type>::Delete(Type k)
  {
      ListNode<Type> *previous = 0;
      ListNode<Type> *current;
      for (current = first; current && current->data != k;
           previous = current, current = current->link)
          ;
      if (current)
      {
          if (previous)
              previous->link = current->link;
          else
              first = first->link;
          delete current;
      }
  }
  */
    template <class Type>
    class ListIterator
    {
    public:
        ListIterator(const List<Type> &l) : list(l) { current = l.first; }
        Type *First();
        Type *Next();
        bool NotNull();
        bool NextNotNull();

    private:
        const List<Type> &list;
        ListNode<Type> *current;
    };

    template <class Type>
    Type *ListIterator<Type>::First()
    {
        if (current)
            return &current->data;
        else
            return 0;
    }

    template <class Type>
    Type *ListIterator<Type>::Next()
    {
        current = current->link;
        return &current->data;
    }

    template <class Type>
    bool ListIterator<Type>::NotNull()
    {
        if (current)
            return true;
        else
            return false;
    }

    template <class Type>
    bool ListIterator<Type>::NextNotNull()
    {
        if (current->link)
            return true;
        else
            return false;
    }

    //template <class Type>
    ostream &operator<<(ostream &os, List<char> &l)
    {
        ListIterator<char> li(l);
        if (!li.NotNull())
            return os;
        os << *li.First() << endl;
        while (li.NextNotNull())
            os << *li.Next() << endl;
        return os;
    }
    class Graph
    {
    private:
        List<Pair> *HeadNodes;
        int *count;
        int *ee;
        int *le;
        int n;

    public:
        Graph(const int vertices = 0) : n(vertices)
        {
            HeadNodes = new List<Pair>[n];
            count = new int[n];
            ee = new int[n];
            le = new int[n];
            for (int i = 0; i < n; i++)
            {
                count[i] = 0;
                ee[i] = 0;
                le[i] = 0;
            }
        };
        ~Graph()
        {
            delete[] count;
            delete[] ee;
            delete[] le;
            delete[] HeadNodes;
        }
        void Setup4();
        void EarlyActivity();
        void EarlyActivity_display();
        void LateActivity();
        void LateActivity_display();

        void display_early_late_criticalActivity();

        void TopologicalOrder();

        void addEdge(int start, int end, int duration)
        {
            if (start < 0 || end >= n)
            {
                cout << "the insert node is out of bound" << endl;
                return;
            }
            ListIterator<Pair> iter(HeadNodes[start]); // check duplication
            for (Pair *first = iter.First(); iter.NotNull(); first = iter.Next())
            {
                if (first->vertex == end)
                {
                    cout << "already exists" << endl;
                    return;
                }
            }
            Pair pair(end, duration);
            HeadNodes[start].Insert(pair);
            count[end]++;
        }
        void printAdjacencyLists()
        {
            cout << "adjacency lists: " << endl;
            for (int i = 0; i < n; i++)
            {
                List<Pair> list = HeadNodes[i];
                cout << "in-degree count = " << count[i] << ", " << i << " ";
                ListIterator<Pair> iter(list);
                if (!iter.NotNull())
                {
                    cout << "->null" << endl;
                }
                else
                {
                    for (Pair *first = iter.First(); iter.NotNull(); first = iter.Next())
                    {
                        cout << "->(vertex " << first->vertex << ",dur = " << first->dur << ")";
                    }
                    cout << endl;
                }
            }
        }
        Graph *inverseGraph() const
        {
            Graph *newG = new Graph(n);
            for (int i = 0; i < n; i++)
            {
                List<Pair> list = HeadNodes[i];
                ListIterator<Pair> iter(list);
                if (iter.NotNull())
                {
                    for (Pair *first = iter.First(); iter.NotNull(); first = iter.Next())
                    {
                        newG->addEdge(first->vertex, i, first->dur);
                    }
                }
            }
            return newG;
        }

    private:
        void displayArr(int *arr, int size) const
        {
            if (!arr)
                return;
            for (int i = 0; i < size; i++)
            {
                if (arr[i] < 10)
                    cout << arr[i] << " ";
                else
                    cout << arr[i] << " ";
            }
        }
        void displayStack(int top, int *countArr) const
        {
            cout << "stack=[";
            for (int i = 0; i < n; i++)
            {
                cout << top << ", ";
                top = countArr[top];
                if (top == -1)
                    break;
            }
            cout << "]" << endl;
        }
        List<Pair> *getAdjacencyLists()
        {
            return this->HeadNodes;
        }
        int *getCountArr()
        {
            return this->count;
        }
    };
    void Graph::TopologicalOrder()
    {
        int top = -1;
        for (int i = 0; i < n; i++)
            if (count[i] == 0)
            {
                count[i] = top;
                top = i;
            }
        for (int i = 0; i < n; i++)
        {
            if (top == -1)
            {
                cout << " network has a cycle " << endl;
                return;
            }
            else
            {
                int j = top;
                top = count[top];
                cout << j << endl;
                ListIterator<Pair> li(HeadNodes[i]);
                if (!li.NotNull())
                    continue;
                int k = (*li.First()).vertex;
                while (1)
                {
                    count[k]--;
                    if (count[k] == 0)
                    {
                        count[k] = top;
                        top = k;
                    }
                    if (li.NextNotNull())
                        k = (*li.Next()).vertex;
                    else
                        break;
                }
            }
        }
    }
    void Graph::Setup4()
    {
        addEdge(0, 1, 5);
        addEdge(0, 2, 6);
        addEdge(1, 3, 3);
        addEdge(2, 3, 6);
        addEdge(2, 4, 3);
        addEdge(3, 4, 3);
        addEdge(3, 5, 4);
        addEdge(3, 6, 4);
        addEdge(4, 6, 1);
        addEdge(4, 7, 4);
        addEdge(5, 9, 4);
        addEdge(6, 8, 5);
        addEdge(7, 8, 2);
        addEdge(8, 9, 2);
    }
    void Graph::display_early_late_criticalActivity()
    {
        EarlyActivity();
        LateActivity();
        cout << endl
             << endl;
        for (int i = 0; i < n; i++)
        {
            List<Pair> list = HeadNodes[i];
            ListIterator<Pair> iter(list);
            if (iter.NotNull())
            {
                for (Pair *first = iter.First(); iter.NotNull(); first = iter.Next())
                {
                    int earlyTime = ee[i];
                    int lateTime = le[first->vertex] - first->dur;
                    int slack = lateTime - earlyTime;
                    string critical;
                    if (slack == 0)
                        critical = "Yes";
                    else
                        critical = "No";
                    cout << "edge(" << i << "->"
                         << first->vertex << "), early time = "
                         << earlyTime << ", late time = "
                         << lateTime
                         << ", slack = " << slack
                         << ", critical = " << critical << endl;
                }
            }
        }
    }
    void Graph::LateActivity_display()
    {
        for (int i = 0; i < n; i++)
        {
            ee[i] = 0;
        }
        EarlyActivity();
        Graph *inversedG = this->inverseGraph();
        List<Pair> *inversedHeadNodes = inversedG->getAdjacencyLists();
        int *inversedCount = inversedG->getCountArr();
        cout << endl
             << endl;
        //inversedG->printAdjacencyLists();
        int max = -1;
        for (int i = 0; i < n; i++)
        {
            if (ee[n - 1] > max)
                max = ee[n - 1];
        }
        for (int i = 0; i < n; i++)
        {
            le[i] = max;
        }
        int top = -1;
        for (int i = 0; i < n; i++)
        {
            if (inversedCount[i] == 0)
            {
                inversedCount[i] = top;
                top = i;
            }
        }
        cout << "le\t\t  0  1  2  3  4  5  6  7  8  9" << endl;
        cout << "initial   ";
        displayArr(le, n);
        displayStack(top, inversedCount);
        for (int i = 0; i < n; i++)
            if (top == -1)
            {
                cout << "network has a cycle" << endl;
                return;
            }
            else
            {
                int j = top;
                top = inversedCount[top];
                cout << "output " << j << "; ";
                ListIterator<Pair> li(inversedHeadNodes[j]);
                if (!li.NotNull())
                    continue;
                Pair p = *li.First();
                while (1)
                {
                    int k = p.vertex;
                    if (le[k] > le[j] - p.dur)
                        le[k] = le[j] - p.dur;
                    inversedCount[k]--; // 괄호가 필요 없나?
                    if (inversedCount[k] == 0)
                    {
                        inversedCount[k] = top;
                        top = k;
                    }
                    if (li.NextNotNull())
                        p = *li.Next();
                    else
                        break;
                }
                displayArr(le, n);
                displayStack(top, inversedCount);
            }
        displayArr(le, n);
        delete inversedG;
        cout << endl
             << endl;
    }

    void Graph::LateActivity()
    {
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            ee[i] = 0;
        }
        //EarlyActivity();
        Graph *inversedG = this->inverseGraph();
        List<Pair> *inversedHeadNodes = inversedG->getAdjacencyLists();
        int *inversedCount = inversedG->getCountArr();
        int max = -1;

        for (int i = 0; i < n; i++)
        {
            if (ee[n - 1] > max)
                max = ee[n - 1];
        }
        for (int i = 0; i < n; i++)
        {
            le[i] = max;
        }
        int top = -1;
        for (int i = 0; i < n; i++)
        {
            if (inversedCount[i] == 0)
            {
                inversedCount[i] = top;
                top = i;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (top == -1)
            {
                cout << "network has a cycle" << endl;
                return;
            }
            else
            {
                int j = top;
                top = inversedCount[top];
                ListIterator<Pair> li(inversedHeadNodes[j]);
                if (!li.NotNull())
                    continue;
                Pair p = *li.First();
                while (1)
                {
                    int k = p.vertex;
                    if (le[k] > le[j] - p.dur)
                    {
                        le[k] = le[j] - p.dur;
                        cout << "le[" << k << "]=min{le[" << j << "]-duration of<" << j << "," << k << ">}" << endl;
                    }
                    inversedCount[k]--;
                    if (inversedCount[k] == 0)
                    {
                        inversedCount[k] = top;
                        top = k;
                    }
                    if (li.NextNotNull())
                        p = *li.Next();
                    else
                        break;
                }
            }
        }
        delete inversedG;
    }

    void Graph::EarlyActivity()
    {
        cout << endl;
        int *countArr = new int[n];
        for (int i = 0; i < n; i++)
        {
            countArr[i] = count[i];
        }
        int top = -1;
        for (int i = 0; i < n; i++)
        {
            if (countArr[i] == 0)
            {
                countArr[i] = top;
                top = i;
            }
        }
        for (int i = 0; i < n; i++)
        {
            ee[i] = 0;
        }
        for (int i = 0; i < n; i++)
        {
            if (top == -1)
            {
                cout << "network has a cycle" << endl;
                return;
            }
            else
            {
                int j = top;
                top = countArr[top];
                ListIterator<Pair> li(HeadNodes[j]);
                if (!li.NotNull())
                    continue;
                Pair p = *li.First();
                while (1)
                {
                    int k = p.vertex;
                    if (ee[k] < ee[j] + p.dur)
                    {
                        ee[k] = ee[j] + p.dur;
                        cout << "ee[" << k << "]=max{ee[" << j << "]+duration of<" << j << "," << k << ">}" << endl;
                    }
                    countArr[k]--;
                    if (countArr[k] == 0)
                    {
                        countArr[k] = top;
                        top = k;
                    }
                    if (li.NextNotNull())
                        p = *li.Next();
                    else
                        break;
                }
            }
        }
        delete[] countArr;
    }

    void Graph::EarlyActivity_display()
    {
        int *countArr = new int[n];
        for (int i = 0; i < n; i++)
        {
            countArr[i] = count[i];
        }
        int top = -1;
        for (int i = 0; i < n; i++)
        {
            if (countArr[i] == 0)
            {
                countArr[i] = top;
                top = i;
            }
        }
        cout << "ee\t\t  0 1 2 3 4 5 6 7 8 9" << endl;
        cout << "initial   ";

        for (int i = 0; i < n; i++)
        {
            ee[i] = 0;
        }
        displayArr(ee, n);
        displayStack(top, countArr);
        for (int i = 0; i < n; i++)
        {
            if (top == -1)
            {
                cout << "network has a cycle" << endl;
                return;
            }
            else
            {
                int j = top;
                top = countArr[top];

                cout << "output " << j << "; ";
                ListIterator<Pair> li(HeadNodes[j]);
                if (!li.NotNull())
                    continue;
                Pair p = *li.First();
                while (1)
                {
                    int k = p.vertex;
                    if (ee[k] < ee[j] + p.dur)
                        ee[k] = ee[j] + p.dur;
                    countArr[k]--;
                    if (countArr[k] == 0)
                    {
                        countArr[k] = top;
                        top = k;
                    }
                    if (li.NextNotNull())
                        p = *li.Next();
                    else
                        break;
                }
                displayArr(ee, n);
                displayStack(top, countArr);
            }
        }
        displayArr(ee, n);
        delete[] countArr;
    }
}

int main(void)
{
    topo::Graph *g = nullptr;
    int select = 0, n, start = -1, end = -1, weight = -1;
    topo::Graph *inversedG = nullptr;

    g = new topo::Graph(10);
    g->Setup4();

    while (select != '0')
    {
        cout << "Select command  1: Adjacency lists와 ee 출력 , 2: inversed Adjacency list 와 le 출력, 3: Eearly Activity & Late Activity 테이블, 4: Quit => ";
        cin >> select;
        switch (select)
        {
        case 1:
            g->printAdjacencyLists();
            g->EarlyActivity();
            break;
        case 2:
            inversedG = g->inverseGraph();
            inversedG->printAdjacencyLists();
            g->LateActivity();
            delete inversedG;
            break;
        case 3:
            g->EarlyActivity_display();
            g->LateActivity_display();
            break;
        case 4:
            exit(0);
        default:
            cout << "Wrong input" << endl;
            cout << "re-enter" << endl;
            break;
        }
    }
    delete g;
    return 0;
}