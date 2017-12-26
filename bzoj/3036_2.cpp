#include<queue>
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
	edge[++cnt]=Edge(u,v,w,head[u]);
	head[u]=cnt,indeg[v]++,outdeg[u]++;
	return;
}

double f[MAXN];
queue<int> q;

int main() {
	input(n),input(m);
	for(int i=1,u,v,w;i<=m;i++) {
		input(u),input(v),input(w),
		addedge(u,v,w);
	}
	q.push(1),f[1]=1.00;
	double ans=0.00;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		for(int i=head[u],v;i;i=edge[i].next) {
			v=edge[i].v;
			f[v]+=f[u]/outdeg[u];
			ans+=edge[i].w*f[u]/outdeg[u];
			if(--indeg[v]==0) q.push(v);
		}
	}
	printf("%.2f\n",ans);
	return 0;
}
