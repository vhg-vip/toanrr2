// C3. Chuong trinh C++ duyet do thi DFS de quy, DFS ngan xep, BFS hang doi
// 		...
// C4. Chu trinh Euler, Hamilton
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
		int		X[MAX];						// luu chu trinh Hamilton (neu co)
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
		bool	DuyetTru();					// tim cac dinh tru cua do thi
		void	DuyetCau();					// tim cac canh cau cua do thi
		bool	KiemTraDoThiEuler();		// kiem tra xem do thi co phai la do thi Euler hay khong: tra ve true neu dung; false neu sai
		void	ChuTrinhEuler(int u);		// liet ke chu trinh Euler cho do thi Euler
		void	Hmt(int k);					// liet ke cac chu trinh Hamilton (neu co) cua do thi cho truoc
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
// Duyet cac canh cau cua do thi
void Dothi::DuyetCau(){
	Reset();
	for(int i=1; i<n; i++){
		for(int j=i+1; j<=n; j++){
			if(A[i][j]==1)							// canh (i, j) thuoc tap canh E hay A[i][j] = A[j][i] = 1
			{
				A[i][j] = 0;	A[j][i] = 0;
				cout << "\n Duyet DFS: ";
				DFS_dequy(1);
				if(Ktra_LienThong())
					cout << "\n Canh " << i-1 << " - " << j-1 << " khong la canh cau";
				else
					cout << "\n Canh " << i-1 << " - " << j-1 << " la canh cau";
				A[i][j] = 1;	A[j][i] = 1;
				Reset();
			}
		}
	}
}
// Duyet cac dinh tru
bool Dothi::DuyetTru(){
	Reset();										// doi chuaxet[1..n] ve true
	for(int u=1; u<=n; u++){
		chuaxet[u]=false;							// loai dinh u va cac canh noi voi no khoi qua trinh duyet DFS hoac BFS
		if(u==1){
			cout << "\n Loai dinh " << u-1 << ", duyet DFS tu dinh 1: ";
			DFS_stack(2);
		}
		else{
			cout << "\n Loai bo dinh " << u-1 << ", duyet DFS tu dinh 0: ";
			DFS_stack(1);
		}
		if(Ktra_LienThong())						// loai bo u van thu duoc do thi lien thong hay loai bo u khong lam tang thanh phan lt
			cout << "\n " << u-1 << " khong la dinh tru";
		else										// loai bo u van thu duoc do thi khong lien thong
			cout << "\n " << u-1 << " la dinh tru";
		Reset();
	}
	
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
// kiem tra xem do thi co phai la do thi Euler hay khong: tra ve true neu dung; false neu sai
bool	Dothi::KiemTraDoThiEuler(){
	for(int i=1; i<=n; i++){						// xet n hang tu hang 1 den hang n
		int sum=0;									// tong bac cua 1 hang
		for(int j=1; j<=n; j++){					// lay tong tat ca cac cot tren hang i = bac dinh i
			sum+=A[i][j];
		}
		if(sum%2==1) return false;					// ton tai it nhat 1 lan co dinh bac le -> do thi khong phai la Euler
	}
	return true;									// moi dinh deu la bac chan -> do thi la do thi Euler
}
// liet ke chu trinh Euler cho do thi Euler
void	Dothi::ChuTrinhEuler(int u){
	stack<int>	nganxep;							// khoi tao ngan xep rong
	stack<int>	CE;									// khoi tao mang CE rong
	nganxep.push(u);								// day u vao ngan xep
	while(!nganxep.empty()){						// ngan xep chua rong
		int s=nganxep.top();						// lay dinh s o dau ngan xep
		for(int t=1; t<=n; t++){					// duyet cac dinh ke cua s trong tap dinh V
			if(A[s][t]==1){							// dinh t la ke voi s
				nganxep.push(t);					// day t vao ngan xep
				A[s][t]=0;	A[t][s]=0;				// loai bo canh (s, t) khoi tap canh E
				break;
			}
			if(t==n){								// khong ton tai dinh t nao la dinh ke cua s
				s=nganxep.top();					// lay dinh ngan xep
				nganxep.pop();						// loai bo dinh ngan xep
				CE.push(s);							// day s sang mang CE
			}
		}
	}
	// In chu trinh Euler
	while(!CE.empty()){								// CE chua rong
		int s=CE.top();								// lay dinh ngan xep ra
		CE.pop();									// loai dinh khoi ngan xep
		if(!CE.empty())
			cout << " " << s << " -> ";
		else
			cout << " " << s;
	}
}
// liet ke cac chu trinh Hamilton (neu co) cua do thi cho truoc
void	Dothi::Hmt(int k){
	for(int y=1; y<=n; y++){						// xet toan bo tap dinh
		if(A[y][X[k-1]]==1){						// dinh y thuoc Ke(X[k-1]) hay (y,X[k-1]) la 1 canh
			if((k==n+1)&&(y==X[1])){				// ghi nhan chu trinh Hamilton neu trong cac dinh ke cua X[n] co v0
				cout << "\n";
				for(int j=1; j<=n; j++){			// neu khong co y==v0 thi khong chu trinh Hamilton
					cout << " " << X[j];
				}
				cout << " " << X[1];
			}
			else{
				if(chuaxet[y]==true){				// dinh y chua xet
					X[k]=y;							// thu nhan y vao chu trinh du kien
					chuaxet[y]=false;				// danh dau da xet y
					Hmt(k+1);						// lap lai qua trinh xet tu dinh y == X[k]
					chuaxet[y]=true;				// tra lai chuaxet[y]=true
				}
			}
		}
	}
}
// chuong trinh chinh
int main(){
	Dothi	G;							// G: Do thi - object
	G.TraLoi();
	//if(G.DocDuLieu("3_5_StronglyConnected.in")){
	//if(G.DocDuLieu("3_6_ArticulationPoint.in")){
	//if(G.DocDuLieu("4_1_EulerCycle.in")){
	if(G.DocDuLieu("4_2_Hamilton20_.in")){
		cout << "\n Doc du lieu OK";
		//G.KhoiTao();					// khoi tao mang chuaxet voi gia tri true
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
		//cout << "\n Kiem tra tinh lien thong manh cua do thi co huong:";
		//G.LienThongManh();			// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet cac dinh tru:";
		//G.DuyetTru();					// duyet de quy tu dinh s cua do thi
		//cout << "\n Duyet cac canh cau:";
		//G.DuyetCau();					// duyet de quy tu dinh s cua do thi
		//cout << "\n Kiem tra do thi co phai la do thi Euler?";
		//if(G.KiemTraDoThiEuler()){
		//	cout << "\n Do thi Euler";
		//	cout << "\n Chu trinh Euler:\n";
		//	G.ChuTrinhEuler(1);
		//}
		//else
		//	cout << "\n Khong phai la do thi Euler";
		cout << "\n Duyet cac cac chu trinh Hamilton:";
		G.KhoiTao();
		G.X[1]=1;						// X[1]=v0
		G.chuaxet[G.X[1]]=false;		// danh dau da xet v0
		G.Hmt(2);						// duyet de quy tu dinh X[1] hay tu v0
	}
	else
		cout << "\n Loi file";
	return 0;
}
