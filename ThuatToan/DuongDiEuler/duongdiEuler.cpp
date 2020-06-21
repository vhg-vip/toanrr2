#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue> 
#define MAX 100

using namespace std;

int	n;							
int A[MAX][MAX];
int		truoc[MAX];	
bool	chuaxet[MAX];

bool DocDuLieu(string tenfile){
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
				read >> A[i][j];	cout << " " << A[i][j];
			}
		}
		read.close();
		return	true;
	}
	return	false;
}

void KhoiTao(){
	for(int i=1; i<=n; i++){
		chuaxet[i]=true;
		truoc[i]=0;
	}
}

void DuongDiEuler(int u){
    stack<int> nganxep;
    stack<int> dCE;
    nganxep.push(u);
    while (!nganxep.empty())
    {
        int s = nganxep.top();
        for(int t=1; t<=n; t++){
            if(A[s][t] == 1){
                nganxep.push(t);
                A[s][t] = 0;
                A[t][s] = 0;
                break;
            }
            else if(t==n) {
                s = nganxep.top();
                nganxep.pop();
                dCE.push(s);
            }
        }
    }
    while(!dCE.empty()){								// CE chua rong
		int s=dCE.top();								// lay dinh ngan xep ra
		dCE.pop();									// loai dinh khoi ngan xep
		cout << " " << s << " -> ";
	}

}

int main(){
    if(DocDuLieu("matrix.txt")){
		cout << "\n Doc du lieu OK";
		KhoiTao();	
		DuongDiEuler(7);
	}
	else
		cout << "\n Loi file";
	return 0;
}