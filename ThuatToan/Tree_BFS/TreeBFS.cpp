#include<iostream>
#include<fstream>
#include<queue>

using namespace std;
#define MAX 100

struct canh
{
    int dinhdau, dinhcuoi;
    int trongso;
};


int A[100][100];
int n;
bool chuaxet[100] = {true};
int dem = 0;
canh Tree[100];
queue <int> q;

bool DocFile(string tenfile){
	ifstream read(tenfile.c_str());
	if(read.is_open()){
		read >> n;
		cout << "\n So dinh cua do thi: " << n;
		cout << "\n Ma tran ke:";
		for(int i=1; i<=n; i++){
			cout << "\n";
			for(int j=1; j<=n; j++){
				read >> A[i][j];	cout << " " << A[i][j];
			}
		}
        cout << endl;
		read.close();
		return	true;
	}
	return	false;
}


void KhoiTao(){
	for(int i=1; i<=n; i++){
		chuaxet[i]=true;
	}
}

void Print(){
    for(int i=1; i<=dem; i++){
        cout << Tree[i].dinhdau << " " << Tree[i].dinhcuoi << endl;
    }
}

void Tree_BFS(int u){
    q.push(u);
    chuaxet[u] = false;
    while(!q.empty()){
        int s = q.front();
        q.pop();
        for(int i=1; i<=n; i++){
            if(A[s][i] == 1 && chuaxet[i] == true){
                q.push(i);
                dem++;
                Tree[dem].dinhdau = s;
                Tree[dem].dinhcuoi = i;
                // cout << s << " " << i << endl;
                chuaxet[i] = false;
            }
        }
    }
    if(dem < n-1) cout << "Do thi ko lien thong";
    else Print();
}

int main(){
    DocFile("tree_BFS.in");
    KhoiTao();
    Tree_BFS(7);
}