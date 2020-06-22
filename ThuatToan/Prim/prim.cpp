#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

#define MAX = 100000;

struct canh
{
	int dinhdau, dinhcuoi;
	int trongso;
};


int n, A[100][100];
int Vh[100], V[100], Vsize;
canh Tree[100];
int dem = 0, dodai = 0;
bool chuaxet[100] = {true};


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
	for(int i=1; i<=n; i++){
		chuaxet[i] = true;
		V[i] = i;
	}
	
}

void Result(){
	cout << "Do dai ngan nhat: " << dodai << endl;
	cout << "Cac canh cua cay khung nho nhat: " << endl;
	for(int i=1; i<=dem; i++){
		cout << Tree[i].dinhdau << " " << Tree[i].dinhcuoi << endl;
	}
}

void Prim(int u){
	int top = 1, min, dau = 0, cuoi = 0;
	int dinhTree[100];
	dinhTree[top] = u;
	chuaxet[u] = false;
	while(dem<n-1){
		min = 100000;
		cout << "Vong: " << dem << endl;
		for(int i=1; i<=top; i++){
			int t = dinhTree[i];
			for(int j=1; j<=n; j++){
				// cout << A[t][j] << " ";
				if(chuaxet[j] == true && A[t][j] < min && A[t][j] > 0){
				
					min = A[t][j];
					cout << min << " ";
					dau = t;
					cuoi = j;
					cout << "dinh = " << t << ": " << dau << " " << cuoi << endl;
				}
			}
			cout << endl;
		}
		dem++;
		dodai += min;
		Tree[dem].dinhdau = dau;
		Tree[dem].dinhcuoi = cuoi;
		chuaxet[cuoi] = false;
		top++;
		dinhTree[top] = cuoi;
	}
}

int main(){
	DocFile("prim.in");
	KhoiTao();
	Prim(1);
	Result();
}