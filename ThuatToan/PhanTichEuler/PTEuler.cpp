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

void	ChuTrinhEuler(int u){
	stack<int>	nganxep;							// khoi tao ngan xep rong
	stack<int>	CE;									// khoi tao mang CE rong
	nganxep.push(u);								// day u vao ngan xep
	while(!nganxep.empty()){						// ngan xep chua rong
		int s=nganxep.top();						// lay dinh s o dau ngan xep
		for(int t=1; t<=n; t++){					// duyet cac dinh ke cua s trong tap dinh V
			if(A[s][t]==1){							// dinh t la ke voi s
				nganxep.push(t);
                cout << t << " ";					// day t vao ngan xep
				A[s][t]=0;	A[t][s]=0;				// loai bo canh (s, t) khoi tap canh E
				break;
			}
			if(t==n){								// khong ton tai dinh t nao la dinh ke cua s
				s=nganxep.top();					// lay dinh ngan xep
				nganxep.pop();						// loai bo dinh ngan xep
				CE.push(s);	                        // day s sang mang CE
			}
		}
        
	}
	// In chu trinh Euler
	while(!CE.empty()){								// CE chua rong
		int s=CE.top();								// lay dinh ngan xep ra
		CE.pop();									// loai dinh khoi ngan xep
		cout << " " << s << " -> ";
	}
}

bool	KiemTraDoThiEuler(){
	for(int i=1; i<=n; i++){						// xet n hang tu hang 1 den hang n
		int sum=0;									// tong bac cua 1 hang
		for(int j=1; j<=n; j++){					// lay tong tat ca cac cot tren hang i = bac dinh i
			sum+=A[i][j];
		}
		if(sum%2==1) return false;					// ton tai it nhat 1 lan co dinh bac le -> do thi khong phai la Euler
	}
	return true;									// moi dinh deu la bac chan -> do thi la do thi Euler
}

void KhoiTao(){
	for(int i=1; i<=n; i++){
		chuaxet[i]=true;
		truoc[i]=0;
	}
}

int main(){
    if(DocDuLieu("matrix.txt")){
		cout << "\n Doc du lieu OK";
		KhoiTao();	
		cout << "\n Kiem tra do thi co phai la do thi Euler?";
		if(KiemTraDoThiEuler()){
			cout << "\n Do thi Euler";
			cout << "\n Chu trinh Euler:\n";
			ChuTrinhEuler(5);
		}
		else
			cout << "\n Khong phai la do thi Euler";
		
	}
	else
		cout << "\n Loi file";
	return 0;
}