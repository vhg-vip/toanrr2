// Chuong trinh C++ duyet do thi DFS de quy, DFS ngan xep, BFS hang doi
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#define MAX 100
using namespace std;
class Dothi{
		int		n;							// so dinh cua do thi;
		int 	A[MAX][MAX];				// ma tran ke cua do thi;
	public:
		string	myname="\n My graph! ";		// ten cua do thi
		int		s;							// dinh bat dau duyet
		bool	chuaxet[MAX];				// mang danh dau cac dinh da duyet hay chua duyet
		void	KhoiTao();					// khoi tao mang chuaxet voi true
		bool	DocDuLieu(string tenfile);	// ham doc do thi tu file
		void	NhapDinh();					// nhap dinh bat dau duyet
		void	DFS_dequy(int u);			// duyet de quy
		void	DFS_stack(int u);			// khu duyet de quy bang cach su dung ngan xep - stack
		void	BFS_queue(int u);			// duyet theo be rong - BFS tu dinh u, su dung hang doi - queue
		void	TraLoi();					// bao ten
};
// doc du lieu tu file
bool Dothi::DocDuLieu(string tenfile){
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
// khoi tao
void Dothi::KhoiTao(){
	for(int i=1; i<=n; i++)
		chuaxet[i]=true;
}
// nhap dinh bat dau duyet
void Dothi::NhapDinh(){
	cout << "\n Nhap dinh bat dau duyet: ";
	cout << "\n s = ";
	cin >> s;
}
// tim kiem DFS de quy
void Dothi::DFS_dequy(int u){
	cout << " " << u-1;		// tham dinh u
	chuaxet[u]=false;		// danh dau da duyet
	for(int v=1; v<=n; v++)
		if((A[u][v]==1)&&(chuaxet[v]==true))
			DFS_dequy(v);
}
// tim kiem DFS khong de quy, su dung ngan xep - stack
void Dothi::DFS_stack(int u){
	stack<int>	nganxep;
	nganxep.push(u);
	cout << " " << u-1;
	chuaxet[u]=false;
	while(!nganxep.empty()){
		u=nganxep.top();
		nganxep.pop();
		for(int v=1; v<=n; v++){
			if((A[u][v]==1)&&(chuaxet[v]==true)){
				cout << " " << v-1;
				chuaxet[v]=false;
				nganxep.push(u);
				nganxep.push(v);
				break;
			}
		}
	}
}
// duyet theo be rong - BFS su dung hang doi - queue
void Dothi::BFS_queue(int u){
	queue<int> hangdoi;
	hangdoi.push(u);
	chuaxet[u]=false;
	while(!hangdoi.empty()){
		u=hangdoi.front();
		hangdoi.pop();
		cout << " " << u-1;
		for(int v=1; v<=n; v++){
			if((A[u][v]==1)&&(chuaxet[v]==true)){
				hangdoi.push(v);
				chuaxet[v]=false;
			}
		}
	}
	
}
// Ham tra loi ten cua doi tuong do thi khi duoc hoi
void Dothi::TraLoi(){
	cout << myname;
}
// chuong trinh chinh
int main(){
	Dothi	G;
	G.TraLoi();
	if(G.DocDuLieu("3_1_DFS.in")){
		cout << "\n Doc du lieu OK";
		G.KhoiTao();					// khoi tao mang chuaxet voi gia tri true
		G.NhapDinh();					// nhap dinh bat dau duyet: s
		//cout << "\n Duyet DFS de quy:";
		//G.DFS_dequy(G.s);				// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet DFS dung ngan xep:";
		//G.DFS_stack(G.s);				// duyet de quy tu dinh s cua do thi
		cout << "\n Duyet BFS dung hang doi:";
		G.BFS_queue(G.s);				// duyet de quy tu dinh s cua do thi
	}
	else
		cout << "\n Loi file";
	return 0;
}
