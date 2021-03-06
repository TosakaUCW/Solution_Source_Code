#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <queue>

const int N = 1e7 + 5;

int n, m;
long long ans, dis[N];
int head[N], num_edge;
bool vis[N];

struct Node
{
    int next, to, dis;
} edge[N];
struct node
{
    int cur;
    long long dis;
    bool friend operator<(node A, node B) {
        return A.dis > B.dis;
    };
};

std::priority_queue<node> Q;

void add_edge(int u, int v, int dis)
{
    edge[++num_edge] = Node{ head[u], v, dis };
    head[u] = num_edge;
}

int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while ('0' > ch or ch > '9')
        f = ch == '-' ? -1 : 1, ch = getchar();
    while ('0' <= ch and ch <= '9')
        x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

void dijkstra(int s)
{
    Q.push(node{ s, 0 });
    dis[s] = 0;
    while (!Q.empty())
    {
        node X = Q.top();
        Q.pop();
        if (vis[X.cur])
            continue;
        vis[X.cur] = true;
        for (int i = head[X.cur]; i; i = edge[i].next)
        {
            int v = edge[i].to;
            if (dis[X.cur] + edge[i].dis < dis[v])
            {
                dis[v] = dis[X.cur] + edge[i].dis;
                if (!vis[v])
                    Q.push(node{ v, dis[v] });
            }
        }
    }
}

int main()
{
    int T = read();
    while (T--)
    {
        ans = num_edge = 0;
        memset(head, 0, sizeof head);
        memset(dis, 0x3f, sizeof dis);
        memset(vis, false, sizeof vis);
        n = read(), m = read();
        for (int i = 1, u, v, dis; i <= m; i++)
            u = read(), v = read(), dis = read(),
            add_edge(u, v, dis), add_edge(v + n, u + n, dis);
        dijkstra(1);
        for (int i = 2; i <= n; i++)
            ans += dis[i];
        dijkstra(n + 1);
        for (int i = 2 + n; i <= n * 2; i++)
            ans += dis[i];
        printf("%lld\n", ans);
    }
    return 0;
}