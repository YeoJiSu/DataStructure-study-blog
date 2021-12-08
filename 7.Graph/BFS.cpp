/*
BFS = Breadth First Search 너비 우선 탐색 알고리즘
요약 : 시작점과 가까운 노드 순으로 탐색이 이루어진다. 
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int check[7];
// 방문 처리를 체크할 배열 (true 면 방문 한 것 )

vector<int> a[8];
// 1부터 7까지의 노드를 처리하기 위한 것

void bfs(int start)
{
    queue<int> q;
    q.push(start);       // q에 시작점을 넣어줌
    check[start] = true; // 시작점 방문 처리

    while (!q.empty())
    { // q가 빌 때까지 반복
        int x = q.front();
        q.pop(); // q에서 젤 앞 하나를 꺼냄
        cout << x << " ";
        for (int i = 0; i < a[x].size(); i++)
        {
            int y = a[x][i]; // a[x]와 인접한 모든 노드들에 대해
            if (!check[y])
            {                    // 그 노드를 방문 안했다면
                q.push(y);       // q에 담고
                check[y] = true; // 방문 처리를 한다.
            }
        }
    }
}
int main()
{
    //그래프 모양에 따라 push_back 처리를 한다.
    a[1].push_back(2);
    a[2].push_back(1);

    a[1].push_back(3);
    a[3].push_back(1);

    a[2].push_back(3);
    a[3].push_back(2);

    a[2].push_back(4);
    a[4].push_back(5);

    a[2].push_back(5);
    a[5].push_back(2);

    a[4].push_back(5);
    a[5].push_back(4);

    a[3].push_back(6);
    a[6].push_back(3);

    a[3].push_back(7);
    a[7].push_back(3);

    a[6].push_back(7);
    a[7].push_back(6);

    int start;
    cout << "1부터 7까지 중 시작점을 선택하세요\n=> ";
    cin >> start;
    bfs(start);
}