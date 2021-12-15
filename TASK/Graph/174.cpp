/*
6.4 shortest path
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
const int nmax = 100;
const int MAX_WEIGHT = 9999999;

class Graph
{
private:
    int length[nmax][nmax]; // connection matrix
    int a[nmax][nmax];
    int dist[nmax]; // distance from v to u
    bool s[nmax];
    int newdist[nmax];

    const int n;

public:
    void ShortestPath(const int);
    void ShortestPath_display(const int);
    void BellmanFord(const int);
    void BellmanFord2(const int);
    void AllLengths();
    int choose();
    void Out(int startNode, int n);
    void OutA(int);

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

    void insertEdge(int start, int end, int weight);
    void displayConnectionMatrix();
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
        cout << "[";
        for (int i = 0; i < n; i++)
        {
            if (s[i])
                //printf("%d")
                cout << i << ",";
            else
                cout << "  ";
        }
        cout << "]; ";
    }
};

////origin
//void Graph::displayConnectionMatrix() {
//	for(int i = 0; i < n; i++) {
//		bool exists = false;
//		for (int k = 0; k < n; k++) {
//			if (length[i][k] == MAX_WEIGHT)
//				continue;
//			exists = true;
//			cout << i << " -> " << k << "(weight=" << length[i][k] << "), ";
//		}
//		if (exists)
//			cout << endl;
//	}
//}

void Graph::displayConnectionMatrix()
{
    cout << "     ";
    for (int k = 0; k < n; k++)
        printf("%5d", k);
    cout << endl;
    for (int i = 0; i < n; i++)
    {

        printf("%5d", i);
        for (int k = 0; k < n; k++)
        {
            if (i == k)
            {
                printf("%5d", 0);
                continue;
            }
            if (length[i][k] == MAX_WEIGHT)
            {
                cout << "     ";
                continue;
            }
            printf("%5d", length[i][k]);
        }
        cout << endl;
    }
}

void Graph::insertEdge(int start, int end, int weight)
{
    if (start >= n || end >= n || start < 0 || end < 0)
    {
        cout << "the input node is out of boiund, the biggest node is " << (n - 1) << endl;
        return;
    }
    length[start][end] = weight;
}

void Graph::Out(int startNode, int n)
{
    // cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (i == startNode)
        {
            printf("    0");
            //cout << "0" << ", ";
        }
        else if (dist[i] == MAX_WEIGHT)
            printf("   +��");
        //cout << "infinite" << ", ";
        else
            printf("%6d", dist[i]);
        //cout << dist[i] << ", ";
    }
    cout << endl;
}

void Graph::OutA(int n)
{
    // cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "startNode = " << i << ": ";
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                printf("    0");
                //cout << "0 " << " ";
            }
            else if (a[i][j] > MAX_WEIGHT - 100000) // 100000 is one a big enought number
                printf("   +��");
            //cout << "+��" << " ";
            else
                printf("%5d", a[i][j]);
            //cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::ShortestPath(const int v)
{
    for (int i = 0; i < n; i++)
    { // intialize
        s[i] = false;
        dist[i] = length[v][i];
    }
    s[v] = true;
    dist[v] = 0;

    //Out(n);
    for (int i = 0; i < n - 2; i++)
    { // determine n - 1 paths from vertex v
        Out(i, n);
        int u = choose(); // choose returns a value u;

        // dist[u] = minimum dist[w], where s[w] = false
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
    { // initialize
        s[i] = false;
        dist[i] = length[v][i];
    }

    //>>>>>>>>>>display
    cout << 1 << "; ";
    displayS();
    cout << "       ";
    //cout << "   "<< v << "   ";
    //cout << "vertex selected: " << v << "; ";
    Out(v, n);
    //<<<<<<<<<<

    s[v] = true;
    dist[v] = 0;

    //Out(n);
    int i = 0;
    for (; i < n - 2; i++)
    {                     // determine n-1 paths from vertex v
        int u = choose(); // choose returns a value u;
        //dist[u] = minimum dist[w], where s[w] = false
        cout << i + 2 << "; ";
        displayS();

        s[u] = true;

        //printf("%5d", u);
        cout << "   " << u << "   ";
        //cout << "vertex selected: " << u << "; ";

        for (int w = 0; w < n; w++)
            if (!s[w])
                if (dist[u] + length[u][w] < dist[w])
                    dist[w] = dist[u] + length[u][w];
        Out(v, n);
    }
    cout << i + 2 << ", ";
    displayS();
    cout << "       ";
    //cout << ":                   " << ", ";
    //Out(v, n);
}

int Graph::choose()
{
    int prevmax = -1;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if ((!s[i]) && ((prevmax == -1) || (dist[i] < prevmax)))
        {
            prevmax = dist[i];
            index = i;
        }
    }
    return index;
}

void Graph::BellmanFord(const int v)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = length[v][i];
    }

    cout << endl;
    int k = 0;
    for (k = 1; k <= n - 1; k++)
    {
        cout << "k = " << k << ", ";
        Out(v, n);
        for (int u = 0; u < n; u++)
        {
            if (u != v)
            {
                for (int i = 0; i < n; i++)
                {
                    if ((u != i) && (length[i][u] < MAX_WEIGHT))
                    {
                        if (dist[u] > dist[i] + length[i][u])
                        {
                            dist[u] = dist[i] + length[i][u];
                        }
                    }
                }
            }
        }
    }
    //cout << "k = " << k << ", ";
    //Out(n);
}

void Graph::BellmanFord2(const int v)
{ //Single source all destination shortest paths with negative edge lengths
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i]; //initialize dist
    for (int k = 2; k <= n - 1; k++)
    {
        for (int l = 0; l < n; l++)
            newdist[l] = dist[l];
        for (int u = 0; u < n; u++)
            if (u != v)
            {
                for (int i = 0; i < n; i++)
                    if ((u != i) && (length[i][u] < MAX_WEIGHT))
                        if (newdist[u] > dist[i] + length[i][u])
                            newdist[u] = dist[i] + length[i][u];
            }
        for (int i = 0; i < n; i++)
            dist[i] = newdist[i];
    }
}

void Graph::AllLengths()
{
    // lenght[n][n] is the adjacency matrix of a graph with n vertices.
    // a[i][j] is the length of the shortest path between i and j
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = length[i][j]; // copy length into a

    int k = 0;
    for (; k < n; k++)
    { // for a path with highest vertex index k
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

Graph *defaultSetup1()
{
    Graph *g = new Graph(7);

    g->insertEdge(0, 1, 6);
    g->insertEdge(0, 2, 5);
    g->insertEdge(0, 3, 5);
    g->insertEdge(1, 4, -1);
    g->insertEdge(2, 1, -2);
    g->insertEdge(2, 4, 1);
    g->insertEdge(3, 2, -2);
    g->insertEdge(3, 5, -1);
    g->insertEdge(4, 6, 3);
    g->insertEdge(5, 6, 3);

    return g;
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

Graph *setup_allPairShortestPaths()
{
    Graph *g = new Graph(3);
    g->insertEdge(0, 1, 4);
    g->insertEdge(0, 2, 11);
    g->insertEdge(1, 0, 6);
    g->insertEdge(1, 2, 2);
    g->insertEdge(2, 0, 3);

    return g;
}

int main(void)
{
    Graph *g = nullptr;
    int select = 0, n, start = -1, end = -1, weight = -1;
    cout << "1: custom setup,\n2: Default Setup1[sortest path(non-negative)],\n"
         << "3: Default Setup2[single source/all destinations(negative edge costs)](HW!!!!)\n4: Default Setup3[allPairShortestPaths] =>";
    cin >> select;
    if (select == 1)
    {
        cout << "Input the total node number: ";
        cin >> n;
        g = new Graph(n);
    }
    else if (select == 2)
    {
        g = defaultSetup1();
    }
    else if (select == 3)
    {
        g = defaultSetup2();
    }
    else if (select == 4)
    {
        g = setup_allPairShortestPaths();
    }
    else
    {
        throw "illegal input";
    }

    while (select != '0')
    {
        cout << "\nSelect command 1: AddEdge,\n2: AdjacencyLists,\n3: singleSource/all destinations(non-negative edge cost)\n"
             << "4; single source/all destinations(negative edge costs),\n5. All-pairs shortest pahts,\n6. Quit\n => ";
        cin >> select;
        switch (select)
        {
        case 1:
            cout << "Add an edge: " << endl;
            cout << "--------Input start node: ";
            cin >> start;
            cout << "--------Input destination node: ";
            cin >> end;
            cout << "--------Input weight: ";
            cin >> weight;

            g->insertEdge(start, end, weight);
            break;
        case 2:
            //display
            g->displayConnectionMatrix();
            break;
        case 3:
            cout << "\nsingle source/all destinations: non-negative edge costs: " << endl;
            if (!g->isNonNegativeEdgeCost())
            {
                cout << "Negative edge cost exists!!" << endl;
                cout << "Please re-build the graph with non-negative edge costs." << endl;
                break;
            }
            cout << "\n --------> Input start node: ";
            cin >> start;

            g->ShortestPath_display(start);
            break;
        case 4:
            cout << "\nsingle source/all destinations: negative edge costs: " << endl;
            cout << "\n --------> Input start node: ";
            cin >> start;

            g->BellmanFord(start);
            break;
        case 5:
            cout << "\nAll-pairs shortest pahts:" << endl;
            g->AllLengths();
            break;
        case 6:
            exit(0);
        default:
            cout << "WRONG INPUT " << endl;
            cout << "Re-Enter" << endl;
            break;
        }
    }
    delete g;
    return 0;
}