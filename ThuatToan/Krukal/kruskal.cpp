#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

struct canh
{
	int dinhdau, dinhcuoi;
	int trongso;
};


int n, A[100][100];
canh Tree[100];
int dem = 0, dodai = 0;
bool chuaxet[100] = {true};
canh E[1000];
int socanh = 1;


bool DocFile(string tenfile){
	ifstream read(tenfile.c_str());
	if(read.is_open()){
		read >> n;
		cout << "\n So dinh cua do thi: " << n;
		cout << "\n Ma tran ke:";
		for(int i=1; i<=n; i++){
			cout << "\n";
			for(int j=1; j<=n; j++){
				read >> A[i][j];	
                cout  << A[i][j] << " ";
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
        for(int j=i; j<=n; j++){
            if(A[i][j] > 0){
                E[socanh].dinhdau = i;
                E[socanh].dinhcuoi = j;
                E[socanh].trongso = A[i][j];
                socanh++;
            }
            
        }
    }
}

bool cmp(canh a, canh b){
    
    if(a.trongso < b.trongso) return true;
    if(a.trongso = b.trongso && a.dinhdau < b.dinhdau) return true;
    if(a.trongso = b.trongso && a.dinhdau < b.dinhdau && a.dinhcuoi == b.dinhcuoi) return true;

    return false;
}

void SapXepCanh(){
    sort(E, E+socanh, cmp);
    for(int i=1; i<=socanh; i++){
        cout << E[i].dinhdau << " " << E[i].dinhcuoi << " " << E[i].trongso << endl;
    }
}

void Result(){
    cout << "Do dai cay la: " << dodai << endl;
    for(int i=1; i<=dem; i++){
        cout << Tree[i].dinhdau << " " << Tree[i].dinhcuoi << endl;
    }
}

void Kruskal(){
    int c = 1;
    dem = 1;
    chuaxet[E[c].dinhdau] = false;
    chuaxet[E[c].dinhcuoi] = false;
    Tree[dem].dinhdau = E[c].dinhdau;
    Tree[dem].dinhcuoi = E[c].dinhcuoi;
    dodai += E[c].trongso;
    while(dem < n-1 && c < socanh){
        if((chuaxet[E[c].dinhdau] == true && chuaxet[E[c].dinhcuoi] == false ) || (chuaxet[E[c].dinhdau] == false && chuaxet[E[c].dinhcuoi] == true )){
            dem++;
            Tree[dem].dinhdau = E[c].dinhdau;
            Tree[dem].dinhcuoi = E[c].dinhcuoi;
            chuaxet[E[c].dinhdau] = false;
            chuaxet[E[c].dinhcuoi] = false;
            dodai += E[c].trongso;
        }
        c++;
    }
    Result();
}


int main(){
    DocFile("kruskal.in");
    KhoiTao();
    SapXepCanh();
    Kruskal();
}