// Chuong trinh C++ duyet do thi DFS de quy
#include <iostream>
#include <string>
#include <fstream>
#define MAX 100
using namespace std;
class Dothi{
		int		n;							// so dinh cua do thi;
		int 	A[MAX][MAX];				// ma tran ke cua do thi;
	public:
		string	myname="\n My graph! ";			// ten cua do thi
		int		s;							// dinh bat dau duyet
		bool	chuaxet[MAX];				// mang danh dau cac dinh da duyet hay chua duyet
		void	KhoiTao();					// khoi tao mang chuaxet voi true
		bool	DocDuLieu(string tenfile);	// ham doc do thi tu file
		void	NhapDinh();					// nhap dinh bat dau duyet
		void	DFS_dequy(int u);			// duyet de quy
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
	cout << " " << u;		// tham dinh u
	chuaxet[u]=false;		// danh dau da duyet
	for(int v=1; v<=n; v++)
		if((A[u][v]==1)&&(chuaxet[v]))
			DFS_dequy(v);
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
		cout << "\n Duyet DFS de quy:";
		G.DFS_dequy(G.s);				// duyet de quy tu dinh s cua do thi
	}
	else
		cout << "\n Loi file";
	return 0;
}
