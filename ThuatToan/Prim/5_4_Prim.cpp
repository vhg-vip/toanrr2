// C3. Chuong trinh C++ duyet do thi DFS de quy, DFS ngan xep, BFS hang doi
// 		...
// C4. Chu trinh Euler, Hamilton
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#define MAX 100
#define INF 10000
using namespace std;
struct	dinh{
	int		num, id;						// so va id cua dinh
	char	name;							// ten cua dinh
};
struct	canh{
	dinh	u, v;							// u dinh dau , v dinh cuoi: u.num<v.num
	int		c;								// trong so cua canh
};
class Dothi{
		int		n;							// so dinh cua do thi;
		int 	A[MAX][MAX];				// ma tran ke cua do thi;
		int		ne, neT;					// so canh cua do di va so canh bao trum
		canh	E[MAX], ET[MAX];			// danh sach canh cua cay va danh sach canh cua cay bao trum
	public:
		string	myname;						// ten cua do thi
		int		s, t;						// dinh bat dau duyet
		int		soTPLT;						// bien dem so thanh phan lien thong
		int		truoc[MAX];					// luu duong di
		bool	chuaxet[MAX];				// mang danh dau cac dinh da duyet hay chua duyet
		int		X[MAX];						// luu chu trinh Hamilton (neu co)
		void	TraLoi();					// bao ten
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
		void	Tree_DFS_dequy(int u);		// Xay dung cay khung cua do thi su dung thuat toan DFS de quy
		void	Edge_sort();				// Sap xep cac canh cua do thi theo trong so c tang dan
		void	Kruskal();					// Ham xay dung cay khung nho nhat cua do thi (su dung pp. Kruskal)
		void	Prim(int s);				// Ham xay dung cay bao trum theo Prim
		Dothi();							// Constructor
};
// Constructor
Dothi::Dothi(){
	myname="\n My graph! ";					// ten cua do thi
	n=0;	ne=0;	neT=0;					// khoi dung so dinh, so canh cua do thi = 0
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
				// Xay dung tap canh cho do thi vo huong
				if((A[i][j]>0)&&(j>i)){		// co canh ij
					ne++;
					//E[ne].u.num=i;	E[ne].v.num=j;	E[ne].c=A[i][j];
					E[ne].u.num=i;	E[ne].v.num=j;	E[ne].c=A[i][j];
				}
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
// Xay dung cay khung cua do thi su dung thuat toan DFS de quy
void	Dothi::Tree_DFS_dequy(int u){
	chuaxet[u]=false;
	for(int	v=1; v<=n;	v++){						// tim cac dinh v ke cua u
		if((A[u][v]>0)&&(chuaxet[v]==true)){		// v ke voi u
			//cout << "\n u=" << u << ", v=" << v;
			//if(u<v){								// thu nhan cac canh theo quy uoc dau < cuoi hay u<v
				neT++; ET[neT].u.num=u;	ET[neT].v.num=v;	ET[neT].c=A[u][v];
				cout << "\n Canh " << neT << ": " << u << ", " << v;
			//}
			Tree_DFS_dequy(v);
		}
	}
	
}
// Sap xep cac canh cua do thi theo trong so c tang dan
void	Dothi::Edge_sort(){
	cout << "\n Trong so canh truoc sap xep:";
	for(int e=1; e<=ne; e++){	cout << "  " << E[e].c;	}
	for(int e=1; e<ne; e++){						// selection sort
		canh etmp;
		for(int e1=e+1; e1<=ne; e1++){
			if(E[e1].c<E[e].c){
				etmp=E[e];	E[e]=E[e1];	E[e1]=etmp;
			}
		}
	}
	cout << "\n Trong so canh sau khi sap xep:";
	for(int e=1; e<=ne; e++){	cout << "  " << E[e].c;	}
}
// Ham xay dung cay khung nho nhat cua do thi (su dung pp. Kruskal)
void	Dothi::Kruskal(){
	int		netmp=1, mincost=0;
	dinh	V[MAX];						// Ban dau, tap n tap, moi tap la 1 dinh cua do thi
	for(int i=1; i<=n; i++){			// id cua moi dinh ban dau duoc tao = so cua dinh, khi moi dinh duoc nhap vao 1 tap
										// chi so cua dinh do se nhan id cua tap
		V[i].id=i;	V[i].num=i;
	}
	while((neT<n-1)&&(netmp<=ne)){
		canh e=E[netmp];				// canh co do dai be nhat
		if(V[e.u.num].id!=V[e.v.num].id){	// 2 dinh u, v cua canh e thuoc 2 tap khac nhau, khong tao thanh chu trinh
											// noi 2 tap lai voi nhau thong qua canh e, thu nhan canh e vao cay khung nho nhat
			// Doi chi so 1 tap ve chi so tap con lai
			for(int j=1; j<=n; j++){		// xet toan bo tap dinh
				int idtmp=V[e.v.num].id;
				if(V[j].id==idtmp){	// cu dinh V[j] nao co id trung id cua dinh v thi chi so V[j].id se nhan chi cua dinh u
					V[j].id=V[e.u.num].id;
				}
			}
			// thu nhan e vao cay khung nho nhat
			//cout << "\n cost canh " << netmp << ": " << e.c;
			mincost+=e.c;	neT++;	ET[neT]=e;	
		}
		netmp++;
	}
	// in cay khung nho nhat
	if(neT==n-1){
		cout << "\n Cay khung nho nhat theo Kruskal la:";
		for(int i=1; i<=neT; i++){
			cout << "\n Canh " << i << ": " << ET[i].u.num << ", " << ET[i].v.num;
		}
		cout << "\n Minimum cost: " << mincost;
	}
	else{
		cout << "\n Do thi khong lien thong";
	}
}
// Ham xay dung cay bao trum cua do thi (su dung thuat toan Prim)
void	Dothi::Prim(int s){
	int		dH=0;						//dH: do dai cay
	dinh	V[MAX];						//Tap dinh cua do thi
	V[s].id=s;	V[s].num=s;				//tap VH
	for(int i=1; i<=n; i++){
		if(i!=s){
			V[i].num=i;	V[i].id=n-s+1;	//tap V, id cua cac dinh = n-s+1
		}
	}
	int Vid=n-s+1;						//id cua tap V, id nay se chuyen thanh s neu V rong
	neT=0;
	while((neT<n-1)&&(Vid==n-s+1)){		//Lap khi chua du cay khung va V!=rong
		for(int i=1; i<=ne; i++){		//Tim canh nho nhat co 1 dinh thuoc V, 1 dinh thuoc VH
			if(((V[E[i].u.num].id==s)&&(V[E[i].v.num].id==Vid))||
			   ((V[E[i].u.num].id==Vid)&&(V[E[i].v.num].id==s))){
				neT++;
				ET[neT]=E[i];			//Thu nap canh i vao cay khung
				dH+=E[i].c;				//Cap nhat do dai cay khung
				if(V[E[i].v.num].id==Vid)	//Bo sung u hoac v sang tap VH
					V[E[i].v.num].id=s;	//<=> loai dinh u hoac v khoi tap V
				else
					V[E[i].u.num].id=s;
				Vid=s;					//Gia su den cho nay tap V la rong
				for(int j=1; j<=n; j++){//Kiem tra xem V thuc su rong hay ko
					if(V[j].id==n-s+1){
						Vid=n-s+1;	break;
					}
				}
				break;					// Moi lan lap while, chi thu nhan 1 canh,
			}		
		}
	}
	//Kiem tra xem do thi co lien thong hay khong
	if(neT<n-1){						// So canh cua cay khung != n-1
		cout << "\n Do thi khong lien thong";
	}
	else{								// So canh cua cay khung == n-1
		cout << "\n Cay bao trum nho nhat theo Prim dH = " << dH;
		for(int e=1; e<=neT; e++){
			cout << "\n Canh: " << ET[e].u.num << "-" << ET[e].v.num
			     << ", " << ET[e].c;
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
	//if(G.DocDuLieu("4_2_Hamilton20_.in")){
	//if(G.DocDuLieu("5_1_SpanningTree_DFS.in")){
	if(G.DocDuLieu("5_3_MSTsimple.in")){
	//if(G.DocDuLieu("5_3_MSTkiemnghiem.in")){
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
		//cout << "\n Duyet cac cac chu trinh Hamilton:";
		//G.KhoiTao();
		//G.X[1]=1;						// X[1]=v0
		//G.chuaxet[G.X[1]]=false;		// danh dau da xet v0
		//G.Hmt(2);						// duyet de quy tu dinh X[1] hay tu v0
		//cout << "\n Cay khung cua do thi su dung DFS de quy:";
		//G.KhoiTao();
		//G.Tree_DFS_dequy(13);
		G.Edge_sort();
		G.Kruskal();
		G.Prim(1);
	}
	else
		cout << "\n Loi file";
	return 0;
}
