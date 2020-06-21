#include <iostream>
using namespace std;
int n,s,t,a[20][20],fr[20],qu[20],tr[20];

void dfs(int u)
{
    fr[u]=0;
    for (int v=1; v<=n; v++)
        if (a[u][v] && fr[v]) {
            tr[v]=u;
            dfs(v);
        }
}

void bfs(int u)
{
    // khởi tạo queue
    int l=0,r=0;
    r++; qu[r]=u;
    tr[u]=0;
    // lặp
    while (l<r) {
        l++;
        u=qu[l];
        fr[l]=0;
        for (int v=1; v<=n; v++)
            if (a[u][v] && fr[v]) {
                r++; qu[r]=v;
                tr[v]=u;
            }
    }
}
bool check_ltm()
{
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++) fr[j]=1; // reInit()
        dfs(i);
        for (int j=1; j<=n; j++)
            if(fr[j]==0) return false;
    }
    return true;
}

int main()
{
    // đọc ma trận nxn
    cin >> n;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++) cin >> a[i][j];
    if (check_ltm()) cout << "do thi lien thong manh";
    else cout << "do thi khong lien thong manh";
}