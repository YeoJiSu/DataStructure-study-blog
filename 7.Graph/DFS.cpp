/*
DFS = Depth First Search 깊이 우선 탐색 알고리즘
*/

#include <iostream>
#include <vector>

using namespace std;

int check[7];
vector<int> a[8];

void dfs(int x)
{
    if (check[x])
        return;       //방문했다면 종료해라
    check[x] = true;  //방문 안했으면 이제 방문 했다고 표시하고
    cout << x << " "; // 방문 한 노드 출력
    for (int i = 0; i < a[x].size(); i++)
    {
        // 인접한 노드를 탐색해서
        int y = a[x][i];
        // 재귀함수 호출
        dfs(y);
    }
}
int main()
{
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
    dfs(start);
}