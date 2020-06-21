#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<queue>

using namespace std;

int canh[100] = {1,2, 1,3, 1,4, 2,3, 2,4, 3,4, 3,5, 5,6, 5,7, 5,8, 5,9, 6,7, 6,9, 7,8, 8,9, 9,10, 10,11, 10,12, 10,13, 11,12, 11,13, 12,13};
int matrix[500][500]={0}; 
int truoc[100]={0};
vector < vector<int> > ke(14); 

void init(){
    for(int i=0; i<50; i+=2){
        // cout << canh[i] << " ";
        if(canh[i]==0) break;
        int a = canh[i];
        int b = canh[i+1];
        // cout << a << " " << b ;
        matrix[a][b]=1;
        matrix[b][a]=1;
    }
}

int BFS(int s){
    queue <int> q;
    bool chuaxet[15];
    for(int i=0; i<15; i++) chuaxet[i] = true;
    q.push(s);
    chuaxet[s]=false;
    int sum = 1;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        // cout << u << ": ";
        for(int i=1; i<=13; i++){
            if(matrix[u][i]==1){
                // cout << i << " ";
                int v = i;
                if(chuaxet[v]){
                    q.push(v);
                    chuaxet[v] = false;
                    truoc[v] = u;
                    sum++;
                }
            }
        }
        // cout << endl;
    }
    // cout << sum << " ";
    return sum;
}

void duyet_tru(int dinh){
    int chuaxet[20];
    for(int i=1; i<=dinh; i++) chuaxet[i]=true;
    for(int i=1; i<=dinh; i++){
        int u=i;
        chuaxet[u] = false;
        if(BFS(1) != dinh-1){
            cout << u << " la dinh tru" << endl;
            
        }
        for(int i=1; i<=dinh; i++) chuaxet[i]=true;
    }
}

int main(){
    init();
    BFS(1);
    duyet_tru(13);
}