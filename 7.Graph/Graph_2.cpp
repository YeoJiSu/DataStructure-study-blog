#include <iostream>
#include <stdlib.h>
using namespace std;

const int nmax = 100;
const int MAX_WEIGHT = 9999999;

//Shortest Path 구현하기
class Graph
{
private:
    int length[nmax][nmax];
    int a[nmax][nmax];
    int dist[nmax];
    bool s[nmax];
    int newdist[nmax];

    const int n;

public:
    void ShortestPath(const int);
    void ShortestPath_display(const int);
    void AllLengths();
    int choose();
    void Out(int startNode, int n);
    void OutA(int);
    void insertEdge(int, int, int);

    Graph(int nodeSize) : n(nodeSize)
    {
        for (int i = 0; i < nmax; i++)
        {
            for (int k = 0; k < nmax; k++)
            {
                length[i][k] = MAX_WEIGHT;
            }
        }
    }
    bool isNonNegativeEdgeCost()
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < n; k++)
            {
                if (length[i][k] < 0)
                    return false;
            }
        }
        return true;
    }

private:
    void displayS()
    {
        cout << "{";
        for (int i = 1; i < n; i++)
        {
            if (s[i])
                cout << i << ",";
            else
                cout << "  ";
        }
        cout << "}";
    }
};

void Graph::insertEdge(int start, int end, int weight)
{
    if (start >= n || end >= n || start < 0 || end < 0)
    {
        cout << "the input node is out of bound, the biggest node is " << (n - 1) << endl;
    }
    length[start][end] = weight;
}

void Graph::Out(int startNode, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i == startNode)
        {
            cout << "  0"
                 << "  ";
        }
        else if (dist[i] == MAX_WEIGHT)
            cout << " +∞"
                 << "  ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;
}

void Graph::OutA(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "startNode = " << i << ": ";
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                cout << "0 "
                     << ": ";
            }
            else if (a[i][j] > MAX_WEIGHT - 100000)
                cout << "+∞"
                     << " ";
            else
                cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::ShortestPath(const int v)
{
    for (int i = 0; i < n; i++)
    {
        s[i] = false;
        dist[i] = length[v][i];
    }
    s[v] = true;
    dist[v] = 0;

    for (int i = 0; i < n - 2; i++)
    {
        Out(i, n);
        int u = choose();
        s[u] = true;
        for (int w = 0; w < n; w++)
            if (!s[w])
                if (dist[u] + length[u][w] < dist[w])
                    dist[w] = dist[u] + length[u][w];
    }
    Out(v, n);
}

void Graph::ShortestPath_display(const int v)
{
    for (int i = 0; i < n; i++)
    {
        s[i] = false;
        dist[i] = length[v][i];
    }
    cout << "\t\t  |\t\t\t\t   |\t\t  |\t\t\t\t\tDistance\n";
    cout << "\t\t  |\t\t\t\t   |  Vertex  |----------------------------------------\n";
    cout << "Iteration |\t\t\tS\t   | Selected |  [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]\n";
    cout << "-------------------------------------------------------------------------------\n";
    cout << "  Initial |--\t\t\t   | \t---\t  |  ";
    Out(v, n);
    s[v] = true;
    dist[v] = 0;
    int i = 0;
    for (; i < n - 2; i++)
    {
        int u = choose();
        cout << "\t\t" << i + 1 << " |";
        displayS();
        s[u] = true;
        cout << "|\t " << u << " \t  |  ";

        for (int w = 0; w < n; w++)
            if (!s[w])
                if (dist[u] + length[u][w] < dist[w])
                    dist[w] = dist[u] + length[u][w];
        Out(v, n);
    }
    cout << "\t\t  |";
    displayS();
    cout << "|\t\t  |  " << endl;
    //Out(v,n);
}

int Graph::choose()
{
    int prevmax = -1;
    int index = -1;
    for (int i = 0; i < n; i++)
        if ((!s[i]) && ((prevmax == -1) || (dist[i] < prevmax)))
        {
            prevmax = dist[i];
            index = i;
        }
    return index;
}

void Graph::AllLengths()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = length[i][j];
    int k = 0;
    for (; k < n; k++)
    {
        cout << "\n A[" << k - 1 << "]" << endl;
        OutA(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if ((a[i][k] + a[k][j]) < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
    }
    cout << "\n A[" << k - 1 << "]" << endl;
    OutA(n);
}

Graph *defaultSetup2()
{
    Graph *g = new Graph(8);

    g->insertEdge(1, 0, 300);
    g->insertEdge(2, 1, 800);
    g->insertEdge(2, 0, 1000);
    g->insertEdge(3, 2, 1200);
    g->insertEdge(4, 3, 1500);
    g->insertEdge(4, 5, 250);
    g->insertEdge(5, 3, 1000);
    g->insertEdge(5, 7, 1400);
    g->insertEdge(5, 6, 900);
    g->insertEdge(6, 7, 1000);
    g->insertEdge(7, 0, 1700);

    return g;
}

int main()
{
    char what;
    int select, n, s, startEdge, endEdge, weight;
    cout << "1. 예제 그래프의  최단경로를 구하는 과정 출력하기\n2. 임의의 그래프 입력 받아 최단경로를 구하는 과정 출력하기" << endl;
    cout << "당신의 선택은? => ";
    cin >> select;

    while (true)
    {
        if (select == 1)
        {
            Graph *g = defaultSetup2();
            for (int start = 0; start <= 7; start++)
            {
                cout << "시작점: " << start << endl;
                g->ShortestPath_display(start);
                cout << "\n"
                     << endl;
            }
            delete g;
            break;
        }
        else if (select == 2)
        {
            cout << "input the total node number: ";
            cin >> n;
            Graph *g = new Graph(n);
            while (true)
            {
                cout << "종료하려면 q 를 입력하시오 ";
                cin >> what;
                if (what == 'q')
                    break;
                cout << "startNode? ";
                cin >> startEdge;
                cout << "endNode  ? ";
                cin >> endEdge;
                cout << "weight   ? ";
                cin >> weight;
                g->insertEdge(startEdge, endEdge, weight);
            }
            for (int start = 0; start <= 7; start++)
            {
                cout << "시작점: " << start << endl;
                g->ShortestPath_display(start);
                cout << "\n"
                     << endl;
            }
            delete g;
            break;
        }
        else
        {
            cout << "다시 입력하시오: ";
            cin >> select;
        }
    }
}