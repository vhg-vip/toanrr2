#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<queue>

using namespace std;

int canh[100] = {1,6, 2,3, 2,8, 3,9, 3,13, 4,1, 4,6, 5,7, 6,10, 6,12, 7,11, 7,13, 8,4, 8,12, 9,5, 9,7, 10,2, 10,3, 11,2, 11,8, 12,4, 12,10, 13,9, 13,11};
vector < vector<int> > ke(14);  
int truoc[100]={0};
int demcanh=0;

void init(){
    for(int i=0; i<50; i+=2){
        // cout << canh[i] << " ";
        if(canh[i]==0) break;
        int a = canh[i];
        int b = canh[i+1];
        // cout << a << " " << b ;
        ke[a].push_back(b);
        demcanh++;
    }
    // cout << ke.size() << endl;
    // for(int d=1; d<ke.size(); d++){
    //     int k = ke[d].size();
    //     for(int j=0; j<k; j++){
    //         cout << ke[d][j] << " ";
    //     }
    //     cout << endl;
    // }
}

int DFS(int s){
    stack<int> st;
    st.push(s);
    bool chuaxet[15];
    for(int i=0; i<15; i++) chuaxet[i] = true;
    chuaxet[s]=false;
    int sum=1;
    cout << s << " ";
    while(!st.empty()){
        int u = st.top();
        st.pop();
        for(int i=0; i<ke[u].size(); i++){
            int v = ke[u][i];
            if(chuaxet[v]){
                sum++;
                chuaxet[v] = false;
                st.push(u);
                st.push(v);
                truoc[v]=u;
                cout << v << " ";
                break;
            }
        }
    }
    return sum;
}

bool strongConnected(){
    int dinh =13;
    bool chuaxet[15];
    for(int i=1; i<=dinh; i++) chuaxet[i] = true;
    for(int i=1; i<=dinh; i++){
        int u = i;
        if(DFS(u) != dinh) return false;
        else{
            for(int i=1; i<=dinh; i++) chuaxet[i] = true;
        }
        cout << endl;
    }
    return true;
}

int main(){
    init();
    if(strongConnected()) cout << "do thi lien thong manh";
    else cout << "do thi ko lien thong manh";
   
}