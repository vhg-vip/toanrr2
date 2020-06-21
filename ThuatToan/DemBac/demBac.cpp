#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

int n;
int A[20][20];

bool DocDuLieu(string tenfile){
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
		read.close();
		return	true;
	}
	return	false;
}

void doThiVoHuong(){
    int dem = 0;
    for(int i=1; i<=n; i++){
        dem=0;
        for(int j=1; j<=n; j++){
            if(A[i][j]==1) dem++;
        }
        cout << "Dinh " << i << ": " << dem << endl;
    }
}

void doThiCoHuong(){
	int dem1 = 0, dem2=0;
    for(int i=1; i<=n; i++){
        dem1=0;
		dem2 = 0;
        for(int j=1; j<=n; j++){
            if(A[i][j]==1) dem1++;
			if(A[j][i]==1) dem2++;
        }
        cout << "Dinh " << i << ": " << dem1 << endl;
		cout << "Dinh " << i << ": " << dem2 << endl;
		cout << endl;
    }
}

int main(){
    if(DocDuLieu("matrix.txt")){
        cout << "\n Doc du lieu OK" << endl;
        // doThiVoHuong();
		doThiCoHuong();
    }
}