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
		string	myname;						// ten cua do thi
		int		s, t;						// dinh bat dau duyet
		int		soTPLT;						// bien dem so thanh phan lien thong
		int		truoc[MAX];					// luu duong di
		bool	chuaxet[MAX];				// mang danh dau cac dinh da duyet hay chua duyet
		void	KhoiTao();					// khoi tao mang chuaxet voi true
		void	Reset();					// tra lai gia tri ban dau cho mot so bien
		bool	DocDuLieu(string tenfile);	// ham doc do thi tu file
		void	NhapDinh();					// nhap dinh bat dau duyet
		void	DFS_dequy(int u);			// duyet de quy
		void	DFS_stack(int u);			// khu duyet de quy bang cach su dung ngan xep - stack
		void	BFS_queue(int u);			// duyet theo be rong - BFS tu dinh u, su dung hang doi - queue
		void	Duyet_TPLT();				// dem so thanh phan lien thong cua do thi
		void	InDuongDi(int s, int t);	// liet ke duong di tu s den t
		bool	Ktra_LienThong();			// kiem tra DFS(u) hoac BFS(u) = V?
		bool	LienThongManh();			// kiem tra tinh lien thong manh cua do thi
		void	TraLoi();					// bao ten
		Dothi();							// Constructor
};
// Constructor
Dothi::Dothi(){
	myname="\n My graph! ";					// ten cua do thi
}
// doc du lieu tu file
bool Dothi::DocDuLieu(string tenfile){
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
// khoi tao
void Dothi::KhoiTao(){
	for(int i=1; i<=n; i++){
		chuaxet[i]=true;
		truoc[i]=0;
	}
}
// khoi tao
void Dothi::Reset(){
	for(int i=1; i<=n; i++){
		chuaxet[i]=true;
		truoc[i]=0;
	}
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
				truoc[v]=u;
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
				truoc[v]=u;
			}
		}
	}
	
}
// ham dem so thanh phan lien thong cua do thi
void Dothi::Duyet_TPLT(){
	soTPLT=0;
	for(int u=1; u<=n; u++){
		if(chuaxet[u]==true){
			soTPLT++;
			cout << "\n Thanh phan lien thong thu " << soTPLT << ": ";
			BFS_queue(u);
		}
	}
}
// In duong di tu s den t
void Dothi::InDuongDi(int s, int t){
	int u;
	if(truoc[t]==0){
		cout << "\n Khong co duong di tu " << s << " den " << t;
	}
	else	//truoc[t] != 0
	{
		cout << "\n Duong di: " << t-1;				// dau tien dua ra dinh t
		u=truoc[t];									// u la dinh truoc khi den t
		while(u!=s){
			cout << " -> " << u-1;
			u = truoc[u];							// lan nguoc lai dinh truoc u
		}
		cout << " -> " << s-1;
	}
}
// kiem tra DFS(u) hoac BFS(u) = V?
bool	Dothi::Ktra_LienThong(){
	for(int i=1; i<=n; i++){
		if(chuaxet[i]==true)						// DFS(u) hoac BFS(u) <> V
			return false;
	}
	return true;
}
// kiem tra tinh lien thong manh cua do thi
bool	Dothi::LienThongManh(){
	Reset();
	for(int u=1; u<=n; u++){
		cout << "\n Duyet BFS tu dinh " << u-1 << " : ";
		BFS_queue(u);
		if(!Ktra_LienThong()){
			cout << "\n Do thi khong lien thong manh";
			return false;
		}
		else
			Reset();
	}
	cout << "\n Do thi lien thong manh";
	return true;									// voi tat ca cac u, lan nao BFS(u) hay DFS(u) cung bang V
}
// Ham tra loi ten cua doi tuong do thi khi duoc hoi
void Dothi::TraLoi(){
	cout << myname;
}
// chuong trinh chinh
int main(){
	Dothi	G;							// G: Do thi - object
	G.TraLoi();
	//if(G.DocDuLieu("3_5_StronglyConnected.in")){
	if(G.DocDuLieu("3_5_StronglyConnected_T.in")){
		cout << "\n Doc du lieu OK";
		G.KhoiTao();					// khoi tao mang chuaxet voi gia tri true
		//G.NhapDinh();					// nhap dinh bat dau duyet: s
		//cout << "\n Duyet DFS de quy:";
		//G.DFS_dequy(G.s);				// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet DFS dung ngan xep:";
		//G.DFS_stack(G.s);				// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet BFS dung hang doi:";
		//G.BFS_queue(G.s);				// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet dem so thanh phan lien thong:";
		//G.Duyet_TPLT();				// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet DFS:";
		//G.DFS_stack(G.s);				// duyet de quy tu dinh s cua do thi
		//G.InDuongDi(G.s, G.t);		// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet BFS:";
		//G.Reset();					// reset lai cac bien
		//G.BFS_queue(G.s);				// duyet de quy tu dinh s cua do thi
		//G.InDuongDi(G.s, G.t);		// duyet de quy tu dinh s cua do thi
		cout << "\n Kiem tra tinh lien thong manh cua do thi co huong:";
		G.LienThongManh();				// duyet de quy tu dinh s cua do thi
	}
	else
		cout << "\n Loi file";
	return 0;
}
