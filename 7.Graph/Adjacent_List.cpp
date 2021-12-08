/*
Adjacency List 만들기
*/

#include <iostream>
#include <list>

using namespace std;

class Graph
{
private:
    int V;
    list<int> *l;

public:
    Graph(int V)
    {
        this->V = V;
        l = new list<int>[V];
    }
    void addVertex(int x, int y)
    {
        l[x].push_back(y);
        l[y].push_back(x);
    }
    void print_AdjacentList()
    {
        for (int i = 0; i < V; i++)
        {
            cout << "Vertex " << i << " => ";
            for (int x : l[i])
            {
                cout << x << ", ";
            }
            cout << endl;
        }
    }
};
int main()
{
    Graph g(4);
    g.addVertex(0, 1);
    g.addVertex(0, 2);
    g.addVertex(2, 3);
    g.addVertex(1, 2);

    g.print_AdjacentList();
}