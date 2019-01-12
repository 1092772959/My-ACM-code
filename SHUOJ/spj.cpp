#include <bits/stdc++.h>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1

int spj(FILE* input, FILE* user_output);

void close_file(FILE* f){
    if (f != NULL){
        fclose(f);
    }
}
    
int main(int argc, char* args[])
{
    FILE *input = NULL , *user_output = NULL;
    int result;
    if (argc != 3)
    {
        printf("Usage: spj x.in x.out\n");
        return ERROR;
    }
    printf("Pending...\n");
    input = fopen(args[1], "r");
    user_output = fopen(args[2], "r");
    if (input == NULL || user_output == NULL)
    {
        printf("Failed to open output file\n");
        close_file(input);
        close_file(user_output);
        return ERROR;
    }

    result = spj(input, user_output);
    cout<<result<<endl;
    close_file(input);
    close_file(user_output);
    return result;
}

/**************************************************/
const char* result[] = {"ok", "wrong answer"};
const int N = 1e5;
const int M = 4e5;
const int E = 1e3;
const int INF = 0x3f3f3f3f;

int spj(FILE* input, FILE* user_output)
{
    int n, m;
    if (fscanf(user_output, "%d %d", &n, &m) != 2) return printf("%s, unexcept eof.\n", result[1]), WA;
    if (n < 1 || m < 1 || n > N || m > M) return printf("%s, n = %d, m = %d.\n", result[1], n, m), WA;
    vector<vector<pair<int, int>>> G(n + 1);
    set<pair<int, int>> edges;
    for (int i = 0, u, v, w; i < m; i++)
    {
        if (fscanf(user_output, "%d %d %d", &u, &v, &w) != 3) return printf("%s, unexcept eof.\n", result[1]), WA;
        // out of range
        if (u < 1 || u > n || v < 1 || v > n || w < 1 || w > E) return printf("%s, fail on u = %d, v = %d, w = %d.\n", result[1], u, v, w), WA;
        // self loop
        if (u == v) return printf("%s, self loop on u = %d, v = %d, w = %d.\n", result[1], u, v, w), WA;
        // multiple edges
        if (edges.find({u, v}) != edges.end()) return printf("%s, multiple edges on u = %d, v = %d, w = %d.\n", result[1], u, v, w), WA;
        edges.insert({u, v});
        G[u].emplace_back(v, w);
    }
    if (fscanf(user_output, "%*s") != EOF) return printf("%s, too many input.\n", result[1]), WA;
    printf("Running & Checking...\n");
    vector<int> d(n + 1, INF), inq(n + 1, 0);
    queue<int> q;
    d[1] = 0;
    inq[1] = 1;
    q.push(1);
    int cnt = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (auto& e : G[u])
        {
            int &v = e.first, &w = e.second;
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                if (!inq[v])
                {
                    q.push(v);
                    if (++cnt > 1e7) return printf("%s, successful hacking attempt!\n", result[0]), AC;
                    inq[v] = 1;
                }
            }
        }
    }
    printf("exec time: %d ms\n", cnt / 10000);
    
    return printf("%s, unsuccessful hacking attempt!\n", result[1]), WA;
}