#include<iostream>
#include<fstream>

using namespace std;

struct nhan
{
    int trongso, truoc;
};


int A[100][100], n;
bool chuaxet[100] = {true};
nhan d[100], tmp[100];

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
    }
}

void Dijkstra(int s){
    d[s].trongso = 0;
    d[s].truoc = s;
    for(int i=1; i<=n; i++){
        d[i].trongso = A[s][i];
        d[i].truoc = s;
    }
}

int main(){
    DocFile("matrix.in");
    KhoiTao();
}