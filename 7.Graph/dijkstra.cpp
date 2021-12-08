#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int number = 6;
int INF = 1000000000;

// 전체 그래프를 초기화 함.
int a[6][6] = {
    {0, 2, 5, 1, INF, INF},
    {2, 0, 3, 2, INF, INF},
    {5, 3, 0, 3, 1, 5},
    {1, 2, 3, 0, 1, INF},
    {INF, INF, 1, 1, 0, 2},
    {INF, INF, 5, INF, 2, 0}};

bool v[6]; // 방문 여부를 저장한 배열
int d[6];  // 최단 거리를 저장한 배열

/* 
선형 탐색 방법 => 시간 복잡도가 O(N^2)
효율적인 방법이 아님.
*/
int getSmallIndex()
{
    int min = INF;
    int index = 0;
    for (int i = 0; i < number; i++)
    {
        if (d[i] < min && !v[i])
        {
            min = d[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start)
{ //다익스트라를 수행하는 함수
    for (int i = 0; i < number; i++)
    {
        d[i] = a[start][i];
    }
    v[start] = true;
    for (int i = 0; i < number - 2; i++)
    {
        int current = getSmallIndex();
        v[current] = true;
        for (int j = 0; j < 6; j++)
        {
            if (!v[j])
            {
                if (d[current] + a[current][j] < d[j])
                {
                    d[j] = d[current] + a[current][j];
                }
            }
        }
    }
}

/*
힙 구조를 활용한 방법 => 시간 복잡도 O(N * logN)
*/

vector<pair<int, int> > a2[7]; // 간선 정보
int d2[7];                     // 최소 비용

void dijkstra2(int start)
{
    d2[start] = 0;
    priority_queue<pair<int, int> > pq; //힙 구조
    pq.push(make_pair(start, 0));
    // 가까운 순서대로 처리하므로 queue를 사용하는 것이다.
    while (!pq.empty())
    {
        int current = pq.top().first;
        // 짧은 것이 먼저 오게끔 음수화 한다.
        int distance = -pq.top().second;
        pq.pop();

        // 최단경로가 아니면 스킵한다.
        if (d2[current] < distance)
            continue;
        for (int i = 0; i < a2[current].size(); i++)
        {
            // 선택된 노드의 인접 노드에 대해
            int next = a2[current][i].first;
            // 비용 계산
            int nextDistance = distance + a2[current][i].second;
            if (nextDistance < d2[next])
            {
                d2[next] = nextDistance;
                pq.push(make_pair(next, -nextDistance));
            }
        }
    }
}

int main(void)
{
    dijkstra(0);
    for (int i = 0; i < number; i++)
    {
        cout << d[i] << " ";
    }

    // 기본적으로 연결되지 않은 경우 비용은 무한.
    for (int i = 1; i <= number; i++)
    {
        d2[i] = INF;
    }

    a2[1].push_back(make_pair(2, 2));
    a2[1].push_back(make_pair(4, 1));
    a2[1].push_back(make_pair(3, 5));

    a2[2].push_back(make_pair(1, 2));
    a2[2].push_back(make_pair(4, 2));
    a2[2].push_back(make_pair(3, 3));

    a2[3].push_back(make_pair(2, 3));
    a2[3].push_back(make_pair(1, 5));
    a2[3].push_back(make_pair(4, 3));
    a2[3].push_back(make_pair(5, 1));
    a2[3].push_back(make_pair(6, 5));

    a2[4].push_back(make_pair(1, 1));
    a2[4].push_back(make_pair(2, 2));
    a2[4].push_back(make_pair(3, 3));
    a2[4].push_back(make_pair(5, 1));

    a2[5].push_back(make_pair(4, 1));
    a2[5].push_back(make_pair(3, 1));
    a2[5].push_back(make_pair(6, 2));

    a2[6].push_back(make_pair(5, 2));
    a2[6].push_back(make_pair(3, 5));

    dijkstra2(1);

    cout << endl;
    for (int i = 1; i <= number; i++)
    {
        cout << d2[i] << " ";
    }
}