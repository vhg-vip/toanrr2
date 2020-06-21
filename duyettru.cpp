#include <stdio.h>
#include <conio.h>
#include <iostream>
#define MAX 50
#define TRUE 1
#define FALSE 0
int A[MAX][MAX], n, chuaxet[MAX], solt = 0;
//Doc du lieu
void Read_Data(void)
{
    int i, j;
    FILE *fp;
    fp = fopen("dothi.IN", "r");
    fscanf(fp, "%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("\n");
        for (j = 1; j <= n; j++)
        {
            fscanf(fp, "%d", &A[i][j]);
        }
    }
}
//Thuat toan BFS
void BFS(int u)
{
    int queue[MAX], low = 1, high = 1, s, t;
    queue[low] = u;
    chuaxet[u] = FALSE;
    while (low <= high)
    {
        s = queue[low];
        low = low + 1;
        //printf("%3d", s);
        for (t = 1; t <= n; t++)
        {
            if (A[s][t] && chuaxet[t])
            {
                high = high + 1;
                queue[high] = t;
                chuaxet[t] = FALSE;
            }
        }
    }
}
//Thuat toan DFS
void DFS(int u)
{
    int v; //printf("%3d",u);
    chuaxet[u] = FALSE;
    for (v = 1; v <= n; v++)
    {
        if (A[u][v] && chuaxet[v])
            DFS(v);
    }
}
//Khoi dau lai mang chuaxet[]
void ReInit(void)
{
    for (int i = 1; i <= n; i++)
        chuaxet[i] = TRUE;
}
//Kiem tra so lien thong >1?
int Test_So_Lien_Thong(void)
{
    for (int u = 1; u <= n; u++)
        if (chuaxet[u])
            return (1);
    return (0);
}
//Duyệt các đỉnh trụ
void main()
{
    Read_Data();
    ReInit();
    for (int u = 1; u <= n; u++)
    {
        DFS(1); //BFS(1);
        if (Test_So_Lien_Thong())
            printf("\n Dinh %d la tru", u);
        ReInit();
    }
}