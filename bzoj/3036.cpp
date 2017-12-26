#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;

template<typename T>
void input(T &x) {
	x=0; T a=1;
	register char c=getchar();
	for(;c<48||c>57;c=getchar())
		if(c==45) a=-1;
	for(;c>=48&&c<=57;c=getchar())
		x=x*10+c-48;
	x*=a;
	return;
}

#define MAXN 100010
#define MAXM 200010

struct Edge {
	int u,v,w,next;
	Edge(int u=0,int v=0,int w=0,int next=0):
		u(u),v(v),w(w),next(next) {}
};

int n,m;
Edge edge[MAXM];
int head[MAXN],cnt;
int indeg[MAXN],outdeg[MAXN];

void addedge(int u,int v,int w) {
	edge[++cnt]=Edge(u,v,w,head[u]),
	head[u]=cnt,indeg[v]++,outdeg[u]++;
	return;
}

int q[MAXN],qhead=1,qtail=0;

void topo_sort() {
	for(int i=1;i<=n;i++)
		if(!indeg[i]) q[++qtail]=i;
	while(qhead<=qtail) {
		int u=q[qhead++];
		for(int i=head[u];i;i=edge[i].next)
			if(--indeg[edge[i].v]==0)
				q[++qtail]=edge[i].v;
	}
	return;
}

double f[MAXN];

int main() {
	input(n),input(m);
	for(int i=1,u,v,w;i<=m;i++) {
		input(u),input(v),input(w),
		addedge(u,v,w);
	}
	topo_sort();
	f[n]=0.00;
	for(int i=n-1,u;i>=1;i--) {
		f[u=q[i]]=0.00;
		for(int j=head[u];j;j=edge[j].next)
			f[u]+=f[edge[j].v]+edge[j].w;
		f[u]/=outdeg[u];
	}
	printf("%.2f\n",f[1]);
	return 0;
}
