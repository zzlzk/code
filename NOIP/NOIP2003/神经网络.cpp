#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 110
struct Edge {
	int u,v,w,next;
	Edge(int u=0,int v=0,int w=0,int next=0):
		u(u),v(v),w(w),next(next) {}
}edge[20010];
int head[maxn],cnt;
int C[maxn];
int st[maxn],top;
int indeg[maxn];
inline int input() {
	int x=0,a=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-') a=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-'0';
	return x*a;
}
inline void addedge(int u,int v,int w) {
	edge[++cnt]=Edge(u,v,w,head[u]);
	head[u]=cnt;
	return;
}
void topo() {
	while(top!=0) {
		int u=st[top--];
		if(C[u]<=0) {
			for(int i=head[u];i;i=edge[i].next) {
				int v=edge[i].v;
				indeg[v]--;
				if(indeg[v]==0) st[++top]=v;
			}
			continue;
		}
		for(int i=head[u];i;i=edge[i].next) {
			int v=edge[i].v;
			C[v]+=C[u]*edge[i].w;
			indeg[v]--;
			if(indeg[v]==0) st[++top]=v;
		}
	}
	return;
}
int main() {
	int n=input(),p=input();
	for(int i=1,U;i<=n;i++) {
		C[i]=input();
		U=input();
		if(C[i]!=0) st[++top]=i;
		else C[i]-=U;
	}
	for(int i=1;i<=p;i++) {
		int u=input(),v=input(),w=input();
		addedge(u,v,w);
		indeg[v]++;
	}
	topo();
	bool flag=false;
	for(int i=1;i<=n;i++)
		if(!head[i]&&C[i]>0) {
			printf("%d %d\n",i,C[i]);
			flag=true;
		}
	if(flag==false) printf("NULL");
	return 0;
}
