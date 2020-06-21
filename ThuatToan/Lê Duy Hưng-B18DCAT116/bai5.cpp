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
    int l=0,r=0;
    r++; qu[r]=u;
    tr[u]=0;
    fr[u]=0;
    while (l<r) {
        l++;
        u=qu[l];
        for (int v=1; v<=n; v++)
            if (a[u][v] && fr[v]) {
                r++; qu[r]=v;
                tr[v]=u;
                fr[v]=0;
            }
    }
}

void duong_s_den_t (){
    int m=0,b[20];
    m++; b[m]=t;
    if (tr[t]==0) {
        cout << "Khong co duong di";
        return;
    }
    int u=tr[t];
    while (tr[u]!=0)
    {
        m++; b[m]=u;
        u=tr[u]; 
    }
    m++; b[m]=s;
    for (int i=m; i>0; i--) cout << b[i] << " " ;
}

int main()
{
    // đọc ma trận nxn, đỉnh s và t
    cin >> n >> s >> t;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++) cin >> a[i][j];
    for (int j=1; j<=n; j++) fr[j]=1;
    tr[s]=0;
    dfs(s);
    duong_s_den_t();
}