#include<iostream>
#include <fstream>

using namespace std;

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

bool DocFile(string tenfile){
	ifstream read(tenfile.c_str());
	if(read.is_open()){
		read >> n;
		//read >> n >> s >> t;
		cout << "\n So dinh cua do thi: " << n;
		//cout << "\n Dinh bat dau duong di s = " << s;
		//cout << "\n Dinh cuoi duong di t = " << t;
		cout << "\n Ma tran ke:";
		for(int i=1; i<=n; i++){
			cout << "\n";
			for(int j=1; j<=n; j++){
				read >> A[i][j];	cout  << A[i][j] << " ";
			}
		}
        cout << endl;
		read.close();
		return	true;
	}
	return	false;
}

void KhoiTao(){
    for(int i=1; i<=n; i++) chuaxet[i] = true;
}


void Print(){
    for(int i=1; i<dem; i++){
        cout << Tree[i].dinhdau << " " << Tree[i].dinhcuoi;
        cout << endl;
    }
}

void Tree_DFS(int u){
    chuaxet[u] = false;
    for(int i=1; i<=n; i++){
        if(A[u][i] == 1 && chuaxet[i] == true){
            dem++;
            // cout << dem << " ";
            Tree[dem].dinhdau = u;
            Tree[dem].dinhcuoi = i;
            cout << "Canh " << dem << ": " << u << " " << i << endl;
            Tree_DFS(i);
        }
    }
}

int main(){
    
    DocFile("tree.in");
    KhoiTao();
    Tree_DFS(3);
    // if(dem < n-1) cout << "Do thi ko lien thong";
    // else 
    
}