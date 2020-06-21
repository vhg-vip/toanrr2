#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<queue>

using namespace std;

int canh[100] = {1,2, 1,3, 1,4, 1,5, 2,3, 2,4, 3,4, 5,6, 5,7, 5,8, 5,9, 6,7, 6,9, 7,8, 7,10, 8,9, 10,11, 10,12, 10,13, 11,12, 11,13, 12,13 };
vector < vector<int> > ke(14);  
int truoc[100]={0};

void init(){
    for(int i=0; i<50; i+=2){
        // cout << canh[i] << " ";
        if(canh[i]==0) break;
        int a = canh[i];
        int b = canh[i+1];
        // cout << a << " " << b ;
        ke[a].push_back(b);
        ke[b].push_back(a);
    }
}


void DFS(int s){
    stack<int> st;
    st.push(s);
    bool chuaxet[15];
    for(int i=0; i<15; i++) chuaxet[i] = true;
    chuaxet[s]=false;
    int sum=1;
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
                // cout << v << " ";
                break;
            }
        }
    }
    // cout << endl << sum ;
}

void find(int s, int t){
    // for(int i=0; i<20; i++) cout << truoc[i] << " ";
    if(truoc[t] == 0){
        cout << "ko co duong di" << endl;
    }
    else{
        cout << t << " ";
        int u = truoc[t];
        while(u!=s){
            cout << u << " ";
            u = truoc[u];
        }
        cout << s << " ";
    }
}

int main(){
    init();
    DFS(1);
    find(1,13);
}